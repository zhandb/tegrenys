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
	NetworkService = system->GetModule(1111);
	connect(this, SIGNAL(CreateSocket()), NetworkService, SLOT(OnCreateSocket()));
	emit CreateSocket();
}