#ifndef TGSqliteQuery_h__
#define TGSqliteQuery_h__

#include "sqlite3.h"
#include "TGSqlite.h"
#include "TGDataObject.h"

class TGSqliteQuery
{
public:
	TGSqliteQuery();
	~TGSqliteQuery();
	void Exec(TGSqlite* database, QString sql, TGDataRecord* schema);
	bool Read(TGDataRecord* data);
private:
	sqlite3_stmt* Query; 
	int ColumnCount;
};
#endif // TGSqliteQuery_h__