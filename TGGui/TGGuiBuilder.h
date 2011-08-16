#ifndef TGGuiBuider_h__
#define TGGuiBuider_h__

#include "..\TGSqlite\TGSqlite.h"
#include <QWidget>
#include "TGRefCounter.h"
#include "TGBaseViewport.h"
#include "tggui_global.h"
#include "TGVideoRectangle.h"
#include "tgsystem.h"

typedef TGMap<UID, PTGBasePrimitive> TGPrimitivesMap;

class TGWidgetHandler : public TGReferenceCounter
{
public:
	TGWidgetHandler(QWidget* widget)
	{
		Widget = widget;
	}

	~TGWidgetHandler()
	{
		delete Widget;
	}
private:
	QWidget* Widget;
};

TG_REFC_PTR(TGWidgetHandler)
TG_REFC_PTR(TGGuiBuilder);

typedef QList<PTGWidgetHandler> TGWidgetList;

class TGGUI_EXPORT TGGuiBuilder : public TGModule
{
	Q_OBJECT
public:
	TGGuiBuilder(UID module_uid, PTGModule system, QObject *parent = 0);
	~TGGuiBuilder();
	void Build(TGSqlite* database);
	void CreateWidgets(TGSqlite* database, QWidget* parent, int parent_id);
	QWidget* CreateWidget(QWidget* parent, QString class_name);
	static void RegisterPrimitive(UID primitive_uid, PTGBasePrimitive primitive);

	PTGBasePrimitive GetPrimitive(UID primitive_uid);
public:
	//TGVideoRectangle* video_rect;
private:
	TGWidgetList WidgetList;
	TGPrimitivesMap PrimitivesMap;
	static PTGGuiBuilder StaticGuiBuilder;
signals:
	void AddViewPort(UID uid, PTGBaseViewport vp);
	void SetCurrentViewport(UID uid);
	void AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer);
};



#endif // TGGuiBuider_h__