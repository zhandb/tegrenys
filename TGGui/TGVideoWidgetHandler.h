#ifndef TGVideoWidgetHandler_h__
#define TGVideoWidgetHandler_h__
//-----------------------------------------------------------------------------
#include "TGSystemTypes.h"
#include "TGBaseVideoWidget.h"
//-----------------------------------------------------------------------------

class TGVideoWidgetHandler : public TGModule
{
	Q_OBJECT
public:
	TGVideoWidgetHandler(UID module_uid, PTGSystem system);
	~TGVideoWidgetHandler();
	virtual void Init();
	Q_INVOKABLE virtual void AddChildModule(UID module_uid, PTGModule module);

private:
	PTGBaseVideoWidget VideoWidget;
};
//-----------------------------------------------------------------------------
#endif // TGVideoWidgetHandler_h__