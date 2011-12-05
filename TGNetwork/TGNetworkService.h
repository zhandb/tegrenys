#ifndef TGNetworkService_h__
#define TGNetworkService_h__
//---------------------------------------------------------------------
#include <QtCore\QThread>
#include <winsock2.h>
#include <windows.h>
#include "tgnetwork_global.h"
#include "TGSocket.h"
#include <QtCore\QFile>
#include "TGEndSignatureParser.h"
#include "..\TGIPPCodec\TGMJPEGDecoder.h"
#include "..\TGSystem\TGSystemTypes.h"
#include "..\TGSystem\tgsystem.h"
//---------------------------------------------------------------------
class TGMJPEGDecoder;
//---------------------------------------------------------------------
#define TGSOCKET_TYPE_UID UID("{04AD711B-4536-4b78-B7DC-95D85809A1FA}")
#define TGHTTP_PARSER_TYPE_UID UID("{9E46B2FF-F5B6-4f0d-BCEC-DF1FBCEAD8F9}")
//---------------------------------------------------------------------

class TGNETWORK_EXPORT TGNetworkService :  public TGModule, TGModuleFactory
{
	Q_OBJECT
	Q_INTERFACES(TGModuleFactory)
public:
	TGNetworkService();
	TGNetworkService(UID module_uid, PTGSystem system);
	~TGNetworkService();
	virtual void RegisterModuleTypes(PTGSystem system);
protected:
	virtual PTGModule CreateModuleProc(UID type_id, UID module_id);
public slots:
	void timerEvent(QTimerEvent* event);
};
//---------------------------------------------------------------------
TG_REFC_PTR(TGNetworkService);
//---------------------------------------------------------------------

#endif // TGNetworkService_h__