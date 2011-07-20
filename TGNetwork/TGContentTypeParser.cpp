#include "TGContentTypeParser.h"
//---------------------------------------------------------------------
TGContentTypeParser::TGContentTypeParser() : TGEndSignatureParser("\r\n\r\n")
{

}
//---------------------------------------------------------------------
TGContentTypeParser::~TGContentTypeParser()
{

}
//---------------------------------------------------------------------

void TGContentTypeParser::ProcessRequest()
{
	ParserDataList;
	Bypass = true;
}
//---------------------------------------------------------------------
void TGContentTypeParser::OnDataReceived(TGDataFragment data_fragment)
{
	if (!Bypass)
	{
		TGEndSignatureParser::OnDataReceived(data_fragment);
	}
	else
	{
		Bypass = false;
	}
}