/*
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//        Copyright(c) 2003-2011 Intel Corporation. All Rights Reserved.
//
*/

#ifndef __UMC_VIDEO_RESIZING_H__
#define __UMC_VIDEO_RESIZING_H__

#include "vm_types.h"
#include "ippdefs.h"
#include "umc_base_codec.h"

namespace UMC
{

class VideoResizing : public BaseCodec
{
  DYNAMIC_CAST_DECL(VideoResizing, BaseCodec)
public:
  VideoResizing();

  // Set interpolation method
  virtual Status SetMethod(int lInterpolation);

  // Initialize codec with specified parameter(s)
  virtual Status Init(BaseCodecParams *) { return UMC_OK; };

  // Convert frame
  virtual Status GetFrame(MediaData *in, MediaData *out);

  // Get codec working (initialization) parameter(s)
  virtual Status GetInfo(BaseCodecParams *) { return UMC_OK; };

  // Close all codec resources
  virtual Status Close(void) { return UMC_OK; };

  // Set codec to initial state
  virtual Status Reset(void) { return UMC_OK; };

protected:
  int mInterpolation;
};

} // namespace UMC

#endif /* __UMC_VIDEO_RESIZING_H__ */
