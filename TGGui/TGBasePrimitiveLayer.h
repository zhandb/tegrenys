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