#include "TGNetworkService.h"
#include "TGHttpParser.h"
#include "..\TGIPPCodec\TGMJPEGDecoder.h"
//---------------------------------------------------------------------
TGNetworkService::TGNetworkService(UID module_uid, PTGModule system) : TGModule(module_uid, system)
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2,2), &wsa_data);

	startTimer(1);

	TGSystem* sys = (TGSystem*)&*system;
	sys->RegisterFactoryModuleType(TGSOCKET_TYPE_UID, this);

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

void TGNetworkService::timerEvent(QTimerEvent* event)
{
	for (TGModuleMap::iterator socket = ModuleMap.begin(); socket != ModuleMap.end(); ++socket)
	{
		((TGSocket*)&*socket->second)->Poll();
	}
}
//---------------------------------------------------------------------------

PTGModule TGNetworkService::CreateModuleProc(UID type_id, UID module_id)
{
	if (type_id == TGSOCKET_TYPE_UID)
	{
		PTGModule socket = new TGSocket(module_id, System);
		//TODO: как удалить сокет после использования?
		ModuleMap[module_id] = socket;
		return socket;
	}
	
	return NULL;
}
//---------------------------------------------------------------------
