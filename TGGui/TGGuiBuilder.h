#ifndef TGGuiBuider_h__
#define TGGuiBuider_h__

#include "..\TGSqlite\TGSqlite.h"
#include <QWidget>
#include "TGRefCounter.h"
#include "TGBaseViewport.h"
#include "tggui_global.h"
#include "TGVideoRectangle.h"
#include "tgsystem.h"
#include "TGBaseVideoWidget.h"
#include "tggui.h"
#include <QtPlugin>

typedef TGMap<UID, PTGBasePrimitive> TGPrimitivesMap;

//class TGWidgetHandler : public TGReferenceCounter
//{
//public:
//	TGWidgetHandler(QWidget* widget)
//	{
//		Widget = widget;
//	}
//
//	~TGWidgetHandler()
//	{
//		delete Widget;
//	}
//private:
//	QWidget* Widget;
//};
//
//TG_REFC_PTR(TGWidgetHandler)
TG_REFC_PTR(TGGuiManager);

typedef QMap<UID, QWidget*> TGWidgetMap;

class TGGUI_EXPORT TGGuiManager : public TGModule, public TGModuleFactory
{
	Q_OBJECT
	Q_INTERFACES(TGModuleFactory)
public:
	TGGuiManager();
	TGGuiManager(UID module_uid, PTGSystem system, QObject *parent = 0);
	~TGGuiManager();
	virtual void RegisterModuleTypes(PTGSystem system);

	void Build(TGSqlite* database);
	void CreateWidgets(TGSqlite* database, QWidget* parent, UID parent_id);
	QWidget* CreateWidget(UID uid, QWidget* parent, QString class_name);

	//static void RegisterPrimitive(UID primitive_uid, PTGBasePrimitive primitive);

	//PTGBasePrimitive GetPrimitive(UID primitive_uid);
	
protected:
	virtual PTGModule CreateModuleProc(UID type_id, UID module_id);

public:
	//TGVideoRectangle* video_rect;
private:
	TGWidgetMap WidgetList;
	//TGPrimitivesMap PrimitivesMap;
	//static PTGGuiBuilder StaticGuiBuilder;
signals:
	void AddViewPort(UID uid, PTGBaseViewport vp);
	void SetCurrentViewport(UID uid);
	void AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer);
public slots:
	virtual void Init();
};



#endif // TGGuiBuider_h__