#include "stdafx.h"
#include "tegrenys.h"
#include <QHBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include "TGDataObject.h"
//#include "TGTreeModel.h"
#include "TGSqlite\TGSqlite.h"
#include "TGSqlite\TGSqliteQuery.h"
#include "TGGui\TGGuiBuilder.h"
#include "TGBaseTextureManager.h"
//#include "TGCodec\tgcodec.h"
#include "TGNetwork\TGNetworkService.h"

Tegrenys::Tegrenys(QWidget *parent, Qt::WFlags flags)
{

	//ui.setupUi(this);
	//tree = new QTreeView();
	//setCentralWidget(tree);

	//TGCodec codec;

	/*TGSqliteQuery q;
	TGDataRecord schema;
	q.Exec(&sq, "SELECT * FROM mytable", &schema);*/

	GB = new TGGuiBuider();
	//GB->Build(main_database);

	int r = 0;

	NS = new TGNetworkService();
	//Sleep(INFINITE);

	
	/*QVector<QVariant> data;

	data << "111" << "222" << "444";

	TGDataRecords data_set;

	data_set.push_back(new TGDataRecord(data));
	
	data.clear();
	data << "555" << "666" << "777" << "888";

	data_set.push_back(new TGDataRecord(data));
	
	data.clear();
	data << "aaa" << "bbb" << "ccc" << "ddd";

	data_set.push_back(new TGDataRecord(data));

	TGTreeModel* model = new TGTreeModel();
	model->AddColumn(0);
	model->AddColumn(1);
	model->AddColumn(2);

	model->SetDataSet(&data_set);*/

	//QStandardItem *parentItem = st_model.invisibleRootItem();
	//for (int i = 0; i < 4; ++i) 
	//{
	//	QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
	//	parentItem->appendRow(item);
	//	QStandardItem* col = new QStandardItem(QString("column %0").arg(i));
	//	QStandardItem* col2 = new QStandardItem(QString("column2 %0").arg(i));

	//	QList<QStandardItem*> lst;
	//	lst << col;

	//	QList<QStandardItem*> lst2;
	//	lst2 << col2;

	//	parentItem->insertColumn(1, lst);
	//	parentItem->insertColumn(2, lst2);
	//	//parentItem->insertColumn(3, lst);
	//	parentItem = item;
	//}

	//tree->setModel(model);

	//parentItem->setText("1312324");
}

Tegrenys::~Tegrenys()
{
	delete main_database;
}
