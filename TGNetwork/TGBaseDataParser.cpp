//---------------------------------------------------------------------
#include "TGBaseDataParser.h"
//---------------------------------------------------------------------
TGBaseDataParser::TGBaseDataParser(QObject* receiver)
{
	Receiver = receiver;
}
//---------------------------------------------------------------------
TGBaseDataParser::~TGBaseDataParser()
{

}
//---------------------------------------------------------------------
void TGBaseDataParser::OnDataReceived(TGDataFragmentList& data_fragments)
{

}
//---------------------------------------------------------------------
void TGBaseDataParser::ReceiveData(TGDataFragmentList data_fragments)
{
	OnDataReceived(data_fragments);
}
//---------------------------------------------------------------------
