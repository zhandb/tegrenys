//---------------------------------------------------------------------
#include "TGVideoRectangle.h"
#include "TGBasePrimitivePainter.h"
#include "TGDXTexture.h"
#include "TGGuiBuilder.h"
//---------------------------------------------------------------------
TGVideoRectangle::TGVideoRectangle(UID module_id, PTGSystem system) : TGBaseRectangle(module_id, system, true)
{
	Texture = NULL;
	IsTextureLocked = false;
	//TGGuiBuilder::RegisterPrimitive("{19345C9B-57FF-4a63-879C-AFDBB92DAD6D}", this);

	SetSize(QSizeF(1, 1));
	//SetPos(TGPointF(-3, -0.5, 0.0));
}
//---------------------------------------------------------------------
TGVideoRectangle::~TGVideoRectangle()
{

}
//---------------------------------------------------------------------

void TGVideoRectangle::Init()
{
	TGDataObject config = System->LoadConfig(ModuleUID, "VideoRectangle");

	UID source_uid = config.Attribute("Source").toString();

	System->ConnectTo(source_uid, SIGNAL(LockDestinationBuffer(TGBufferLockStruct)), this, SLOT(OnLockTexture(TGBufferLockStruct)), TGSignals::Incoming);
	System->ConnectTo(source_uid, SIGNAL(UnlockDestinationBuffer()), this, SLOT(OnUnlockTexture()), TGSignals::Incoming);
	System->ConnectTo(source_uid, SLOT(OnDestinationBufferLocked(TGBufferLockStruct)), this, SIGNAL(TextureLocked(TGBufferLockStruct)), TGSignals::Outgoing);
}
//---------------------------------------------------------------------

int TGVideoRectangle::Add(TGBasePrimitivePainter* painter)
{
	if (!Texture)
	{
		PTGBaseTextureDescriptor video_descriptor = new TGVideoTextureDescriptor();
		video_descriptor->texture_size = QSize(640, 480);

		Texture = painter->AddTexture(video_descriptor);
	}

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

	TGDXTexture* dx_texture = (TGDXTexture*)&*Texture;

	D3DLOCKED_RECT LR;

	/*dx_texture->Texture->LockRect(0, &LR, NULL, D3DLOCK_NO_DIRTY_UPDATE);

	for (int j = 0;  j < dx_texture->Descr->texture_size.height(); ++j)
	{
		for (int i = 0; i < dx_texture->Descr->texture_size.width() * 4 - 80; ++i)
		{
			*((BYTE*)LR.pBits + i + j * LR.Pitch) = rand() % 256;
		}
	}
	
	dx_texture->Texture->UnlockRect(0);*/
	
	painter->AddPolygon(Polygon, true, Texture);
	
	return 1;
}
//---------------------------------------------------------------------------

void TGVideoRectangle::OnLockTexture(TGBufferLockStruct lock_struct)
{
	TGDXTexture* dx_texture = (TGDXTexture*)&*Texture;
	D3DLOCKED_RECT LR;
	if (dx_texture)
	{
		dx_texture->Texture->LockRect(0, &LR, NULL, D3DLOCK_NO_DIRTY_UPDATE);
		lock_struct.Data = (UCHAR*)LR.pBits;
		lock_struct.Pitch = LR.Pitch;
		IsTextureLocked = true;
	}
	
	emit TextureLocked(lock_struct);
}
//---------------------------------------------------------------------------

void TGVideoRectangle::OnUnlockTexture()
{
	if (IsTextureLocked)
	{
		TGDXTexture* dx_texture = (TGDXTexture*)&*Texture;
		dx_texture->Texture->UnlockRect(0);
	}
}
//---------------------------------------------------------------------------

void TGVideoRectangle::DelRef()
{
	TGReferenceCounter::DelRef();
}
//---------------------------------------------------------------------------

