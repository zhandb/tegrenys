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
#include "TGGuiTypes.h"

Tegrenys::Tegrenys(QWidget *parent, Qt::WFlags flags)
{
	System = new TGSystem();

	//TODO: –азобратьс€ с пор€дком загрузки модулей

	System->LoadPlugins();


	System->CreateModule(TGVIDEOWIDGET_TYPE_UID, UID("{D887D9A2-C050-4a77-881C-6065DD98B025}"), UID());
	System->CreateModule(TGDXVIEWPORT_TYPE_UID, UID("{B9E2204C-8265-4482-949F-F6B8D98F13C3}"), UID());
	System->CreateModule(TGDXPRIMITIVELAYER_TYPE_UID, UID("{005E9139-659E-469d-8D7F-89AF60A78C39}"), UID());
	System->CreateModule(TGBASE_VIDEO_RECTANGLE_TYPE_UID, UID("{8A179B79-5A2B-4a89-A359-ACD963E8D9EE}"), UID());
	System->CreateModule(TG_IP9100_TYPE_UID, "{0F6BECA6-08CE-41c7-A81D-4DBA0BDC00C5}", UID());

	System->InitModules();

	/*TGDataObject config;
	config.SetAttribute("Host", "192.168.0.33");
	config.SetAttribute("Port", 80);
	System->SetConfig("{0F6BECA6-08CE-41c7-A81D-4DBA0BDC00C5}", config);*/
	
	
	//DXPRIMITIVELAYER -> BASEVIDEORECTANGLE
	System->AddChildModule(UID("{005E9139-659E-469d-8D7F-89AF60A78C39}"), UID("{8A179B79-5A2B-4a89-A359-ACD963E8D9EE}"));

	//GUIMANAGER -> DXVIDEOWIDGET
	System->AddChildModule(UID("{8A747671-5239-4aa6-99CB-D222947E0EE7}"), UID("{D887D9A2-C050-4a77-881C-6065DD98B025}"));
	//DXVIDEOWIDGET -> DXVIEWPORT
	System->AddChildModule(UID("{D887D9A2-C050-4a77-881C-6065DD98B025}"), UID("{B9E2204C-8265-4482-949F-F6B8D98F13C3}"));
	//DXVIEWPORT -> DXPRIMITIVELAYER
	System->AddChildModule(UID("{B9E2204C-8265-4482-949F-F6B8D98F13C3}"), UID("{005E9139-659E-469d-8D7F-89AF60A78C39}"));
	
	//sys->AddChildModule(UID("{005E9139-659E-469d-8D7F-89AF60A78C39}"), UID("{EF56795C-23E3-4715-A1E8-EC33390E3661}"), TGBASE_TEXTURED_RECTANGLE_TYPE_UID);
	
}

Tegrenys::~Tegrenys()
{
	System->DeInit();
}
