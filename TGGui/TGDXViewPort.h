#ifndef TGDXViewPort_h__
#define TGDXViewPort_h__
#include "TGBaseViewport.h"
#include <d3d9.h>

class TGDXViewport : public TGBaseViewport
{
public:
	TGDXViewport(TGDataObject& config);
	~TGDXViewport();
	void SetDevice(IDirect3DDevice9* device);
	virtual void ApplyViewPort();
private:
	IDirect3DDevice9* Device;
};

#endif // TGDXViewPort_h__