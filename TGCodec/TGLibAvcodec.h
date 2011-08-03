#ifndef TGLibAvcodec_h__
#define TGLibAvcodec_h__

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

#include <QString>

extern "C" 
{
#include "avcodec.h"
#include "avformat.h"
#include "swscale.h"
}

class TGLibAvcodec
{
public:
	TGLibAvcodec();
	~TGLibAvcodec();
	void OpenFile(QString filename);
	void OpenStream(QByteArray stream);
	void ReadFrame();
private:
	AVStream* VideoStream;
	AVFormatContext* Context; 
	AVFrame* Frame;
	AVPacket Packet;
	int StreamIndex;
	struct SwsContext* img_convert_ctx; 
};
#endif // TGLibAvcodec_h__