#ifndef TGBaseDataParser_h__
#define TGBaseDataParser_h__

#include "..\TGSystem\TGRefCounter.h"
#include <stdint.h>
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

typedef std::list<TGDataFragment> TGDataFragmentList;

class TGBaseDataParser : public TGReferenceCounter
{
public:
	TGBaseDataParser();
	~TGBaseDataParser();
	void PromoteData();
	void ReceiveData(TGDataFragment data_fragment);
protected:
	virtual void OnDataReceived(TGDataFragment data_fragment);
protected:
	TGParsersMap ParsersMap;
	uint32_t CurrentParserID;
	TGDataFragmentList ParserDataList;
};
#endif // TGBaseDataParser_h__