#include "TGAnimatedRectangle.h"
#include "TGBasePrimitivePainter.h"

//---------------------------------------------------------------------
TGAnimatedRectangle::TGAnimatedRectangle() : TGBaseRectangle(true)
{
	StateChanged = true;
	StateID = 1000;
	LastAnimationTime = 0;
	PhaseLifeTime = 0;
}
//---------------------------------------------------------------------
TGAnimatedRectangle::~TGAnimatedRectangle()
{

}
//---------------------------------------------------------------------
int TGAnimatedRectangle::Add(TGBasePrimitivePainter* painter)
{
	if (StateChanged)
	{
		StateChanged = false;
		State = painter->GetState(StateID);
		LastAnimationTime = painter->GetTime();
	}

	if (PhaseLifeTime <= 0)
	{
		if (!State.empty())
		{
			if (!State.front().Animation.empty())
			{
				TGAnimationPhase ph = State.front().Animation.front();
				State.front().Animation.pop_front();
				State.front().Animation.push_back(ph);

				ph = State.front().Animation.front();
				PhaseLifeTime += ph.Delay;
				Texture = ph.Image;
			}
		}

	}

	if (LastAnimationTime <= painter->GetTime())
	{
		int delta_time = painter->GetTime() - LastAnimationTime;

		if (delta_time > PhaseLifeTime)
		{
			PhaseLifeTime -= delta_time;
			LastAnimationTime = painter->GetTime();
		}
	}
	else
	{
		LastAnimationTime = painter->GetTime();
	}

	
	//TGBasePrimitive::Add?

	float TLeft = 0;
	float TTop = 0;

	float TRight = 0;
	float TBottom = 0;

	PTGBaseTexture texture = Texture;

	if (texture)
	{
		QRect texture_rect = QRect(QPoint(0, 0), Texture->Descr->texture_size);

		if (Texture->Descr->TextureType == TGBaseTextureDescriptor::SubTexture)
		{
			TGSubTextureDescriptor* descr = (TGSubTextureDescriptor*)&*Texture->Descr;
			QRect sub_texture_rect = descr->sub_texture_rect;
			if (descr->parent)
			{
				texture = descr->parent;
				texture_rect = QRect(QPoint(0, 0), texture->Descr->texture_size);
			}

			TLeft = Texture->Descr->TX * sub_texture_rect.left() / texture_rect.width();
			TTop = Texture->Descr->TY * sub_texture_rect.top() / texture_rect.height();

			TRight = Texture->Descr->TX * sub_texture_rect.right() / texture_rect.width();
			TBottom = Texture->Descr->TY * sub_texture_rect.bottom() / texture_rect.height();
		}
	}


	Polygon[0].TX = TLeft;
	Polygon[0].TY = TBottom;

	Polygon[1].TX = TRight;
	Polygon[1].TY = TBottom;

	Polygon[2].TX = TLeft;
	Polygon[2].TY = TTop;

	Polygon[3].TX = TRight;
	Polygon[3].TY = TTop;

	painter->AddPolygon(Polygon, true, Texture);

	return 1;
}