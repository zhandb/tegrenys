#ifndef TGBoundaryParser_h__
#define TGBoundaryParser_h__

#include "TGEndSignatureParser.h"

static uint32_t content_type_id = FOURCC("CNTN");

class TGBoundaryParser : public TGEndSignatureParser
{
public:
	TGBoundaryParser(QObject* receiver);
	~TGBoundaryParser();

protected:
	virtual void ProcessRequest();
private:
	PTGEndSignatureParser ContentTypeParser;
};

TG_REFC_PTR(TGBoundaryParser)

#endif // TGBoundaryParser_h__

