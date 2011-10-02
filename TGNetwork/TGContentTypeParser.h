#ifndef TGContentTypeParser_h__
#define TGContentTypeParser_h__

#include "TGEndSignatureParser.h"


class TGContentTypeParser : public QObject, public TGEndSignatureParser
{
	Q_OBJECT
public:
	TGContentTypeParser(PTGModule receiver);
	~TGContentTypeParser();

protected:
	virtual void ProcessRequest();
	virtual void OnDataReceived(TGDataFragmentList& data_fragments);
private:
	bool Bypass;
	TGString CurrentContentType;
signals:
	void ContentReady(TGString content_type, TGDataFragmentList& data);
};

TG_REFC_PTR(TGContentTypeParser)

#endif // TGContentTypeParser_h__