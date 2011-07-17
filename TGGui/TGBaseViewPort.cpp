#include "TGBaseViewport.h"
//---------------------------------------------------------------------
TGBaseViewport::TGBaseViewport(TGViewPortRect view_port, TGViewPortColor color) : ViewPort(view_port), Color(color)
{

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
void TGBaseViewport::AddLayer(PTGBasePrimitiveLayer layer)
{
	PrimitiveLayers.push_back(layer);
}
//---------------------------------------------------------------------
void TGBaseViewport::MouseEvent(QMouseEvent* event)
{
	for (TGPrimitiveLayersList::iterator layer = PrimitiveLayers.begin(); layer != PrimitiveLayers.end(); ++layer)
	{
		TG3DRay pick_vector;
		QSize viewport = QSize(ViewPort.width(), ViewPort.height());
		(*layer)->CalcPickVector(event->x() - ViewPort.x(), event->y() - ViewPort.y(), pick_vector, viewport);
		(*layer)->MouseEvent(event, pick_vector);
	}
}