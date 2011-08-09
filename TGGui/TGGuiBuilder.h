#ifndef TGGuiBuider_h__
#define TGGuiBuider_h__

#include "..\TGSqlite\TGSqlite.h"
#include <QWidget>
#include "TGRefCounter.h"
#include "TGBaseViewport.h"
#include "tggui_global.h"
#include "TGVideoRectangle.h"


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

typedef QList<PTGWidgetHandler> TGWidgetList;

class TGGUI_EXPORT TGGuiBuider : public QObject, public TGReferenceCounter
{
	Q_OBJECT
public:
	TGGuiBuider();
	~TGGuiBuider();
	void Build(TGSqlite* database);
	void CreateWidgets(TGSqlite* database, QWidget* parent, int parent_id);
	QWidget* CreateWidget(QWidget* parent, QString class_name);
public:
	TGVideoRectangle* video_rect;
private:
	TGWidgetList WidgetList;
	TGSqlite* gui_database;
	
signals:
	void AddViewPort(UID uid, PTGBaseViewport vp);
	void SetCurrentViewport(UID uid);
	void AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer);
};

TG_REFC_PTR(TGGuiBuider);

#endif // TGGuiBuider_h__