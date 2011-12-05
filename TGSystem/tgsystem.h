#ifndef TGSYSTEM_H
#define TGSYSTEM_H
//-----------------------------------------------------------
#include "TGSystemTypes.h"
#include "..\TGSqlite\TGSqlite.h"
#include <QtCore\QMutex>
#include "tgsystem_global.h"
#include "TGDataObject.h"
//-----------------------------------------------------------
typedef TGMap<UID, PTGModule> TGFactoryModuleMap;
typedef TGMap<UID, PTGModule> TGModuleMap;
//-----------------------------------------------------------

class TGModuleFactory
{
public:
	virtual ~TGModuleFactory() {};
	virtual void RegisterModuleTypes(PTGSystem system) = 0;

};
//-----------------------------------------------------------
Q_DECLARE_INTERFACE(TGModuleFactory, "Tegrenys.TGModuleFactory")
//-----------------------------------------------------------
namespace TGSignals
{
	enum SignalType{Incoming, Outgoing};
	struct Connection
	{
		QString LocalMethodName;
		QString RemoteMethodName;
		PTGModule LocalModule;
		SignalType SignalType; 
	};
//-----------------------------------------------------------
//typedef TGList<Connection> ConnectionsList;
//typedef TGMap<UID, ConnectionsList> ConnectionsMap;
};
//-----------------------------------------------------------
typedef TGMap<UID, TGDataObject> TGConfigMap;
//-----------------------------------------------------------

class TGSystem : public TGReferenceCounter
{
public:
	TGSystem();
	~TGSystem();
	TGSqlite* GetDataBase();

	void LoadPlugins();
	void LoadModules();
	void RegisterFactoryModuleType(UID type_id, PTGModule factory_module);
	void UnregisterFactoryModuleType(UID type_id);
	PTGModule CreateModule(UID type_id, UID module_id, UID thread_id);
	void AddChildModule(UID parent, UID module_uid);
	virtual void RegisterModule(UID module_uid, PTGModule module);
	virtual void DeInit();
	void InitModules();
	bool ConnectTo(UID remote_module_id, const char* remote_method_name, PTGModule local_module, const char* local_method_name, TGSignals::SignalType signal_type);
	void SetConfig(UID module_id, TGDataObject& config);
	const TGDataObject LoadConfig(UID module_id, TGString table_name);

private:
	bool LoadPlugin(TGString plugin_name);
	//void AddPendingConnection(UID remote_module_id, const char* remote_method_name, PTGModule local_module, const char* local_method_name, TGSignals::SignalType signal_type);
	bool ConnectTo(PTGModule remote_module, const char* remote_method_name, PTGModule local_module, const char* local_method_name, TGSignals::SignalType signal_type);
	//void ApplyPendingConnections(UID module_id, PTGModule module);
private:
	QMutex Mutex;
	TGString SystemPath;
	TGSqlite* SystemDataBase;
	TGFactoryModuleMap FactoryModules;
	TGModuleMap Modules;
	TGConfigMap ConfigMap;
	//TGSignals::ConnectionsMap PendingConnections;

};
//-----------------------------------------------------------
#endif // TGSYSTEM_H
