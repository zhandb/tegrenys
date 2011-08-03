/* ////////////////////////////////////////////////////////////////////////// */
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

#ifndef __UMC_MJPEG_VIDEO_DECODER_H
#define __UMC_MJPEG_VIDEO_DECODER_H

#include "umc_defs.h"
#if defined (UMC_ENABLE_MJPEG_VIDEO_DECODER)
#include "ippdefs.h"
#include "ippcore.h"
#include "ipps.h"
#include "ippi.h"
#include "ippcc.h"
#include "ippj.h"
#include "umc_structures.h"
#include "umc_video_decoder.h"

// internal JPEG decoder object forward declaration
class CBaseStreamInput;
class CJPEGDecoder;

namespace UMC
{

class MJPEGVideoDecoder : public VideoDecoder
{
public:
    // Default constructor
    MJPEGVideoDecoder(void);

    // Destructor
    virtual ~MJPEGVideoDecoder(void);

    // Initialize for subsequent frame decoding.
    virtual Status Init(BaseCodecParams* init);

    // Reset decoder to initial state
    virtual Status Reset(void);

    // Close decoding & free all allocated resources
    virtual Status Close(void);

    // Get next frame
    virtual Status GetFrame(MediaData* in, MediaData* out);

    // reset skip frame counter
    Status  ResetSkipCount(void)       { return UMC_ERR_NOT_IMPLEMENTED; }

    // increment skip frame counter
    Status  SkipVideoFrame(Ipp32s)     { return UMC_ERR_NOT_IMPLEMENTED; }

    // get skip frame counter statistic
    Ipp32u GetNumOfSkippedFrames(void) { return 0; }

protected:

    Status _GetFrameInfo(Ipp8u* pBitStream, Ipp32s nSize);

    Status _DecodeField(CBaseStreamInput* in, Ipp32s* nUsedBytes);

    bool                    m_IsInit;
    bool                    m_firstFrame;
    bool                    m_firstField;
    bool                    m_interleaved;
    VideoDecoderParams      m_DecoderParams;
    ColorFormat             m_colorFormat;
    Ipp32s                  m_frameNo;
    MemID                   m_frameMID;
    Ipp8u*                  m_frame;
    IppiSize                m_frameDims;
    Ipp32s                  m_frameStep;
    Ipp32s                  m_frameChannels;
    Ipp32s                  m_framePrecision;
    ColorFormat             m_frameColor;
    Ipp32s                  m_fieldStep;
    Ipp64f                  m_dec_time;
    CJPEGDecoder*           m_dec;
    int                     m_frameSampling;
};

} // end namespace UMC

#endif // UMC_ENABLE_MJPEG_VIDEO_DECODER
#endif //__UMC_MJPEG_VIDEO_DECODER_H
