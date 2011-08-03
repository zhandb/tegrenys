#include "tgcodec.h"
#include <windows.h>
#include "TGLibAvcodec.h"

#define UMC_ENABLE_MJPEG_VIDEO_DECODER

#include "jpeg\umc_mjpeg_video_decoder.h"

TGCodec::TGCodec()
{
	Codec = new TGLibAvcodec();
	//Codec->OpenFile("g:\\A Christmas Carol 3D Half-SBS.mkv");

	UMC::MJPEGVideoDecoder* decoder = new UMC::MJPEGVideoDecoder();

	UMC::VideoDecoderParams VDecParams;

	VDecParams.info.stream_type = rVideoInfo.stream_type;
	VDecParams.info.stream_subtype = rVideoInfo.stream_subtype;
	if (pDecSpecInfo && pDecSpecInfo->GetDataSize()) {
		VDecParams.m_pData = pDecSpecInfo;
	}

	if (UMC_OK == umcRes) {
		VideoProcessingParams postProcessingParams;
		postProcessingParams.m_DeinterlacingMethod = (DeinterlacingMethod)lDeinterlacing;
		postProcessingParams.InterpolationMethod = lInterpolation;
		rColorConverter.SetParams(&postProcessingParams);

		VDecParams.info                 = rVideoInfo;
		VDecParams.lFlags               = ulVideoDecoderFlags;//FLAG_VDEC_CONVERT | FLAG_VDEC_REORDER;
		VDecParams.numThreads           = numThreads;
		VDecParams.pPostProcessing      = &rColorConverter;

	UMC::Status s =decoder->Init(&bcp);

	Codec->OpenStream("c:\\3faces.jpg");

	//Codec->OpenFile("j:\\mammamia.avi");
	while (true)
	{
		Codec->ReadFrame();
	}
}

TGCodec::~TGCodec()
{
	delete Codec;
}
