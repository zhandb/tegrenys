#include "TGBoundaryParser.h"
#include "TGContentTypeParser.h"
//---------------------------------------------------------------------
TGBoundaryParser::TGBoundaryParser(PTGModule receiver) : TGEndSignatureParser(receiver, "")
{
	ContentTypeParser = new TGContentTypeParser(receiver);
}
//---------------------------------------------------------------------
TGBoundaryParser::~TGBoundaryParser()
{

}
//---------------------------------------------------------------------
void TGBoundaryParser::ProcessRequest()
{
	ParserDataList;
	
	//—юда приходит список фрагментов, содержащий contenttype и сами данные, 
	//всегда один целостный пакет. 

	ContentTypeParser->ReceiveData(ParserDataList);
}