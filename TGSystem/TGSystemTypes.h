#ifndef TGSystemTypes_h__
#define TGSystemTypes_h__
#include <map>
#include <QString>
#include <QObject>
#include <QTimer>
#include <Quuid>
#include "TGRefCounter.h"
#include "TGDataObject.h"
//-----------------------------------------------------------
#define TGMap std::map 
//-----------------------------------------------------------
typedef QUuid UID;
typedef QString TGString;
typedef QTimer TGTimer;
//-----------------------------------------------------------
TG_REFC_PTR(TGModule)
//-----------------------------------------------------------
typedef TGMap<UID, PTGModule> TGModuleMap;
//-----------------------------------------------------------

class TGModule : public QObject, public TGReferenceCounter
{
	Q_OBJECT
public:
	TGModule(UID module_uid, PTGModule system);
	~TGModule();
	virtual void Init();
	virtual void DeInit();
	void RegisterModule(UID module_uid, PTGModule module);
	PTGModule GetModule(UID module_id);
	UID CreateModule(UID type_id);
	
protected:
	virtual PTGModule CreateModuleProc(UID type_id, UID module_id){return NULL;};
	virtual void ModuleCreated(UID type_id, UID module_id, PTGModule module){};
signals: 
	void CreateModuleSignal(PTGModule caller, UID type_id, UID module_id);
	void ModuleCreatedSignal(PTGModule caller, UID type_id, UID module_id, PTGModule result);
public slots:
	virtual void OnCreateModuleSlot(PTGModule caller, UID type_id, UID module_id);
	virtual void OnModuleCreatedSlot(PTGModule caller, UID type_id, UID module_id, PTGModule result);
	virtual void SetConfig(const TGDataObject& config){};
protected:
	PTGModule System;
	TGModuleMap ModuleMap;
};
//---------------------------------------------------------------------------
#endif // TGSystemTypes_h__