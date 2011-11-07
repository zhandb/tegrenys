#ifndef TGDXPrimitivePainter_h__
#define TGDXPrimitivePainter_h__

#include "TGBasePrimitivePainter.h"
#include "TGDXVertexBuffer.h"

class TGDXPrimitivePainter : public TGBasePrimitivePainter
{
public:
	TGDXPrimitivePainter(PTGSystem system);
	~TGDXPrimitivePainter();

	void SetDevice(IDirect3DDevice9* device, QSize size);
	void Render();

	virtual void BeforeBuildPrimitives();
	virtual void AfterBuildPrimitives();

	virtual void AddPolyline(TGPointF pos, TGPolygonF points, QColor color);
	virtual void AddSolidPolygon(TGPointF pos, TGPolygonF points, QColor color);
	virtual void AddTexturedRectangle(TGPolygonF points, TGBaseTexture* texture);
	virtual void AddPolygon(TGPolygonF points, bool solid, TGBaseTexture* texture);
	virtual TGBaseTexture* CreateBaseTexture();
	void CopyRGB32DataToTexture(TGBaseTexture* texture, QSize size, DWORD pitch, BYTE* data);

	virtual void InverseMatrix(TGMatrix4& matrix, TGMatrix4& inv_matrix);


protected:
	TGDXVertexBuffer VertexBuffer;
protected:
	virtual void BeginPrimitive(TGPrimitiveTypes PrimitiveType = TGPrimitiveType_LineStrip, TGBaseTexture* Texture = NULL, bool alpha_enabled = true);
	virtual void EndPrimitive();
	virtual void CleanPrimitives();

private:
	IDirect3DDevice9* Device;
	//SNDXTextItemIndexEntriesList DXTextItemIndexEntries;
	bool DeviceChanged;
	bool AlphaEnabled;	
private:
	void AddVertex(TGPointF pos, QColor color);
	
};
#endif // TGDXPrimitivePainter_h__