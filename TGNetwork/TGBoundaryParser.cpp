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
	
	//���� �������� ������ ����������, ���������� contenttype � ���� ������, 
	//������ ���� ��������� �����. 

	ContentTypeParser->ReceiveData(ParserDataList);
}