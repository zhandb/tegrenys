//---------------------------------------------------------------------
#include "TGHttpParser.h"
#include "TGBoundaryParser.h"
//---------------------------------------------------------------------
TGHttpParser::TGHttpParser() : TGEndSignatureParser("\r\n\r\n")
{
	ParsersMap[boundary_id] = new TGBoundaryParser();
}
//---------------------------------------------------------------------
TGHttpParser::~TGHttpParser()
{

}
//---------------------------------------------------------------------
void TGHttpParser::ProcessRequest(PTGTextLineRequest request)
{
	CurrentParserID = boundary_id;
}