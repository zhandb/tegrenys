#ifndef TGBaseTexture_h__
#define TGBaseTexture_h__

#include <QImage>
#include "TGRefCounter.h"

class TGBaseTexture;

struct TGBaseTextureDescriptor
{
	TGBaseTexture* parent;
	QString file_name;
	QSize texture_size;
	QRect sub_texture_rect;
};

class TGBaseTexture : public TGReferenceCounter
{
public:
	TGBaseTexture(TGBaseTextureDescriptor& descr);
	~TGBaseTexture();
public:
	float TX;
	float TY;
	
	TGBaseTextureDescriptor Descr;
};

TG_REFC_PTR(TGBaseTexture)

#endif // TGBaseTexture_h__