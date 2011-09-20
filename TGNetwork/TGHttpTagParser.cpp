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
	enum TGHttpTagParserState{None, TagName, TagValue};

	TGHttpTagParserState state = TagName;
	
	int tmp_buffer_ptr = 0;

	PTGBuffer tmp_buffer = new TGBuffer();
	tmp_buffer->Allocate(1024);

	TGString tag_name;
	
	const char* tmp = tmp_buffer->GetConstData();

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
				}

				if (data[j] == '\r' && data[j + 1] == '\n')
				{
					tmp[tmp_buffer_ptr] = 0;
					tmp_buffer_ptr = 0;
					tag_name = tmp;
				}
			}

			if (state == TagName)
			{
				if (data[j] != ':')
				{
					tmp[tmp_buffer_ptr++] = data[j];
				}
				else
				{
					if (j < i->Size - 1 && data[j + 1] == ' ')
					{
						j++;
						state = TagValue;
						tmp[tmp_buffer_ptr] = 0;
						tmp_buffer_ptr = 0;
						tag_name = tmp;
					}

				}
			}
		}
	}
}
//-------------------------------------------------------------------
