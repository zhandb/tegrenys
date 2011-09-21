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

	PTGBuffer res = ParserDataList.GatherData();
	TGHttpTagParser tp;
	TGHttpTagMap tm;
	tp.ParseData(ParserDataList, tm);
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