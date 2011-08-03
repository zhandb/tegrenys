/*
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2005-2011 Intel Corporation. All Rights Reserved.
//
*/

#ifndef __BASESTREAMOUT_H__
#define __BASESTREAMOUT_H__

#include "umc_defs.h"
#if defined (UMC_ENABLE_MJPEG_VIDEO_DECODER)
#include "jpegbase.h"
#include "basestream.h"


class CBaseStreamOutput : public CBaseStream
{
public:
  CBaseStreamOutput(void) {}
  ~CBaseStreamOutput(void) {}

  virtual JERRCODE Write(void* buf,uic_size_t len,uic_size_t* cnt) = 0;
};

#endif // UMC_ENABLE_MJPEG_VIDEO_DECODER
#endif // __BASESTREAMOUT_H__

