#include "tgsystem.h"
#include <QCoreApplication>
//---------------------------------------------------------------------------
PTGModule TGSystem::StaticSystem;
//---------------------------------------------------------------------------

TGSystem::TGSystem() : TGModule(0, NULL)
{
	SystemPath = QCoreApplication::applicationDirPath();

	SystemDataBase = new TGSqlite();

	SystemDataBase->OpenDatabase(SystemPath + "/test.db");

	StaticSystem = this;
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

void TGSystem::AddChildModule(UID parent, UID module_uid, UID module_type_id)
{
	QMutexLocker locker(&Mutex);

	PTGModule module = CreateModule(module_type_id, module_uid);
	if (module)
	{
		TGModuleMap::iterator i = Modules.find(parent);
		if (i != Modules.end())
		{
			//i->second->AddChildModule(module_uid, module);
			QMetaObject::invokeMethod(i->second, "AddChildModule", Q_ARG(UID, module_uid), Q_ARG(PTGModule, module));
		}
		else
		{
			OutputDebugString(L"Can't find parent object!");
		}
	}
}
//---------------------------------------------------------------------------

void TGSystem::RegisterModule(UID module_uid, PTGModule module)
{
	Modules[module_uid] = module;
}
//---------------------------------------------------------------------------

PTGModule TGSystem::CreateModule(UID type_id, UID module_id)
{
	PTGModule module = NULL;

	TGFactoryModuleMap::iterator factory_module = FactoryModules.find(type_id);
	if (factory_module != FactoryModules.end())
	{
		module = factory_module->second->CreateModuleProc(type_id, module_id);
		if (module)
		{
			module->Init();
		}
	}

	return module;
}
//---------------------------------------------------------------------------

void TGSystem::DeInit()
{
	for (TGModuleMap::iterator i = Modules.begin(); i != Modules.end(); ++i)
	{
		i->second->DeInit();
	}

	Modules.clear();
	FactoryModules.clear();
	TGModule::DeInit();
}
//---------------------------------------------------------------------------

PTGModule TGSystem::GetSystem()
{
	return StaticSystem;
}
//---------------------------------------------------------------------------

