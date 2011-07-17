#ifndef TGBasePrimitiveLayer_h__
#define TGBasePrimitiveLayer_h__

#include <QRect>
#include <QList>

#include "TGRefCounter.h"
#include "TGBasePrimitive.h"
#include "TGDataObject.h"

struct TG3DPoint
{
	float X;
	float Y;
	float Z;
};

struct TGBasePrimitiveLayerCamera
{	
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

class TGBasePrimitiveLayer : public TGReferenceCounter
{
public:
	TGBasePrimitiveLayer(UID uid);
	~TGBasePrimitiveLayer();
	void SetupProjection(TGBasePrimitiveLayerParams params);
	virtual void SetupCamera(TGBasePrimitiveLayerCamera& camera);
	virtual void SetupViewPort(QSize viewport, bool keep_base_view);
	virtual void ApplyLayer();
	virtual void CalcPickVector(int x, int y, TG3DRay& pick_vector, QSize view_port);
	void MouseEvent(QMouseEvent* event, TG3DRay& pick_vector);

	void BuildPrimitives(TGBasePrimitivePainter* painter);
	int GetPrimitivesCount();
	TGPrimitivesList Primitives; //should be protected
	UID GetUID();
protected:
	TGBasePrimitiveLayerParams Params;
	int PrimitivesCount;
	UID LayerUID;
};

TG_REFC_PTR(TGBasePrimitiveLayer)

typedef QList<PTGBasePrimitiveLayer> TGPrimitiveLayersList;


#endif // TGBasePrimitiveLayer_h__