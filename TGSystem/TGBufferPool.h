#ifndef TGBufferPool_h__
#define TGBufferPool_h__
//---------------------------------------------------------------------
#include "TGRefCounter.h"
#include "TGBuffer.h"
//---------------------------------------------------------------------

class TGBufferPool : public TGReferenceCounter
{
public:
	TGBufferPool();
	~TGBufferPool();
	PTGBuffer Allocate();
};
//---------------------------------------------------------------------

#endif // TGBufferPool_h__