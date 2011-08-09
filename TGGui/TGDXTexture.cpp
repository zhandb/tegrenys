#include "TGDXTexture.h"

//---------------------------------------------------------------------
TGDXTexture::TGDXTexture(PTGBaseTextureDescriptor& descr) : TGBaseTexture(descr)
{
	Texture = NULL;
	Device = NULL;
}

//---------------------------------------------------------------------
TGDXTexture::~TGDXTexture()
{
	if (Texture)
	{
		Texture->Release();
		Texture = NULL;
	}
}

//---------------------------------------------------------------------
void TGDXTexture::SetTextureData32(QSize size, DWORD pitch, BYTE* data)
{

}