#ifndef TGBoundaryParser_h__
#define TGBoundaryParser_h__

#include "TGEndSignatureParser.h"

class TGBoundaryParser : public TGEndSignatureParser
{
public:
	TGBoundaryParser(PTGModule receiver);
	~TGBoundaryParser();

protected:
	virtual void ProcessRequest();
private:
	PTGEndSignatureParser ContentTypeParser;
};

TG_REFC_PTR(TGBoundaryParser)

#endif // TGBoundaryParser_h__

