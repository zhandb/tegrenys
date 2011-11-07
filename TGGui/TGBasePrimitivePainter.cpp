#include "TGBasePrimitivePainter.h"
#include "TGDataObject.h"
#include "TGBaseTexturedRectangle.h"
#include "TGVideoRectangle.h"

//---------------------------------------------------------------------
TGBasePrimitivePainter::TGBasePrimitivePainter(PTGSystem system)
{
	PrimitivesCount = 0;
	PrimitiveBufferSize = 0;
	PrimitiveIndex = NULL;
	FocusedPrimitive = NULL;
	AnimationManager = new TGAnimationManager(system);
	AnimationTimer.start();
	CurrentAnimationTime = 0;
}
//---------------------------------------------------------------------
TGBasePrimitivePainter::~TGBasePrimitivePainter()
{
	ReleasePrimitiveIndex();
	//ReleaseChildPrimitives();
	//CurrentViewport = NULL;
}
//---------------------------------------------------------------------
bool TGBasePrimitivePainter::MouseEvent(QMouseEvent* event)
{
	for (TGBaseViewportsMap::iterator viewport = Viewports.begin(); viewport != Viewports.end(); ++viewport)
	{
		TGBaseViewport* vp = (TGBaseViewport*)&*viewport->second;
		vp->MouseEvent(event);
	}

	return true;
}
//---------------------------------------------------------------------
void TGBasePrimitivePainter::BuildPrimitives()
{
	for (TGBaseViewportsMap::iterator viewport = Viewports.begin(); viewport != Viewports.end(); ++viewport)
	{
		TGBaseViewport* vp = (TGBaseViewport*)&*viewport->second;

		for (TGModuleList::iterator layer = vp->ChildModules.begin(); layer != vp->ChildModules.end(); ++layer)
		{
			TGBasePrimitiveLayer* pl = (TGBasePrimitiveLayer*)&**layer;
			pl->BuildPrimitives(this);
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
void TGBasePrimitivePainter::AddViewport(UID uid, PTGModule viewport)
{
	Viewports[uid] = viewport;
}
//---------------------------------------------------------------------
//void TGBasePrimitivePainter::SetCurrentViewport(UID uid)
//{
//	TGBaseViewportsMap::iterator vp = Viewports.find(uid);
//	if (vp != Viewports.end())
//		CurrentViewport = vp->second;
//}
////---------------------------------------------------------------------
//void TGBasePrimitivePainter::AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer)
//{
//	if (CurrentViewport)
//	{
//		TGBaseViewport* vp = (TGBaseViewport*)&*CurrentViewport;
//		vp->AddLayer(layer);
//	}
//}
////---------------------------------------------------------------------
uint32_t TGBasePrimitivePainter::GetTime()
{
	return CurrentAnimationTime;
}
//---------------------------------------------------------------------

TGObjectsStateList TGBasePrimitivePainter::GetState(UID state_id)
{
	return AnimationManager->GetState(state_id);
}
//---------------------------------------------------------------------------

void TGBasePrimitivePainter::AddLayer(UID viewport_uid, UID layer_uid, PTGBasePrimitiveLayer layer)
{
	/*TGBaseViewportsMap::iterator vp = Viewports.find(viewport_uid);
	if (vp != Viewports.end())
	{
		TGBaseViewport* view_port = (TGBaseViewport*)&*vp->second;
		view_port->AddLayer(layer_uid, layer);

		TGBaseTexturedRectangle* p = new TGBaseTexturedRectangle(layer, "{8BC0D4A6-4BBA-431c-83CA-3357D87CF21A}");
		p->SetColor(QColor("red"));
		p->SetSize(QSizeF(1, 1));
		p->SetPos(TGPointF(-1, -0.5, 0.0));

		TGVideoRectangle* p2 = new TGVideoRectangle(layer);
		PTGBasePrimitive pp2 = p2;
		p2->SetSize(QSizeF(3, 2));
		p2->SetPos(TGPointF(-200, -0.5, -0.1));
	}*/
}