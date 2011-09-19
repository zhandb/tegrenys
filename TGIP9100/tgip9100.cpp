#include "tgip9100.h"
#include "..\TGSystem\tgsystem.h"

TGIP9100::TGIP9100(UID module_uid, PTGModule system) : TGModule(module_uid, system)
{
	
}

TGIP9100::~TGIP9100()
{

}
//---------------------------------------------------------------------------

void TGIP9100::Init()
{
	CreateModule(UID("{04AD711B-4536-4b78-B7DC-95D85809A1FA}"), UID("{0D7FA52D-32AB-4239-A7D5-33FE28D103A9}"));
	CreateModule(UID("{0DDC8946-E848-4eb9-BF16-82A16805217D}"), UID("{53DC0858-76C1-4a2d-840F-655F78EC2030}"));

	/*NetworkService = System->GetModule(1111);
	connect(this, SIGNAL(CreateSocket()), NetworkService, SLOT(OnCreateSocket()));
	connect(NetworkService, SIGNAL(SocketCreated(UID)), this, SLOT(OnSocketCreated(UID)));
	emit CreateSocket();*/
}
//---------------------------------------------------------------------------

void TGIP9100::OnSocketCreated(UID socket_uid)
{
	/*PTGModule socket = System->GetModule(socket_uid);

	connect(this, SIGNAL(SocketConnect(TGString, uint32_t, uint32_t)), socket, SLOT(OnSocketConnect(TGString, uint32_t, uint32_t)));
	connect(socket, SIGNAL(SocketConnected()), this, SLOT(OnSocketConnected()));

	emit SocketConnect("192.168.0.33", 80, 0);*/
}
//---------------------------------------------------------------------------

void TGIP9100::OnSocketConnected()
{
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
//---------------------------------------------------------------------------

void TGIP9100::ModuleCreatedProc(UID type_id, UID module_id, PTGModule module)
{
	int r = 0;
}
//---------------------------------------------------------------------------
