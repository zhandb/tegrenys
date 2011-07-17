#include "TGBoundaryParser.h"
#include "TGContentTypeParser.h"
//---------------------------------------------------------------------
TGBoundaryParser::TGBoundaryParser() : TGEndSignatureParser("--WINBONDBOUDARY\r\n")
{
	ParsersMap[content_type_id] = new TGContentTypeParser();
}
//---------------------------------------------------------------------
TGBoundaryParser::~TGBoundaryParser()
{

}
//---------------------------------------------------------------------
void TGBoundaryParser::ProcessRequest(PTGTextLineRequest request)
{
	CurrentParserID = content_type_id;
}