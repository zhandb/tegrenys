#ifndef TGBaseTexture_h__
#define TGBaseTexture_h__

#include <QtGui/QImage>
#include "TGRefCounter.h"

class TGBaseTexture;
TG_REFC_PTR(TGBaseTexture)

class TGBaseTextureDescriptor : public TGReferenceCounter
{
public:
	enum TGTextureTypes{File, SubTexture, Video};
	float TX;
	float TY;
	QSize texture_size;
	TGTextureTypes TextureType;
	TGBaseTextureDescriptor()
	{
		TX = 1.0;
		TY = 1.0;
	}
};

TG_REFC_PTR(TGBaseTextureDescriptor)

class TGFileTextureDescriptor : public TGBaseTextureDescriptor
{
public:
	TGFileTextureDescriptor()
	{
		TextureType = File;
	}

public:
	QString file_name;
};


class TGSubTextureDescriptor : public TGBaseTextureDescriptor
{
public:
	TGSubTextureDescriptor()
	{
		TextureType = SubTexture;
	}

public:
	PTGBaseTexture parent;
	QRect sub_texture_rect;
};

class TGVideoTextureDescriptor : public TGBaseTextureDescriptor
{
public:
	TGVideoTextureDescriptor()
	{
		TextureType = Video;
	}
};	

class TGBaseTexture : public TGReferenceCounter
{
public:
	TGBaseTexture(PTGBaseTextureDescriptor& descr);
	~TGBaseTexture();
public:
	
	PTGBaseTextureDescriptor Descr;
};


#endif // TGBaseTexture_h__