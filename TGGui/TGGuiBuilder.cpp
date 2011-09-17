#include "stdafx.h"
#include "TGGuiBuilder.h"
#include "TGSqliteQuery.h"
#include <QMainWindow>
#include "TGBaseVideoWidget.h"
#include "TGDXVideoWidget.h"
#include "TGDXViewPort.h"
#include "TGDXPrimitiveLayer.h"
#include "TGBaseTexturedRectangle.h"
#include "TGAnimatedRectangle.h"
#include "TGVideoRectangle.h"
#include "tgsystem.h"

//-----------------------------------------------------------------------------

TGGuiBuilder::TGGuiBuilder(UID module_uid, PTGModule system, QObject *parent) : TGModule(module_uid, system)
{
	StaticGuiBuilder = this;

	sqlite3* db = NULL;
	sqlite3_open_v2("", &db, SQLITE_OPEN_READWRITE /*| SQLITE_OPEN_CREATE*/, NULL);
	sqlite3_close(db);

	TGSqlite::main_database = ((TGSystem*)&*system)->GetDataBase();

	Build(((TGSystem*)&*system)->GetDataBase());
}
//-----------------------------------------------------------------------------

TGGuiBuilder::~TGGuiBuilder()
{
}
//-----------------------------------------------------------------------------

void TGGuiBuilder::Build(TGSqlite* database)
{
	/*SELECT  Controls.ID, Controls.ControlClass FROM Root
		JOIN Controls ON Root.RootControl = Controls.ID AND Controls.ParentControl = 0*/

	CreateWidgets(database, NULL, 0);
}
//-----------------------------------------------------------------------------

void TGGuiBuilder::CreateWidgets(TGSqlite* database, QWidget* parent, int parent_id)
{
	TGSqliteQuery root_control_query;
	TGDataRecord schema;
	root_control_query.Exec(
		database, 
		QString("SELECT  ID, ControlClass FROM Controls WHERE ParentControl = %1").arg(parent_id), 
		&schema);

	TGDataRecord data;
	while (root_control_query.Read(&data))
	{
		QString class_name = data[1].toString();
		QWidget* widget = CreateWidget(parent, class_name);
		if (widget)
			CreateWidgets(database, widget, data[0].toInt());
	}
}
//-----------------------------------------------------------------------------

QWidget* TGGuiBuilder::CreateWidget(QWidget* parent, QString class_name)
{
	QWidget* widget = NULL;

	if (class_name == "TGMainWindow")
	{
		//widget = new QMainWindow(parent);
		//widget->show();
	}

	if (class_name == "TGBaseVideoWidget")
	{
		widget = new TGDXVideoWidget(parent);
		connect(this, SIGNAL(AddViewPort(UID, PTGBaseViewport)), widget, SLOT(AddViewPort(UID, PTGBaseViewport)));
		connect(this, SIGNAL(SetCurrentViewport(UID)), widget, SLOT(SetCurrentViewport(UID)));
		connect(this, SIGNAL(AddLayerToCurrentViewport(PTGBasePrimitiveLayer)), widget, SLOT(AddLayerToCurrentViewport(PTGBasePrimitiveLayer)));

		widget->show();

		PTGBaseViewport vp = new TGDXViewport(QRect(0, 0, 1280, 1024), QColor("darkblue"));
		emit AddViewPort("{3192C1FA-6FA6-44f0-8DB4-DCE1B67F6E25}", vp);

		/*PTGBaseViewport vp2 = new TGDXViewport(QRect(400, 100, 500, 600), QColor("green"));
		emit AddViewPort(222, vp2);*/

		emit SetCurrentViewport("{3192C1FA-6FA6-44f0-8DB4-DCE1B67F6E25}");

		PTGBasePrimitiveLayer PrimitiveLayer = new TGDXPrimitiveLayer("{3192C1FA-6FA6-44f0-8DB4-DCE1B67F6E25}");

		TGBasePrimitiveLayerParams params;
		params.BaseViewPort = QSize(1, 1);
		params.BaseDistance = 1.0;
		params.MinDistance = 0.0;
		params.MaxDistance = 100.0;

		PrimitiveLayer->SetupProjection(params);

		TGBasePrimitiveLayerCamera camera;
		camera.BasePoint.X = 0.0;
		camera.BasePoint.Y = 0.0;
		camera.BasePoint.Z = 0.0;

		camera.EyePoint.X = 0.0;
		camera.EyePoint.Y = 0.0;
		camera.EyePoint.Z = -3.0;

		PrimitiveLayer->SetupCamera(camera);

		emit AddLayerToCurrentViewport(PrimitiveLayer);

		/*TGVideoRectangle* p2 = new TGVideoRectangle(PrimitiveLayer);
		PTGBasePrimitive pp2 = p2;
		p2->SetSize(QSizeF(3, 2));
		p2->SetPos(TGPointF(-200, -0.5, -0.1));*/
		
		TGBaseTexturedRectangle* p = new TGBaseTexturedRectangle(PrimitiveLayer, "{8BC0D4A6-4BBA-431c-83CA-3357D87CF21A}");
		p->SetColor(QColor("red"));
		p->SetSize(QSizeF(1, 1));
		p->SetPos(TGPointF(-1, -0.5, 0.0));
		
		TGAnimatedRectangle* p1 = new TGAnimatedRectangle(PrimitiveLayer);
		p1->SetColor(QColor("red"));
		p1->SetSize(QSizeF(0.3, 0.3));
		p1->SetPos(TGPointF(-1, -0.5, -0.1));
		
		/*emit SetCurrentViewport(222);

		PrimitiveLayer = new TGDXPrimitiveLayer(222);

		params.BaseViewPort = QSize(2, 2);
		params.BaseDistance = 1.0;
		params.MinDistance = 1.0;
		params.MaxDistance = 100.0;

		PrimitiveLayer->SetupProjection(params);

		camera.BasePoint.X = 0.0;
		camera.BasePoint.Y = 0.0;
		camera.BasePoint.Z = 0.0;

		camera.EyePoint.X = 0.0;
		camera.EyePoint.Y = 0.0;
		camera.EyePoint.Z = -1;

		PrimitiveLayer->SetupCamera(camera);

		emit AddLayerToCurrentViewport(PrimitiveLayer);

		p = new TGBaseTexturedRectangle(1);
		p->SetColor(QColor("red"));
		p->SetSize(QSizeF(0.8, 0.8));
		p->SetPos(TGPointF(-0.9, -0.9, 0.0));
		PrimitiveLayer->Primitives.push_back(p);*/
	}

	if (widget)
	{
		PTGWidgetHandler wh = new TGWidgetHandler(widget);
		WidgetList.push_back(wh);
	}
	return widget;
}
//---------------------------------------------------------------------------

void TGGuiBuilder::RegisterPrimitive(UID primitive_uid, PTGBasePrimitive primitive)
{
	StaticGuiBuilder->PrimitivesMap[primitive_uid] = primitive;
}
//---------------------------------------------------------------------------

PTGBasePrimitive TGGuiBuilder::GetPrimitive(UID primitive_uid)
{
	PTGBasePrimitive res = NULL;

	TGPrimitivesMap::iterator primitive = PrimitivesMap.find(primitive_uid);
	if (primitive != PrimitivesMap.end())
		res = primitive->second;

	return res;
}
//---------------------------------------------------------------------------
PTGGuiBuilder TGGuiBuilder::StaticGuiBuilder;
//---------------------------------------------------------------------------
