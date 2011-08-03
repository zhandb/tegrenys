/* ///////////////////////////////////////////////////////////////////////////// */
/*
//
//              INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license  agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in  accordance  with the terms of that agreement.
//        Copyright (c) 2003-2011 Intel Corporation. All Rights Reserved.
//
//
*/

#include "umc_defs.h"
#if defined (UMC_ENABLE_MJPEG_VIDEO_DECODER)
#include <string.h>
#include "vm_debug.h"
#include "umc_video_data.h"
#include "umc_mjpeg_video_decoder.h"
#include "membuffin.h"
#include "jpegdec.h"

// VD: max num of padding bytes at the end of AVI frame
//     should be 1 by definition (padding up to Ipp16s boundary),
//     but in reality can be bigger
#define AVI_MAX_PADDING_BYTES 4


namespace UMC {

VideoDecoder *CreateMJPEGDecoder() { return new MJPEGVideoDecoder(); }


MJPEGVideoDecoder::MJPEGVideoDecoder(void)
{
  m_IsInit      = false;
  m_firstFrame  = false;
  m_firstField  = false;
  m_interleaved = false;
  m_frameMID    = 0;
  m_frameNo     = 0;
  m_frame       = 0;
  m_frameStep   = 0;
  m_fieldStep   = 0;
  m_dec_time    = 0.0;
  m_dec         = 0;
  m_frameSampling = 0;
} // ctor


MJPEGVideoDecoder::~MJPEGVideoDecoder(void)
{
  Close();
} // dtor


Status MJPEGVideoDecoder::Init(BaseCodecParams* lpInit)
{
  UMC::Status status;

  VideoDecoderParams* pDecoderParams;

  pDecoderParams = DynamicCast<VideoDecoderParams>(lpInit);

  if(0 == pDecoderParams)
    return UMC_ERR_NULL_PTR;

  status = Close();
  if(UMC_OK != status)
    return UMC_ERR_INIT;

  status = VideoDecoder::Init(lpInit);
  if(UMC_OK != status)
    return UMC_ERR_INIT;

  m_DecoderParams  = *pDecoderParams;

  m_ClipInfo       = pDecoderParams->info;
  m_PostProcessing = pDecoderParams->pPostProcessing;

  status = m_LastDecodedFrame.ReleaseImage();
  if(UMC_OK != status)
    return status;

  m_IsInit       = true;
  m_firstFrame   = true;
  m_interleaved  = false;
  m_frameNo      = 0;
  m_frame        = 0;
  m_frameStep    = 0;
  m_fieldStep    = 0;
  m_frameSampling = 0;

  if(0 == m_dec)
  {
    m_dec = new CJPEGDecoder;
    if(0 == m_dec)
      return UMC_ERR_ALLOC;
  }

  return UMC_OK;
} // MJPEGVideoDecoder::Init()


Status MJPEGVideoDecoder::Reset(void)
{
  if(0 != m_frameMID)
  {
    m_pMemoryAllocator->Unlock(m_frameMID);
    m_pMemoryAllocator->Free(m_frameMID);
    m_frameMID = 0;
  }

  m_IsInit       = true;
  m_firstFrame   = true;
  m_frameNo      = 0;
  m_interleaved  = false;
  m_frame        = 0;
  m_frameStep    = 0;
  m_fieldStep    = 0;
  m_frameSampling = 0;

  m_dec->Reset();

  return UMC_OK;
} // MJPEGVideoDecoder::Reset()


Status MJPEGVideoDecoder::Close(void)
{
  if(0 != m_frameMID)
  {
    m_pMemoryAllocator->Unlock(m_frameMID);
    m_pMemoryAllocator->Free(m_frameMID);
    m_frameMID = 0;
  }

  m_IsInit       = false;
  m_firstFrame   = false;
  m_firstField   = false;
  m_interleaved  = false;
  m_frameNo      = 0;
  m_frame        = 0;
  m_frameStep    = 0;
  m_fieldStep    = 0;
  m_frameSampling = 0;

  if(0 != m_dec)
    delete m_dec;

  m_dec = 0;

  return VideoDecoder::Close();
} // MJPEGVideoDecoder::Close()


Status MJPEGVideoDecoder::GetFrame(MediaData* in, MediaData* out)
{
  Ipp32s     nSize;
  Ipp32s     nUsedBytes;
  Ipp8u*     pBitStream;
  Status     status;

  if(0 == in)
    return UMC_ERR_NOT_ENOUGH_DATA;

  if(0 == out)
    return UMC_ERR_NULL_PTR;

  nUsedBytes = 0;
  pBitStream = (Ipp8u*)in->GetDataPointer();
  nSize      = (Ipp32s)in->GetDataSize();

  vm_debug_trace1(VM_DEBUG_NONE, __VM_STRING("MJPEG, frame: %d\n"), m_frameNo);

  if(m_firstFrame)
  {
    m_firstFrame = false;
    m_firstField = true;

    status = _GetFrameInfo(pBitStream,nSize);
    if(UMC_OK != status)
      return status;

    if(0 == m_pMemoryAllocator)
      return UMC_ERR_ALLOC;

    status = m_pMemoryAllocator->Alloc(&m_frameMID,m_frameStep*m_frameDims.height,UMC_ALLOC_PERSISTENT,16);
    if(UMC_OK != status)
      return UMC_ERR_ALLOC;

    m_frame = (Ipp8u*)m_pMemoryAllocator->Lock(m_frameMID);
    if(0 == m_frame)
      return UMC_ERR_ALLOC;
  }

  CMemBuffInput stream;

  stream.Open(pBitStream,nSize);

  if(m_interleaved)
  {
    // interleaved frame

    // get field
    status = _DecodeField(&stream, &nUsedBytes);
    if(UMC_OK != status)
      return status;

    if(m_firstField)
    {
      // request next field
      m_firstField = !m_firstField;
      in->MoveDataPointer(nUsedBytes);
      return UMC_ERR_NOT_ENOUGH_DATA;
    }
    else
    {
      m_firstField = !m_firstField;
    }
  }
  else
  {
    // progressive frame

    status = _DecodeField(&stream, &nUsedBytes);

    if(status > 0)
    {
      Reset();
      in->MoveDataPointer(nUsedBytes);

      return UMC_OK;
    }

    if(UMC_OK != status)
      return status;
  }

  in->MoveDataPointer(nUsedBytes);

  // got complete frame
  m_frameNo++;

  m_ClipInfo.clip_info.width  = m_frameDims.width;
  m_ClipInfo.clip_info.height = m_frameDims.height;

  if (m_interleaved)
    m_ClipInfo.clip_info.height *= 2;

  if (m_LastDecodedFrame.GetColorFormat() != m_colorFormat)
  {
    m_LastDecodedFrame.Init(m_ClipInfo.clip_info.width,
                            m_ClipInfo.clip_info.height,
                            m_colorFormat);
  }

  m_LastDecodedFrame.SetFrameType(I_PICTURE);
  m_LastDecodedFrame.SetTime(in->GetTime());

  if(m_frameSampling == 3)
  {
    m_LastDecodedFrame.SetPlanePointer(m_frame, 0);
    m_LastDecodedFrame.SetPlanePointer(m_frame + m_frameDims.width, 1);
    m_LastDecodedFrame.SetPlanePointer(m_frame + m_frameDims.width + (m_frameDims.width>>1) , 2);

    m_LastDecodedFrame.SetPlanePitch(m_frameStep, 0);
    m_LastDecodedFrame.SetPlanePitch(m_frameStep, 1);
    m_LastDecodedFrame.SetPlanePitch(m_frameStep, 2);
  }
  else
  {
    m_LastDecodedFrame.SetPlanePointer(m_frame, 0);
    m_LastDecodedFrame.SetPlanePitch(m_frameStep, 0);

  }

  if (!m_PostProcessing)
  {
    m_PostProcessing = createVideoProcessing();
    m_allocatedPostProcessing = m_PostProcessing;
  }

  status = m_PostProcessing->GetFrame(&m_LastDecodedFrame, out);
  if(UMC_OK != status)
  {
    return status;
  }

  // can't calculate time for the next frame
  in->SetTime(-1.0);

  return status;
} // MJPEGVideoDecoder::GetFrame()


Status MJPEGVideoDecoder::_GetFrameInfo(Ipp8u* pBitStream, Ipp32s nSize)
{
  Ipp32s   nchannels;
  Ipp32s   precision;
  JSS      sampling;
  JCOLOR   color;
  CMemBuffInput in;
  JERRCODE jerr;

  if(0 == m_dec)
    return UMC_ERR_NOT_INITIALIZED;

  in.Open(pBitStream,nSize);

  jerr = m_dec->SetSource(&in);
  if(JPEG_OK != jerr)
    return UMC_ERR_FAILED;

  jerr = m_dec->ReadHeader(
    &m_frameDims.width,&m_frameDims.height,&nchannels,&color,&sampling,&precision);

  if(JPEG_ERR_BUFF == jerr)
    return UMC_ERR_NOT_ENOUGH_DATA;

  if(JPEG_OK != jerr)
    return UMC_ERR_FAILED;

  m_frameSampling = (int) sampling;

  if(JS_422 == sampling && JC_YCBCR == color)
  {
    m_colorFormat = YUY2;
    m_frameStep = m_frameDims.width*2;
  }
  else if (JS_411 == sampling && JC_YCBCR == color)
  {
    m_colorFormat = YUV420;
    m_frameStep = m_frameDims.width*2;
  }
  else
  {
    m_colorFormat = RGB24;
    m_frameStep = m_frameDims.width*3 + DIB_PAD_BYTES(m_frameDims.width,3);
  }

  // frame is interleaved if clip height is twice more than JPEG frame height
  if(m_frameDims.height == (m_DecoderParams.info.clip_info.height >> 1))
  {
    m_interleaved = true;
    m_frameDims.height *= 2;
  }

  return UMC_OK;
} // MJPEGVideoDecoder::_GetFrameInfo()


Status MJPEGVideoDecoder::_DecodeField(CBaseStreamInput* in, Ipp32s* cnt)
{
  Ipp32s   dstStep;
  Ipp32s   dstPlaneStep[4];
  Ipp8u*   pDst;
  Ipp8u*   pDstPlane[4];
  JCOLOR   color;
  JSS      sampling;
  JERRCODE jerr;

  if(0 == m_dec)
    return UMC_ERR_NOT_INITIALIZED;

  jerr = m_dec->SetSource(in);
  if(JPEG_OK != jerr)
    return UMC_ERR_FAILED;

  jerr = m_dec->ReadHeader(
    &m_frameDims.width, &m_frameDims.height, &m_frameChannels, &color, &sampling, &m_framePrecision);

  if(JPEG_ERR_BUFF == jerr)
    return UMC_ERR_NOT_ENOUGH_DATA;

  if(JPEG_OK != jerr)
    return UMC_ERR_FAILED;

  pDst    = m_frame;
  dstStep = m_frameStep;

  if(m_frameSampling != (int)sampling)
  {
    in->Seek(-m_dec->GetNumDecodedBytes(),UIC_SEEK_CUR);
    *cnt = 0;
    return UMC_WRN_INVALID_STREAM;
  }

  m_frameSampling = (int)sampling;

  if(m_dec->IsAVI1APP0Detected())
  {
    switch(m_dec->GetAVI1APP0Polarity())
    {
      default:
      case 0:
        pDst    = m_interleaved & !m_firstField ? m_frame + m_frameStep : m_frame;
        dstStep = m_interleaved ? m_frameStep*2 : m_frameStep;
        break;

      case 1:
        pDst    = m_firstField ? m_frame : m_frame + m_frameStep;
        dstStep = m_frameStep*2;
        break;

      case 2:
        pDst    = m_firstField ? m_frame : m_frame + m_frameStep;
        dstStep = m_frameStep*2;
        break;
    }
  }

  if(JS_422 == sampling && JC_YCBCR == color)
  {
    jerr = m_dec->SetDestination(pDst, dstStep, m_frameDims, m_frameChannels, color, sampling);
  }
  else if(JS_411 == sampling && JC_YCBCR == color)
  {
    pDstPlane[0] = pDst;
    pDstPlane[1] = pDst + m_frameDims.width;
    pDstPlane[2] = pDst + m_frameDims.width  + (m_frameDims.width >> 1);
    pDstPlane[3] = 0;

    dstPlaneStep[0] = dstStep;
    dstPlaneStep[1] = dstStep;
    dstPlaneStep[2] = dstStep;
    dstPlaneStep[3] = 0;

    jerr = m_dec->SetDestination(pDstPlane, dstPlaneStep, m_frameDims, m_frameChannels, color, sampling);
  }
  else
  {
    jerr = m_dec->SetDestination(pDst, dstStep, m_frameDims, m_frameChannels, JC_BGR);
  }

  if(JPEG_OK != jerr)
    return UMC_ERR_FAILED;

  jerr = m_dec->ReadData();

  if(JPEG_ERR_BUFF == jerr)
    return UMC_ERR_NOT_ENOUGH_DATA;

  if(JPEG_OK != jerr)
    return UMC_ERR_FAILED;

  *cnt = m_dec->GetNumDecodedBytes();

  return UMC_OK;
} // MJPEGVideoDecoder::_DecodeField()

} // end namespace UMC

#endif // UMC_ENABLE_MJPEG_VIDEO_DECODER
