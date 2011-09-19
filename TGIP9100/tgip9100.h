#ifndef TGIP9100_H
#define TGIP9100_H

#include "tgip9100_global.h"
#include "..\TGSystem\TGSystemTypes.h"
#include "..\TGSystem\TGBuffer.h"

class TGIP9100_EXPORT TGIP9100 : public TGModule
{
	Q_OBJECT
public:
	TGIP9100(UID module_uid, PTGModule system);
	~TGIP9100();
	virtual void Init();

private:
	PTGModule NetworkService;
protected:
	virtual void ModuleCreatedProc(UID type_id, UID module_id, PTGModule module);
signals:
	void CreateSocket();
	void SocketConnect(TGString host, uint32_t remote_port, uint32_t localport);
	void Write(PTGBuffer data);

private slots:
	void OnSocketCreated(UID socket_uid);
	void OnSocketConnected();
};

#endif // TGIP9100_H
