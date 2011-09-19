#ifndef TGSYSTEM_H
#define TGSYSTEM_H
//-----------------------------------------------------------
#include "TGSystemTypes.h"
#include "..\TGSqlite\TGSqlite.h"
//-----------------------------------------------------------
typedef TGMap<UID, PTGModule> TGFactoryModuleMap;
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
	void ConnectToModuleFactory(PTGModule caller, UID type_id, UID module_id);
private:
	TGString SystemPath;
	TGSqlite* SystemDataBase;
	TGFactoryModuleMap FactoryModules;
};
//-----------------------------------------------------------
TG_REFC_PTR(TGSystem);
//-----------------------------------------------------------
#endif // TGSYSTEM_H
