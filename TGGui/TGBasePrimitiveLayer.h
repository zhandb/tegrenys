#ifndef TGBasePrimitiveLayer_h__
#define TGBasePrimitiveLayer_h__

#include <QtCore\QRect>
#include <QtCore\QList>

#include "TGRefCounter.h"
#include "TGBasePrimitive.h"
//#include "TGDataObject.h"
#include "TGSystemTypes.h"

struct TG3DPoint
{
	float X;
	float Y;
	float Z;

	TG3DPoint(){};
	TG3DPoint(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};

class TGBasePrimitiveLayerCameraAnimation
{
public:
	enum Type{None, Linear};
	float FinishValue;
	ULONG TimeLength;
public:
	float GetValue(float time_value)
	{

	}
};

class TGBasePrimitiveLayerCamera
{	
public:
	enum CoordsIndex{BaseX, BaseY, BaseZ, EyeX, EyeY, EyeZ};
	float GetPoint(CoordsIndex index)
	{
		switch (index)
		{
		case BaseX : return BasePoint.X;
		case BaseY: return BasePoint.Y;
		case BaseZ: return BasePoint.Z;
		case EyeX:   return EyePoint.X;
		case EyeY:  return EyePoint.Y;
		case EyeZ:  return EyePoint.Z;
		}
	};

	void SetBasePoint(const TG3DPoint& base_point);
	void SetEyePoint(const TG3DPoint& eye_point);
private:
	TGBasePrimitiveLayerCameraAnimation Animations[6];
	TG3DPoint EyePoint;
	TG3DPoint BasePoint;
};

struct TGBasePrimitiveLayerParams
{
	QSize BaseViewPort;
	float BaseDistance;
	float MinDistance;
	float MaxDistance;
};

class TGBasePrimitiveLayer : public TGModule
{
	Q_OBJECT
public:
	TGBasePrimitiveLayer(UID module_id, PTGSystem system);
	~TGBasePrimitiveLayer();
	void SetupProjection(TGBasePrimitiveLayerParams params);
	virtual void SetupCamera(TGBasePrimitiveLayerCamera& camera);
	virtual void SetupViewPort(QSize viewport, bool keep_base_view);
	virtual void ApplyLayer();
	virtual void CalcPickVector(int x, int y, TG3DRay& pick_vector, QSize view_port);
	void MouseEvent(QMouseEvent* event, TG3DRay& pick_vector);

	void BuildPrimitives(TGBasePrimitivePainter* painter);
	int GetPrimitivesCount();
	
	void AddPrimitive(PTGBasePrimitive primitive);

protected:
	//TGPrimitivesList Primitives; //should be protected
	TGBasePrimitiveLayerParams Params;
	int PrimitivesCount;
};

TG_REFC_PTR(TGBasePrimitiveLayer)

//typedef std::list<PTGModule> TGPrimitiveLayersList;
//typedef std::map<UID, PTGModule> TGPrimitiveLayersMap;


#endif // TGBasePrimitiveLayer_h__