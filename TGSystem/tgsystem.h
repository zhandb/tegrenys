#ifndef TGSYSTEM_H
#define TGSYSTEM_H
//-----------------------------------------------------------
#include "TGSystemTypes.h"
#include "..\TGSqlite\TGSqlite.h"
//-----------------------------------------------------------
class TGSystem : public TGModule
{
public:
	TGSystem();
	~TGSystem();
	TGSqlite* GetDataBase();
	
private:
	TGString SystemPath;
	TGSqlite* SystemDataBase;
};

//-----------------------------------------------------------
#endif // TGSYSTEM_H
