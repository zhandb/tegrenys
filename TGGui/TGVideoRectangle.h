#ifndef TGVideoRectangle_h__
#define TGVideoRectangle_h__

#include "TGBaseRectangle.h"
#include "TGDataObject.h"
#include "TGVideoStructs.h"
#include "TGSystemTypes.h"

class TGVideoRectangle : public QObject, public TGBaseRectangle
{
	Q_OBJECT
public:
	TGVideoRectangle(PTGBasePrimitiveLayer owner);
	~TGVideoRectangle();
	virtual int Add(TGBasePrimitivePainter* painter);
	virtual void DelRef();
private:
	PTGBaseTexture Texture;
	bool IsTextureLocked;
signals:
	void TextureLocked(TGTextureLockStruct lock_struct);
public slots:
	void OnLockTexture(TGTextureLockStruct lock_struct);
	void OnUnlockTexture();
};

#endif // TGVideoRectangle_h__