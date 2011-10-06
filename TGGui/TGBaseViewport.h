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
	TGBaseViewport(TGDataObject& config);
	~TGBaseViewport();
	virtual void ApplyViewPort();
	void AddLayer(UID layer_uid, PTGBasePrimitiveLayer layer);

	void MouseEvent(QMouseEvent* event);
protected:
	TGViewPortRect ViewPort;
	TGViewPortColor Color;
public:
	TGPrimitiveLayersList PrimitiveLayers;
	TGPrimitiveLayersMap LayersMap;
};

TG_REFC_PTR(TGBaseViewport)

typedef std::map<UID, PTGBaseViewport> TGBaseViewportsMap;


#endif // TGBaseViewport_h__