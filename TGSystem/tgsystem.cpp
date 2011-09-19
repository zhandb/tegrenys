#include "tgsystem.h"
#include <QCoreApplication>
//---------------------------------------------------------------------------
TGSystem::TGSystem() : TGModule(0, NULL)
{
	SystemPath = QCoreApplication::applicationDirPath();

	SystemDataBase = new TGSqlite();

	SystemDataBase->OpenDatabase(SystemPath + "/test.db");
}
//---------------------------------------------------------------------------

TGSystem::~TGSystem()
{
	delete SystemDataBase;
	SystemDataBase = NULL;
}
//---------------------------------------------------------------------------

TGSqlite* TGSystem::GetDataBase()
{
	return SystemDataBase;
}
//---------------------------------------------------------------------------

void TGSystem::RegisterFactoryModuleType(UID type_id, PTGModule factory_module)
{
	FactoryModules[type_id] = factory_module;
}
//---------------------------------------------------------------------------

void TGSystem::UnregisterFactoryModuleType(UID type_id)
{
	TGFactoryModuleMap::iterator factory_module = FactoryModules.find(type_id);
	if (factory_module != FactoryModules.end())
		FactoryModules.erase(factory_module);
}
//---------------------------------------------------------------------------

void TGSystem::ConnectToModuleFactory(PTGModule caller, UID type_id, UID module_id)
{
	TGFactoryModuleMap::iterator factory_module = FactoryModules.find(type_id);
	if (factory_module != FactoryModules.end())
	{
		connect(caller, SIGNAL(CreateModuleSignal(PTGModule, UID, UID)), factory_module->second, SLOT(OnCreateModuleSlot(PTGModule, UID, UID)));
		//factory_module->second->CreateModule(type_id, module_id);
	}
	else
	{
		OutputDebugString(L"Can't create module of requested type!");
	}
}
//---------------------------------------------------------------------------

