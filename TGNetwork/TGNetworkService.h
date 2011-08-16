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
//---------------------------------------------------------------------
class TGMJPEGDecoder;
//---------------------------------------------------------------------

class TGNETWORK_EXPORT TGNetworkService :  public TGModule
{
	Q_OBJECT
public:
	TGNetworkService(UID module_uid, PTGModule system);
	~TGNetworkService();

private:
	PTGSocket Socket;
	PTGEndSignatureParser TLP;
	TGMJPEGDecoder MJD;

public slots:
	void OnCreateSocket();
	void OnSocketConnected();
	void OnDataReceived(PTGBuffer data);
	void OnSocketDisconnected();
	void timerEvent(QTimerEvent* event);
signals:
	void Write(PTGBuffer data);
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGNetworkService);
//---------------------------------------------------------------------

#endif // TGNetworkService_h__