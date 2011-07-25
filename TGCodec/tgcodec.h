#ifndef TGCODEC_H
#define TGCODEC_H

#include "tgcodec_global.h"

class TGLibAvcodec;

class TGCODEC_EXPORT TGCodec
{
public:
	TGCodec();
	~TGCodec();

private:
	TGLibAvcodec* Codec;
};

#endif // TGCODEC_H
