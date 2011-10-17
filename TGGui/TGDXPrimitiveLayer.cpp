#include "TGDXPrimitiveLayer.h"
#include "TGBaseTexturedRectangle.h"
#include "TGAnimatedRectangle.h"
//---------------------------------------------------------------------
TGDXPrimitiveLayer::TGDXPrimitiveLayer(UID module_id, PTGModule module) : TGBasePrimitiveLayer(module_id, module)
{
	D3DDevice = NULL;

	TGBasePrimitiveLayerParams params;
	params.BaseViewPort = QSize(1, 1);
	params.BaseDistance = 1.0;
	params.MinDistance = 0.0;
	params.MaxDistance = 100.0;

	SetupProjection(params);

	TGBasePrimitiveLayerCamera camera;
	camera.BasePoint.X = 0.0;
	camera.BasePoint.Y = 0.0;
	camera.BasePoint.Z = 0.0;

	camera.EyePoint.X = 0.0;
	camera.EyePoint.Y = 0.0;
	camera.EyePoint.Z = -3.0;

	SetupCamera(camera);
}
//---------------------------------------------------------------------
TGDXPrimitiveLayer::~TGDXPrimitiveLayer()
{

}
//---------------------------------------------------------------------
void TGDXPrimitiveLayer::SetupViewPort(QSize viewport, bool keep_base_view)
{
	float field_of_view = Params.BaseViewPort.width();

	if (!keep_base_view)
		field_of_view = Params.BaseViewPort.width() * viewport.height() / Params.BaseViewPort.height();

	float view_angle = atanf(field_of_view * 0.5f / Params.BaseDistance) * 2;

	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix, view_angle, (float)viewport.width() / (float)viewport.height(), Params.MinDistance, Params.MaxDistance);	
	
	/*D3DVIEWPORT9 vp;
	vp.X = 0; 
	vp.Y = 0;
	vp.Width = 500;
	vp.Height = 600;
	vp.MinZ = 0.0;
	vp.MaxZ = 1.0;
	D3DDevice->SetViewport(&vp);*/
}
//---------------------------------------------------------------------
void TGDXPrimitiveLayer::SetDevice(IDirect3DDevice9* device, QSize viewport, bool keep_base_view)
{
	D3DDevice = device;
	SetupViewPort(viewport, keep_base_view);
	ApplyLayer();
}
//---------------------------------------------------------------------
void TGDXPrimitiveLayer::ApplyLayer()
{
	if (D3DDevice)
	{
		D3DDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
		D3DDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);
	}
}
//---------------------------------------------------------------------
void TGDXPrimitiveLayer::SetupCamera(TGBasePrimitiveLayerCamera& camera)
{
	D3DXVECTOR3 base_point = D3DXVECTOR3(camera.BasePoint.X, camera.BasePoint.Y, camera.BasePoint.Z);
	D3DXVECTOR3 eye_point = D3DXVECTOR3(camera.EyePoint.X, camera.EyePoint.Y, camera.EyePoint.Z);
	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixLookAtLH(&ViewMatrix, &eye_point, &base_point, &up);
	D3DXMatrixInverse(&InvViewMatrix, 0, &ViewMatrix);
}
//---------------------------------------------------------------------
void TGDXPrimitiveLayer::CalcPickVector(int x, int y, TG3DRay& pick_vector, QSize view_port)
{
	float px = 0.0f;
	float py = 0.0f;
	D3DXVECTOR3 PickOrigin = D3DXVECTOR3(0, 0, 0);

	px = ((( 2.0f * x) / view_port.width())  - 1.0f) / ProjectionMatrix(0, 0);
	py = (((-2.0f * y) / view_port.height()) + 1.0f) / ProjectionMatrix(1, 1);

	D3DXVECTOR3 PickDirection = D3DXVECTOR3(px, py, 1.0f);

	D3DXVec3TransformCoord(&PickOrigin, &PickOrigin, &InvViewMatrix);
	D3DXVec3TransformNormal(&PickDirection, &PickDirection, &InvViewMatrix);
	D3DXVec3Normalize(&PickDirection, &PickDirection);

	pick_vector.origin.X = PickOrigin.x;
	pick_vector.origin.Y = PickOrigin.y;
	pick_vector.origin.Z = PickOrigin.z;

	pick_vector.direction.X = PickDirection.x;
	pick_vector.direction.Y = PickDirection.y;
	pick_vector.direction.Z = PickDirection.z;

}