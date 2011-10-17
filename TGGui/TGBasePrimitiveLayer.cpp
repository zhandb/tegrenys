#include "TGBasePrimitiveLayer.h"
#include "TGBaseTexturedRectangle.h"
//---------------------------------------------------------------------
TGBasePrimitiveLayer::TGBasePrimitiveLayer(UID module_id, PTGModule module) : TGModule(module_id, module)
{
	PrimitivesCount = 0;

	TGBaseTexturedRectangle* p = new TGBaseTexturedRectangle(this, "{8BC0D4A6-4BBA-431c-83CA-3357D87CF21A}");
	p->SetColor(QColor("red"));
	p->SetSize(QSizeF(1, 1));
	p->SetPos(TGPointF(-1, -0.5, 0.0));
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

void TGBasePrimitiveLayer::MouseEvent(QMouseEvent* event, TG3DRay& pick_vector)
{
	for (TGPrimitivesList::iterator primitive = Primitives.begin(); primitive != Primitives.end(); ++primitive)
	{
		(*primitive)->MouseEvent(event, pick_vector);
	}
}
//---------------------------------------------------------------------------

void TGBasePrimitiveLayer::AddPrimitive(PTGBasePrimitive primitive)
{
	Primitives.push_back(primitive);
}