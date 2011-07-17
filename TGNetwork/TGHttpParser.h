#ifndef TGHttpParser_h__
#define TGHttpParser_h__
//---------------------------------------------------------------------
#include "TGEndSignatureParser.h"
//---------------------------------------------------------------------
static uint32_t boundary_id = FOURCC("BOUN");

class TGHttpParser : public TGEndSignatureParser
{
public:
	TGHttpParser();
	~TGHttpParser();
protected:
	virtual void ProcessRequest(PTGTextLineRequest request);
};
//---------------------------------------------------------------------
#endif // TGHttpParser_h__