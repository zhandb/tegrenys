#include "TGContentTypeParser.h"
#include <QtCore\QFile>
//---------------------------------------------------------------------
TGContentTypeParser::TGContentTypeParser(PTGModule receiver) : TGEndSignatureParser(receiver, "\r\n\r\n")
{
	//count = 0;
	Bypass = false;

	connect(this, SIGNAL(ContentReady(TGString, TGDataFragmentList&)), receiver, SLOT(OnContentReceived(TGString, TGDataFragmentList&)));
}
//---------------------------------------------------------------------
TGContentTypeParser::~TGContentTypeParser()
{

}
//---------------------------------------------------------------------

void TGContentTypeParser::ProcessRequest()
{
	CurrentContentType = ParserDataList.ToString().remove("Content-Type: ");

	Bypass = true;
}
//---------------------------------------------------------------------
void TGContentTypeParser::OnDataReceived(TGDataFragmentList& data_fragments)
{
	//ѕервым пакетом приходит ContentType + JPEG, вторым данные JPEG  так далее

	if (data_fragments.empty())
		return;

	const char* c = data_fragments.front().Data->GetConstData() + data_fragments.front().StartOffset;

	
	if (!Bypass)
	{
		TGEndSignatureParser::OnDataReceived(data_fragments);
	}
	else
	{
		Bypass = false;

		PTGBuffer data = data_fragments.GatherData();

		emit ContentReady(CurrentContentType, data_fragments);

		data_fragments.clear();
	}
}