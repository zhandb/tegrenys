#ifndef TGHttpParser_h__
#define TGHttpParser_h__
//---------------------------------------------------------------------
#include "TGEndSignatureParser.h"
#include "TGBoundaryParser.h"
//---------------------------------------------------------------------
static uint32_t boundary_id = FOURCC("BOUN");

class TGHttpParser : public TGEndSignatureParser
{
public:
	TGHttpParser();
	~TGHttpParser();
protected:
	virtual void ProcessRequest();
	virtual void OnDataReceived(TGDataFragment data_fragment);
private:
	PTGBoundaryParser BoundaryParser;
};
//---------------------------------------------------------------------
#endif // TGHttpParser_h__