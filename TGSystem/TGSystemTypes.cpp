#include "TGSystemTypes.h"
#include "tgsystem.h"
//---------------------------------------------------------------------------
TGModule::TGModule(UID module_uid, PTGModule system)
{
	System = system;
	if (system)
		system->RegisterModule(module_uid, this);
}
//---------------------------------------------------------------------------

TGModule::~TGModule()
{
	//DeInit();
}
//---------------------------------------------------------------------------

void TGModule::DeInit()
{
	//Parent = NULL;

	for (TGModuleMap::iterator module = ModuleMap.begin(); module != ModuleMap.end(); ++module)
	{
		module->second->DeInit();
	}

	ModuleMap.clear();
}
//---------------------------------------------------------------------------

void TGModule::RegisterModule(UID module_uid, PTGModule module)
{
	ModuleMap[module_uid] = module;
}
//---------------------------------------------------------------------------

PTGModule TGModule::GetModule(UID module_id)
{
	PTGModule res;
	TGModuleMap::iterator module = ModuleMap.find(module_id);
	if (module != ModuleMap.end())
		res = module->second;

	return res;
}
//---------------------------------------------------------------------------

void TGModule::Init()
{

}
//---------------------------------------------------------------------------

UID TGModule::CreateModule(UID type_id)
{
	TGSystem* sys = (TGSystem*)&*System;

	UID module_uid = QUuid::createUuid();
	sys->ConnectToModuleFactory(this, type_id, module_uid);
	emit CreateModuleSignal(this, type_id, module_uid);

	return module_uid;
}
//---------------------------------------------------------------------------

void TGModule::OnCreateModuleSlot(PTGModule caller, UID type_id, UID module_id)
{
	disconnect(caller, SIGNAL(CreateModuleSignal(PTGModule, UID, UID)), this, SLOT(OnCreateModuleSlot(PTGModule, UID, UID)));
	PTGModule module = CreateModuleProc(type_id, module_id);
	if (module)
	{
		connect(this, SIGNAL(ModuleCreatedSignal(PTGModule, UID, UID, PTGModule)), caller, SLOT(OnModuleCreatedSlot(PTGModule, UID, UID, PTGModule)));
		emit ModuleCreatedSignal(caller, type_id, module_id, module);
		disconnect(this, SIGNAL(ModuleCreatedSignal(PTGModule, UID, UID, PTGModule)), caller, SLOT(OnModuleCreatedSlot(PTGModule, UID, UID, PTGModule)));
	}
	
}
//---------------------------------------------------------------------------

void TGModule::OnModuleCreatedSlot(PTGModule caller, UID type_id, UID module_id, PTGModule result)
{
	if (caller == this)
	{
		ModuleCreated(type_id, module_id, result);
	}
}
//---------------------------------------------------------------------------
