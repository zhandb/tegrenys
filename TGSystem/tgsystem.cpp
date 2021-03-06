#include "tgsystem.h"
#include <QtCore\QCoreApplication>
#include "..\TGSqlite\TGSqliteQuery.h"
#include <QtCore\QPluginLoader>
//---------------------------------------------------------------------------

TGSystem::TGSystem()
{
	SystemPath = QCoreApplication::applicationDirPath();

	SystemDataBase = new TGSqlite();

	SystemDataBase->OpenDatabase(SystemPath + "/test.db");

	//TGSqlite::main_database = SystemDataBase;
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

void TGSystem::AddChildModule(UID parent, UID module_uid)
{
	QMutexLocker locker(&Mutex);

	TGModuleMap::iterator parent_iter = Modules.find(parent);
	TGModuleMap::iterator module_iter = Modules.find(module_uid);

	Q_ASSERT(parent_iter != Modules.end() && module_iter != Modules.end());
	QMetaObject::invokeMethod(parent_iter->second, "AddChildModule", Q_ARG(UID, module_uid), Q_ARG(PTGModule, module_iter->second));
	
}
//---------------------------------------------------------------------------

void TGSystem::RegisterModule(UID module_uid, PTGModule module)
{
	Modules[module_uid] = module;
}
//---------------------------------------------------------------------------

PTGModule TGSystem::CreateModule(UID type_id, UID module_id, UID thread_id)
{
	PTGModule module = NULL;

	TGFactoryModuleMap::iterator factory_module = FactoryModules.find(type_id);
	if (factory_module != FactoryModules.end())
	{
		module = factory_module->second->CreateModuleProc(type_id, module_id);
		if (module)
		{
			//ApplyPendingConnections(module_id, module);
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
	//PendingConnections.clear();
//	TGModule::DeInit();
}
//---------------------------------------------------------------------------

void TGSystem::LoadModules()
{
	TGSqliteQuery root_control_query;
	TGDataRecord schema;
	root_control_query.Exec(
		GetDataBase(), 
		QString("SELECT  ID, ModuleType FROM Modules"),
		&schema);

	TGDataRecord data;
	while (root_control_query.Read(&data))
	{
		//QString uid = data[0].toString();
		/*QString class_name = data[1].toString();
		QWidget* widget = CreateWidget(data[0].toString(), parent, class_name);
		if (widget)
			CreateWidgets(database, widget, data[0].toString());*/
	}
}
//---------------------------------------------------------------------------

bool TGSystem::LoadPlugin(TGString plugin_name)
{
	QPluginLoader pl(SystemPath + "/" + plugin_name);
	QObject* obj = pl.instance();
	TGModuleFactory* module_factory = qobject_cast<TGModuleFactory*>(obj);
	if (module_factory)
		module_factory->RegisterModuleTypes(this);
	return true;
}
//---------------------------------------------------------------------------

void TGSystem::LoadPlugins()
{
	TGSqliteQuery root_control_query;
	TGDataRecord schema;
	root_control_query.Exec(
		GetDataBase(), 
		QString("SELECT  ID, Path FROM Plugins"),
		&schema);

	TGDataRecord data;
	while (root_control_query.Read(&data))
	{
		QString uid = data[0].toString();
		QString path = data[1].toString();
		LoadPlugin(path + ".dll");
	}
}
//---------------------------------------------------------------------------

bool TGSystem::ConnectTo(UID remote_module_id, const char* remote_method_name, PTGModule local_module, const char* local_method_name, TGSignals::SignalType signal_type)
{
	bool res = false;
	//QMutexLocker locker(&Mutex);
	TGModuleMap::iterator remote_module = Modules.find(remote_module_id);
	if (remote_module != Modules.end())
	{
		ConnectTo(remote_module->second, remote_method_name, local_module, local_method_name, signal_type);
	}
	else
	{
		//AddPendingConnection(remote_module_id, remote_method_name, local_module, local_method_name, signal_type);
	}

	return res;
}
//---------------------------------------------------------------------------

bool TGSystem::ConnectTo(PTGModule remote_module, const char* remote_method_name, PTGModule local_module, const char* local_method_name, TGSignals::SignalType signal_type)
{
	bool res = false;
	if (signal_type == TGSignals::Incoming)
		res = QObject::connect(remote_module, remote_method_name, local_module, local_method_name);
	else
		res = QObject::connect(local_module, local_method_name, remote_module, remote_method_name);

	return res;
}
//---------------------------------------------------------------------------

//void TGSystem::AddPendingConnection(UID remote_module_id, const char* remote_method_name, PTGModule local_module, const char* local_method_name, TGSignals::SignalType signal_type)
//{
//	//TODO: ����� ����� ������� ��� �� ������������ ����������
//	TGSignals::Connection connection;
//	connection.LocalMethodName = local_method_name;
//	connection.RemoteMethodName = remote_method_name;
//	connection.LocalModule = local_module;
//	connection.SignalType = signal_type;
//
//	PendingConnections[remote_module_id].push_back(connection);
//}
////---------------------------------------------------------------------------

//void TGSystem::ApplyPendingConnections(UID module_id, PTGModule module)
//{
//	TGSignals::ConnectionsMap::iterator i = PendingConnections.find(module_id);
//	if (i != PendingConnections.end())
//	{
//		for (TGSignals::ConnectionsList::iterator j = i->second.begin(); j != i->second.end(); ++j)
//		{
//			ConnectTo(module, j->RemoteMethodName.toLocal8Bit(), j->LocalModule, j->LocalMethodName.toLocal8Bit(), j->SignalType);
//		}
//		PendingConnections.erase(i);
//	}
//}
////---------------------------------------------------------------------------

void TGSystem::SetConfig(UID module_id, TGDataObject& config)
{
	TGModuleMap::iterator module = Modules.find(module_id);
	Q_ASSERT(module != Modules.end());

	QMetaObject::invokeMethod(module->second, "SetConfig", Q_ARG(TGDataObject, config));
}
//---------------------------------------------------------------------------

void TGSystem::InitModules()
{
	for (TGModuleMap::iterator i = Modules.begin(); i != Modules.end();++i)
	{
		QMetaObject::invokeMethod(i->second, "Init");
	}
}
//---------------------------------------------------------------------------

const TGDataObject TGSystem::LoadConfig(UID module_id, TGString table_name)
{
	TGDataObject module_config;

	TGConfigMap::iterator config = ConfigMap.find(module_id);
	if (config == ConfigMap.end())
	{
		TGSqliteQuery config_query;
		TGDataRecord schema;
		config_query.Exec(
			SystemDataBase, 
			TGString("select * from %1").arg(table_name), 
			&schema);

		TGDataRecord data;
		while (config_query.Read(&data))
		{
			TGDataObject new_config;
			for (int i = 0; i < schema.size(); ++i)
			{
				new_config.SetAttribute(schema[i].toString(), data[i]);
			}

			UID uid = new_config.Attribute("ID").toString();
			
			ConfigMap[uid] = new_config;

			if (uid == module_id)
				module_config = new_config;
		}	
	}
	else
	{
		module_config = config->second;
	}

	return module_config;
}
//---------------------------------------------------------------------------

