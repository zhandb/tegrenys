#ifndef TGIP9100_H
#define TGIP9100_H

#include "tgip9100_global.h"
#include "..\TGSystem\TGSystemTypes.h"
#include "..\TGSystem\TGBuffer.h"
#include "..\TGNetwork\TGHttpParser.h"
#include "..\TGSystem\TGVideoStructs.h"


class TGIP9100_EXPORT TGIP9100 : public TGModule
{
	Q_OBJECT
public:
	TGIP9100(UID module_uid, PTGModule system);
	~TGIP9100();
	virtual void Init();
	virtual void DeInit();


private:
	//PTGModule Socket;
	PTGHttpParser HttpParser;
	PTGBuffer DestinationBuffer;
signals:
	void CreateSocket();
	void SocketConnect(TGString host, uint32_t remote_port, uint32_t localport);
	void Write(PTGBuffer data);
	void SendJpegToDecoder(TGDataFragmentList& data);
	void DestinationBufferLocked(TGBufferLockStruct ls);

public slots:
	void OnSocketConnected();
	void OnDataReceived(PTGBuffer data);
	void OnContentReceived(TGString content_type, TGDataFragmentList& data);
	void OnLockDestinationBuffer(TGBufferLockStruct ls);
	void OnUnlockDestinationBuffer();

};

#endif // TGIP9100_H
