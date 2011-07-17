#ifndef TGBasePrimitive_h__
#define TGBasePrimitive_h__

#include <QList>
#include <windows.h>
#include <QMouseEvent>
#include <QColor>

#include "TGBaseTexture.h"

enum TGPrimitiveTypes{TGPrimitiveType_LineStrip, TGPrimitiveType_TriangleList, TGPrimitiveType_TriangleStrip};

class TGBasePrimitive;

TG_REFC_PTR(TGBasePrimitive);

typedef QList<PTGBasePrimitive> TGPrimitivesList;

struct TGPointF
{
public:
	TGPointF(){};
	TGPointF(float x, float y, float z, float tx = 0.0f, float ty = 0.0f)
	{
		X = x;
		Y = y;
		Z = z;
		TX = tx;
		TY = ty;
	}

	TGPointF(const TGPointF& p)
	{
		X = p.x();
		Y = p.y();
		Z = p.z();
		TX = p.tx();
		TY = p.ty();
	}

	float x() const 
	{
		return X;
	}

	float y() const
	{
		return Y;
	}

	float z() const
	{
		return Z;
	}

	float tx() const
	{
		return TX;
	}

	float ty() const
	{
		return TY;
	}

	TGPointF operator +(TGPointF p)
	{
		return TGPointF(X + p.x(), Y + p.y(), Z + p.z());
	}

	TGPointF operator +=(TGPointF p)
	{
		return TGPointF(X + p.x(), Y + p.y(), Z + p.z());
	}
public:
	float X;
	float Y;
	float Z;
	float TX;
	float TY;
};

struct TG3DRay
{
	TGPointF origin;
	TGPointF direction;
};



struct TGRectF
{
friend class TGPolygonF;
public:
	TGRectF(TGPointF center, QSizeF size)
	{
		Center = center;
		Size = size;
	}
private:
	TGPointF Center;
	QSizeF Size;
};

struct TGPolygonF : public std::vector<TGPointF> 
{
public:
	TGPolygonF(){};
	TGPolygonF(TGRectF rect)
	{
		push_back(TGPointF(0, 0, 1.0) + rect.Center);
		push_back(TGPointF(rect.Size.width(), 0, 1.0)  + rect.Center);
		push_back(TGPointF(0, rect.Size.height(), 1.0) + rect.Center);
		push_back(TGPointF(rect.Size.width(), rect.Size.height(), 1.0)  + rect.Center);
	}

	TGPolygonF operator <<(TGPointF p)
	{
		push_back(p);
		return *this;
	}
};

struct TGMatrix4 
{
	float m[4][4];
};

struct TGPrimitiveIndexEntry2
{
	int StartIndex;
	int VerticesCount;
	TGBaseTexture* Texture;
	TGPrimitiveTypes PrimitiveType;
	bool AlphaBlendEnabled;
};

class TGBasePrimitive : public TGReferenceCounter
{
public:
	friend class TGBasePrimitivePainter;

	enum TGBasePrimitiveFlags
	{	
		None = 0, 
		IsUnderCursor = 1, 
		AcceptsHoverEvents = 2, 
		IsMouseGrabber = 4, 
		IsMovable = 8, 
		UsingAbsolutePos = 16, 
		UsingAbsoluteSize = 32, 
		IsVisible = 64, 
		UsesDigitalZoom = 128, 
		IsFocusable = 256,
		IgnoreMouseEvents = 512
	};

	enum TGBasePrimitiveAlignment{Align_None = 0, HAlign_Left = 1, HAlign_Right = 2, HAlign_HCenter = 4, VAlign_Top = 8, VAlign_Bottom = 16, VAlign_VCenter = 32};

public:
	TGBasePrimitive();
	virtual void SetPos(TGPointF pos);

	void SetVisible(bool visible, bool apply_to_children = true);

	TGPointF GetPos();
	virtual void SetColor(QColor color);
	virtual int Add(TGBasePrimitivePainter* painter) = 0;
	void ResetWorldTransform();

	TGPointF TransformVector(TGPointF& vector, TGMatrix4& transform);
	void TransformPolygon(TGPolygonF& in, TGMatrix4& transform, TGPolygonF& out);
	
	//ѕрием сообщений мыши от VideoWidget
	bool MouseEvent(QMouseEvent* event, TG3DRay& pick_ray);
	//√раницы объекта в его внутренних координатах, без учета преобразований
	virtual bool Contains(TGPointF point) = 0;
	virtual bool Intersects(TGPointF* intersect_point);
	//ќперации со свойствами примитива
	void SetFlag(TGBasePrimitiveFlags flag);
	void ResetFlag(TGBasePrimitiveFlags flag);
	bool CheckFlag(TGBasePrimitiveFlags flag);
	TGBasePrimitive* GetParent();

	virtual void FocusInEvent();
	virtual void FocusOutEvent();

	virtual void CalcIntersectionPoint(TG3DRay* pick_ray, TGPointF* intersect_point); 

protected:
	void SetParent(TGBasePrimitive* parent);
	//void SetupTransform();
	int RenderChildPrimitives(TGBasePrimitivePainter* painter, TGPrimitivesList* primitives);
	//void ApplyParentTransform();
	//ѕередаетс€ вначале дочерним примитивам, если какой-то примитив возвращает true, то дальше не передаетс€
	virtual void MouseHoverEvent();
	virtual void MouseLeaveEvent();
	virtual void MoveEvent(TGPointF new_pos);
	void RaisePrimitive();
	TGBasePrimitivePainter* GetPainter();
	TGBasePrimitive* AddChildPrimitive(TGBasePrimitive* primitive);
	void RaiseChildPrimitive(TGBasePrimitive* primitive);
	void ReleaseChildPrimitives();
	void RemoveChildPrimitive(TGBasePrimitive* primitive);
	virtual ~TGBasePrimitive();

protected:
	QColor Color;
	DWORD Alignment;
	TGPointF Pos;
	TGBasePrimitive* Parent;
	TGPrimitivesList ChildPrimitives;
	DWORD Flags;
	TGPointF NormalVector;
	TGPolygonF Polygon;
	TGPointF PickPoint;
	bool MousePicked;
};




#endif // TGBasePrimitive_h__