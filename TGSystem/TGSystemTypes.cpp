#include "TGSystemTypes.h"
#include "tgsystem.h"
//---------------------------------------------------------------------------

TGModule::TGModule(UID module_uid, PTGModule system)
{
	qRegisterMetaType<PTGModule>("PTGModule");

	System = system;
	if (system)
		system->RegisterModule(module_uid, this);
}
//---------------------------------------------------------------------------

TGModule::~TGModule()
{
	DeInit();
}
//---------------------------------------------------------------------------

void TGModule::DeInit()
{
	System = NULL;
	
	for (TGModuleList::iterator module = ChildModules.begin(); module != ChildModules.end(); ++module)
	{
		(*module)->DeInit();
	}

	ChildModules.clear();
}
//---------------------------------------------------------------------------

void TGModule::Init()
{

}
//---------------------------------------------------------------------------

PTGModule TGModule::CreateModule(UID type_id)
{
	TGSystem* sys = (TGSystem*)&*System;
	UID module_uid = QUuid::createUuid();
	return sys->CreateModule(type_id, module_uid);
}
//---------------------------------------------------------------------------

void TGModule::AddChildModule(UID module_id, PTGModule module)
{
	ChildModules.push_back(module);
}
//---------------------------------------------------------------------------
