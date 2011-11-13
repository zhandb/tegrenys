#include "TGBaseViewport.h"
//---------------------------------------------------------------------
TGBaseViewport::TGBaseViewport(UID module_uid, PTGSystem system) : TGModule(module_uid, system)
{
	//Color = config.Attribute("Color").value<QColor>();
	Anchors = 0;
	SetViewport(10, 10, 10, 10, QSize(400, 300), QColor("darkblue"), 0);
}
//---------------------------------------------------------------------
TGBaseViewport::~TGBaseViewport()
{

}
//---------------------------------------------------------------------
void TGBaseViewport::ApplyViewPort()
{

}
//---------------------------------------------------------------------
//void TGBaseViewport::AddLayer(UID layer_uid, PTGModule layer)
//{
//	PrimitiveLayers.push_back(layer);
//	LayersMap[layer_uid] = layer;
//}
////---------------------------------------------------------------------
void TGBaseViewport::MouseEvent(QMouseEvent* event)
{
	for (TGModuleList::iterator layer = ChildModules.begin(); layer != ChildModules.end(); ++layer)
	{
		TG3DRay pick_vector;
		QSize viewport = QSize(ViewPort.width(), ViewPort.height());
		TGBasePrimitiveLayer* pl = (TGBasePrimitiveLayer*)&**layer;
		pl->CalcPickVector(event->x() - ViewPort.x(), event->y() - ViewPort.y(), pick_vector, viewport);
		pl->MouseEvent(event, pick_vector);
	}
}
//---------------------------------------------------------------------------

void TGBaseViewport::SetViewport(int left_margin, int top_margin, int right_margin, int bottom_margin, QSize size, TGViewPortColor color, int anchors)
{
	Anchors = anchors;
	Color = color;
	LeftMargin = left_margin;
	RightMargin = right_margin;
	TopMargin = top_margin;
	BottomMargin = bottom_margin;
	Size = size;
}
//---------------------------------------------------------------------------

void TGBaseViewport::ParentSizeChanged(QSize parent_size)
{
	ViewPort.setSize(Size);
	ViewPort.moveCenter(QPoint(parent_size.width() / 2, parent_size.height() / 2));

	if (Anchors & Left)
		ViewPort.setLeft(0 + LeftMargin);

	if (Anchors & Right)
	{
		if (Anchors & Left)
			ViewPort.setRight(parent_size.width() - RightMargin);
		else
			ViewPort.moveRight(parent_size.width() - RightMargin);
	}

	if (Anchors & Top)
		ViewPort.setTop(0 + TopMargin);

	if (Anchors & Bottom)
	{
		if (Anchors & Top)
			ViewPort.setBottom(parent_size.height() - BottomMargin);
		else
			ViewPort.moveBottom(parent_size.height() - BottomMargin);
	}
}
//---------------------------------------------------------------------------
