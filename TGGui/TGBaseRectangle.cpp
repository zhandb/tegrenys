//---------------------------------------------------------------------
#include "TGBaseRectangle.h"
//---------------------------------------------------------------------
TGBaseRectangle::TGBaseRectangle(bool is_solid) : TGBasePolygon(TGPolygonF(), is_solid)
{
}
//---------------------------------------------------------------------
TGBaseRectangle::~TGBaseRectangle()
{

}

void TGBaseRectangle::SetSize(QSizeF size)
{
	Size = size;
	if (!IsSolid)
	{
		Polygon.clear();
		Polygon << TGPointF(0, 0, 1.0) << TGPointF(Size.width(), 0, 1.0) << TGPointF(0, Size.height(), 1.0) << TGPointF(Size.width(), Size.height(), 1.0);
	}
	else
	{
		Polygon.clear();
		Polygon.push_back(TGPointF(-size.width() / 2, -size.height() / 2, 0.0));
		Polygon.push_back(TGPointF(size.width() / 2, -size.height() / 2, 0.0));
		Polygon.push_back(TGPointF(-size.width() / 2, size.height() / 2, 0.0));
		Polygon.push_back(TGPointF(size.width() / 2, size.height() / 2, 0.0));
		//Polygon << TGPointF(0, 0, 1.0) << TGPointF(Size.width(), 0, 1.0) << TGPointF(0, Size.height(), 1.0) << TGPointF(Size.width(), Size.height(), 1.0);
	}
}
//---------------------------------------------------------------------
bool TGBaseRectangle::Intersects(TGPointF* intersect_point)
{
	return ((intersect_point->x() >= Polygon[0].x()) 
		&& (intersect_point->x() <= Polygon[3].x())
		&& (intersect_point->y() >= Polygon[0].y())
		&& (intersect_point->y() <= Polygon[3].y()));
}
//-----------------------------------------------------------------------------

