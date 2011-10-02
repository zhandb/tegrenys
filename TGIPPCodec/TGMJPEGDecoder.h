#ifndef TGMJPEGDecoder_h__
#define TGMJPEGDecoder_h__
//------------------------------------------------------------------------
#include "tgippcodec_global.h"
#include "..\TGSystem\TGBuffer.h"
#include "..\TGCodec\jpeg\jpegbase.h"
#include "..\TGNetwork\TGBaseDataParser.h"
#include "membuffin.h"
#include "..\TGSystem\TGVideoStructs.h"
#include "..\TGSystem\TGSystemTypes.h"
//------------------------------------------------------------------------

class CJPEGDecoder;
class CBaseStreamInput;

typedef unsigned char   Ipp8u;
typedef signed int     Ipp32s;

struct TGFrameInfo
{
	Ipp32s   NChannels;
	Ipp32s   Precision;
	JSS      Sampling;
	JCOLOR   Color;
	int      FrameWidth; 
	int      FrameHeight;
};


class TGIPPCODEC_EXPORT TGMJPEGDecoder : public TGModule
{
	Q_OBJECT
public:
	TGMJPEGDecoder(UID module_uid, PTGModule system);
	~TGMJPEGDecoder();
	void Decode(PTGBuffer in_buffer, PTGBuffer out_buffer);
private:
	CJPEGDecoder* JpegDecoder;
	PTGBufferPool BufferPool;
	CMemBuffInput InputStream;
	PTGBuffer CurrentInputBuffer;
	bool DecoderBusy;
	TGDataFragmentList CurrentFrame;
private:
	void Init();
	void DeInit();

	JERRCODE GetFrameInfo(TGDataFragmentList& data, TGFrameInfo* frame_info);
	void DecodeField(Ipp32s* size, TGFrameInfo* frame_info);
signals:
	void LockTexture(TGTextureLockStruct lock_struct);
	void UnlockTexture();
public slots:
	void OnDataReceived(TGDataFragmentList& data);
	void OnTextureLocked(TGTextureLockStruct ls);
};
//------------------------------------------------------------------------

#endif // TGMJPEGDecoder_h__