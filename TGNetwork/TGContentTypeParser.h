#ifndef TGContentTypeParser_h__
#define TGContentTypeParser_h__

#include "TGEndSignatureParser.h"


class TGContentTypeParser : public TGEndSignatureParser
{
public:
	TGContentTypeParser(QObject* receiver);
	~TGContentTypeParser();

protected:
	virtual void ProcessRequest();
	virtual void OnDataReceived(TGDataFragmentList& data_fragments);
private:
	int count;
	bool Bypass;
};

TG_REFC_PTR(TGContentTypeParser)

#endif // TGContentTypeParser_h__