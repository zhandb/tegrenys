#ifndef TGBaseDataParser_h__
#define TGBaseDataParser_h__

#include "..\TGSystem\TGRefCounter.h"
//#include <stdint.h>
#include "..\TGSystem\TGBuffer.h"
#include <map>

TG_REFC_PTR(TGBaseDataParser);

typedef std::map<uint32_t, PTGBaseDataParser> TGParsersMap;

struct TGDataFragment
{
	uint32_t StartOffset;
	PTGBuffer Data;
	uint32_t Size;

	TGDataFragment(uint32_t start_offset, PTGBuffer data, uint32_t size)
	{
		StartOffset = start_offset;
		Size = size;
		Data = data;
	}
};

struct TGDataFragmentList : public std::list<TGDataFragment> 
{
	TGDataFragmentList(){};

	TGDataFragmentList(uint32_t start_offset, PTGBuffer data, uint32_t size)
	{
		push_back(TGDataFragment(start_offset, data, size));
	}
};

class TGBaseDataParser : public TGReferenceCounter
{
public:
	TGBaseDataParser(QObject* receiver);
	~TGBaseDataParser();
	void ReceiveData(TGDataFragmentList data_fragments);
protected:
	virtual void OnDataReceived(TGDataFragmentList& data_fragments);
protected:
	TGDataFragmentList ParserDataList;
	QObject* Receiver;
};
#endif // TGBaseDataParser_h__