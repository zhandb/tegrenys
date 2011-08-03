#include "TGContentTypeParser.h"
#include <QFile>
//---------------------------------------------------------------------
TGContentTypeParser::TGContentTypeParser(QObject* receiver) : TGEndSignatureParser(receiver, "\r\n\r\n")
{
	count = 0;
	Bypass = false;
}
//---------------------------------------------------------------------
TGContentTypeParser::~TGContentTypeParser()
{

}
//---------------------------------------------------------------------

void TGContentTypeParser::ProcessRequest()
{
	ParserDataList;
	Bypass = true;
}
//---------------------------------------------------------------------
void TGContentTypeParser::OnDataReceived(TGDataFragmentList& data_fragments)
{
	//ѕервым пакетом приходит ContentType, вторым данные JPEG  так далее

	if (!Bypass)
	{
		TGEndSignatureParser::OnDataReceived(data_fragments);
	}
	else
	{
		Bypass = false;

		/*QFile file;

		file.setFileName(QString("c:\\test\\%1.jpg").arg(count++, 3, 10, QChar('0')));
		file.open(QIODevice::WriteOnly);

		for (TGDataFragmentList::iterator i = data_fragments.begin(); i != data_fragments.end(); ++i)
		{
			file.write(i->Data->GetConstData() + i->StartOffset, i->Size);
		}
		file.close();*/
	}
}