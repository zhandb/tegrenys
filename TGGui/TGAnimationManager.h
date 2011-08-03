#ifndef TGAnimationManager_h__
#define TGAnimationManager_h__

#include "TGRefCounter.h"
#include "TGBaseTextureManager.h"
//#include <stdint.h>

struct TGAnimationPhase
{
	PTGBaseTexture Image;
	uint32_t Delay;
};

typedef std::list<TGAnimationPhase> TGAnimation;

typedef std::map<UID, TGAnimation> TGAnimationMap;

struct TGObjectState
{
	TGAnimation Animation;
	int MousePushed;
	int MouseHover;
};

typedef std::list<TGObjectState> TGObjectsStateList;

typedef std::map<UID, TGObjectsStateList> TGObjectStatesMap;


class TGAnimationManager : public TGReferenceCounter
{
public:
	TGAnimationManager();
	~TGAnimationManager();
	void LoadAnimations(PTGBaseTextureManager texture_manager);
	void LoadStates();
	TGObjectsStateList GetState(UID state_id);
private:
	TGAnimationMap Animations;
	TGObjectStatesMap States;
};

TG_REFC_PTR(TGAnimationManager)

#endif // TGAnimationManager_h__