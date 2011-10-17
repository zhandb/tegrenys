#include "TGBaseViewport.h"
//---------------------------------------------------------------------
TGBaseViewport::TGBaseViewport(UID module_uid, PTGModule system) : TGModule(module_uid, system)
{
	//Color = config.Attribute("Color").value<QColor>();
}
//---------------------------------------------------------------------
TGBaseViewport::~TGBaseViewport()
{

}
//---------------------------------------------------------------------
void TGBaseViewport::ApplyViewPort()
{

}
//---------------------------------------------------------------------
void TGBaseViewport::AddLayer(UID layer_uid, PTGModule layer)
{
	PrimitiveLayers.push_back(layer);
	LayersMap[layer_uid] = layer;
}
//---------------------------------------------------------------------
void TGBaseViewport::MouseEvent(QMouseEvent* event)
{
	for (TGPrimitiveLayersList::iterator layer = PrimitiveLayers.begin(); layer != PrimitiveLayers.end(); ++layer)
	{
		TG3DRay pick_vector;
		QSize viewport = QSize(ViewPort.width(), ViewPort.height());
		TGBasePrimitiveLayer* pl = (TGBasePrimitiveLayer*)&**layer;
		pl->CalcPickVector(event->x() - ViewPort.x(), event->y() - ViewPort.y(), pick_vector, viewport);
		pl->MouseEvent(event, pick_vector);
	}
}
//---------------------------------------------------------------------------

void TGBaseViewport::AddChildModule(UID module_uid, PTGModule module)
{
	AddLayer(module_uid, module);
}
//---------------------------------------------------------------------
