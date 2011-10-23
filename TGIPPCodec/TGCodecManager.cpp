#include "TGCodecManager.h"
#include "TGMJPEGDecoder.h"
#include "..\TGSystem\tgsystem.h"
//---------------------------------------------------------------------------

TGCodecManager::TGCodecManager(UID module_uid, PTGSystem system) : TGModule(module_uid, system)
{
	TGSystem* sys = (TGSystem*)&*system;
	sys->RegisterFactoryModuleType(TGMJPEG_DECODER_TYPE_UID, this);
}
//---------------------------------------------------------------------------

TGCodecManager::~TGCodecManager()
{

}
//---------------------------------------------------------------------------

PTGModule TGCodecManager::CreateModuleProc(UID type_id, UID module_id)
{
	if (type_id == TGMJPEG_DECODER_TYPE_UID)
		return new TGMJPEGDecoder(module_id, System);

	return NULL;
}
//---------------------------------------------------------------------------
