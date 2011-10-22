#ifndef TGVideoRectangle_h__
#define TGVideoRectangle_h__

#include "TGBaseRectangle.h"
#include "TGDataObject.h"
#include "TGVideoStructs.h"
#include "TGSystemTypes.h"

class TGVideoRectangle : public TGBaseRectangle
{
	Q_OBJECT
public:
	TGVideoRectangle(UID module_id, PTGModule system);
	~TGVideoRectangle();
	virtual int Add(TGBasePrimitivePainter* painter);
	virtual void DelRef();
private:
	PTGBaseTexture Texture;
	bool IsTextureLocked;
signals:
	void TextureLocked(TGBufferLockStruct lock_struct);
public slots:
	void OnLockTexture(TGBufferLockStruct lock_struct);
	void OnUnlockTexture();
};

#endif // TGVideoRectangle_h__