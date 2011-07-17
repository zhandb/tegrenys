#include "stdafx.h"
#include "TGSqliteQuery.h"

//-----------------------------------------------------------------------------

TGSqliteQuery::TGSqliteQuery()
{
	Query = NULL;
	ColumnCount = 0;
}
//-----------------------------------------------------------------------------

TGSqliteQuery::~TGSqliteQuery()
{
	sqlite3_finalize(Query);
	Query = NULL;
}
//-----------------------------------------------------------------------------

void TGSqliteQuery::Exec(TGSqlite* database, QString sql, TGDataRecord* schema)
{
	QByteArray sql_utf8 = sql.toUtf8();

	sqlite3_prepare_v2(database->db, sql_utf8, sql_utf8.size(), &Query, NULL);

	ColumnCount = sqlite3_column_count(Query);
	schema->clear();

	for (int i = 0; i < ColumnCount; ++i)
	{
		const char* column_name = sqlite3_column_name(Query, i);
		schema->push_back(column_name);	
	}
}
//-----------------------------------------------------------------------------

bool TGSqliteQuery::Read(TGDataRecord* data)
{
	bool res = false;

	data->clear();

	int sqlite_res = sqlite3_step(Query);
	if (sqlite_res == SQLITE_ROW)
	{
		res = true;

		for (int i = 0; i < ColumnCount; ++i)
		{
			QString s;
			s = (char*)sqlite3_column_text(Query, i);

			data->push_back(s);
		}
	}

	return res;
}

//-----------------------------------------------------------------------------

