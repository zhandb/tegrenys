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
