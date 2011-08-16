//---------------------------------------------------------------------
#include "TGBaseTexturedRectangle.h"
#include "TGBasePrimitivePainter.h"
//---------------------------------------------------------------------
TGBaseTexturedRectangle::TGBaseTexturedRectangle(PTGBasePrimitiveLayer owner, UID texture_id) : TGBaseRectangle(owner, true)
{
	Texture = NULL;
	TextureID = texture_id;
}
//---------------------------------------------------------------------
TGBaseTexturedRectangle::~TGBaseTexturedRectangle()
{

}
//---------------------------------------------------------------------

int TGBaseTexturedRectangle::Add(TGBasePrimitivePainter* painter)
{
	if (!Texture)
		Texture = painter->GetTexture(TextureID);

	//TGBasePrimitive::Add?

	float TLeft = 0;
	float TTop = 0;

	float TRight = 1.0;
	float TBottom = 1.0;

	if (Texture)
	{
		QRect texture_rect = QRect(QPoint(0, 0), Texture->Descr->texture_size);
		
		if (Texture->Descr->TextureType == TGBaseTextureDescriptor::SubTexture)
		{
			TGSubTextureDescriptor* descr = (TGSubTextureDescriptor*)&*Texture->Descr;
			QRect sub_texture_rect = descr->sub_texture_rect;
			if (descr->parent)
			{
				Texture = descr->parent;
				texture_rect = QRect(QPoint(0, 0), descr->texture_size);
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