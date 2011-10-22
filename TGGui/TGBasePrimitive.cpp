#include "TGBasePrimitive.h"
#include "TGBasePrimitivePainter.h"
#include <d3dx9math.h>
//---------------------------------------------------------------------
TGBasePrimitive::TGBasePrimitive(UID module_id, PTGModule system) : TGModule(module_id, system)
{
	/*if (owner)
		owner->AddPrimitive(this);*/

	Parent = NULL;
	Flags = None;

	NormalVector.X = 0;
	NormalVector.Y = 0;
	NormalVector.Z = 1;

	ResetWorldTransform();

	MousePicked = false;

	SetFlag(IsVisible);
	SetFlag(UsesDigitalZoom);
	SetFlag(IsMovable);
	SetFlag(AcceptsHoverEvents);
}
//---------------------------------------------------------------------
void TGBasePrimitive::SetPos(TGPointF pos)
{
	Pos = pos;
}
//---------------------------------------------------------------------
void TGBasePrimitive::SetVisible(bool visible, bool apply_to_children /*= true*/)
{
	visible ? SetFlag(IsVisible) : ResetFlag(IsVisible);

	if (apply_to_children)
		for (TGPrimitivesList::iterator child = ChildPrimitives.begin(); child != ChildPrimitives.end(); ++child)
		{
			(*child)->SetVisible(CheckFlag(IsVisible), apply_to_children);
		}
}
//---------------------------------------------------------------------
TGPointF TGBasePrimitive::GetPos()
{
	return Pos;
}
//---------------------------------------------------------------------
void TGBasePrimitive::SetColor(QColor color)
{
	Color = color;
}
//---------------------------------------------------------------------
int TGBasePrimitive::Add(TGBasePrimitivePainter* painter)
{
	return RenderChildPrimitives(painter, &ChildPrimitives);
}
//---------------------------------------------------------------------
void TGBasePrimitive::SetFlag(TGBasePrimitiveFlags flag)
{
	Flags |= flag;
}
//---------------------------------------------------------------------
void TGBasePrimitive::ResetFlag(TGBasePrimitiveFlags flag)
{
	Flags = Flags &~ flag;
}
//---------------------------------------------------------------------
bool TGBasePrimitive::CheckFlag(TGBasePrimitiveFlags flag)
{
	return (Flags & flag) != 0;
}
//---------------------------------------------------------------------
TGBasePrimitive* TGBasePrimitive::GetParent()
{
	return Parent;
}
//---------------------------------------------------------------------
void TGBasePrimitive::FocusInEvent()
{

}
//---------------------------------------------------------------------
void TGBasePrimitive::FocusOutEvent()
{

}
//---------------------------------------------------------------------
void TGBasePrimitive::SetParent(TGBasePrimitive* parent)
{
	Parent = parent;
}
//---------------------------------------------------------------------
int TGBasePrimitive::RenderChildPrimitives(TGBasePrimitivePainter* painter, TGPrimitivesList* primitives)
{
	int primitives_count = primitives->size();

	for (TGPrimitivesList::iterator primitive = primitives->begin(); primitive != primitives->end(); ++primitive)
	{
		(*primitive)->Add(painter);
		primitives_count += (*primitive)->RenderChildPrimitives(painter, &(*primitive)->ChildPrimitives);
	}

	return primitives_count;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void TGBasePrimitive::MouseHoverEvent()
{

}
//---------------------------------------------------------------------
void TGBasePrimitive::MouseLeaveEvent()
{

}
//---------------------------------------------------------------------
void TGBasePrimitive::MoveEvent(TGPointF new_pos)
{

}
//---------------------------------------------------------------------
void TGBasePrimitive::RaisePrimitive()
{
	if (GetParent())
	{
		GetParent()->RaiseChildPrimitive(this);
	}
}
//---------------------------------------------------------------------
TGBasePrimitivePainter* TGBasePrimitive::GetPainter()
{
	TGBasePrimitive* res = this;
	while (res->Parent)
		res = res->Parent;
	return (TGBasePrimitivePainter*)res;
}
//---------------------------------------------------------------------
TGBasePrimitive* TGBasePrimitive::AddChildPrimitive(TGBasePrimitive* primitive)
{
	ChildPrimitives.push_back(primitive);
	primitive->SetParent(this);
	/*if (primitive_uid != UID())
	{
		primitive->PrimitiveUID = primitive_uid;
		GetPainter()->RegisterPrimitive(primitive, primitive_uid);
	}*/
	return primitive;
}
//---------------------------------------------------------------------
void TGBasePrimitive::RaiseChildPrimitive(TGBasePrimitive* primitive)
{
	for (TGPrimitivesList::iterator child = ChildPrimitives.begin(); child != ChildPrimitives.end(); ++child)
	{
		if (primitive == (*child))
		{
			ChildPrimitives.erase(child);
			ChildPrimitives.push_back(primitive);
			break;
		}
	}
}
//---------------------------------------------------------------------
void TGBasePrimitive::ReleaseChildPrimitives()
{
	for (TGPrimitivesList::iterator child = ChildPrimitives.begin(); child != ChildPrimitives.end(); ++child)
	{
		(*child)->ReleaseChildPrimitives();
		delete (*child);
	}

	ChildPrimitives.clear();
}
//---------------------------------------------------------------------
void TGBasePrimitive::RemoveChildPrimitive(TGBasePrimitive* primitive)
{
	for (TGPrimitivesList::iterator child = ChildPrimitives.begin(); child != ChildPrimitives.end(); ++child)
	{
		if (primitive == (*child))
		{
			delete (*child);

			ChildPrimitives.erase(child);
			break;
		}
	}
}
//---------------------------------------------------------------------
TGBasePrimitive::~TGBasePrimitive()
{
	ReleaseChildPrimitives();
	/*if (PrimitiveUID != UID())
	{
		if (GetPainter())
			GetPainter()->UnregisterPrimitive(PrimitiveUID);
	}*/
}
//---------------------------------------------------------------------
bool TGBasePrimitive::MouseEvent(QMouseEvent* event, TG3DRay& pick_ray)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		TGPointF intersection_point;
		CalcIntersectionPoint(&pick_ray, &intersection_point);
		
		if (Intersects(&intersection_point))
		{
			PickPoint = intersection_point;
			MousePicked = true;
		}
	}

	if (event->type() == QEvent::MouseButtonRelease)
	{
		MousePicked = false;
	}

	if (event->type() == QEvent::MouseMove)
	{
			if (MousePicked)
			{
				TGPointF intersection_point;
				CalcIntersectionPoint(&pick_ray, &intersection_point);

				float dx = intersection_point.x() - PickPoint.x();
				float dy = intersection_point.y() - PickPoint.y();

				for (TGPolygonF::iterator point = Polygon.begin(); point != Polygon.end(); ++point)
				{
					(*point).X += dx;
					(*point).Y += dy;
				}

				PickPoint = intersection_point;
			}
	}

	return true;
}
//---------------------------------------------------------------------
bool TGBasePrimitive::Intersects(TGPointF* intersect_point)
{
	return false;
}
//---------------------------------------------------------------------
void TGBasePrimitive::ResetWorldTransform()
{

}
//---------------------------------------------------------------------
TGPointF TGBasePrimitive::TransformVector(TGPointF& vector, TGMatrix4& transform)
{
	float x = vector.x() * transform.m[0][0] + vector.y() * transform.m[0][1] + vector.z() * transform.m[0][2] + transform.m[0][3];
	float y = vector.x() * transform.m[1][0] + vector.y() * transform.m[1][1] + vector.z() * transform.m[1][2] + transform.m[1][3];
	float z = vector.x() * transform.m[2][0] + vector.y() * transform.m[2][1] + vector.z() * transform.m[2][2] + transform.m[2][3];

	return TGPointF(x, y, z, vector.tx(), vector.ty());
}
//---------------------------------------------------------------------
void TGBasePrimitive::TransformPolygon(TGPolygonF& in, TGMatrix4& transform, TGPolygonF& out)
{
	out.clear();
	for (TGPolygonF::iterator point = in.begin(); point != in.end(); ++point)
	{
		out.push_back(TransformVector(*point, transform));
	}
}
//---------------------------------------------------------------------
void TGBasePrimitive::CalcIntersectionPoint(TG3DRay* pick_ray, TGPointF* intersect_point)
{
	TGPointF origin = pick_ray->origin;
	TGPointF direction = pick_ray->direction;

	float dp_start = NormalVector.x() * origin.x() + NormalVector.y() * origin.y() + NormalVector.z() * origin.z();
	float dp_dir = NormalVector.x() * direction.x() + NormalVector.y() * direction.y() + NormalVector.z() * direction.z();

	float plane_d =  - (NormalVector.x() * Polygon[0].x() + NormalVector.y() * Polygon[0].y() + NormalVector.z() * Polygon[0].z());

	float t = - (dp_start + plane_d) /  dp_dir;

	intersect_point->X = origin.x() + direction.x() * t;
	intersect_point->Y = origin.y() + direction.y() * t;
	intersect_point->Z = origin.z() + direction.z() * t;
}