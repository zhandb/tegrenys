#ifndef TGIP9100_H
#define TGIP9100_H

#include "tgip9100_global.h"
#include "..\TGSystem\TGSystemTypes.h"

class TGIP9100_EXPORT TGIP9100 : public TGModule
{
	Q_OBJECT
public:
	TGIP9100(UID module_uid, PTGModule system);
	~TGIP9100();
	virtual void Init();

private:
	PTGModule NetworkService;
signals:
	void CreateSocket();
private slots:
	void OnSocketCreated(UID socket_uid);
};

#endif // TGIP9100_H
