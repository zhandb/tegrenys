#ifndef TGDXTexture_h__
#define TGDXTexture_h__

#include "TGBaseTexture.h"
#include <d3dx9.h>
struct TGDXTexture : public TGBaseTexture
{
public:
	TGDXTexture(PTGBaseTextureDescriptor& descr);

	~TGDXTexture();

	virtual void SetTextureData32(QSize size, DWORD pitch, BYTE* data);
public:
	IDirect3DTexture9* Texture;
	IDirect3DDevice9* Device;
};

#endif // TGDXTexture_h__