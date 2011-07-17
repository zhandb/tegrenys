#include "TGDXTextureManager.h"
#include "TGDXTexture.h"
//---------------------------------------------------------------------
TGDXTextureManager::TGDXTextureManager()
{
	Device = NULL;
}
//---------------------------------------------------------------------
TGDXTextureManager::~TGDXTextureManager()
{

}
//---------------------------------------------------------------------
void TGDXTextureManager::InitTexture(TGBaseTexture* texture)
{
	TGDXTexture* dx_texture = (TGDXTexture*)texture;

	if (dx_texture->Device != Device)
	{
		ReleaseTexture(texture);
		if (Device)
		{
			if (texture->Descr.file_name.length())
			{
				QImage image(texture->Descr.file_name);
				if (image.format() != QImage::Format_ARGB32)
					image = image.convertToFormat(QImage::Format_ARGB32);

				UINT tmp_w = image.width();
				UINT tmp_h = image.height();
				D3DFORMAT format = D3DFMT_A8R8G8B8;
				D3DXCheckTextureRequirements(Device, &tmp_w, &tmp_h, NULL, D3DUSAGE_DYNAMIC, &format, D3DPOOL_DEFAULT);

				dx_texture->TX = double(image.width()) / double(tmp_w);
				dx_texture->TY = double(image.height()) / double(tmp_h);

				D3DXCreateTexture(Device,
					tmp_w, tmp_h,
					0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
					&dx_texture->Texture);

				SetTextureImage(dx_texture, &image);
			}
			else
			{
				UINT tmp_w = texture->Descr.texture_size.width();
				UINT tmp_h = texture->Descr.texture_size.height();
				D3DFORMAT format = D3DFMT_A8R8G8B8;
				D3DXCheckTextureRequirements(Device, &tmp_w, &tmp_h, NULL, D3DUSAGE_DYNAMIC, &format, D3DPOOL_DEFAULT);

				dx_texture->TX = double(texture->Descr.texture_size.width()) / double(tmp_w);
				dx_texture->TY = double(texture->Descr.texture_size.height()) / double(tmp_h);

				D3DXCreateTexture(Device,
					tmp_w, tmp_h,
					0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
					&dx_texture->Texture);
			}

			dx_texture->Device = Device;
		}
	}
}
//---------------------------------------------------------------------
void TGDXTextureManager::SetDevice(IDirect3DDevice9* device)
{
	Device = device;
	InitTextures();
}
//---------------------------------------------------------------------
void TGDXTextureManager::ReleaseTexture(TGBaseTexture* texture)
{
	if (texture)
	{
		TGDXTexture* dx_texture = (TGDXTexture*)texture;
		if (dx_texture->Texture)
		{
			dx_texture->Texture->Release();
			dx_texture->Texture = NULL;
		}
	}
}
//---------------------------------------------------------------------
TGBaseTexture* TGDXTextureManager::CreateTexture(TGBaseTextureDescriptor& descr)
{
	return new TGDXTexture(descr);
}
//---------------------------------------------------------------------
void TGDXTextureManager::SetTextureImage(TGBaseTexture* texture, QImage* image)
{
	D3DLOCKED_RECT LR;
	TGDXTexture* dx_texture = (TGDXTexture*)texture;

	if (texture && dx_texture->Texture)
	{
		dx_texture->Texture->LockRect(0, &LR, NULL, D3DLOCK_NO_DIRTY_UPDATE);
		if (LR.pBits)
		{
			BYTE* Dest = (BYTE*)LR.pBits;

			const BYTE* Src = image->bits();

			unsigned int image_pitch = image->width() * 4;

			for (int i = 0; i < image->height(); i++)
			{
				memcpy(Dest, Src, image_pitch < LR.Pitch ? image_pitch : LR.Pitch);
				Dest += LR.Pitch;
				Src += image_pitch;
			}
			dx_texture->Texture->UnlockRect(0);
		}
	}
}
//---------------------------------------------------------------------
void TGDXTextureManager::SetTextureImage(TGBaseTexture* texture, const uchar* data, const int pitch)
{
	D3DLOCKED_RECT LR;
	TGDXTexture* dx_texture = (TGDXTexture*)texture;

	if (texture && dx_texture->Texture)
	{
		dx_texture->Texture->LockRect(0, &LR, NULL, D3DLOCK_NO_DIRTY_UPDATE);
		if (LR.pBits)
		{
			BYTE* Dest = (BYTE*)LR.pBits;

			const BYTE* Src = data;

			unsigned int image_pitch = pitch;

			for (int i = 0; i < texture->Descr.texture_size.height(); i++)
			{
				memcpy(Dest, Src, image_pitch < LR.Pitch ? image_pitch : LR.Pitch);
				Dest += LR.Pitch;
				Src += image_pitch;
			}
			dx_texture->Texture->UnlockRect(0);
		}
	}
}
//---------------------------------------------------------------------
void TGDXTextureManager::InvalidateTexture(TGBaseTexture* texture)
{
	TGDXTexture* dx_texture = (TGDXTexture*)texture;
	dx_texture->Device = NULL;
	InitTextures();
}