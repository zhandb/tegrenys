#ifndef TGBaseVideoWidget_h__
#define TGBaseVideoWidget_h__
//-----------------------------------------------------------------------------
#include <QtGui/QWidget>
#include "TGBasePrimitivePainter.h"
#include "TGBasePrimitiveLayer.h"
//-----------------------------------------------------------------------------

class TGBaseVideoWidget : public QWidget, public TGReferenceCounter
{
	Q_OBJECT
public:
	TGBaseVideoWidget(PTGSystem system);
	~TGBaseVideoWidget();
	virtual void paintEvent(QPaintEvent* event); 
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void AddViewport(UID uid, PTGModule viewport);
	//virtual void AddLayer(UID viewport_uid, UID layer_uid, TGDataObject& config){};
	
protected:
	PTGBasePrimitivePainter PP;
};
//-----------------------------------------------------------------------------
TG_REFC_PTR(TGBaseVideoWidget)
//-----------------------------------------------------------------------------

#endif // TGBaseVideoWidget_h__