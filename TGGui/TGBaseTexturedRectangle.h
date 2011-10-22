#ifndef TGBaseTexturedRectangle_h__
#define TGBaseTexturedRectangle_h__

#include "TGBaseRectangle.h"
#include "TGSystemTypes.h"

class TGBaseTexturedRectangle : public TGBaseRectangle
{
public:
	TGBaseTexturedRectangle(UID module_id, PTGModule system, UID texture_id);
	~TGBaseTexturedRectangle();
	virtual int Add(TGBasePrimitivePainter* painter);
private:
	PTGBaseTexture Texture;
	UID TextureID;
};

#endif // TGBaseTexturedRectangle_h__