#ifndef TGVideoRectangle_h__
#define TGVideoRectangle_h__

#include "TGBaseRectangle.h"
#include "TGDataObject.h"
#include "TGVideoStructs.h"

class TGVideoRectangle : public QObject, public TGBaseRectangle
{
	Q_OBJECT
public:
	TGVideoRectangle();
	~TGVideoRectangle();
	virtual int Add(TGBasePrimitivePainter* painter);
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