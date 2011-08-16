#include "tgsystem.h"
#include <QCoreApplication>
//---------------------------------------------------------------------------
TGSystem::TGSystem() : TGModule(0, NULL)
{
	SystemPath = QCoreApplication::applicationDirPath();

	SystemDataBase = new TGSqlite();

	SystemDataBase->OpenDatabase(SystemPath + "/test.db");
}
//---------------------------------------------------------------------------

TGSystem::~TGSystem()
{
	delete SystemDataBase;
	SystemDataBase = NULL;
}
//---------------------------------------------------------------------------

TGSqlite* TGSystem::GetDataBase()
{
	return SystemDataBase;
}
//---------------------------------------------------------------------------

