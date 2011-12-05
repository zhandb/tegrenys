#ifndef TGTextLineParser_h__
#define TGTextLineParser_h__

#include <QtCore\QObject>
#include "..\TGSystem\TGRefCounter.h"
#include "..\TGSystem\TGBuffer.h"
#include "TGBaseDataParser.h"
//---------------------------------------------------------------------
struct TGTextRequestLine 
{
	const char* TagName;
	const char* TagValue;
};
//---------------------------------------------------------------------
typedef std::list<TGTextRequestLine> TGTextRequestLinesList;
//---------------------------------------------------------------------
struct TGTextLineRequest : public TGReferenceCounter
{
	PTGBuffer RequestBuffer;
	TGTextRequestLinesList RequestLines;
};
TG_REFC_PTR(TGTextLineRequest);

class TGEndSignatureParser : public TGBaseDataParser
{
public:
	TGEndSignatureParser(PTGModule receiver, QByteArray signature);
	~TGEndSignatureParser();
	void SetSignature(QByteArray signature);
private:
	QByteArray Signature;
	uint32_t SignatureCounter;
	
protected:
	//void ParseRequest(PTGBuffer buffer);
	virtual void ProcessRequest();
	virtual void OnDataReceived(TGDataFragmentList& data_fragments);
	//Ишем окончание сигнатуры (или полную сигнатуру в текущем фрагменте
	//если найдено - возращаем количество байт, включая сигнатуру, иначе -1
	int SearchForSignature(TGDataFragment data_fragment);
	//Удаляем количество байт, равное длине сигнатуры
	void RemoveSignature();
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGEndSignatureParser);
//---------------------------------------------------------------------

#endif // TGTextLineParser_h__