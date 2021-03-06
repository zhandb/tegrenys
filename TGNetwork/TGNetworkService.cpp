#include "TGNetworkService.h"
#include "TGHttpParser.h"
#include "..\TGIPPCodec\TGMJPEGDecoder.h"
#include "tgnetwork.h"
#include <QtCore\QtPlugin>
//---------------------------------------------------------------------
Q_EXPORT_PLUGIN2(TGNetwork, TGNetworkService);
//---------------------------------------------------------------------

TGNetworkService::TGNetworkService(UID module_uid, PTGSystem system) : TGModule(module_uid, system)
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2,2), &wsa_data);

	startTimer(1);
}
//---------------------------------------------------------------------------

TGNetworkService::TGNetworkService()
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2,2), &wsa_data);

	startTimer(1);
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
		//����� �������������� � ������ NetworkService ��� ����, ����� ������ ��������� ���
		//TODO: ��� ������� ����� ����� �������������?
		//ModuleMap[module_id] = socket;
		AddChildModule(module_id, socket);
		return socket;
	}
	
	return NULL;
}
//---------------------------------------------------------------------------

void TGNetworkService::RegisterModuleTypes(PTGSystem system)
{
	system->RegisterFactoryModuleType(TGSOCKET_TYPE_UID, this);
}
//---------------------------------------------------------------------
