#ifndef TGVideoStructs_h__
#define TGVideoStructs_h__

struct TGBufferLockStruct
{
	uint32_t Width;
	uint32_t Height;
	UCHAR* Data;
	uint32_t Pitch;
};

#endif // TGVideoStructs_h__