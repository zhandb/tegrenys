#ifndef TGAnimatedRectangle_h__
#define TGAnimatedRectangle_h__
//---------------------------------------------------------------------
#include "TGBaseTexturedRectangle.h"
#include "TGAnimationManager.h"
//---------------------------------------------------------------------
class TGAnimatedRectangle : public TGBaseRectangle
{
public:
	TGAnimatedRectangle(UID module_id, PTGSystem system);
	~TGAnimatedRectangle();
	virtual int Add(TGBasePrimitivePainter* painter);
protected:
	UID StateID;
	bool StateChanged;
	TGObjectsStateList State;
	PTGBaseTexture Texture;
	uint32_t LastAnimationTime;
	int PhaseLifeTime;
};
//---------------------------------------------------------------------

#endif // TGAnimatedRectangle_h__