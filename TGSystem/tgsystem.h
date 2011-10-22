#ifndef TGSYSTEM_H
#define TGSYSTEM_H
//-----------------------------------------------------------
#include "TGSystemTypes.h"
#include "..\TGSqlite\TGSqlite.h"
#include <QMutex>
#include "tgsystem_global.h"
//-----------------------------------------------------------
typedef TGMap<UID, PTGModule> TGFactoryModuleMap;
typedef TGMap<UID, PTGModule> TGModuleMap;
//-----------------------------------------------------------
TG_REFC_PTR(TGSystem);
//-----------------------------------------------------------

class TGSystem : public TGModule
{
	Q_OBJECT
public:
	TGSystem();
	~TGSystem();
	TGSqlite* GetDataBase();
	void RegisterFactoryModuleType(UID type_id, PTGModule factory_module);
	void UnregisterFactoryModuleType(UID type_id);
	PTGModule CreateModule(UID type_id, UID module_id);
	void AddChildModule(UID parent, UID module_uid, UID module_type_id);
	virtual void RegisterModule(UID module_uid, PTGModule module);
	virtual void DeInit();
	static PTGModule GetSystem();

	bool ConnectToEvent(UID event_source, const char* event_name, PTGModule event_receiver, const char* slot_name);
	bool ConnectToSlot(PTGModule event_source, const char* event_name, UID event_receiver, const char* slot_name);
private:
	QMutex Mutex;
	TGString SystemPath;
	TGSqlite* SystemDataBase;
	TGFactoryModuleMap FactoryModules;
	TGModuleMap Modules;
	static PTGModule StaticSystem;
};
//-----------------------------------------------------------
#endif // TGSYSTEM_H
