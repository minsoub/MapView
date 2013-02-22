/*
 * TrackReportOption.cpp
 *
 *  Created on: 2012. 5. 09.
 *      Author: JMS
 *  Description : 데이터 블록에 현시할 수 있는 리스트를 보여준다.
 *                     사용자가 데이터 블록에 현시 할 리스트를 선택하면 맵을 다시 그려야 한다..
 */
#include "TrackReportOption.h"

TrackReportOption::TrackReportOption(QWidget *parent)
    : QWidget(parent)
{
	setupUi(this);

	connect(btnLeft,  SIGNAL(clicked()), this, SLOT(listLeft()));
	connect(btnRight, SIGNAL(clicked()), this, SLOT(listRight()));
	connect(btnDone,  SIGNAL(clicked()), this, SLOT(optionSave()));

	listDataBlock->setEditTriggers(QAbstractItemView::NoEditTriggers );
	listDataBlock->setSelectionMode(QAbstractItemView::ExtendedSelection);
	listSelectDataBlock->setEditTriggers(QAbstractItemView::NoEditTriggers );
	listSelectDataBlock->setSelectionMode(QAbstractItemView::ExtendedSelection);

	cboBlock->addItem("All");
	cboBlock->addItem("5");
	cboBlock->addItem("10");		// default
	cboBlock->addItem("20");
	cboBlock->setCurrentIndex(2);
}

TrackReportOption::~TrackReportOption()
{

}

/**
 * The selected data block move data blocks.
 */
void TrackReportOption::listLeft()
{
	QList<QListWidgetItem *> list = listSelectDataBlock->selectedItems();

	for (int i=0; i<list.size(); i++) {
		QListWidgetItem *at = list[i];
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText(at->text());
		listSelectDataBlock->removeItemWidget(at);
		delete at;
	}
}

/**
 * The data block move the selected data block.
 */
void TrackReportOption::listRight()
{
	QList<QListWidgetItem *> list = listDataBlock->selectedItems();

	for (int i=0; i<list.size(); i++) {
		QListWidgetItem *at = list[i];
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText(at->text());
		listDataBlock->removeItemWidget(at);
		delete at;
	}
}

/**
 * Selected Option data send MapCanvas class.
 * setReportOption signals is occured.
 */
void TrackReportOption::optionSave()
{

	option->Clear();
	for (int i=0; i<listSelectDataBlock->count(); i++) {
		QString data = listSelectDataBlock->item(i)->text();
		setFlag(data);
	}

	if (cboBlock->currentIndex() != -1) {
		if (cboBlock->currentText() == "All") {
			option->blockCount = 0;
		}else {
			option->blockCount = cboBlock->currentText().toInt();
		}
	}

	emit setReportOption();

	close();
}

/**
 * ReportOption set
 */
void TrackReportOption::setFlag(QString data)
{
	if (data == "Track Number") {
		option->trackNumber = true;
	}else if(data == "Assigned FL") {
		option->assignedFL = true;
	}else if(data == "Warning") {
		option->warning = true;
	}else if(data == "SSR") {
		option->ssr = true;
	}else if(data == "Callsign") {
		option->callsing = true;
	}else if(data == "Mode-C") {
		option->modec = true;
	}else if(data == "Velocity") {
		option->velocity = true;
	}
}
/**
 * QListItem에 출력할 리스트를 재구성한다.
 */
void TrackReportOption::refreshList(ReportOption *opt)
{
	option = opt;

	listDataBlock->clear();
	listSelectDataBlock->clear();

	if (!option->trackNumber) {
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText("Track Number");
	}else {
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText("Track Number");
	}

	if (!option->assignedFL) {
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText("Assigned FL");
	}else {
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText("Assigned FL");
	}

	if (!option->warning) {
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText("Warning");
	}else {
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText("Warning");
	}

	if (!option->ssr) {
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText("SSR");
	}else {
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText("SSR");
	}

	if (!option->callsing) {
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText("Callsign");
	}else {
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText("Callsign");
	}

	if (!option->modec) {
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText("Mode-C");
	}else {
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText("Mode-C");
	}

	if (!option->velocity) {
		QListWidgetItem *item = new QListWidgetItem(listDataBlock);
		item->setText("Velocity");
	}else {
		QListWidgetItem *item = new QListWidgetItem(listSelectDataBlock);
		item->setText("Velocity");
	}
}
