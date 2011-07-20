#ifndef TGContentTypeParser_h__
#define TGContentTypeParser_h__

#include "TGEndSignatureParser.h"


class TGContentTypeParser : public TGEndSignatureParser
{
public:
	TGContentTypeParser();
	~TGContentTypeParser();

protected:
	virtual void ProcessRequest();
	virtual void OnDataReceived(TGDataFragment data_fragment);
};

TG_REFC_PTR(TGContentTypeParser)

#endif // TGContentTypeParser_h__