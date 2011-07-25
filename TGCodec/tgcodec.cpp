#include "tgcodec.h"
#include <windows.h>
#include "TGLibAvcodec.h"

TGCodec::TGCodec()
{
	Codec = new TGLibAvcodec();
	//Codec->OpenFile("g:\\A Christmas Carol 3D Half-SBS.mkv");
	Codec->OpenFile("j:\\mammamia.avi");
	while (true)
	{
		Codec->ReadFrame();
	}
}

TGCodec::~TGCodec()
{
	delete Codec;
}
