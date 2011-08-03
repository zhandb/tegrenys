//---------------------------------------------------------------------
#include "TGLibAvcodec.h"
#include <windows.h>
#include <QFile>
//---------------------------------------------------------------------
TGLibAvcodec::TGLibAvcodec()
{
	av_register_all();
	Context = NULL;
	StreamIndex = -1;
}
//---------------------------------------------------------------------
TGLibAvcodec::~TGLibAvcodec()
{

}
//---------------------------------------------------------------------
void TGLibAvcodec::OpenFile(QString filename)
{
	Packet.data = NULL;

	int err = av_open_input_file(&Context, filename.toLocal8Bit().constData(), NULL, 0, NULL);
	if (err >= 0)
	{
		err = av_find_stream_info(Context);
		if (err >= 0)
		{
			for (int i = 0; i < Context->nb_streams; ++i) 
			{
				AVCodecContext* codec_context = Context->streams[i]->codec;

				if (codec_context->codec_type == CODEC_TYPE_VIDEO) 
				{
					AVCodec* codec = avcodec_find_decoder(codec_context->codec_id);

					if (codec)
					{
						err = avcodec_open(codec_context, codec);
						if (err >= 0)
						{
							VideoStream = Context->streams[i];
							Frame = avcodec_alloc_frame();
							int frame_size = avpicture_get_size(codec_context->pix_fmt, codec_context->width, codec_context->height);
							uint8_t* frame_buffer = new uint8_t[frame_size];
							avpicture_fill((AVPicture*)Frame, frame_buffer,
								codec_context->pix_fmt, codec_context->width, codec_context->height);
							StreamIndex = i;
							break;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------
void TGLibAvcodec::ReadFrame()
{
	// free last packet if exist
	if (Packet.data != NULL) 
	{
		av_free_packet (&Packet);
	}

	// get the next frame
	while (av_read_frame(Context, &Packet) >= 0) 
	{
		if(Packet.stream_index != StreamIndex) 
		{
			av_free_packet (&Packet);
			continue;
		}
		else
			break;
	}

	int got_picture;
	avcodec_decode_video(VideoStream->codec, Frame, &got_picture, Packet.data, Packet.size);

	if (got_picture) 
	{
		img_convert_ctx = sws_getContext
			(
			VideoStream->codec->width,
			VideoStream->codec->height,
			VideoStream->codec->pix_fmt,
			VideoStream->codec->width,
			VideoStream->codec->height,
			PIX_FMT_RGB24,
			SWS_BICUBIC,
			NULL, NULL, NULL
			);

		AVFrame* rgb;
		//rgb = *Frame;

		rgb = avcodec_alloc_frame();
		int frame_size = avpicture_get_size(PIX_FMT_BGR24, VideoStream->codec->width, VideoStream->codec->height);
		uint8_t* frame_buffer = new uint8_t[frame_size];
		avpicture_fill((AVPicture*)rgb, frame_buffer,
			PIX_FMT_BGR24, VideoStream->codec->width, VideoStream->codec->height);
		
		int s = sws_scale
			(
			img_convert_ctx, 
			Frame->data,
			Frame->linesize, 0,
			VideoStream->codec->height / 2,
			rgb->data, 
			rgb->linesize
			);
		sws_freeContext(img_convert_ctx); 

		delete [] frame_buffer;
	}
}
//---------------------------------------------------------------------
void TGLibAvcodec::OpenStream(QByteArray stream)
{
	ByteIOContext bio;
	QByteArray ba;

	QFile file("c:\\3faces.jpg");
	file.open(QIODevice::ReadOnly);
	ba = file.readAll();
	
	int e1 = init_put_byte(&bio, (uchar*)ba.constData(), ba.size(), 1, this, NULL, NULL, NULL);

	AVInputFormat* fmt = NULL;

	av_probe_input_buffer(&bio, &fmt, "", 0, 0, ba.size());
	uchar b[4096 + AVPROBE_PADDING_SIZE];
	memset(b, 0, sizeof(b));
	memcpy(b, ba.constData(), 4096);
	AVProbeData probe_data;
	probe_data.filename = "555";
	probe_data.buf_size =  4096; // av_open_input_file tries this many times with progressively larger buffers each time, but this must be enough
	probe_data.buf = (uchar*)malloc(4096);
	memcpy(probe_data.buf, ba.constData(), 4096);

	int score;
	AVInputFormat *ret = av_probe_input_format(&probe_data, 1);
	// cleanup
	//free(probe_data.buf);
	//probe_data.buf = NULL;
	//return ret;

	//av_open_input_stream(&Context, &bio, "555", NULL, NULL);



}