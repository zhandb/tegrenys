#ifndef TGSqlite_h__
#define TGSqlite_h__

#include "sqlite3.h"
#include <QString>

class TGSqlite
{
public:
	TGSqlite();
	~TGSqlite();
	void OpenDatabase(QString filename);
	void CloseDatabase();
	static TGSqlite* GetMainDatabase();
private:
	sqlite3 *db; 
	static TGSqlite* main_database;

friend class TGSqliteQuery;
};

#endif // TGSqlite_h__