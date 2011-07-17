#ifndef TGBoundaryParser_h__
#define TGBoundaryParser_h__

#include "TGEndSignatureParser.h"

static uint32_t content_type_id = FOURCC("CNTN");

class TGBoundaryParser : public TGEndSignatureParser
{
public:
	TGBoundaryParser();
	~TGBoundaryParser();

protected:
	virtual void ProcessRequest(PTGTextLineRequest request);
};

#endif // TGBoundaryParser_h__