#ifndef TGBaseTextureManager_h__
#define TGBaseTextureManager_h__

//#include "TGDataObject.h"
#include "TGBaseTexture.h"
#include "TGSystemTypes.h"

#include <QMap>
//#include "TGSqlite.h"

typedef QMap<UID, PTGBaseTexture> TGBaseTextureMap;

class TGBaseTextureManager : public TGReferenceCounter
{
public:
	TGBaseTextureManager(PTGSystem system);
	~TGBaseTextureManager();
	void Init();
	TGBaseTexture* GetBaseTexture(UID texture_id);
	PTGBaseTexture AddTexture(PTGBaseTextureDescriptor texture_desc);
private:
	TGBaseTextureMap TexturesMap;
	TGBaseTextureMap SubTexturesMap;
	TGBaseTextureMap VideoTexturesMap;
	PTGSystem System;
private:
	virtual TGBaseTexture* CreateTexture(PTGBaseTextureDescriptor& descr) = 0;
	virtual void SetTextureImage(TGBaseTexture* texture, QImage* image) = 0;
	void LoadTextures();
public:
	virtual void SetTextureImage(TGBaseTexture* texture, const uchar* data, const int pitch) = 0;

	
protected:
	virtual void InitTexture(TGBaseTexture* texture) = 0;
	virtual void ReleaseTexture(TGBaseTexture* texture) = 0;
	void InitTextures();
	virtual void InvalidateTexture(TGBaseTexture* texture) = 0;
};

TG_REFC_PTR(TGBaseTextureManager);

#endif // TGBaseTextureManager_h__