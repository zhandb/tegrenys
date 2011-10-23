#ifndef TGDXPrimitiveLayer_h__
#define TGDXPrimitiveLayer_h__

#include "TGBasePrimitiveLayer.h"
#include <d3dx9math.h>


class TGDXPrimitiveLayer : public TGBasePrimitiveLayer
{
public:
	TGDXPrimitiveLayer(UID module_id, PTGSystem system);
	~TGDXPrimitiveLayer();
	virtual void SetupViewPort(QSize viewport, bool keep_base_view);
	virtual void SetupCamera(TGBasePrimitiveLayerCamera& camera);
	void SetDevice(IDirect3DDevice9* device, QSize viewport, bool keep_base_view);
	virtual void ApplyLayer();
	void CalcPickVector(int x, int y, TG3DRay& pick_vector, QSize view_port);
private:
	D3DXMATRIX ProjectionMatrix;
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX InvViewMatrix;

	IDirect3DDevice9* D3DDevice;
	//QSize ViewPort;
};
#endif // TGDXPrimitiveLayer_h__