#include "TGBaseTextureManager.h"
#include "TGSqliteQuery.h"
//#include "tegrenys.h"
#include <afxcom_.h>
//---------------------------------------------------------------------
TGBaseTextureManager::TGBaseTextureManager()
{
	
}
//---------------------------------------------------------------------
TGBaseTextureManager::~TGBaseTextureManager()
{

}
//---------------------------------------------------------------------
TGBaseTexture* TGBaseTextureManager::GetBaseTexture(UID texture_id)
{
	TGBaseTexture* res = NULL;

	TGBaseTextureMap::iterator tex_iter = TexturesMap.find(texture_id);
	if (tex_iter != TexturesMap.end())
	{
		res = *tex_iter;
	}
	else
	{
		TGBaseTextureMap::iterator tex_iter = SubTexturesMap.find(texture_id);
		if (tex_iter != SubTexturesMap.end())
		{
			res = *tex_iter;
		}
	}

	return res;
}
//---------------------------------------------------------------------

void TGBaseTextureManager::LoadTextures()
{
	TGSqliteQuery textures_query;
	TGDataRecord schema;
	textures_query.Exec(
		TGSqlite::GetMainDatabase(), 
		QString("SELECT * FROM Textures"), 
		&schema);

	TGDataRecord data;
	while (textures_query.Read(&data))
	{
		QString file_name = data[1].toString();
		unsigned int ID = data[0].toInt();
		TGBaseTextureDescriptor descr;
		descr.parent = NULL;
		descr.file_name = file_name;
		descr.sub_texture_rect = QRect();
		descr.texture_size.setWidth(data[2].toInt());
		descr.texture_size.setHeight(data[3].toInt());
		descr.sub_texture_rect = QRect(QPoint(0, 0), descr.texture_size);

		ASSERT(!TexturesMap.contains(ID));
		TexturesMap[ID] = CreateTexture(descr);
	}	

	TGSqliteQuery sub_textures_query;
	TGDataRecord sub_schema;
	sub_textures_query.Exec(
		TGSqlite::GetMainDatabase(), 
		QString("SELECT * FROM SubTextures"), 
		&schema);

	while (sub_textures_query.Read(&data))
	{
		UID ID = data[0].toInt();
		UID parent_id = data[1].toInt();

		TGBaseTextureDescriptor descr;

		TGBaseTextureMap::iterator parent_tex = TexturesMap.find(parent_id);
		ASSERT(parent_tex != TexturesMap.end());
		descr.parent = TexturesMap[parent_id];

		descr.sub_texture_rect = QRect();
		descr.sub_texture_rect.setLeft(data[2].toInt());
		descr.sub_texture_rect.setTop(data[3].toInt());

		descr.sub_texture_rect.setWidth(data[4].toInt());
		descr.sub_texture_rect.setHeight(data[5].toInt());

		ASSERT(!SubTexturesMap.contains(ID));
		SubTexturesMap[ID] = CreateTexture(descr);
	}	
}
//---------------------------------------------------------------------
TGBaseTexture* TGBaseTextureManager::CreateTexture(TGBaseTextureDescriptor& descr)
{
	return new TGBaseTexture(descr);
}
//---------------------------------------------------------------------
void TGBaseTextureManager::InitTextures()
{
	for (TGBaseTextureMap::iterator tex = TexturesMap.begin(); tex != TexturesMap.end(); ++tex)
	{
		InitTexture(tex.value());
	}
}
//---------------------------------------------------------------------
void TGBaseTextureManager::Init()
{
	LoadTextures();
}
//---------------------------------------------------------------------
UID TGBaseTextureManager::AddTexture(TGBaseTextureDescriptor texture_desc)
{
	unsigned int ID = rand();
	texture_desc.sub_texture_rect = QRect(QPoint(0, 0), texture_desc.texture_size);
	ASSERT(!TexturesMap.contains(ID));
	TGBaseTexture* new_texture = CreateTexture(texture_desc);
	TexturesMap[ID] = new_texture;
	InvalidateTexture(new_texture);
	return ID;
}
//---------------------------------------------------------------------

