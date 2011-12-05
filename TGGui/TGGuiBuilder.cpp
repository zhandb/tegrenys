#include "stdafx.h"
#include "TGGuiBuilder.h"
#include "TGSqliteQuery.h"
#include <QtGui\QMainWindow>
#include "TGBaseVideoWidget.h"
#include "TGDXVideoWidget.h"
#include "TGDXViewPort.h"
#include "TGDXPrimitiveLayer.h"
#include "TGBaseTexturedRectangle.h"
#include "TGAnimatedRectangle.h"
#include "TGVideoRectangle.h"
#include "tgsystem.h"
#include "TGGuiTypes.h"
#include "TGVideoWidgetHandler.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(TGGui, TGGuiManager);
//---------------------------------------------------------------------------

TGGuiManager::TGGuiManager(UID module_uid, PTGSystem system, QObject *parent) : TGModule(module_uid, system)
{
	//StaticGuiBuilder = this;
}
//---------------------------------------------------------------------------

TGGuiManager::TGGuiManager()
{
	
}
//-----------------------------------------------------------------------------

TGGuiManager::~TGGuiManager()
{
	for (TGWidgetMap::iterator iter = WidgetList.begin(); iter != WidgetList.end(); ++iter)
	{
		delete *iter;
	}
}
//-----------------------------------------------------------------------------

void TGGuiManager::Build(TGSqlite* database)
{
	/*SELECT  Controls.ID, Controls.ControlClass FROM Root
		JOIN Controls ON Root.RootControl = Controls.ID AND Controls.ParentControl = 0*/

	CreateWidgets(database, NULL, 0);
}
//-----------------------------------------------------------------------------

void TGGuiManager::CreateWidgets(TGSqlite* database, QWidget* parent, UID parent_id)
{
	TGSqliteQuery root_control_query;
	TGDataRecord schema;
	root_control_query.Exec(
		database, 
		QString("SELECT  ID, ControlClass FROM Controls WHERE ParentControl = \"%1\"").arg(parent_id), 
		&schema);

	TGDataRecord data;
	while (root_control_query.Read(&data))
	{
		//QString uid = data[0].toString();
		QString class_name = data[1].toString();
		QWidget* widget = CreateWidget(data[0].toString(), parent, class_name);
		if (widget)
			CreateWidgets(database, widget, data[0].toString());
	}
}
//-----------------------------------------------------------------------------

