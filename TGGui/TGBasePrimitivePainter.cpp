#include "TGBasePrimitivePainter.h"
#include "TGDataObject.h"

//---------------------------------------------------------------------
TGBasePrimitivePainter::TGBasePrimitivePainter()
{
	PrimitivesCount = 0;
	PrimitiveBufferSize = 0;
	PrimitiveIndex = NULL;
	FocusedPrimitive = NULL;
	AnimationManager = new TGAnimationManager();
	AnimationTimer.start();
	CurrentAnimationTime = 0;
}
//---------------------------------------------------------------------
TGBasePrimitivePainter::~TGBasePrimitivePainter()
{
	ReleasePrimitiveIndex();
	//ReleaseChildPrimitives();
	CurrentViewport = NULL;
}
//---------------------------------------------------------------------
bool TGBasePrimitivePainter::MouseEvent(QMouseEvent* event)
{
	for (TGBaseViewportsMap::iterator viewport = Viewports.begin(); viewport != Viewports.end(); ++viewport)
	{
		(*viewport)->MouseEvent(event);
	}

	return true;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::BuildPrimitives()
{
	for (TGBaseViewportsMap::iterator viewport = Viewports.begin(); viewport != Viewports.end(); ++viewport)
	{
		for (TGPrimitiveLayersList::iterator layer = (*viewport)->PrimitiveLayers.begin(); layer != (*viewport)->PrimitiveLayers.end(); ++layer)
		{
			(*layer)->BuildPrimitives(this);
		}
	}
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::BeginPrimitive(TGPrimitiveTypes PrimitiveType /*= TGPrimitiveType_LineStrip*/, TGBaseTexture* Texture /*= NULL*/, bool alpha_enabled /*= true*/)
{
	if (PrimitivesCount == PrimitiveBufferSize)
	{
		CreatePrimitiveIndex(PrimitiveBufferSize + 100);
	}
	PrimitiveIndex[PrimitivesCount].PrimitiveType = PrimitiveType;
	PrimitiveIndex[PrimitivesCount].AlphaBlendEnabled = alpha_enabled;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::EndPrimitive()
{
	PrimitivesCount++;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::CleanPrimitives()
{
	PrimitivesCount = 0;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::Build()
{
	CurrentAnimationTime = AnimationTimer.elapsed();

	BeforeBuildPrimitives();
	BuildPrimitives();
	AfterBuildPrimitives();
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::SetFocus(TGBasePrimitive* primitive)
{
	if (FocusedPrimitive)
		FocusedPrimitive->FocusOutEvent();
	if (primitive)
		primitive->FocusInEvent();

	FocusedPrimitive = primitive;
}
//---------------------------------------------------------------------
//void TGBasePrimitivePainter::AddPrimitive(TGBasePrimitive* primitive, TGBasePrimitive* parent /*= NULL*/, DWORD primitive_uid /*= UID()*/)
//{
//	if (parent)
//		parent->AddChildPrimitive(primitive);
//	else
//		AddChildPrimitive(primitive);
//}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::Add(TGBasePrimitivePainter* painter)
{

}
//---------------------------------------------------------------------
bool TGBasePrimitivePainter::Contains(TGPointF pos)
{
	return false;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::CreatePrimitiveIndex(int new_primitive_buffer_size)
{
	if (PrimitiveBufferSize < new_primitive_buffer_size)
	{
		TGPrimitiveIndexEntry2* new_buffer = new TGPrimitiveIndexEntry2[new_primitive_buffer_size];

		if (PrimitiveIndex)
			memcpy(new_buffer, PrimitiveIndex, sizeof(TGPrimitiveIndexEntry2) * PrimitiveBufferSize);

		ReleasePrimitiveIndex();

		PrimitiveIndex = new_buffer;
		PrimitiveBufferSize = new_primitive_buffer_size;
	}
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::ReleasePrimitiveIndex()
{
	if (PrimitiveIndex)
	{
		delete [] PrimitiveIndex;
		PrimitiveIndex = NULL;
	}
}
//---------------------------------------------------------------------
TGBaseTexture* TGBasePrimitivePainter::GetTexture(UID texture_id)
{
	return TextureManager->GetBaseTexture(texture_id);
}
//---------------------------------------------------------------------
PTGBaseTexture TGBasePrimitivePainter::AddTexture(PTGBaseTextureDescriptor descr)
{
	return TextureManager->AddTexture(descr);
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::AddViewport(UID uid, PTGBaseViewport viewport)
{
	Viewports[uid] = viewport;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::SetCurrentViewport(UID uid)
{
	TGBaseViewportsMap::iterator vp = Viewports.find(uid);
	if (vp != Viewports.end())
		CurrentViewport = *vp;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer)
{
	if (CurrentViewport)
	{
		CurrentViewport->AddLayer(layer);
	}
}
//---------------------------------------------------------------------
uint32_t TGBasePrimitivePainter::GetTime()
{
	return CurrentAnimationTime;
}
//---------------------------------------------------------------------

TGObjectsStateList TGBasePrimitivePainter::GetState(UID state_id)
{
	return AnimationManager->GetState(state_id);
}