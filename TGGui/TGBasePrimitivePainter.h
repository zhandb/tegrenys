#ifndef TGBasePrimitivePainter_h__
#define TGBasePrimitivePainter_h__
#include <QPointF>
#include <QPolygonF>
#include <QColor>
#include <QMouseEvent>
#include <QTime>

#include "TGBaseTexture.h"
#include "TGBasePrimitive.h"
#include "TGBaseTextureManager.h"
#include "TGBasePrimitiveLayer.h"
#include "TGBaseViewport.h"
#include "TGAnimationManager.h"

class TGBasePrimitivePainter : public TGReferenceCounter
{
public:
	TGBasePrimitivePainter(PTGSystem system);
	~TGBasePrimitivePainter();

	void AddViewport(UID uid, PTGModule viewport);

	//void SetCurrentViewport(UID uid);

	//void AddLayerToCurrentViewport(PTGBasePrimitiveLayer layer);
	void AddLayer(UID viewport_uid, UID layer_uid, PTGBasePrimitiveLayer layer);

	void Build();
	virtual void Render() = 0;

	uint32_t GetTime();

	TGObjectsStateList GetState(UID state_id);

	//Процедуры добавления базовых элементов примитивов
	virtual void AddPolyline(TGPointF pos, TGPolygonF points, QColor color) = 0;
	virtual void AddSolidPolygon(TGPointF pos, TGPolygonF points, QColor color) = 0;
	virtual void AddTexturedRectangle(TGPolygonF pos, TGBaseTexture* pixmap) = 0;
	virtual void AddPolygon(TGPolygonF points, bool solid, TGBaseTexture* texture) = 0;
	virtual void InverseMatrix(TGMatrix4& matrix, TGMatrix4& inv_matrix) = 0;

	virtual TGBaseTexture* CreateBaseTexture() = 0;

	//virtual SNFont QueryFont(SNBaseFontID font_id);

	virtual bool MouseEvent(QMouseEvent* event);

	void CreatePrimitiveIndex(int new_primitive_buffer_size);
	void ReleasePrimitiveIndex();

	TGBaseTexture* GetTexture(UID texture_id);
	PTGBaseTexture AddTexture(PTGBaseTextureDescriptor descr);

	//void RegisterFont(SNBaseFontID font_id, SNFont font);

	//void SetCanvasSize(QSize size);
	//SNSize GetCanvasSize();

	//void AddPrimitive(SNBasePrimitive* primitive, UID primitive_uid, UID parent_uid = UID());
	//void RemovePrimitive(UID primitive_uid);
	//void SetFocus(UID primitive_uid);
	//void RemoveChildPrimitives(UID parent_uid);

	//void AddPrimitive(TGBasePrimitive* primitive, TGBasePrimitive* parent = NULL, DWORD primitive_uid = DWORD());

	//void RemovePrimitive(SNBasePrimitive* primitive);

	//void RemoveChildPrimitives(SNBasePrimitive* parent);

	void SetFocus(TGBasePrimitive* primitive);

	//virtual void CopyRGB32DataToTexture(TGBaseTexture* texture, TGSize size, uint32_t pitch, uchar* data) = 0;
	
	//void RegisterPrimitive(SNBasePrimitive* primitive, UID primitive_uid);
	//void UnregisterPrimitive(UID primitive_uid);
	//SNBasePrimitive* FindPrimitive(UID primitive_uid);

protected:
	//Специфичное построение списка примитивов в OpenGL и DX (заполнение Vertex-буфера и т.п.)
	virtual void BeforeBuildPrimitives() = 0;
	virtual void BuildPrimitives();
	virtual void AfterBuildPrimitives() = 0;

	virtual void BeginPrimitive(TGPrimitiveTypes PrimitiveType = TGPrimitiveType_LineStrip, TGBaseTexture* Texture = NULL, bool alpha_enabled = true);
	virtual void EndPrimitive();
	virtual void CleanPrimitives();

	//SNPointF MapToDigitalZoom(SNPointF point);
	//SNPointF MapFromDigitalZoom(SNPointF point);

	void Add(TGBasePrimitivePainter* painter);
	bool Contains(TGPointF pos);

protected:
	//SNPrimitiveUIDMap PrimitiveMap;
	//QSize CanvasSize;
	//SNBaseFontMapper* FontMapper;
	DWORD PrimitivesCount;
	DWORD PrimitiveBufferSize;
	TGBaseViewportsMap Viewports;
	//PTGBaseViewport CurrentViewport;

	//SNPrimitivesList Primitives;
	TGPrimitiveIndexEntry2* PrimitiveIndex;
	TGBasePrimitive* FocusedPrimitive;
	QTime AnimationTimer;
	uint32_t CurrentAnimationTime;
public:
	PTGBaseTextureManager TextureManager;
	PTGAnimationManager AnimationManager;
};

TG_REFC_PTR(TGBasePrimitivePainter)

#endif // TGBasePrimitivePainter_h__