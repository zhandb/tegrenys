#include "TGDXViewPort.h"
#include "TGDXPrimitiveLayer.h"
#include "TGBaseTexturedRectangle.h"
//---------------------------------------------------------------------
TGDXViewport::TGDXViewport(UID module_uid, PTGSystem system) : TGBaseViewport(module_uid, system)
{
	Device = NULL;
	//ViewPort = config.Attribute("Rect").toRect();
	//ViewPort = QRect(10, 20 , 600, 800);
	//Color = QColor(0, 0, 32);
}
//---------------------------------------------------------------------
TGDXViewport::~TGDXViewport()
{

}
//---------------------------------------------------------------------
void TGDXViewport::SetDevice(IDirect3DDevice9* device)
{
	Device = device;
	
	for (TGModuleList::iterator layer = ChildModules.begin(); layer != ChildModules.end(); ++layer)
	{
		((TGDXPrimitiveLayer*)&**layer)->SetDevice(device, QSize(ViewPort.width(), ViewPort.height()), true);
	}
}
//---------------------------------------------------------------------
void TGDXViewport::ApplyViewPort()
{
	D3DVIEWPORT9 vp;
	vp.X = ViewPort.x(); 
	vp.Y = ViewPort.y();
	vp.Width = ViewPort.width();
	vp.Height = ViewPort.height();
	vp.MinZ = 0.0;
	vp.MaxZ = 1.0;

	Device->SetViewport(&vp);
	Device->Clear(0, 0, D3DCLEAR_TARGET, Color.rgba(), 1.0f, 0);
}