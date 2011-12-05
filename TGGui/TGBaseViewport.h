#ifndef TGBaseViewport_h__
#define TGBaseViewport_h__
//---------------------------------------------------------------------
#include <QtCore/QRect>
#include <QtGui/QColor>
#include "TGBasePrimitiveLayer.h"
#include "TGDataObject.h"
//---------------------------------------------------------------------
#define TGViewPortRect QRect
#define TGViewPortColor QColor
//---------------------------------------------------------------------
class TGBaseViewport : public TGModule
{
	Q_OBJECT
public:
	TGBaseViewport(UID module_uid, PTGSystem system);
	~TGBaseViewport();
	virtual void ApplyViewPort();

	void MouseEvent(QMouseEvent* event);
	void SetViewport(int left_margin, int top_margin, int right_margin, int bottom_margin, QSize size, TGViewPortColor color, int anchors);
	void ParentSizeChanged(QSize size);
public:
	enum AnchorTypes{Left = 1, Right = 2, Top = 4, Bottom = 8};

protected:
	TGViewPortRect ViewPort;
	TGViewPortColor Color;
	int LeftMargin;
	int TopMargin;
	int RightMargin;
	int BottomMargin;
	QSize Size;
	int Anchors;
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGBaseViewport)
//---------------------------------------------------------------------
typedef std::map<UID, PTGModule> TGBaseViewportsMap;
//---------------------------------------------------------------------

#endif // TGBaseViewport_h__