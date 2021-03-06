#include "TGVideoWidgetHandler.h"
#include "TGDXVideoWidget.h"
#include "TGGuiTypes.h"
//---------------------------------------------------------------------------

TGVideoWidgetHandler::TGVideoWidgetHandler(UID module_uid, PTGSystem system) : TGModule(module_uid, system)
{
	VideoWidget = NULL;
}
//---------------------------------------------------------------------------

TGVideoWidgetHandler::~TGVideoWidgetHandler()
{

}
//---------------------------------------------------------------------------

void TGVideoWidgetHandler::Init()
{
	VideoWidget = new TGDXVideoWidget(System);
	VideoWidget->show();
}
//---------------------------------------------------------------------------

void TGVideoWidgetHandler::AddChildModule(UID module_uid, PTGModule module)
{
	VideoWidget->AddViewport(module_uid, module);
}
//---------------------------------------------------------------------------

