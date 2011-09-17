#ifndef TGSystemTypes_h__
#define TGSystemTypes_h__
#include <map>
#include <QString>
#include <QObject>
#include <QTimer>
#include <Quuid>
#include "TGRefCounter.h"
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
	void DeInit();
	void RegisterModule(UID module_uid, PTGModule module);
	PTGModule GetModule(UID module_id);
protected:
	PTGModule System;
	TGModuleMap ModuleMap;
};
//---------------------------------------------------------------------------
#endif // TGSystemTypes_h__