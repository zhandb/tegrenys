#include "TGHttpTagParser.h"
//-------------------------------------------------------------------

TGHttpTagParser::TGHttpTagParser()
{

}
//-------------------------------------------------------------------

TGHttpTagParser::~TGHttpTagParser()
{

}
//-------------------------------------------------------------------

void TGHttpTagParser::ParseData(TGDataFragmentList& data_fragments)
{
	TagMap.clear();

	int tmp_buffer_ptr = 0;

	PTGBuffer tmp_buffer = new TGBuffer();
	tmp_buffer->Allocate(1024);

	TGString tag_name;
	
	char* tmp = (char*)tmp_buffer->GetConstData();

	for (TGDataFragmentList::iterator i = data_fragments.begin(); i != data_fragments.end(); ++i)
	{
		for (int j = 0; j < i->Size; ++j)
		{
			const char* data = i->Data->GetConstData();
			if (j < i->Size - 1)
			{
				if (data[j] == ':' && data[j + 1] == ' ')
				{
					tmp[tmp_buffer_ptr] = 0;
					tmp_buffer_ptr = 0;
					tag_name = tmp;
					j++;
					continue;
				}

				if (data[j] == '\r' && data[j + 1] == '\n')
				{
					tmp[tmp_buffer_ptr] = 0;
					tmp_buffer_ptr = 0;
					
					if (!tag_name.length())
						tag_name = "HttpHeader";
					
					TagMap[tag_name] = tmp;
					
					j++;
					continue;
				}
			}

			tmp[tmp_buffer_ptr++] = data[j];
			if (tmp_buffer_ptr == MAX_HTTP_TAG_LENGTH)
				return;
		}
	}

	if (tmp_buffer_ptr)
	{
		tmp[tmp_buffer_ptr] = 0;
		tmp_buffer_ptr = 0;

		TagMap[tag_name] = tmp;
	}
}
//---------------------------------------------------------------------------

TGString TGHttpTagParser::GetTag(const char* tag_name, TGString& default /*= TGString("")*/)
{
	TGHttpTagMap::iterator i = TagMap.find(tag_name);
	if (i != TagMap.end())
		return i->second;
	else
		return default;
}
//-------------------------------------------------------------------
