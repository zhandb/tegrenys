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

Tegrenys::Tegrenys(QWidget *parent, Qt::WFlags flags)
{
	System = new TGSystem();

	//TODO: –азобратьс€ с пор€дком загрузки модулей

	NS = new TGNetworkService("{EC8A5B5E-F4B4-405e-AFF7-BD722B33DBAE}", System);
	new TGCodecManager("{6095F41E-EC10-4974-BD62-2DB00F8E59FF}", System);

	IPServer = new TGIP9100("{0F6BECA6-08CE-41c7-A81D-4DBA0BDC00C5}", System);
	IPServer->Init();

	GB = new TGGuiBuilder("{8A747671-5239-4aa6-99CB-D222947E0EE7}", System);
	
	//VideoRect = GB->GetPrimitive("{19345C9B-57FF-4a63-879C-AFDBB92DAD6D}");

	//QObject* obj = dynamic_cast<QObject*>(&*VideoRect);

	
}

Tegrenys::~Tegrenys()
{
	System->DeInit();
}
