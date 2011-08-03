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
	TGHttpParser(QObject* receiver);
	~TGHttpParser();
protected:
	virtual void ProcessRequest();
	virtual void OnDataReceived(TGDataFragmentList& data_fragments);
private:
	PTGBoundaryParser BoundaryParser;
	bool Bypass;
};
//---------------------------------------------------------------------
#endif // TGHttpParser_h__