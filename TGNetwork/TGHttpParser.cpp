//---------------------------------------------------------------------
#include "TGHttpParser.h"
#include "TGBoundaryParser.h"
//---------------------------------------------------------------------
TGHttpParser::TGHttpParser(QObject* receiver) : TGEndSignatureParser(receiver, "\r\n\r\n")
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
	//������ ������� �������� ��������� Http, ��� ����� ���������� �����
	//���������� ������ �������� � BoundaryParser
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