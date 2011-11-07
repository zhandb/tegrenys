#ifndef TGDXTextureManager_h__
#define TGDXTextureManager_h__
//---------------------------------------------------------------------
#include "TGBaseTextureManager.h"
#include <d3d9.h>
//---------------------------------------------------------------------

class TGDXTextureManager : public TGBaseTextureManager
{
public:
	TGDXTextureManager(PTGSystem system);
	~TGDXTextureManager();
	void SetDevice(IDirect3DDevice9* device);
protected:
	virtual void InitTexture(TGBaseTexture* texture);
	virtual void ReleaseTexture(TGBaseTexture* texture);
	virtual TGBaseTexture* CreateTexture(PTGBaseTextureDescriptor& descr);
	virtual void SetTextureImage(TGBaseTexture* texture, QImage* image);
	virtual void SetTextureImage(TGBaseTexture* texture, const uchar* data, const int pitch);

	virtual void InvalidateTexture(TGBaseTexture* texture);

private:
	IDirect3DDevice9* Device;
};
#endif // TGDXTextureManager_h__