#ifndef TGGuiModule_h__
#define TGGuiModule_h__

class TGGuiModule : public TGModule
{
	Q_OBJECT
public:
	TGGuiModule(UID module_uid, PTGModule system);
	~TGGuiModule();
};
#endif // TGGuiModule_h__