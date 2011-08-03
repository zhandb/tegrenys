/*
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2005-2011 Intel Corporation. All Rights Reserved.
//
*/

#ifndef __MEMBUFFIN_H__
#define __MEMBUFFIN_H__

#include "umc_defs.h"
#if defined (UMC_ENABLE_MJPEG_VIDEO_DECODER)
//#include <stdio.h>
#ifndef __BASESTREAM_H__
#include "basestream.h"
#endif
#ifndef __BASESTREAMIN_H__
#include "basestreamin.h"
#endif


class CMemBuffInput : public CBaseStreamInput
{
public:
  CMemBuffInput(void);
  ~CMemBuffInput(void);

  JERRCODE Open(Ipp8u* pBuf, int buflen);
  JERRCODE Close(void);

  JERRCODE Seek(long offset, int origin);
  JERRCODE Read(void* buf,uic_size_t len,uic_size_t* cnt);
  JERRCODE TellPos(long* pos);
  int NBytesRead(void) { return m_currpos; }

private:
  JERRCODE Open(vm_char* name) { name = name; return JPEG_NOT_IMPLEMENTED; }

protected:
  Ipp8u*  m_buf;
  int     m_buflen;
  int     m_currpos;

};

#endif // UMC_ENABLE_MJPEG_VIDEO_DECODER
#endif // __MEMBUFFIN_H__

