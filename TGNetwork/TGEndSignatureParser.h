#ifndef TGTextLineParser_h__
#define TGTextLineParser_h__

#include <QObject>
#include "..\TGSystem\TGRefCounter.h"
#include "..\TGSystem\TGBuffer.h"
#include "TGBaseDataParser.h"

struct TGTextRequestLine 
{
	const char* TagName;
	const char* TagValue;
};

typedef std::list<TGTextRequestLine> TGTextRequestLinesList;

struct TGTextLineRequest : public TGReferenceCounter
{
	PTGBuffer RequestBuffer;
	TGTextRequestLinesList RequestLines;
};
TG_REFC_PTR(TGTextLineRequest);

class TGEndSignatureParser : public TGBaseDataParser
{
public:
	TGEndSignatureParser(QByteArray signature);
	~TGEndSignatureParser();
	void SetSignature(QByteArray signature);
private:
	QByteArray Signature;
	uint32_t SignatureCounter;
	
protected:
	void ParseRequest(PTGBuffer buffer);
	virtual void ProcessRequest(PTGTextLineRequest request);
	virtual void OnDataReceived(TGDataFragment data_fragment);
};

TG_REFC_PTR(TGEndSignatureParser);

#endif // TGTextLineParser_h__