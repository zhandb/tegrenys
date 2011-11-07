#include "stdafx.h"
#include "TGSqlite.h"
//-----------------------------------------------------------------------------
//TODO: убрать main_database
TGSqlite* TGSqlite::main_database;

TGSqlite::TGSqlite()
{
	db = NULL;
}
//-----------------------------------------------------------------------------

TGSqlite::~TGSqlite()
{
	CloseDatabase();
}
//-----------------------------------------------------------------------------

void TGSqlite::OpenDatabase(QString filename)
{
	CloseDatabase();
	sqlite3_open_v2(filename.toUtf8(), &db, SQLITE_OPEN_READWRITE /*| SQLITE_OPEN_CREATE*/, NULL);
}
//-----------------------------------------------------------------------------

void TGSqlite::CloseDatabase()
{
	if (db)
	{
		sqlite3_close(db);
		db = NULL;
	}
}
//---------------------------------------------------------------------
TGSqlite* TGSqlite::GetMainDatabase()
{
	return main_database;
}