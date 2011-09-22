#ifndef TGHttpTagParser_h__
#define TGHttpTagParser_h__
//-------------------------------------------------------------------
#include "..\TGSystem\TGSystemTypes.h"
#include "TGBaseDataParser.h"
//-------------------------------------------------------------------
#define MAX_HTTP_TAG_LENGTH 1024
//-------------------------------------------------------------------
typedef TGMap<TGString, TGString> TGHttpTagMap;

class TGHttpTagParser
{	
public:
	TGHttpTagParser();
	~TGHttpTagParser();
	void ParseData(TGDataFragmentList& data_fragments, TGHttpTagMap& tag_map);
};
//-------------------------------------------------------------------

#endif // TGHttpTagParser_h__