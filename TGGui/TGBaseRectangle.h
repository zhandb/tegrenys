#ifndef TGBaseRectangle_h__
#define TGBaseRectangle_h__

#include "TGBasePolygon.h"

class TGBaseRectangle : public TGBasePolygon
{
public:
	TGBaseRectangle(bool is_solid);
	~TGBaseRectangle();
	void SetSize(QSizeF size);
	virtual bool Intersects(TGPointF* intersect_point);

protected:
	QSizeF Size;
};
#endif // TGBaseRectangle_h__