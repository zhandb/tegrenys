#ifndef TGSystemTypes_h__
#define TGSystemTypes_h__
#include <map>
#include <QString>
#include <QObject>
#include <QTimer>
#include <Quuid>
#include "TGRefCounter.h"
#include "TGDataObject.h"
#include "tgsystem_global.h"
//-----------------------------------------------------------
#define TGMap std::map
#define TGList std::list
//-----------------------------------------------------------
typedef QUuid UID;
typedef QString TGString;
typedef QTimer TGTimer;
//-----------------------------------------------------------
TG_REFC_PTR(TGModule)
//-----------------------------------------------------------
typedef TGList<PTGModule> TGModuleList;
//-----------------------------------------------------------
class TGSystem;
TG_REFC_PTR(TGSystem);
//-----------------------------------------------------------

class TGModule : public QObject, public TGReferenceCounter
{
	Q_OBJECT
public:
	TGModule(){};
	TGModule(UID module_uid, PTGSystem system);
	~TGModule();
	virtual void DeInit();
	virtual void RegisterModule(UID module_uid, PTGSystem module){};
	PTGModule CreateModule(UID type_id);
	virtual PTGModule CreateModuleProc(UID type_id, UID module_id){return NULL;};
	
	//TODO: Should be protected
	TGModuleList ChildModules;

public slots:
	virtual void SetConfig(TGDataObject config){Config = config;};
	virtual void Init();
	virtual void AddChildModule(UID module_id, PTGModule module);

protected:
	PTGSystem System;
	TGDataObject Config;
	UID ModuleUID;
	
};
//---------------------------------------------------------------------------
#endif // TGSystemTypes_h__