QWidget* TGGuiManager::CreateWidget(UID uid, QWidget* parent, QString class_name)
{
	QWidget* widget = NULL;

	if (class_name == "TGMainWindow")
	{
		//widget = new QMainWindow(parent);
		//widget->show();
	}

	if (class_name == "TGBaseVideoWidget")
	{
		TGSystem* sys = (TGSystem*)&*System;

		
		TGDataObject viewport_config;
		viewport_config.SetAttribute("Rect", QRect(10, 20, 800, 600));
		viewport_config.SetAttribute("Color", QColor("darkblue"));

		
		TGDataObject layer_config;
		//dx_videowidget->AddLayer(UID("{A5DDBB01-F595-46ed-9D7E-8B95F04776E4}"), UID("{381BAAA0-10E6-40be-A463-3B42C71E55AC}"), layer_config);
		//connect(this, SIGNAL(AddViewPort(UID, PTGBaseViewport)), widget, SLOT(AddViewPort(UID, PTGBaseViewport)));
		//connect(this, SIGNAL(SetCurrentViewport(UID)), widget, SLOT(SetCurrentViewport(UID)));
		//connect(this, SIGNAL(AddLayerToCurrentViewport(PTGBasePrimitiveLayer)), widget, SLOT(AddLayerToCurrentViewport(PTGBasePrimitiveLayer)));

		//widget->show();

		/*PTGBaseViewport vp = new TGDXViewport(QRect(0, 0, 1280, 1024), QColor("darkblue"));
		emit AddViewPort("{3192C1FA-6FA6-44f0-8DB4-DCE1B67F6E25}", vp);*/

		/*PTGBaseViewport vp2 = new TGDXViewport(QRect(400, 100, 500, 600), QColor("green"));
		emit AddViewPort(222, vp2);*/

		//emit SetCurrentViewport("{3192C1FA-6FA6-44f0-8DB4-DCE1B67F6E25}");

		/*PTGBasePrimitiveLayer PrimitiveLayer = new TGDXPrimitiveLayer("{3192C1FA-6FA6-44f0-8DB4-DCE1B67F6E25}");

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

		emit AddLayerToCurrentViewport(PrimitiveLayer);*/

		/*TGVideoRectangle* p2 = new TGVideoRectangle(PrimitiveLayer);
		PTGBasePrimitive pp2 = p2;
		p2->SetSize(QSizeF(3, 2));
		p2->SetPos(TGPointF(-200, -0.5, -0.1));*/
		
		/*TGBaseTexturedRectangle* p = new TGBaseTexturedRectangle(PrimitiveLayer, "{8BC0D4A6-4BBA-431c-83CA-3357D87CF21A}");
		p->SetColor(QColor("red"));
		p->SetSize(QSizeF(1, 1));
		p->SetPos(TGPointF(-1, -0.5, 0.0));
		
		TGAnimatedRectangle* p1 = new TGAnimatedRectangle(PrimitiveLayer);
		p1->SetColor(QColor("red"));
		p1->SetSize(QSizeF(0.3, 0.3));
		p1->SetPos(TGPointF(-1, -0.5, -0.1));*/
		
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

	/*if (widget)
	{
		PTGWidgetHandler wh = new TGWidgetHandler(widget);
		WidgetList.push_back(wh);
	}*/

	WidgetList[uid] = widget;
	return widget;
}
//---------------------------------------------------------------------------

PTGModule TGGuiManager::CreateModuleProc(UID type_id, UID module_id)
{
	if (type_id == TGVIDEOWIDGET_TYPE_UID)
	{
		return new TGVideoWidgetHandler(module_id, System);
	}

	if (type_id == TGDXVIEWPORT_TYPE_UID)
	{
		return new TGDXViewport(module_id, System);
	}

	if (type_id == TGDXPRIMITIVELAYER_TYPE_UID)
	{
		return new TGDXPrimitiveLayer(module_id, System);
	}

	if (type_id == TGBASE_TEXTURED_RECTANGLE_TYPE_UID)
	{
		return new TGBaseTexturedRectangle(module_id, System, "{8BC0D4A6-4BBA-431c-83CA-3357D87CF21A}");
	}

	if (type_id == TGBASE_VIDEO_RECTANGLE_TYPE_UID)
	{
		return new TGVideoRectangle(module_id, System);
	}

	return NULL;
}
//---------------------------------------------------------------------------

void TGGuiManager::RegisterModuleTypes(PTGSystem system)
{
	System = system;
	System->RegisterModule(UID("{8A747671-5239-4aa6-99CB-D222947E0EE7}"), this);
	system->RegisterFactoryModuleType(TGVIDEOWIDGET_TYPE_UID, this);
	system->RegisterFactoryModuleType(TGDXVIEWPORT_TYPE_UID, this);
	system->RegisterFactoryModuleType(TGDXPRIMITIVELAYER_TYPE_UID, this);
	system->RegisterFactoryModuleType(TGBASE_TEXTURED_RECTANGLE_TYPE_UID, this);
	system->RegisterFactoryModuleType(TGBASE_VIDEO_RECTANGLE_TYPE_UID, this);
	Init();
}
//---------------------------------------------------------------------------

void TGGuiManager::Init()
{
	//TODO Разобраться, почему нужна инициализация в каждом модуле
	sqlite3* db = NULL;
	sqlite3_open_v2("", &db, SQLITE_OPEN_READWRITE /*| SQLITE_OPEN_CREATE*/, NULL);
	sqlite3_close(db);

	//TGSqlite::main_database = System->GetDataBase();

	Build(System->GetDataBase());
}
//---------------------------------------------------------------------------
//
//void TGGuiBuilder::RegisterPrimitive(UID primitive_uid, PTGBasePrimitive primitive)
//{
//	StaticGuiBuilder->PrimitivesMap[primitive_uid] = primitive;
//}
////---------------------------------------------------------------------------
//
//PTGBasePrimitive TGGuiBuilder::GetPrimitive(UID primitive_uid)
//{
//	PTGBasePrimitive res = NULL;
//
//	TGPrimitivesMap::iterator primitive = PrimitivesMap.find(primitive_uid);
//	if (primitive != PrimitivesMap.end())
//		res = primitive->second;
//
//	return res;
//}
////---------------------------------------------------------------------------

