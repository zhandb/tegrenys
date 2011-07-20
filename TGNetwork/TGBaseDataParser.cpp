//---------------------------------------------------------------------
#include "TGBaseDataParser.h"
//---------------------------------------------------------------------
TGBaseDataParser::TGBaseDataParser()
{
	//CurrentParserID = 0;
	Bypass = false;
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
	/*PTGBaseDataParser current_parser = ParsersMap[CurrentParserID];
	if (current_parser)
	{
		for (TGDataFragmentList::iterator data_fragment = ParserDataList.begin(); data_fragment != ParserDataList.end(); ++data_fragment)
		{
			current_parser->OnDataReceived(*data_fragment);
		}
	}
	
	ParserDataList.clear();*/
}
//---------------------------------------------------------------------
void TGBaseDataParser::ReceiveData(TGDataFragment data_fragment)
{
	OnDataReceived(data_fragment);

	////≈сли назначен следующий парсер, передаем данные ему
	//if (CurrentParserID)
	//{
	//	ParserDataList.push_back(data_fragment);
	//	PromoteData();
	//}

	////≈сли режим прозрачности не включен, обрабатываем в текущем парсере
	//if (!Bypass)
	//{
	//	OnDataReceived(data_fragment);
	//}
}
//---------------------------------------------------------------------
