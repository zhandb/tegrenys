#ifndef TGDataObject_h__
#define TGDataObject_h__

#include <QVector>
#include <QList>
#include <QVariant>
#include <QAbstractItemModel>

struct TGDataRecord;

typedef QList<TGDataRecord*> TGDataRecords;

class TGDataRecord : public QVector<QVariant>
{
public:
	TGDataRecord();
	TGDataRecord(QVector<QVariant>& data);
	~TGDataRecord();
};

//-----------------------------------------------------------------------------


#endif