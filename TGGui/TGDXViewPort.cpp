#include "TGDXViewPort.h"
#include "TGDXPrimitiveLayer.h"
#include "TGBaseTexturedRectangle.h"
//---------------------------------------------------------------------
TGDXViewport::TGDXViewport(TGDataObject& config) : TGBaseViewport(config)
{
	Device = NULL;
	ViewPort = config.Attribute("Rect").toRect();
}
//---------------------------------------------------------------------
TGDXViewport::~TGDXViewport()
{

}
//---------------------------------------------------------------------
void TGDXViewport::SetDevice(IDirect3DDevice9* device)
{
	Device = device;
	
	for (TGPrimitiveLayersList::iterator layer = PrimitiveLayers.begin(); layer != PrimitiveLayers.end(); ++layer)
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