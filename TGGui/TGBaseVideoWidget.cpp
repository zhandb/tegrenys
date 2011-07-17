#include "TGBaseVideoWidget.h"
#include <QPainter>
//-----------------------------------------------------------------------------

TGBaseVideoWidget::TGBaseVideoWidget(QWidget* parent) : QWidget(parent)
{
	setMouseTracking(true);
}
//-----------------------------------------------------------------------------

TGBaseVideoWidget::~TGBaseVideoWidget()
{
}
//-----------------------------------------------------------------------------

void TGBaseVideoWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(rect(), QBrush(QColor(0, 0, 128)));
}
//---------------------------------------------------------------------
void TGBaseVideoWidget::mousePressEvent(QMouseEvent* event)
{
	PP->MouseEvent(event);
}
//---------------------------------------------------------------------
void TGBaseVideoWidget::mouseReleaseEvent(QMouseEvent* event)
{
	//TGPointF pos = TGPointF(event->pos().x(), event->pos().y());
	PP->MouseEvent(event);
}
//---------------------------------------------------------------------
void TGBaseVideoWidget::mouseMoveEvent(QMouseEvent* event)
{
	//TGPointF pos = TGPointF(event->pos().x(), event->pos().y());
	PP->MouseEvent(event);
}
//---------------------------------------------------------------------
void TGBaseVideoWidget::AddViewPort(UID uid, PTGBaseViewport vp)
{
	PP->AddViewport(uid, vp);
}
//---------------------------------------------------------------------
void TGBaseVideoWidget::SetCurrentViewport(UID uid)
{
	PP->SetCurrentViewport(uid);
}
//---------------------------------------------------------------------
void TGBaseVideoWidget::AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer)
{
	PP->AddLayerToCurrentViewport(layer);
}
//---------------------------------------------------------------------
