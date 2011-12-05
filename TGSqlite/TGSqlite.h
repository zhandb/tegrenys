#ifndef TGSqlite_h__
#define TGSqlite_h__

#include "sqlite3.h"
#include <QtCore\QString>

class TGSqlite
{
public:
	TGSqlite();
	~TGSqlite();
	void OpenDatabase(QString filename);
	void CloseDatabase();
private:
	sqlite3 *db; 
	

friend class TGSqliteQuery;
};

#endif // TGSqlite_h__