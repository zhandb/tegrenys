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
	NetworkService = System->GetModule(1111);
	connect(this, SIGNAL(CreateSocket()), NetworkService, SLOT(OnCreateSocket()));
	connect(NetworkService, SIGNAL(SocketCreated(UID)), this, SLOT(OnSocketCreated(UID)));
	emit CreateSocket();
}
//---------------------------------------------------------------------------

void TGIP9100::OnSocketCreated(UID socket_uid)
{
	PTGModule socket = System->GetModule(socket_uid);

	connect(this, SIGNAL(SocketConnect(TGString, uint32_t, uint32_t)), socket, SLOT(OnSocketConnect(TGString, uint32_t, uint32_t)));
	connect(socket, SIGNAL(SocketConnected()), this, SLOT(OnSocketConnected()));

	emit SocketConnect("192.168.0.33", 80, 0);
}
//---------------------------------------------------------------------------

void TGIP9100::OnSocketConnected()
{

}
//---------------------------------------------------------------------------