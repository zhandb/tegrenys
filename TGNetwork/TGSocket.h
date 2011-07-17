#ifndef TGSocket_h__
#define TGSocket_h__
//------------------------------------------------------
#include <QObject>
#include "tgnetwork_global.h"
#include <winsock2.h>

#include "windows.h"
#include <stdint.h>
#include "qdatetime.h"
#include "..\TGSystem\TGBuffer.h"
#include "..\TGSystem\TGBufferPool.h"

//------------------------------------------------------
typedef std::list<PTGBuffer> TGSocketBuffersList;
//------------------------------------------------------

class TGNETWORK_EXPORT TGSocket : public QObject, public TGReferenceCounter
{
	Q_OBJECT
public:
	TGSocket();
	~TGSocket();
	void Poll();
private:
	virtual void InitSocket();
	void CloseSocket();
	void DoConnect();
	void Bind();
	void WriteFrontBuffer();
private:
	enum TGSocketState{Waiting, StartConnect, Connecting, Connected, Disconnecting, SocketError, FatalError};
	TGSocketState State;
	QString Host;
	uint32_t Port;
	QTime ConnectTime;
	uint32_t ReconnectTime;
	//! Хэндл сокета
	SOCKET		SocketHandle;
	WSAEVENT SocketEvent;
	PTGBufferPool Pool;
	TGSocketBuffersList Buffers;
public slots:
	void Connect(QString host, uint32_t remote_port, uint32_t localport);
	void Write(PTGBuffer data);
signals:
	void SocketConnected();
	void SocketDisconnected();
	void DataReceived(PTGBuffer data);

};
//------------------------------------------------------
TG_REFC_PTR(TGSocket);
//------------------------------------------------------

#endif // TGSocket_h__