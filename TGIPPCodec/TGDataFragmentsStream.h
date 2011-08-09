#ifndef TGDataFragmentsStream_h__
#define TGDataFragmentsStream_h__

#include "basestreamin.h"
#include "..\TGNetwork\TGBaseDataParser.h"

class TGDataFragmentsStream : public CBaseStreamInput
{
public:
	TGDataFragmentsStream(TGDataFragmentList& source);
	~TGDataFragmentsStream();
	JERRCODE Close();
	JERRCODE Seek(long offset, int origin);
	JERRCODE Read(void* buf,uic_size_t len,uic_size_t* cnt);
	JERRCODE TellPos(long* pos);
private:
	JERRCODE Open(vm_char* name) {return JPEG_NOT_IMPLEMENTED;}
	
private:
	TGDataFragmentList::iterator CurrentFragment;
	uint32_t CurrentOffset;
	TGDataFragmentList Source;
};
#endif // TGDataFragmentsStream_h__