#include "TGNetworkService.h"
#include "TGHttpParser.h"
#include "..\TGCodec\tgcodec.h"
//---------------------------------------------------------------------
TGNetworkService::TGNetworkService() : QThread()
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2,2), &wsa_data);

	IOCompletionPortHandle = NULL;

	Socket = new TGSocket();
	TLP = new TGHttpParser(NULL);

	//TGCodec codec;
	
	connect(Socket, SIGNAL(SocketConnected()), this, SLOT(OnSocketConnected()));
	connect(Socket, SIGNAL(SocketDisconnected()), this, SLOT(OnSocketDisconnected()));
	connect(Socket, SIGNAL(DataReceived(PTGBuffer)), this, SLOT(OnDataReceived(PTGBuffer)));
	connect(this, SIGNAL(Write(PTGBuffer)), Socket, SLOT(Write(PTGBuffer)));

	//connect(Socket, SIGNAL(DataReceived(PTGBuffer)), TLP, SLOT(OnDataReceived(PTGBuffer)));

	filecount = 1;
	
	Socket->Connect("192.168.0.33", 80, 0);

	Running = true;
	start();	
}
//---------------------------------------------------------------------
TGNetworkService::~TGNetworkService()
{
	Running = false;
	wait();
	CloseHandle(IOCompletionPortHandle);
	IOCompletionPortHandle = INVALID_HANDLE_VALUE;
}
//---------------------------------------------------------------------
void TGNetworkService::run()
{
	//IOCompletionPortHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 1);
	////SN_ASSERT(IOCompletionPortHandle);

	//DWORD bytes = 0;
	//ULONG_PTR key = NULL;
	//LPOVERLAPPED overlapped;

	//while (Running)
	//{
	//	BOOL res = GetQueuedCompletionStatus(IOCompletionPortHandle, &bytes, &key, &overlapped, 200);
	//	int last_error = 0;
	//	if (!res)
	//		last_error = GetLastError();

	//	if (res || last_error != ERROR_OPERATION_ABORTED)
	//	{
	//		int r = 0;
	//		//SNCSLocker locker(CS);

	//		//SNIntToSocketMap::iterator i = SocketMap.find(key);
	//		//if (i != SocketMap.end())
	//		//{
	//		//	PSNCommandDescriptor cmd = i->second;
	//		//	SN_ASSERT(cmd);
	//		//	cmd->ProcessCommand(DataTypes::Socket::ProcessOverlappedResult(NULL, NULL, bytes, overlapped, last_error));
	//		//}
	//	}
	//}
	while (Running)
	{
		Socket->Poll();
		Sleep(1);
	}
	
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
//---------------------------------------------------------------------
