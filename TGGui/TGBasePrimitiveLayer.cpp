#include "TGBasePrimitiveLayer.h"
//---------------------------------------------------------------------
TGBasePrimitiveLayer::TGBasePrimitiveLayer(UID uid)
{
	PrimitivesCount = 0;
	LayerUID = uid;
}
//---------------------------------------------------------------------
TGBasePrimitiveLayer::~TGBasePrimitiveLayer()
{

}
//---------------------------------------------------------------------
void TGBasePrimitiveLayer::SetupProjection(TGBasePrimitiveLayerParams params)
{
	Params = params;
	ApplyLayer();
}
//---------------------------------------------------------------------
void TGBasePrimitiveLayer::SetupViewPort(QSize viewport, bool keep_base_view)
{
	
}
//---------------------------------------------------------------------
void TGBasePrimitiveLayer::ApplyLayer()
{

}
//---------------------------------------------------------------------
void TGBasePrimitiveLayer::SetupCamera(TGBasePrimitiveLayerCamera& camera)
{
}
//---------------------------------------------------------------------
void TGBasePrimitiveLayer::CalcPickVector(int x, int y, TG3DRay& pick_vector, QSize view_port)
{

}

//---------------------------------------------------------------------
void TGBasePrimitiveLayer::BuildPrimitives(TGBasePrimitivePainter* painter)
{
	PrimitivesCount = 0;

	for (TGPrimitivesList::iterator primitive = Primitives.begin(); primitive != Primitives.end(); ++primitive)
	{
		PrimitivesCount += (*primitive)->Add(painter);
	}
}
//---------------------------------------------------------------------
int TGBasePrimitiveLayer::GetPrimitivesCount()
{
	return PrimitivesCount;
}
//---------------------------------------------------------------------
UID TGBasePrimitiveLayer::GetUID()
{
	return LayerUID;
}
//---------------------------------------------------------------------
void TGBasePrimitiveLayer::MouseEvent(QMouseEvent* event, TG3DRay& pick_vector)
{
	for (TGPrimitivesList::iterator primitive = Primitives.begin(); primitive != Primitives.end(); ++primitive)
	{
		(*primitive)->MouseEvent(event, pick_vector);
	}
}