#ifndef TGDXVideoWidget_h__
#define TGDXVideoWidget_h__

#include "TGBaseVideoWidget.h"
#include "d3d9.h"
#include <QtCore\QTime>
#include "TGDXPrimitivePainter.h"
#include "TGDXTextureManager.h"

class TGDXVideoWidget : public TGBaseVideoWidget
{
public:
	TGDXVideoWidget(PTGSystem system);
	~TGDXVideoWidget();
	//virtual void AddViewport(UID uid, TGDataObject& config);
	//virtual void AddLayer(UID viewport_uid, UID layer_uid, TGDataObject& config);
private:
	IDirect3D9* D3D;
	IDirect3DDevice9* D3DDevice;
	HWND WindowHandle;
	bool ReInitRequired;
	QTime ReInitTimer;
	TGBaseTexture* video;	

private:
	void InitDevice();
	void DeInitDevice();
	virtual void timerEvent(QTimerEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
	void Rendering();
};
#endif // TGDXVideoWidget_h__