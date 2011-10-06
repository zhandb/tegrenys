#include "TGDataObject.h"

//-----------------------------------------------------------------------------

TGDataRecord::TGDataRecord(QVector<QVariant>& data) : QVector<QVariant>(data)
{
}
//-----------------------------------------------------------------------------

TGDataRecord::TGDataRecord()
{

}
//-----------------------------------------------------------------------------

TGDataRecord::~TGDataRecord()
{
}
//-----------------------------------------------------------------------------

TGDataObject::TGDataObject()
{

}
//---------------------------------------------------------------------------

TGDataObject::~TGDataObject()
{

}
//---------------------------------------------------------------------------

void TGDataObject::SetAttribute(QString attribute_name, QVariant name)
{
	Attributes[attribute_name] = name;
}
//---------------------------------------------------------------------------

QVariant TGDataObject::Attribute(QString attribute_name, QVariant default /*= QVariant()*/)
{
	TGDataObjectAttributesMap::iterator i = Attributes.find(attribute_name);
	if (i != Attributes.end())
		return *i;
	else

		return default;
}
//---------------------------------------------------------------------------

