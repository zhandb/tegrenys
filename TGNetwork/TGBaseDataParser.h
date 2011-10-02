#ifndef TGBaseDataParser_h__
#define TGBaseDataParser_h__

#include "..\TGSystem\TGRefCounter.h"
//#include <stdint.h>
#include "..\TGSystem\TGBuffer.h"
#include <map>
#include "..\TGSystem\TGSystemTypes.h"
#include "tgnetwork_global.h"

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

	PTGBuffer GatherData()
	{
		uint32_t size = 0;
		for (TGDataFragmentList::iterator i = begin(); i != end(); ++i)
			size += i->Size;

		PTGBuffer res = new TGBuffer();
		res->Allocate(size);

		uint32_t offset = 0;
		char* p = (char*)res->GetConstData();

		for (TGDataFragmentList::iterator i = begin(); i != end(); ++i)
		{
			memcpy(p + offset, i->Data->GetConstData() + i->StartOffset, i->Size);
			offset += i->Size;
		}
		return res;
	}

	TGString ToString()
	{
		PTGBuffer buf = GatherData();
		return TGString::fromLatin1(buf->GetConstData(), buf->GetDataSize());
	}
};

class TGNETWORK_EXPORT TGBaseDataParser : public TGReferenceCounter
{
public:
	TGBaseDataParser(PTGModule receiver);
	~TGBaseDataParser();
	void ReceiveData(TGDataFragmentList& data_fragments);
protected:
	virtual void OnDataReceived(TGDataFragmentList& data_fragments);
protected:
	TGDataFragmentList ParserDataList;
	PTGModule Receiver;
};
#endif // TGBaseDataParser_h__