#include "stdafx.h"
#include "tegrenys.h"
#include <QHBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include "TGDataObject.h"
//#include "TGTreeModel.h"
#include "TGSqlite\TGSqlite.h"
#include "TGSqlite\TGSqliteQuery.h"
#include "TGGui\TGGuiBuilder.h"
#include "TGBaseTextureManager.h"
//#include "TGCodec\tgcodec.h"
#include "TGNetwork\TGNetworkService.h"
#include "tgsystem.h"
#include "TGIP9100\tgip9100.h"
#include "TGIPPCodec\TGCodecManager.h"
#include <QPluginLoader>

Tegrenys::Tegrenys(QWidget *parent, Qt::WFlags flags)
{
	System = new TGSystem();

	//TODO: –азобратьс€ с пор€дком загрузки модулей

	/*QPluginLoader pl("e:/data-backup/tegrenys_1/debug/TGIP9100.dll");
	QString err = pl.errorString();
	QObject* obj = pl.instance();*/

	System->LoadPlugins();

	PTGModule m = System->CreateModule("{42DC5E02-1D9D-48c3-A38E-8CE965E5CEC2}", "{591A769E-61F4-456f-AB4B-35A5BCA1BB20}");


	NS = new TGNetworkService("{EC8A5B5E-F4B4-405e-AFF7-BD722B33DBAE}", System);
	new TGCodecManager("{6095F41E-EC10-4974-BD62-2DB00F8E59FF}", System);

	GB = new TGGuiManager("{8A747671-5239-4aa6-99CB-D222947E0EE7}", System);

	IPServer = new TGIP9100("{0F6BECA6-08CE-41c7-A81D-4DBA0BDC00C5}", System);
	IPServer->Init();

	
	//VideoRect = GB->GetPrimitive("{19345C9B-57FF-4a63-879C-AFDBB92DAD6D}");

	//QObject* obj = dynamic_cast<QObject*>(&*VideoRect);

	
}

Tegrenys::~Tegrenys()
{
	System->DeInit();
}
