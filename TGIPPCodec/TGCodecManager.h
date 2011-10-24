#ifndef TGCodecManager_h__
#define TGCodecManager_h__
//---------------------------------------------------------------------------
#include "..\TGSystem\TGSystemTypes.h"
#include "tgippcodec_global.h"
#include "..\TGSystem\tgsystem.h"
//---------------------------------------------------------------------------
#define TGMJPEG_DECODER_TYPE_UID UID("{0DDC8946-E848-4eb9-BF16-82A16805217D}")
//---------------------------------------------------------------------------

class TGIPPCODEC_EXPORT TGCodecManager : public TGModule, TGModuleFactory
{
	Q_OBJECT
	Q_INTERFACES(TGModuleFactory)
public:
	TGCodecManager(){};
	TGCodecManager(UID module_uid, PTGSystem system);
	~TGCodecManager();
	virtual void RegisterModuleTypes(PTGSystem system);
protected:
	virtual PTGModule CreateModuleProc(UID type_id, UID module_id);

};
//---------------------------------------------------------------------------

#endif // TGCodecManager_h__