/*
//
//              INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license  agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in  accordance  with the terms of that agreement.
//    Copyright (c) 2003-2011 Intel Corporation. All Rights Reserved.
//
//
*/

#include "umc_video_resizing.h"
#include "umc_video_data.h"
#include "ippi.h"

using namespace UMC;

namespace UMC
{
    BaseCodec *CreateVideoResizing() { return (new VideoResizing()); }
}

VideoResizing::VideoResizing()
{
  mInterpolation = IPPI_INTER_NN;
}

Status VideoResizing::SetMethod(int lInterpolation)
{
  mInterpolation = lInterpolation;
  return UMC_OK;
}

Status VideoResizing::GetFrame(MediaData *input, MediaData *output)
{
  VideoData *in = DynamicCast<VideoData>(input);
  VideoData *out = DynamicCast<VideoData>(output);
  VideoData::PlaneInfo srcPlane;
  VideoData::PlaneInfo dstPlane;
  UMC::eUMC_Status sts = UMC_OK;;
  int k;

  if (NULL == in || NULL == out) {
    return UMC_ERR_NULL_PTR;
  }

  ColorFormat cFormat = in->GetColorFormat();
  if (out->GetColorFormat() != cFormat) {
    return UMC_ERR_INVALID_PARAMS;
  }
  Ipp32s in_Width = in->GetWidth();
  Ipp32s in_Height = in->GetHeight();
  Ipp32s out_Width = out->GetWidth();
  Ipp32s out_Height = out->GetHeight();

  Ipp64f xRatio = static_cast<Ipp64f> (out_Width)  / static_cast<Ipp64f> (in_Width);
  Ipp64f yRatio = static_cast<Ipp64f> (out_Height) / static_cast<Ipp64f> (in_Height);

  Ipp8u* pBuffer;
  int    bufferSize;

  for (k = 0; k < in->GetNumPlanes(); k++) {
    in->GetPlaneInfo(&srcPlane, k);
    out->GetPlaneInfo(&dstPlane, k);

    UMC_CHECK(srcPlane.m_iSampleSize == dstPlane.m_iSampleSize, UMC_ERR_INVALID_PARAMS);
    UMC_CHECK(srcPlane.m_iSamples == dstPlane.m_iSamples, UMC_ERR_INVALID_PARAMS);

    IppiRect RectSrc = {0, 0, srcPlane.m_ippSize.width, srcPlane.m_ippSize.height};
    IppiRect RectDst;

    if (cFormat == YUY2) {
      // YUY2 format defined in VideoData with WidthDiv = 2
      srcPlane.m_ippSize.width *= 2;
      dstPlane.m_ippSize.width *= 2;
      RectSrc.width *= 2;
      ippiResizeYUV422_8u_C2R((const Ipp8u *)srcPlane.m_pPlane,
        srcPlane.m_ippSize,
        (int)srcPlane.m_nPitch,
        RectSrc,
        (Ipp8u *)dstPlane.m_pPlane,
        (int)dstPlane.m_nPitch,
        dstPlane.m_ippSize,
        xRatio,
        yRatio,
        mInterpolation);
      return UMC_OK;
    }

    ippiGetResizeRect(RectSrc, &RectDst, xRatio, yRatio, 0, 0, mInterpolation);

    if(ippStsNoErr != ippiResizeGetBufSize(RectSrc, RectDst, srcPlane.m_iSamples, mInterpolation, &bufferSize))
      return UMC_ERR_UNSUPPORTED;

    pBuffer = (Ipp8u*)ippMalloc(bufferSize);
    if(bufferSize <= 0)
      return UMC_ERR_NULL_PTR;

    if (srcPlane.m_iSampleSize == sizeof(Ipp8u)) {
      switch (srcPlane.m_iSamples) {
      case 1:
        ippiResizeSqrPixel_8u_C1R((const Ipp8u *)srcPlane.m_pPlane,
                          srcPlane.m_ippSize,
                          (int)srcPlane.m_nPitch,
                          RectSrc,
                          (Ipp8u *)dstPlane.m_pPlane,
                          (int)dstPlane.m_nPitch,
                          RectDst,
                          xRatio,
                          yRatio,
                          0,
                          0,
                          mInterpolation,
                          pBuffer);
        break;
      case 3:
        ippiResizeSqrPixel_8u_C3R((const Ipp8u *)srcPlane.m_pPlane,
                          srcPlane.m_ippSize,
                          (int)srcPlane.m_nPitch,
                          RectSrc,
                          (Ipp8u *)dstPlane.m_pPlane,
                          (int)dstPlane.m_nPitch,
                          RectDst,
                          xRatio,
                          yRatio,
                          0,
                          0,
                          mInterpolation,
                          pBuffer);
        break;
      case 4:
        ippiResizeSqrPixel_8u_C4R((const Ipp8u *)srcPlane.m_pPlane,
                          srcPlane.m_ippSize,
                          (int)srcPlane.m_nPitch,
                          RectSrc,
                          (Ipp8u *)dstPlane.m_pPlane,
                          (int)dstPlane.m_nPitch,
                          RectDst,
                          xRatio,
                          yRatio,
                          0,
                          0,
                          mInterpolation,
                          pBuffer);
        break;
      default:
        sts = UMC_ERR_UNSUPPORTED;
      }
    } else if (srcPlane.m_iSampleSize == sizeof(Ipp16u)) {
      switch (srcPlane.m_iSamples) {
      case 1:
        ippiResizeSqrPixel_16u_C1R((const Ipp16u *)srcPlane.m_pPlane,
                           srcPlane.m_ippSize,
                           (int)srcPlane.m_nPitch,
                           RectSrc,
                           (Ipp16u *)dstPlane.m_pPlane,
                           (int)dstPlane.m_nPitch,
                           RectDst,
                           xRatio,
                           yRatio,
                           0,
                           0,
                           mInterpolation,
                           pBuffer);
        break;
      case 3:
        ippiResizeSqrPixel_16u_C3R((const Ipp16u *)srcPlane.m_pPlane,
                           srcPlane.m_ippSize,
                           (int)srcPlane.m_nPitch,
                           RectSrc,
                           (Ipp16u *)dstPlane.m_pPlane,
                           (int)dstPlane.m_nPitch,
                           RectDst,
                           xRatio,
                           yRatio,
                           0,
                           0,
                           mInterpolation,
                           pBuffer);
        break;
      case 4:
        ippiResizeSqrPixel_16u_C4R((const Ipp16u *)srcPlane.m_pPlane,
                           srcPlane.m_ippSize,
                           (int)srcPlane.m_nPitch,
                           RectSrc,
                           (Ipp16u *)dstPlane.m_pPlane,
                           (int)dstPlane.m_nPitch,
                           RectDst,
                           xRatio,
                           yRatio,
                           0,
                           0,
                           mInterpolation,
                           pBuffer);
        break;
      default:
        sts = UMC_ERR_UNSUPPORTED;
      }
    } else {
      sts = UMC_ERR_UNSUPPORTED;
    }
    if(bufferSize > 0)
      ippFree(pBuffer);

    if(sts != UMC_OK)
      return sts;
  }
  return UMC_OK;
}
