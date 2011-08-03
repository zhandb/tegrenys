/*
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2006-2011 Intel Corporation. All Rights Reserved.
//
*/

#include "umc_defs.h"
#if defined (UMC_ENABLE_MJPEG_VIDEO_DECODER)
#ifndef __JPEGBASE_H__
#include "jpegbase.h"
#endif
#ifndef __BASESTREAM_H__
#include "basestream.h"
#endif
#ifndef __BASESTREAMIN_H__
#include "basestreamin.h"
#endif
#ifndef __BITSTREAMIN_H__
#include "bitstreamin.h"
#endif




CBitStreamInput::CBitStreamInput(void)
{
  m_in         = 0;
  m_pData      = 0;
  m_DataLen    = 0;
  m_currPos    = 0;
  m_nUsedBytes = 0;
  m_eod        = 0;

  return;
} // ctor


CBitStreamInput::~CBitStreamInput(void)
{
  Detach();
  return;
} // dtor


JERRCODE CBitStreamInput::Attach(CBaseStreamInput* in)
{
  Detach();

  m_in = in;

  return JPEG_OK;
} // CBitStreamInput::Attach()


JERRCODE CBitStreamInput::Detach(void)
{
  if(0 != m_pData)
  {
    // deallocate internal memory
    ippFree(m_pData);
    m_pData = 0;
  }

  m_in         = 0;
  m_pData      = 0;
  m_DataLen    = 0;
  m_currPos    = 0;
  m_nUsedBytes = 0;
  m_eod        = 0;

  return JPEG_OK;
} // CBitStreamInput::Detach()


JERRCODE CBitStreamInput::Init(int bufSize)
{
  m_DataLen = (int)bufSize;

  if(0 != m_pData)
  {
    ippFree(m_pData);
    m_pData = 0;
  }

  m_pData = (Ipp8u*)ippMalloc(m_DataLen);
  if(0 == m_pData)
  {
    return JPEG_ERR_ALLOC;
  }

  m_currPos    = m_DataLen; // no data yet
  m_nUsedBytes = 0;

  return JPEG_OK;
} // CBitStreamInput::Init()


JERRCODE CBitStreamInput::FillBuffer(int nMinBytes)
{
  int remainder;
  uic_size_t cnt;

  remainder = m_DataLen - m_currPos;

  if(nMinBytes)
  {
    if(remainder >= nMinBytes)
      return JPEG_OK;
  }

  if(remainder && !m_eod)
  {
    ippsMove_8u(&m_pData[m_currPos],m_pData,remainder);
    m_currPos = 0;
  }

  if(!m_eod)
  {
    m_in->Read(m_pData + remainder,m_DataLen - remainder,&cnt);
    if((int)cnt != m_DataLen - remainder)
      m_eod = 1;

    m_currPos = 0;
    m_DataLen = remainder + cnt;
  }
  else
  {
    m_eod = 1;
  }

  if(m_eod && m_currPos >= m_DataLen)
  {
    return JPEG_ERR_BUFF;
  }

  return JPEG_OK;
} // CBitStreamInput::FillBuffer()


JERRCODE CBitStreamInput::Seek(long offset, int origin)
{
  int      _offset;
  JERRCODE jerr;

  switch(origin)
  {
  case UIC_SEEK_CUR:
    {
      _offset = m_currPos + offset;
      if(_offset > 0 && _offset < m_DataLen)
      {
        m_currPos     = _offset;
        m_nUsedBytes += offset;
      }
      else
      {
        m_currPos = m_DataLen;
        m_nUsedBytes += (_offset - m_DataLen);

        jerr = m_in->Seek(_offset - m_DataLen,UIC_SEEK_CUR);
        if(JPEG_OK != jerr)
          return jerr;

        jerr = FillBuffer();
        if(JPEG_OK != jerr)
          return jerr;
      }
      break;
    }

  case UIC_SEEK_SET:
  case UIC_SEEK_END:
  default:
    return JPEG_NOT_IMPLEMENTED;
  }

  return JPEG_OK;
} // CBitStreamInput::Seek()


JERRCODE CBitStreamInput::CheckByte(int pos, int* byte)
{
  JERRCODE jerr;

  if(m_currPos + pos >= m_DataLen)
  {
    jerr = Seek(pos);
    if(JPEG_OK != jerr)
      return jerr;

    *byte = m_pData[0];
  }
  else
  *byte = m_pData[m_currPos + pos];

  return JPEG_OK;
} // CBitStreamInput::CheckByte()


JERRCODE CBitStreamInput::ReadByte(int* byte)
{
  JERRCODE jerr;

  if(m_currPos >= m_DataLen)
  {
    jerr = FillBuffer();
    if(JPEG_OK != jerr)
      return jerr;
  }

  *byte = m_pData[m_currPos];
  m_currPos++;
  m_nUsedBytes++;

  return JPEG_OK;
} // CBitStreamInput::ReadByte()


JERRCODE CBitStreamInput::ReadWord(int* word)
{
  int byte0;
  int byte1;
  JERRCODE jerr;

  jerr = ReadByte(&byte0);
  if(JPEG_OK != jerr)
    return jerr;

  jerr = ReadByte(&byte1);
  if(JPEG_OK != jerr)
    return jerr;

  *word = (byte0 << 8) | byte1;

  return JPEG_OK;
} // CBitStreamInput::ReadWord()


JERRCODE CBitStreamInput::ReadDword(int* dword)
{
  int word0;
  int word1;
  JERRCODE jerr;

  jerr = ReadWord(&word0);
  if(JPEG_OK != jerr)
    return jerr;

  jerr = ReadWord(&word1);
  if(JPEG_OK != jerr)
    return jerr;

  *dword = (word0 << 16) | word1;

  return JPEG_OK;
} // CBitStreamInput::ReadDword()

#endif // UMC_ENABLE_MJPEG_VIDEO_DECODER
