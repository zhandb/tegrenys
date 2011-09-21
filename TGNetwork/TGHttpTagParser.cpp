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

void TGHttpTagParser::ParseData(TGDataFragmentList& data_fragments, TGHttpTagMap& tag_map)
{
	enum TGHttpTagParserState{None, TagName, TagValue};

	TGHttpTagParserState state = TagName;
	
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
					
					tag_map[tag_name] = tmp;
					
					j += 1;
					continue;
				}
			}

			tmp[tmp_buffer_ptr++] = data[j];
			if (tmp_buffer_ptr == MAX_HTTP_TAG_LENGTH)
				return;

			tmp[tmp_buffer_ptr++] = data[j];
		}
	}

	if (tmp_buffer_ptr)
	{
		tmp[tmp_buffer_ptr] = 0;
		tmp_buffer_ptr = 0;

		tag_map[tag_name] = tmp;
	}

	int r = 0;
}
//-------------------------------------------------------------------
