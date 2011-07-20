#include "TGBoundaryParser.h"
#include "TGContentTypeParser.h"
//---------------------------------------------------------------------
TGBoundaryParser::TGBoundaryParser() : TGEndSignatureParser("--WINBONDBOUDARY\r\n")
{
	ContentTypeParser = new TGContentTypeParser();
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

	for (TGDataFragmentList::iterator data = ParserDataList.begin(); data != ParserDataList.end(); ++data)
	{
		ContentTypeParser->ReceiveData(*data);
	}
}