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
}
//---------------------------------------------------------------------
TGNetworkService::~TGNetworkService()
{
}
//---------------------------------------------------------------------

void TGNetworkService::timerEvent(QTimerEvent* event)
{
	for (TGModuleList::iterator socket = ChildModules.begin(); socket != ChildModules.end(); ++socket)
	{
		TGModule* m = *socket;
		((TGSocket*)m)->Poll();
	}
}
//---------------------------------------------------------------------------

PTGModule TGNetworkService::CreateModuleProc(UID type_id, UID module_id)
{
	if (type_id == TGSOCKET_TYPE_UID)
	{
		PTGModule socket = new TGSocket(module_id, System);
		//Сокет регистрируется в списке NetworkService для того, чтобы сервис опрашивал его
		//TODO: как удалить сокет после использования?
		//ModuleMap[module_id] = socket;
		AddChildModule(module_id, socket);
		return socket;
	}
	
	return NULL;
}
//---------------------------------------------------------------------
