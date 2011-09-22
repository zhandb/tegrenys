#ifndef TGRtspParser_h__
#define TGRtspParser_h__

#include "..\TGSystem\TGSystemTypes.h"

class TGRtspParser : public TGModule
{
	Q_OBJECT
public:
	TGRtspParser(UID module_uid, PTGModule system);
	~TGRtspParser();
};
#endif // TGRtspParser_h__