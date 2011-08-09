#include "TGBoundaryParser.h"
#include "TGContentTypeParser.h"
//---------------------------------------------------------------------
TGBoundaryParser::TGBoundaryParser(QObject* receiver) : TGEndSignatureParser(receiver, "--WINBONDBOUDARY\r\n")
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