#include "TGBasePrimitiveLayer.h"
#include "TGBaseTexturedRectangle.h"
#include "TGVideoRectangle.h"
//---------------------------------------------------------------------
TGBasePrimitiveLayer::TGBasePrimitiveLayer(UID module_id, PTGSystem system) : TGModule(module_id, system)
{
	PrimitivesCount = 0;

	/*TGBaseTexturedRectangle* p = new TGBaseTexturedRectangle("{CCD31F99-7DA9-4afd-B524-A4AA35C87EBD}", System, "{8BC0D4A6-4BBA-431c-83CA-3357D87CF21A}");
	p->SetColor(QColor("red"));
	p->SetSize(QSizeF(1, 1));
	p->SetPos(TGPointF(-1, -0.5, 0.0));*/


	/*TGVideoRectangle* p2 = new TGVideoRectangle(layer);
	PTGBasePrimitive pp2 = p2;
	p2->SetSize(QSizeF(3, 2));
	p2->SetPos(TGPointF(-200, -0.5, -0.1));*/
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

	for (TGModuleList::iterator primitive = ChildModules.begin(); primitive != ChildModules.end(); ++primitive)
	{
		TGBasePrimitive* p = (TGBasePrimitive*)&**primitive;

		PrimitivesCount += p->Add(painter);
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
	for (TGModuleList::iterator primitive = ChildModules.begin(); primitive != ChildModules.end(); ++primitive)
	{
		TGBasePrimitive* p = (TGBasePrimitive*)&**primitive;
		p->MouseEvent(event, pick_vector);
	}
}
//---------------------------------------------------------------------------

void TGBasePrimitiveLayer::AddPrimitive(PTGBasePrimitive primitive)
{
	//Primitives.push_back(primitive);
}