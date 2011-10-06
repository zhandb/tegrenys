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

typedef QMap<QString, QVariant>TGDataObjectAttributesMap;

class TGDataObject
{
public:
	TGDataObject();
	~TGDataObject();
	void SetAttribute(QString attribute_name, QVariant name);
	QVariant Attribute(QString attribute_name, QVariant default = QVariant());
public:
	QList<TGDataObject> ChildDataObjects;
private:
	TGDataObjectAttributesMap Attributes;
};

//-----------------------------------------------------------------------------


#endif