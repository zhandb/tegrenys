#ifndef TGNetworkService_h__
#define TGNetworkService_h__
//---------------------------------------------------------------------
#include <QThread>
#include <winsock2.h>
#include <windows.h>
#include "tgnetwork_global.h"
#include "TGSocket.h"
#include <QFile>
#include "TGEndSignatureParser.h"
#include "..\TGIPPCodec\TGMJPEGDecoder.h"
#include "..\TGSystem\TGSystemTypes.h"
#include "..\TGSystem\tgsystem.h"
//---------------------------------------------------------------------
class TGMJPEGDecoder;
//---------------------------------------------------------------------
#define TGSOCKET_TYPE_UID UID("{04AD711B-4536-4b78-B7DC-95D85809A1FA}")
#define TGHTTP_PARSER_TYPE_UID UID("{9E46B2FF-F5B6-4f0d-BCEC-DF1FBCEAD8F9}")
//---------------------------------------------------------------------

class TGNETWORK_EXPORT TGNetworkService :  public TGModule
{
	Q_OBJECT
public:
	TGNetworkService(UID module_uid, PTGModule system);
	~TGNetworkService();

private:
	//PTGSocket Socket;
	PTGEndSignatureParser TLP;
	//TGMJPEGDecoder MJD;
protected:
	virtual PTGModule CreateModuleProc(UID type_id, UID module_id);
public slots:
	void OnCreateSocket();
	void OnSocketConnected();
	void OnDataReceived(PTGBuffer data);
	void OnSocketDisconnected();
	void timerEvent(QTimerEvent* event);
	//virtual void OnCreateModuleSlot(PTGModule caller, UID type_id, UID module_id);
	
signals:
	void Write(PTGBuffer data);
	void SocketCreated(UID socket_uid);
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGNetworkService);
//---------------------------------------------------------------------

#endif // TGNetworkService_h__