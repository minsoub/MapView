/*
 * XpmPickerDialog.cpp
 *
 *  Created on: 2012. 3. 2.
 *      Author: HIST002
 */
#include <iostream>
#include <QDir>

#include "XpmPickerDialog.h"

XpmPickerDialog::XpmPickerDialog(const QString& dir, QWidget* parent):QDialog(parent) {
	// TODO Auto-generated constructor stub
	symboldir = dir;		// symbol directory
	std::cout << "XpmPickerDialog create symboldir : " << symboldir.toStdString() << "\n";

	model = new QStandardItemModel(this);

	QHBoxLayout* hbox1 = new QHBoxLayout;
	labelDir = new QLabel(dir);
	buttonRefresh = new QPushButton("&Refresh");
	hbox1->addWidget(labelDir);
	hbox1->addWidget(buttonRefresh);
	connect(buttonRefresh, SIGNAL(clicked()), this, SLOT(loadIcons()));

	listView = new QListView(this);
	loadIcons();
	listView->setModel(model);
	QHBoxLayout* hbox2 = new QHBoxLayout;

	buttonOk = new QPushButton("&Ok");
	buttonCancel = new QPushButton("&Cancel");

	connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

	hbox2->addStretch();
	hbox2->addWidget(buttonOk);
	hbox2->addWidget(buttonCancel);
	hbox2->addStretch();

	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addLayout(hbox1);
	vbox->addWidget(listView);
	vbox->addLayout(hbox2);
	setLayout(vbox);

	setWindowTitle(tr("symbol selector"));
}

void XpmPickerDialog::loadIcons()
{
	QDir dir(symboldir);
	if (!dir.exists()) return;

	QStringList filters;
	filters += "*.xpm";

	QStringList xpmFileList = dir.entryList(filters, QDir::Files);

	model->clear();

	std::cout << "xpm size : " << xpmFileList.size() << "\n";
	std::cout << "symboldir : " << symboldir.toStdString() << "\n";
	foreach(QString s, xpmFileList)
	{
		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg(s);
		std::cout << "full name : " << fullname.toStdString() << "\n";
		QPixmap icon(fullname);

		QPixmap batang(QSize(icon.width()+2, icon.height()+2));
		batang.fill(QColor(0, 0, 0));

		QPainter painter(&batang);
		painter.initFrom(this);
		painter.drawPixmap(1, 1, icon);

		QStandardItem* item = new QStandardItem(QIcon(batang), s);

		model->appendRow(item);
	}
}

void XpmPickerDialog::done(int result)
{
	if (result == QDialog::Accepted) {
		QModelIndex idx = listView->currentIndex();
		QStandardItem* item = model->itemFromIndex(idx);
		if (item) {
			symbolname = item->text();
		}
	}
	QDialog::done(result);
}


