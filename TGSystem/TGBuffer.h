#ifndef TGBuffer_h__
#define TGBuffer_h__
//---------------------------------------------------------------------
#include "TGRefCounter.h"
#include <stdint.h>
#include <QByteArray>
#include <QMetaType>
//---------------------------------------------------------------------
class TGBufferPool;
TG_REFC_PTR(TGBufferPool);
TG_REFC_PTR(TGBuffer);
//---------------------------------------------------------------------
class TGBuffer : public TGReferenceCounter
{
public:
	TGBuffer();
	~TGBuffer();
	TGBuffer(const TGBuffer& buffer){};
	void Allocate(uint32_t size);
	const char* GetConstData();
	virtual void DelRef();
	uint32_t GetBufferSize();
	uint32_t GetDataSize();
	void Append(uint32_t start_offset, PTGBuffer data, uint32_t size);
private:
	QByteArray Buffer;
	PTGBufferPool Pool;
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGBuffer);
Q_DECLARE_METATYPE(PTGBuffer);
//---------------------------------------------------------------------

#endif // TGBuffer_h__