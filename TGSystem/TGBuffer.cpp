//---------------------------------------------------------------------
#include "TGBuffer.h"
//---------------------------------------------------------------------
TGBuffer::TGBuffer()
{
	qRegisterMetaType<PTGBuffer>("PTGBuffer");
}
//---------------------------------------------------------------------------

TGBuffer::TGBuffer(QByteArray& buffer)
{
	Buffer = buffer;
}
//---------------------------------------------------------------------
TGBuffer::~TGBuffer()
{

}
//---------------------------------------------------------------------
void TGBuffer::Allocate(uint32_t size)
{
	Buffer.resize(size);
}
//---------------------------------------------------------------------
const char* TGBuffer::GetConstData()
{
	return Buffer.data();  
}
//---------------------------------------------------------------------
void TGBuffer::DelRef()
{
	TGReferenceCounter::DelRef();
}
//---------------------------------------------------------------------
uint32_t TGBuffer::GetBufferSize()
{
	return Buffer.capacity();
}
//---------------------------------------------------------------------
uint32_t TGBuffer::GetDataSize()
{
	return Buffer.size();
}
//---------------------------------------------------------------------
void TGBuffer::Append(uint32_t start_offset, PTGBuffer data, uint32_t size)
{
	Buffer.append(data->GetConstData() + start_offset, size);
}