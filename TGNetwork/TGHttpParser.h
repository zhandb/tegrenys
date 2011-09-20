#ifndef TGHttpParser_h__
#define TGHttpParser_h__
//---------------------------------------------------------------------
#include "TGEndSignatureParser.h"
#include "TGBoundaryParser.h"
#include "tgnetwork_global.h"
//---------------------------------------------------------------------
//static uint32_t boundary_id = FOURCC("BOUN");

class TGNETWORK_EXPORT TGHttpParser : public TGEndSignatureParser
{
public:
	TGHttpParser(PTGModule receiver);
	~TGHttpParser();
protected:
	virtual void ProcessRequest();
	virtual void OnDataReceived(TGDataFragmentList& data_fragments);
private:
	PTGBoundaryParser BoundaryParser;
	bool Bypass;
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGHttpParser)
//---------------------------------------------------------------------

#endif // TGHttpParser_h__