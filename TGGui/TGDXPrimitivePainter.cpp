#include "TGDXPrimitivePainter.h"
#include "TGDXTexture.h"
#include "TGDXTextureManager.h"
#include "TGDXPrimitiveLayer.h"
#include "TGDXViewPort.h"
//---------------------------------------------------------------------
TGDXPrimitivePainter::TGDXPrimitivePainter(PTGSystem system) : TGBasePrimitivePainter(system)
{
	Device = NULL;
	DeviceChanged = true;
	AlphaEnabled = false;

	TextureManager = new TGDXTextureManager(system);
	TextureManager->Init();
	AnimationManager->LoadAnimations(TextureManager);

	
	/*PrimitiveLayer = new TGDXPrimitiveLayer();

	params.BaseViewPort = QSize(2, 2);
	params.BaseDistance = 1.0;
	params.MinDistance = 1.0;
	params.MaxDistance = 100.0;

	PrimitiveLayer->SetupProjection(params);

	camera.BasePoint.X = 0.0;
	camera.BasePoint.Y = 0.0;
	camera.BasePoint.Z = 1.0;

	camera.EyePoint.X = -1.8;
	camera.EyePoint.Y = 0.0;
	camera.EyePoint.Z = -2.8;

	PrimitiveLayer->SetupCamera(camera);*/

	//PrimitiveLayers.push_back(PrimitiveLayer);
}
//---------------------------------------------------------------------
TGDXPrimitivePainter::~TGDXPrimitivePainter()
{

}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::AddVertex(TGPointF pos, QColor color)
{
	DWORD rgba = color.rgba();

	TGPrimitiveVertex vertex;

	TGPointF dest_point = pos;

	vertex.color = rgba;
	//vertex.rhw = 1.0f;
	vertex.tu = dest_point.tx();
	vertex.tv = dest_point.ty();

	vertex.x = dest_point.x();
	vertex.y = dest_point.y();
	vertex.z = dest_point.z();

	VertexBuffer.AddVertex(&vertex);
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::Render()
{
	IDirect3DTexture9* current_texture = NULL;

	int primitive_index = 0;

	for (TGBaseViewportsMap::iterator viewport = Viewports.begin(); viewport != Viewports.end(); ++viewport)
	{
		TGDXViewport* vp = (TGDXViewport*)&*viewport->second;
		vp->ApplyViewPort();

		Device->BeginScene();

		if (Device->TestCooperativeLevel() == D3D_OK)
		{
			Device->SetStreamSource(0, VertexBuffer.GetVertexBuffer(), 0, sizeof(TGPrimitiveVertex));
			Device->SetFVF(TGPrimitiveVertex_FVF);
			
			for (TGModuleList::iterator layer = vp->ChildModules.begin(); layer != vp->ChildModules.end(); ++layer)
			{
				TGBasePrimitiveLayer* pl = (TGBasePrimitiveLayer*)&**layer;

				pl->ApplyLayer();

				for (int q = 0; q < pl->GetPrimitivesCount(); ++q)
				{
					if (PrimitiveIndex[primitive_index].AlphaBlendEnabled != AlphaEnabled)
					{
						AlphaEnabled = PrimitiveIndex[primitive_index].AlphaBlendEnabled;
						Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
					}

					TGDXTexture* texture = (TGDXTexture*)PrimitiveIndex[primitive_index].Texture;

					IDirect3DTexture9* next_texture = NULL;

					if (texture)
					{
						if (texture->Descr->TextureType == TGBaseTextureDescriptor::File ||
							texture->Descr->TextureType == TGBaseTextureDescriptor::Video)
						{
							next_texture = texture->Texture;
						}
						else
						{
							if (texture->Descr->TextureType == TGBaseTextureDescriptor::SubTexture)
							{
								TGSubTextureDescriptor* descr = (TGSubTextureDescriptor*)&*texture->Descr;
								next_texture = ((TGDXTexture*)&*descr->parent)->Texture;
							}
						}

						if (next_texture != current_texture)
						{
							current_texture = texture->Texture;
							Device->SetTexture(0, next_texture);
						}
					}


					if (PrimitiveIndex[primitive_index].PrimitiveType == TGPrimitiveType_LineStrip)
						Device->DrawPrimitive(D3DPT_LINESTRIP, PrimitiveIndex[primitive_index].StartIndex, PrimitiveIndex[primitive_index].VerticesCount - 1);

					if (PrimitiveIndex[primitive_index].PrimitiveType == TGPrimitiveType_TriangleList)
						Device->DrawPrimitive(D3DPT_TRIANGLELIST, PrimitiveIndex[primitive_index].StartIndex, PrimitiveIndex[primitive_index].VerticesCount / 3);

					if (PrimitiveIndex[primitive_index].PrimitiveType == TGPrimitiveType_TriangleStrip)
						Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, PrimitiveIndex[primitive_index].StartIndex, PrimitiveIndex[primitive_index].VerticesCount - 2);

					primitive_index++;

				}
			}

		}
		Device->EndScene();
	}

	

	if (DeviceChanged)
		DeviceChanged = false;
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::AddPolyline(TGPointF pos, TGPolygonF points, QColor color)
{
	BeginPrimitive(TGPrimitiveType_LineStrip);
	for (TGPolygonF::iterator point = points.begin(); point != points.end(); ++point)
		AddVertex(*point + pos, color);
	EndPrimitive();
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::AddSolidPolygon(TGPointF pos, TGPolygonF points, QColor color)
{
	BeginPrimitive(TGPrimitiveType_TriangleStrip);
	for (TGPolygonF::iterator point = points.begin(); point != points.end(); ++point)
		AddVertex(*point + pos, color);
	EndPrimitive();
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::AddTexturedRectangle(TGPolygonF points, TGBaseTexture* texture)
{
	BeginPrimitive(TGPrimitiveType_TriangleStrip, texture);

	//TGPolygonF polygon = TGPolygonF(TGRectF(pos, size));

	if (texture)
	{
		/*if (!dx_texture->Texture)
			if (!dx_texture->UseExternalImage)
			{
				InitTexture(dx_texture, dx_texture->Image.size());
			}*/

			QRect texture_rect = QRect(QPoint(0, 0), texture->Descr->texture_size);

			if (texture->Descr->TextureType == TGBaseTextureDescriptor::SubTexture)
			{
				TGSubTextureDescriptor* descr = (TGSubTextureDescriptor*)&*texture->Descr;

				QRect sub_texture_rect = descr->sub_texture_rect;
				texture = descr->parent;
				texture_rect = QRect(QPoint(0, 0), descr->texture_size);

				TGDXTexture* dx_texture = (TGDXTexture*)texture;

				float TLeft = dx_texture->Descr->TX * sub_texture_rect.left() / texture_rect.width();
				float TTop = dx_texture->Descr->TY * sub_texture_rect.top() / texture_rect.height();

				float TRight = dx_texture->Descr->TX * sub_texture_rect.right() / texture_rect.width();
				float TBottom = dx_texture->Descr->TY * sub_texture_rect.bottom() / texture_rect.height();

				/*AddVertex(polygon[0], QColor(255, 255, 255, 255), 0, 0);
				AddVertex(polygon[1], QColor(255, 255, 255), dx_texture->TX, 0);
				AddVertex(polygon[3], QColor(255, 255, 255), 0, dx_texture->TY);
				AddVertex(polygon[2], QColor(255, 255, 255), dx_texture->TX, dx_texture->TY);*/

				//AddVertex(points[0], QColor(255, 255, 255), TLeft, TBottom);
				//AddVertex(points[1], QColor(255, 255, 255), TRight, TBottom);
				//AddVertex(points[2], QColor(255, 255, 255, 255), TLeft, TTop);
				//AddVertex(points[3], QColor(255, 255, 255), TRight, TTop);
			}
			
			
	}

	EndPrimitive();
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::AddPolygon(TGPolygonF points, bool solid, TGBaseTexture* texture)
{
	BeginPrimitive(solid ? TGPrimitiveType_TriangleStrip : TGPrimitiveType_LineStrip, texture);
	
	AddVertex(points[0], QColor(255, 255, 255));
	AddVertex(points[1], QColor(255, 255, 255));
	AddVertex(points[2], QColor(255, 255, 255, 255));
	AddVertex(points[3], QColor(255, 255, 255));

	EndPrimitive();
}

//---------------------------------------------------------------------

TGBaseTexture* TGDXPrimitivePainter::CreateBaseTexture()
{
	PTGBaseTextureDescriptor descr = new TGBaseTextureDescriptor();
	return new TGDXTexture(descr);
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::BeforeBuildPrimitives()
{
	VertexBuffer.ClearVertexBuffer();

	PrimitivesCount = 0;

	if (Device)
		VertexBuffer.Lock();
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::AfterBuildPrimitives()
{
	VertexBuffer.Unlock();
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::BeginPrimitive(TGPrimitiveTypes PrimitiveType /*= TGPrimitiveType_LineStrip*/, TGBaseTexture* Texture /*= NULL*/, bool alpha_enabled /*= true*/)
{
	TGBasePrimitivePainter::BeginPrimitive(PrimitiveType, Texture);
	PrimitiveIndex[PrimitivesCount].StartIndex = VertexBuffer.GetVerticesCount();
	PrimitiveIndex[PrimitivesCount].Texture = Texture;
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::EndPrimitive()
{
	PrimitiveIndex[PrimitivesCount].VerticesCount = VertexBuffer.GetVerticesCount() - PrimitiveIndex[PrimitivesCount].StartIndex;
	TGBasePrimitivePainter::EndPrimitive();
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::CleanPrimitives()
{
	VertexBuffer.ClearVertexBuffer();
	TGBasePrimitivePainter::CleanPrimitives();
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::CopyRGB32DataToTexture(TGBaseTexture* texture, QSize size, DWORD pitch, BYTE* data)
{
	if (texture)
	{
		TGDXTexture* dx_texture = (TGDXTexture*)texture;

		/*if (DeviceChanged || dx_texture->TextureSize != size || dx_texture->Device != Device)
			InitTexture(texture, size);*/


		D3DLOCKED_RECT LR;
		if (dx_texture && dx_texture->Texture)
		{
			dx_texture->Texture->LockRect(0, &LR, NULL, D3DLOCK_NO_DIRTY_UPDATE);
			if (LR.pBits)
			{
				BYTE* Dest = (BYTE*)LR.pBits;

				const BYTE* Src = data;

				for (int i = 0; i < size.height(); i++)
				{
					memcpy(Dest, Src, pitch < LR.Pitch ? pitch : LR.Pitch);
					Dest += LR.Pitch;
					Src += size.width() * 4;
				}
				dx_texture->Texture->UnlockRect(0);
				//dx_texture->ImageChanged = false;
			}
		}
	}
}
//---------------------------------------------------------------------

void TGDXPrimitivePainter::SetDevice(IDirect3DDevice9* device, QSize size)
{
	Device = device;
	AlphaEnabled = false;
	VertexBuffer.SetD3DDevice(device);
	DeviceChanged = true;
	((TGDXTextureManager*)&*TextureManager)->SetDevice(device);

	for (TGBaseViewportsMap::iterator viewport = Viewports.begin(); viewport != Viewports.end(); ++viewport)
	{
		((TGDXViewport*)&*viewport->second)->SetDevice(device);
	}
}
//---------------------------------------------------------------------
void TGDXPrimitivePainter::InverseMatrix(TGMatrix4& matrix, TGMatrix4& inv_matrix)
{
	D3DXMATRIX m;
	m._11 = matrix.m[0][0]; m._12 = matrix.m[0][1]; m._13 = matrix.m[0][2]; m._14 = matrix.m[0][3];
	m._21 = matrix.m[1][0]; m._22 = matrix.m[1][1]; m._23 = matrix.m[1][2]; m._24 = matrix.m[1][3];
	m._31 = matrix.m[2][0]; m._32 = matrix.m[2][1]; m._33 = matrix.m[2][2]; m._34 = matrix.m[2][3];
	m._41 = matrix.m[3][0]; m._42 = matrix.m[3][1]; m._43 = matrix.m[3][2]; m._44 = matrix.m[3][3];

	D3DXMATRIX* res = D3DXMatrixInverse(&m, 0, &m);

	inv_matrix.m[0][0] = m._11; inv_matrix.m[0][1] = m._12; inv_matrix.m[0][2] = m._13; inv_matrix.m[0][3] = m._14;
	inv_matrix.m[1][0] = m._21; inv_matrix.m[1][1] = m._22; inv_matrix.m[1][2] = m._23; inv_matrix.m[1][3] = m._24;
	inv_matrix.m[2][0] = m._31; inv_matrix.m[2][1] = m._32; inv_matrix.m[2][2] = m._33; inv_matrix.m[2][3] = m._34;
	inv_matrix.m[3][0] = m._41; inv_matrix.m[3][1] = m._42; inv_matrix.m[3][2] = m._43; inv_matrix.m[3][3] = m._44;
}