#include "tgip9100.h"
#include "..\TGSystem\tgsystem.h"
#include "..\TGGui\TGGuiTypes.h"

#pragma comment(lib, "tgsystem.lib")
#pragma comment(lib, "tgnetwork.lib")

TGIP9100::TGIP9100(UID module_uid, PTGSystem system) : TGModule(module_uid, system)
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
	PTGModule socket = CreateModule(UID("{04AD711B-4536-4b78-B7DC-95D85809A1FA}"));

	connect(this, SIGNAL(SocketConnect(TGString, uint32_t, uint32_t)), socket, SLOT(OnSocketConnect(TGString, uint32_t, uint32_t)));
	connect(socket, SIGNAL(SocketConnected()), this, SLOT(OnSocketConnected()));
	connect(this, SIGNAL(Write(PTGBuffer)), socket, SLOT(Write(PTGBuffer)));
	connect(socket, SIGNAL(DataReceived(PTGBuffer)), this, SLOT(OnDataReceived(PTGBuffer)));

	emit SocketConnect("192.168.0.33", 80, 0);

	//MJpeg decoder
	PTGModule decoder = CreateModule(UID("{0DDC8946-E848-4eb9-BF16-82A16805217D}"));

	connect(this, SIGNAL(SendJpegToDecoder(TGDataFragmentList&)), decoder, SLOT(OnDataReceived(TGDataFragmentList&)));
	connect(decoder, SIGNAL(LockDestinationBuffer(TGBufferLockStruct)), this, SLOT(OnLockDestinationBuffer(TGBufferLockStruct)));
	connect(this, SIGNAL(DestinationBufferLocked(TGBufferLockStruct)), decoder, SLOT(OnDestinationBufferLocked(TGBufferLockStruct)));
	connect(decoder, SIGNAL(UnlockDestinationBuffer()), this, SLOT(OnUnlockDestinationBuffer()));

	//Video widget
	//CreateModule(TGVIDEOWIDGET_TYPE_UID);
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

void TGIP9100::OnDataReceived(PTGBuffer data)
{
	HttpParser->ReceiveData(TGDataFragmentList(0, data, data->GetDataSize()));
}
//---------------------------------------------------------------------------

void TGIP9100::OnContentReceived(TGString content_type, TGDataFragmentList& data)
{
	emit SendJpegToDecoder(data);
}
//---------------------------------------------------------------------------

void TGIP9100::OnLockDestinationBuffer(TGBufferLockStruct ls)
{
	/*DestinationBuffer = new TGBuffer();
	DestinationBuffer->Allocate(ls.Width * ls.Height * 4);

	ls.Data = (UCHAR*)DestinationBuffer->GetConstData();
	ls.Pitch = ls.Width * 4;
	emit DestinationBufferLocked(ls);*/

	emit LockDestinationBuffer(ls);
}
//---------------------------------------------------------------------------

void TGIP9100::OnUnlockDestinationBuffer()
{
	emit UnlockDestinationBuffer();
}
//---------------------------------------------------------------------------

void TGIP9100::DeInit()
{
	HttpParser = NULL;
	//Socket = NULL;
	TGModule::DeInit();
}
//---------------------------------------------------------------------------

void TGIP9100::OnDestinationBufferLocked(TGBufferLockStruct ls)
{
	emit DestinationBufferLocked(ls);
}
//---------------------------------------------------------------------------
