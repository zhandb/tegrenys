#include "TGBasePolygon.h"
#include "TGBasePrimitivePainter.h"
//---------------------------------------------------------------------
TGBasePolygon::TGBasePolygon(PTGBasePrimitiveLayer owner, TGPolygonF polygon, bool is_solid /*= false*/) : TGBasePrimitive(owner)
{
	Polygon = polygon;
	IsSolid = is_solid;
}
//---------------------------------------------------------------------
int TGBasePolygon::Add(TGBasePrimitivePainter* painter)
{
	//SetCanvasSize(painter->GetCanvasSize());

	int primitives_count = 1;

	if (CheckFlag(IsVisible))
	{
		if (IsSolid)
			painter->AddSolidPolygon(Pos, Polygon, Color);
		else
			painter->AddPolyline(Pos, Polygon, Color);

		primitives_count += TGBasePrimitive::Add(painter);
	}

	return primitives_count;
}
//---------------------------------------------------------------------
bool TGBasePolygon::Contains(TGPointF point)
{
	//return Polygon.containsPoint(point - Pos, Qt::WindingFill);
	return true;
}
//---------------------------------------------------------------------
void TGBasePolygon::SetPolygon(TGPolygonF polygon)
{

}