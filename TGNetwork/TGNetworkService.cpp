#include "TGNetworkService.h"
#include "TGHttpParser.h"
#include "..\TGIPPCodec\TGMJPEGDecoder.h"
//---------------------------------------------------------------------
TGNetworkService::TGNetworkService(UID module_uid, PTGModule system) : TGModule(module_uid, system)
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2,2), &wsa_data);

	startTimer(1);

	//Socket = new TGSocket();

	//TLP = new TGHttpParser(&MJD);

	////TGCodec codec;

	///*TGMJPEGDecoder MJD;
	//QFile j("e:\\data-backup\\transit.jpg");
	//j.open(QIODevice::ReadOnly);
	//QByteArray a = j.readAll();

	//PTGBuffer in = new TGBuffer(a);
	//PTGBuffer out  = new TGBuffer();
	//out->Allocate(1000000);
	//MJD.Decode(in, out);*/

	////MJD.Decode(in, out)

	//connect(Socket, SIGNAL(SocketConnected()), this, SLOT(OnSocketConnected()));
	//connect(Socket, SIGNAL(SocketDisconnected()), this, SLOT(OnSocketDisconnected()));
	//connect(Socket, SIGNAL(DataReceived(PTGBuffer)), this, SLOT(OnDataReceived(PTGBuffer)));
	//connect(this, SIGNAL(Write(PTGBuffer)), Socket, SLOT(Write(PTGBuffer)));

	//connect(&MJD, SIGNAL(LockTexture(TGTextureLockStruct)), receiver, SLOT(OnLockTexture(TGTextureLockStruct)));
	//connect(&MJD, SIGNAL(UnlockTexture()), receiver, SLOT(OnUnlockTexture()));
	//connect(receiver, SIGNAL(TextureLocked(TGTextureLockStruct)), &MJD, SLOT(OnTextureLocked(TGTextureLockStruct)));


	////connect(Socket, SIGNAL(DataReceived(PTGBuffer)), TLP, SLOT(OnDataReceived(PTGBuffer)));

	//Socket->Connect("192.168.0.33", 80, 0);

}
//---------------------------------------------------------------------
TGNetworkService::~TGNetworkService()
{
}
//---------------------------------------------------------------------
void TGNetworkService::OnSocketConnected()
{
	/*file.setFileName(QString("c:\\test%1.html").arg(filecount));
	filecount++;
	file.open(QIODevice::WriteOnly);*/

	
}
//---------------------------------------------------------------------
void TGNetworkService::OnDataReceived(PTGBuffer data)
{
	//file.write(data->GetConstData(), data->GetDataSize());

	TLP->ReceiveData(TGDataFragmentList(0, data, data->GetDataSize()));
}
//---------------------------------------------------------------------
void TGNetworkService::OnSocketDisconnected()
{
	//file.close();
}
//---------------------------------------------------------------------------

void TGNetworkService::timerEvent(QTimerEvent* event)
{
	//Socket->Poll();
	for (TGModuleMap::iterator socket = ModuleMap.begin(); socket != ModuleMap.end(); ++socket)
	{
		((TGSocket*)&*socket->second)->Poll();
	}
}
//---------------------------------------------------------------------------

void TGNetworkService::OnCreateSocket()
{
	UID socket_uid = QUuid::createUuid();
	ModuleMap[socket_uid] = new TGSocket(socket_uid, System);
	emit SocketCreated(socket_uid);
}
//---------------------------------------------------------------------
