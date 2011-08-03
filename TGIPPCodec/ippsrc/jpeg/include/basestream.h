/*
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2005-2011 Intel Corporation. All Rights Reserved.
//
*/

#ifndef __BASESTREAM_H__
#define __BASESTREAM_H__

#include "umc_defs.h"
#if defined (UMC_ENABLE_MJPEG_VIDEO_DECODER)
#include "jpegbase.h"


class CBaseStream
{
public:
  CBaseStream(void) {}
  virtual ~CBaseStream(void) {}

  virtual JERRCODE Open(vm_char* name) = 0;
  virtual JERRCODE Close() = 0;
};

#endif // UMC_ENABLE_MJPEG_VIDEO_DECODER
#endif // __BASESTREAM_H__

