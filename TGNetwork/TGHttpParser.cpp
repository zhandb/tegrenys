//---------------------------------------------------------------------
#include "TGHttpParser.h"
#include "TGBoundaryParser.h"
#include "TGHttpTagParser.h"
//---------------------------------------------------------------------
TGHttpParser::TGHttpParser(PTGModule receiver) : TGEndSignatureParser(receiver, "\r\n\r\n")
{
	ParserState = ReadHeader;
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
		if (!BoundaryParser)
		{
			BoundaryParser = new TGBoundaryParser(Receiver);
			BoundaryParser->SetSignature(bound_sign.toAscii());
			ParserState = ReadMultipartContent;
		}
	}
}
//---------------------------------------------------------------------
void TGHttpParser::OnDataReceived(TGDataFragmentList& data_fragments)
{
	switch (ParserState)
	{
	case ReadHeader:
		TGEndSignatureParser::OnDataReceived(data_fragments);
		break;

	case ReadMultipartContent:
		BoundaryParser->ReceiveData(data_fragments);
		break;
	}
}