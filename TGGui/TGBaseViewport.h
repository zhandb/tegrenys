#ifndef TGBaseViewport_h__
#define TGBaseViewport_h__
//---------------------------------------------------------------------
#include <QRect>
#include <QColor>
#include "TGBasePrimitiveLayer.h"
#include "TGDataObject.h"
//---------------------------------------------------------------------
#define TGViewPortRect QRect
#define TGViewPortColor QColor
//---------------------------------------------------------------------

class TGBaseViewport : public TGReferenceCounter
{
public:
	TGBaseViewport(TGViewPortRect view_port, TGViewPortColor color);
	~TGBaseViewport();
	virtual void ApplyViewPort();
	void AddLayer(PTGBasePrimitiveLayer layer);

	void MouseEvent(QMouseEvent* event);
protected:
	TGViewPortRect ViewPort;
	TGViewPortColor Color;
public:
	TGPrimitiveLayersList PrimitiveLayers;
};

TG_REFC_PTR(TGBaseViewport)

typedef QMap<UID, PTGBaseViewport> TGBaseViewportsMap;


#endif // TGBaseViewport_h__