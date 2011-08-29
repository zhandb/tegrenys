#include "TGNetworkService.h"
#include "TGHttpParser.h"
#include "..\TGCodec\tgcodec.h"
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

	PTGBuffer buffer = new TGBuffer();

	char* reqtemplate = 
			"GET /GetData.cgi HTTP/1.1\r\n" \
			"Accept: text/*\r\n" \
			"Catch-Control: no-cache\r\n" \
			"\r\n";

	char* x = "GET / HTTP/1.1\r\nAccept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, image/pjpeg, application/x-ms-xbap, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*\r\nAccept-Language: ru-RU\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; .NET4.0C; .NET4.0E)\r\nAccept-Encoding: gzip, deflate\r\nHost: ya.ru\r\nConnection: Keep-Alive\r\nCookie: yandex_gid=39\r\n\r\n";
	buffer->Allocate(strlen(reqtemplate));
	memcpy((void*)buffer->GetConstData(), reqtemplate, strlen(reqtemplate));
	emit Write(buffer);
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
	UID socket_uid = qrand();
	ModuleMap[socket_uid] = new TGSocket(socket_uid, System);
	emit SocketCreated(socket_uid);
}
//---------------------------------------------------------------------
