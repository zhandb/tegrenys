#ifndef TGBasePolygon_h__
#define TGBasePolygon_h__

#include "TGBasePrimitive.h"

class TGBasePolygon : public TGBasePrimitive
{
public:
	TGBasePolygon(UID module_id, PTGModule system, TGPolygonF polygon, bool is_solid = false);
	virtual int Add(TGBasePrimitivePainter* painter);
	virtual bool Contains(TGPointF point);
	void SetPolygon(TGPolygonF polygon);

protected:
	bool IsSolid;
};

#endif // TGBasePolygon_h__