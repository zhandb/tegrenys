#include "tgip9100.h"
#include "..\TGSystem\tgsystem.h"

TGIP9100::TGIP9100(UID module_uid, PTGModule system) : TGModule(module_uid, system)
{
	HttpParser = new TGHttpParser(this);
}

TGIP9100::~TGIP9100()
{

}
//---------------------------------------------------------------------------

void TGIP9100::Init()
{
	//Socket
	CreateModule(UID("{04AD711B-4536-4b78-B7DC-95D85809A1FA}"));
	//MJpeg decoder
	CreateModule(UID("{0DDC8946-E848-4eb9-BF16-82A16805217D}"));
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

	buffer->Allocate(strlen(reqtemplate));
	memcpy((void*)buffer->GetConstData(), reqtemplate, strlen(reqtemplate));
	emit Write(buffer);
}
//---------------------------------------------------------------------------

void TGIP9100::ModuleCreatedProc(UID type_id, UID module_id, PTGModule module)
{
	if (type_id == UID("{04AD711B-4536-4b78-B7DC-95D85809A1FA}"))
	{
		Socket = module;
		connect(this, SIGNAL(SocketConnect(TGString, uint32_t, uint32_t)), Socket, SLOT(OnSocketConnect(TGString, uint32_t, uint32_t)));
		connect(Socket, SIGNAL(SocketConnected()), this, SLOT(OnSocketConnected()));
		connect(this, SIGNAL(Write(PTGBuffer)), Socket, SLOT(Write(PTGBuffer)));
		connect(Socket, SIGNAL(DataReceived(PTGBuffer)), this, SLOT(OnDataReceived(PTGBuffer)));

		emit SocketConnect("ya.ru", 80, 0);
	}
}
//-------------------------------------------------------------------

void TGIP9100::OnDataReceived(PTGBuffer data)
{
	HttpParser->ReceiveData(TGDataFragmentList(0, data, data->GetDataSize()));
}
//---------------------------------------------------------------------------
