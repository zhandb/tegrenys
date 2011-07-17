//---------------------------------------------------------------------
#include "TGBaseDataParser.h"
//---------------------------------------------------------------------
TGBaseDataParser::TGBaseDataParser()
{
	CurrentParserID = 0;
}
//---------------------------------------------------------------------
TGBaseDataParser::~TGBaseDataParser()
{

}
//---------------------------------------------------------------------
void TGBaseDataParser::OnDataReceived(TGDataFragment data_fragment)
{

}
//---------------------------------------------------------------------
void TGBaseDataParser::PromoteData()
{
	PTGBaseDataParser current_parser = ParsersMap[CurrentParserID];
	if (current_parser)
	{
		for (TGDataFragmentList::iterator data_fragment = ParserDataList.begin(); data_fragment != ParserDataList.end(); ++data_fragment)
		{
			current_parser->OnDataReceived(*data_fragment);
		}
	}
	
	ParserDataList.clear();
}
//---------------------------------------------------------------------
void TGBaseDataParser::ReceiveData(TGDataFragment data_fragment)
{
	if (!CurrentParserID)
	{
		OnDataReceived(data_fragment);
	}
	else
	{
		ParserDataList.push_back(data_fragment);
		PromoteData();
	}
}
//---------------------------------------------------------------------
