#include "TGCodecManager.h"
#include "TGMJPEGDecoder.h"
#include "..\TGSystem\tgsystem.h"
#include "tgippcodec.h"
#include <QtCore\QtPlugin>
//---------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(TGIPPCodec, TGCodecManager);
//---------------------------------------------------------------------------

TGCodecManager::TGCodecManager(UID module_uid, PTGSystem system) : TGModule(module_uid, system)
{
	
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

void TGCodecManager::RegisterModuleTypes(PTGSystem system)
{
	System = system;
	system->RegisterFactoryModuleType(TGMJPEG_DECODER_TYPE_UID, this);
}
//---------------------------------------------------------------------------
