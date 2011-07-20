//---------------------------------------------------------------------
#include "TGHttpParser.h"
#include "TGBoundaryParser.h"
//---------------------------------------------------------------------
TGHttpParser::TGHttpParser() : TGEndSignatureParser("\r\n\r\n")
{
	BoundaryParser = new TGBoundaryParser();
}
//---------------------------------------------------------------------
TGHttpParser::~TGHttpParser()
{

}
//---------------------------------------------------------------------
void TGHttpParser::ProcessRequest()
{
	Bypass = true;
}
//---------------------------------------------------------------------
void TGHttpParser::OnDataReceived(TGDataFragment data_fragment)
{
	if (Bypass)
		BoundaryParser->ReceiveData(data_fragment);
	else
		TGEndSignatureParser::OnDataReceived(data_fragment);
}