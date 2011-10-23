#include "TGBaseViewport.h"
//---------------------------------------------------------------------
TGBaseViewport::TGBaseViewport(UID module_uid, PTGSystem system) : TGModule(module_uid, system)
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
//void TGBaseViewport::AddLayer(UID layer_uid, PTGModule layer)
//{
//	PrimitiveLayers.push_back(layer);
//	LayersMap[layer_uid] = layer;
//}
////---------------------------------------------------------------------
void TGBaseViewport::MouseEvent(QMouseEvent* event)
{
	for (TGModuleList::iterator layer = ChildModules.begin(); layer != ChildModules.end(); ++layer)
	{
		TG3DRay pick_vector;
		QSize viewport = QSize(ViewPort.width(), ViewPort.height());
		TGBasePrimitiveLayer* pl = (TGBasePrimitiveLayer*)&**layer;
		pl->CalcPickVector(event->x() - ViewPort.x(), event->y() - ViewPort.y(), pick_vector, viewport);
		pl->MouseEvent(event, pick_vector);
	}
}
//---------------------------------------------------------------------------
