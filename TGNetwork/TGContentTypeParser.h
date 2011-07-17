#ifndef TGContentTypeParser_h__
#define TGContentTypeParser_h__

#include "TGEndSignatureParser.h"


class TGContentTypeParser : public TGEndSignatureParser
{
public:
	TGContentTypeParser();
	~TGContentTypeParser();

protected:
	virtual void ProcessRequest(PTGTextLineRequest request);
};
#endif // TGContentTypeParser_h__