#ifndef TGBaseTexturedRectangle_h__
#define TGBaseTexturedRectangle_h__

#include "TGBaseRectangle.h"
#include "TGDataObject.h"

class TGBaseTexturedRectangle : public TGBaseRectangle
{
public:
	TGBaseTexturedRectangle(UID texture_id);
	~TGBaseTexturedRectangle();
	virtual int Add(TGBasePrimitivePainter* painter);
private:
	PTGBaseTexture Texture;
	UID TextureID;
};

#endif // TGBaseTexturedRectangle_h__