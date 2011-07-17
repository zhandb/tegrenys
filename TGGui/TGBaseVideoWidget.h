#ifndef TGBaseVideoWidget_h__
#define TGBaseVideoWidget_h__

#include <QWidget>
#include "TGBasePrimitivePainter.h"
#include "TGBasePrimitiveLayer.h"

class TGBaseVideoWidget : public QWidget
{
	Q_OBJECT
public:
	TGBaseVideoWidget(QWidget* parent);
	~TGBaseVideoWidget();
	virtual void paintEvent(QPaintEvent* event); 
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	
protected:
	PTGBasePrimitivePainter PP;
public slots:
	void AddViewPort(UID uid, PTGBaseViewport vp);
	void SetCurrentViewport(UID uid);
	void AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer);
};
#endif // TGBaseVideoWidget_h__