#ifndef TGIP9100_H
#define TGIP9100_H

#include "tgip9100_global.h"
#include "..\TGSystem\TGSystemTypes.h"
#include "..\TGSystem\TGBuffer.h"
#include "..\TGNetwork\TGHttpParser.h"
#include "..\TGSystem\TGVideoStructs.h"
#include <QtPlugin>
#include "..\TGSystem\tgsystem.h"

#define TG_IP9100_TYPE_UID "{42DC5E02-1D9D-48c3-A38E-8CE965E5CEC2}"

class TGIP9100_EXPORT TGIP9100 : public TGModule
{
	Q_OBJECT
public:
	TGIP9100(UID module_uid, PTGSystem system);
	~TGIP9100();
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
	void LockDestinationBuffer(TGBufferLockStruct ls);
	void UnlockDestinationBuffer();
public slots:
	void OnSocketConnected();
	void OnDataReceived(PTGBuffer data);
	void OnContentReceived(TGString content_type, TGDataFragmentList& data);
	void OnLockDestinationBuffer(TGBufferLockStruct ls);
	void OnUnlockDestinationBuffer();
	void OnDestinationBufferLocked(TGBufferLockStruct ls);
	virtual void Init();

};

class TGIP9100_EXPORT TGIP9100Factory : public TGModule, public TGModuleFactory
{
	Q_OBJECT
	Q_INTERFACES(TGModuleFactory)
public:
	TGIP9100Factory();
	~TGIP9100Factory();
	virtual void RegisterModuleTypes(PTGSystem system);
	virtual PTGModule CreateModuleProc(UID type_id, UID module_id);
};

 
#endif // TGIP9100_H
