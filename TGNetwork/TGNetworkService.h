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
//---------------------------------------------------------------------
class TGNETWORK_EXPORT TGNetworkService :  public QThread, public TGReferenceCounter
{
	Q_OBJECT
public:
	TGNetworkService();
	~TGNetworkService();
protected:
	virtual void run();	
private:
	HANDLE IOCompletionPortHandle;
	bool Running;
	PTGSocket Socket;
	PTGEndSignatureParser TLP;
	QFile file;
	int filecount;
public slots:
	void OnSocketConnected();
	void OnDataReceived(PTGBuffer data);
	void OnSocketDisconnected();
signals:
	void Write(PTGBuffer data);
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGNetworkService);
//---------------------------------------------------------------------

#endif // TGNetworkService_h__