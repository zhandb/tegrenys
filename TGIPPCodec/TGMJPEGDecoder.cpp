//------------------------------------------------------------
#include "TGMJPEGDecoder.h"
#include "umc_mjpeg_video_decoder.h"
#include "umc_structures.h"
#include "membuffin.h"
#include "jpegdec.h"
#include "jpegbase.h"
#include "..\TGSystem\TGBufferPool.h"
#include "TGDataFragmentsStream.h"

//------------------------------------------------------------
TGMJPEGDecoder::TGMJPEGDecoder(UID module_uid, PTGModule system) : TGModule(module_uid, system)
{
	/*Decoder = NULL;
	Params = NULL;
	InData = NULL;
	OutData = NULL;*/

	JpegDecoder = NULL;

	DecoderBusy = false;

	BufferPool = new TGBufferPool();

	Init();
}
//------------------------------------------------------------
TGMJPEGDecoder::~TGMJPEGDecoder()
{
	DeInit();
}
//---------------------------------------------------------------------------

void TGMJPEGDecoder::Init()
{
	JpegDecoder = new CJPEGDecoder();
}
//---------------------------------------------------------------------------

void TGMJPEGDecoder::DeInit()
{
	if (JpegDecoder)
		delete JpegDecoder;

	JpegDecoder = NULL;
}
//---------------------------------------------------------------------------

void TGMJPEGDecoder::Decode(PTGBuffer in_buffer, PTGBuffer out_buffer)
{
	//GetFrameInfo((Ipp8u*) in_buffer->GetConstData(), in_buffer->GetDataSize());

	//CMemBuffInput stream;

	//stream.Open((Ipp8u*) in_buffer->GetConstData(), in_buffer->GetDataSize());

	//int bytes_read = 0;
	//DecodeField(&stream, &bytes_read);
}
//---------------------------------------------------------------------------

JERRCODE TGMJPEGDecoder::GetFrameInfo(TGDataFragmentList& data, TGFrameInfo* frame_info)
{
	//TGDataFragmentsStream in(data);

	JERRCODE jerr = JPEG_OK;

	CurrentInputBuffer = data.GatherData();
	
	UMC::ColorFormat color_format;
	
	InputStream.Open((Ipp8u*)CurrentInputBuffer->GetConstData(), CurrentInputBuffer->GetDataSize());

	jerr = JpegDecoder->SetSource(&InputStream);

	if (jerr == JPEG_OK)
	{
		jerr = JpegDecoder->ReadHeader(&frame_info->FrameWidth, &frame_info->FrameHeight, &frame_info->NChannels, &frame_info->Color, &frame_info->Sampling, &frame_info->Precision);
	}

	return jerr;
}
//---------------------------------------------------------------------------

void TGMJPEGDecoder::DecodeField(Ipp32s* size, TGFrameInfo* frame_info)
{
	Ipp32s   dstPlaneStep[4];
	Ipp8u*   pDst;
	Ipp8u*   pDstPlane[4];

	JERRCODE jerr;
	//InputStream.Seek(0, UIC_SEEK_SET);
	//jerr = JpegDecoder->SetSource(&InputStream);

	PTGBuffer out_buffer = BufferPool->Allocate();

	int FrameStep = frame_info->FrameWidth * 3 + DIB_PAD_BYTES(frame_info->FrameWidth, 3);

	out_buffer->Allocate(FrameStep * frame_info->FrameHeight);

	pDst = (Ipp8u*)out_buffer->GetConstData();

	IppiSize frame_size;
	frame_size.width = frame_info->FrameWidth;
	frame_size.height = frame_info->FrameHeight;

	JpegDecoder->SetDestination(pDst, FrameStep, frame_size, frame_info->NChannels, JC_BGR);

	jerr = JpegDecoder->ReadData();

	/*if(JPEG_ERR_BUFF == jerr)
		return UMC_ERR_NOT_ENOUGH_DATA;

	if(JPEG_OK != jerr)
		return UMC_ERR_FAILED;*/

	*size = JpegDecoder->GetNumDecodedBytes();

	int r = 0;
}
//---------------------------------------------------------------------------

void TGMJPEGDecoder::OnDataReceived(TGDataFragmentList& data)
{
	TGFrameInfo frame_info;

	if (!DecoderBusy)
	{
		CurrentFrame = data;

		GetFrameInfo(CurrentFrame, &frame_info);

		TGTextureLockStruct ls;
		ls.Width = frame_info.FrameWidth;
		ls.Height = frame_info.FrameHeight;
		ls.Data = NULL;
		ls.Pitch = 0;

		DecoderBusy = true;

		emit LockTexture(ls);
	}
}
//---------------------------------------------------------------------------

void TGMJPEGDecoder::OnTextureLocked(TGTextureLockStruct ls)
{
	int size = 0;
	Ipp32s   dstPlaneStep[4];
	Ipp8u*   pDst;
	Ipp8u*   pDstPlane[4];

	//DecodeField(&size, &frame_info);

	JERRCODE jerr;

	//PTGBuffer out_buffer = BufferPool->Allocate();

	//int FrameStep = frame_info->FrameWidth * 3 + DIB_PAD_BYTES(frame_info->FrameWidth, 3);

	int FrameStep = ls.Pitch;

	//out_buffer->Allocate(FrameStep * frame_info->FrameHeight);

	//pDst = (Ipp8u*)out_buffer->GetConstData();

	pDst = ls.Data;

	IppiSize frame_size;
	frame_size.width = ls.Width;
	frame_size.height = ls.Height;

	JpegDecoder->SetDestination(pDst, FrameStep, frame_size, 3, JC_RGBA);

	jerr = JpegDecoder->ReadData();

	/*if(JPEG_ERR_BUFF == jerr)
		return UMC_ERR_NOT_ENOUGH_DATA;

	if(JPEG_OK != jerr)
		return UMC_ERR_FAILED;*/

	size = JpegDecoder->GetNumDecodedBytes();

	emit UnlockTexture();

	DecoderBusy = false;

}