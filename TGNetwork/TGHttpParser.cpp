//---------------------------------------------------------------------
#include "TGHttpParser.h"
#include "TGBoundaryParser.h"
#include "TGHttpTagParser.h"
//---------------------------------------------------------------------
TGHttpParser::TGHttpParser(PTGModule receiver) : TGEndSignatureParser(receiver, "\r\n\r\n")
{
	BoundaryParser = new TGBoundaryParser(receiver);
	Bypass = false;
}
//---------------------------------------------------------------------
TGHttpParser::~TGHttpParser()
{

}
//---------------------------------------------------------------------
void TGHttpParser::ProcessRequest()
{
	//ѕервым пакетом приходит заголовок Http, его можно обработать здесь
	//дальнейшие данные передаем в BoundaryParser

	TGHttpTagParser tp;
	tp.ParseData(ParserDataList);

	TGString content_type = tp.GetTag("Content-Type");
	if (content_type.contains("multipart/x-mixed-replace"))
	{
		TGString bound_sign = "--" + content_type.section("boundary=", 1) + "\r\n";
		BoundaryParser->SetSignature(bound_sign.toAscii());
	}
	
	Bypass = true;
}
//---------------------------------------------------------------------
void TGHttpParser::OnDataReceived(TGDataFragmentList& data_fragments)
{
	if (Bypass)
		BoundaryParser->ReceiveData(data_fragments);
	else
		TGEndSignatureParser::OnDataReceived(data_fragments);
}