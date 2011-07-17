//---------------------------------------------------------------------
#include "TGBaseTexturedRectangle.h"
#include "TGBasePrimitivePainter.h"
//---------------------------------------------------------------------
TGBaseTexturedRectangle::TGBaseTexturedRectangle(UID texture_id) : TGBaseRectangle(true)
{
	TextureID = texture_id;
	Texture = NULL;
}
//---------------------------------------------------------------------
TGBaseTexturedRectangle::~TGBaseTexturedRectangle()
{

}
//---------------------------------------------------------------------
void TGBaseTexturedRectangle::SetImage(QImage image)
{
	/*if (Image.format() != QImage::Format_ARGB32)
		Image = Image.convertToFormat(QImage::Format_ARGB32);*/
}

int TGBaseTexturedRectangle::Add(TGBasePrimitivePainter* painter)
{
	if (!Texture)
		Texture = painter->GetTexture(TextureID);

	//TGBasePrimitive::Add?

	float TLeft = 0;
	float TTop = 0;

	float TRight = 0;
	float TBottom = 0;

	if (Texture)
	{
		QRect texture_rect = QRect(QPoint(0, 0), Texture->Descr.texture_size);
		QRect sub_texture_rect = Texture->Descr.sub_texture_rect;
		if (Texture->Descr.parent)
		{
			Texture = Texture->Descr.parent;
			texture_rect = QRect(QPoint(0, 0), Texture->Descr.texture_size);
		}

		TLeft = Texture->TX * sub_texture_rect.left() / texture_rect.width();
		TTop = Texture->TY * sub_texture_rect.top() / texture_rect.height();

		TRight = Texture->TX * sub_texture_rect.right() / texture_rect.width();
		TBottom = Texture->TY * sub_texture_rect.bottom() / texture_rect.height();
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