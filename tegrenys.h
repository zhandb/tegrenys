#ifndef TEGRENYS_H
#define TEGRENYS_H

#include <QtGui/QMainWindow>
#include "ui_tegrenys.h"
#include "TGSystem\TGDataObject.h"
#include <QTreeView>
#include <QStandardItemModel>
#include "TGSqlite/TGSqlite.h"
#include "TGGui/TGGuiBuilder.h"
#include "TGNetwork/TGNetworkService.h"

//static TGSqlite* main_database;

class Tegrenys
{
public:
	Tegrenys(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Tegrenys();

private:
	//TGDataRecord* root;
	//QTreeView* tree;
	//QStandardItemModel st_model;

	//Ui::TegrenysClass ui;

	PTGGuiBuilder GB;
	PTGNetworkService NS;
	PTGModule  System;
	PTGBasePrimitive VideoRect;
	PTGModule IPServer;

};

#endif // TEGRENYS_H
