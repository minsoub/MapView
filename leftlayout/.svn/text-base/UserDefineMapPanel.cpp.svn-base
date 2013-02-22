/*
 * UserDefineMapPanel.cpp
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */

#include "UserDefineMapPanel.h"

UserDefineMapPanel::UserDefineMapPanel(QWidget* widget):QWidget(widget) {
	// TODO Auto-generated constructor stub
	vbox = NULL;
}

/**
 * vbox children clear
 */
void UserDefineMapPanel::clearLayout(QLayout* l)
{
	if (l == NULL) return;

	QLayoutItem* child;
	while((child = l->takeAt(0)) != 0) {
		if (child->layout()) {
			clearLayout((QLayout*)child->layout());
		}
		delete child->widget();
		delete child;
	}
}

void UserDefineMapPanel::unselectAll()
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItemUD* item = list[i];
		item->checkbox->setCheckState(Qt::Unchecked);
	}
}

CheckLabelItemUD* UserDefineMapPanel::find(int t)
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItemUD* item = list[i];
		if (item->mapNo == t) return item;
	}
	return NULL;
}

/**
 * 체크박스가 클릭되었을 때
 */
void UserDefineMapPanel::checkClick(int idx)
{
	lastCheckedMap = idx;
	lastCheckState = false;
	CheckLabelItemUD* item = find(idx);
	if (item != NULL) {
		lastCheckState = item->checkbox->checkState();
		if (lastCheckState) item->checkbox->setCheckState(Qt::Checked);
	}
	emit checkboxclicked(idx);
}

/**
 * 라벨이 클릭되었을 때
 */
void UserDefineMapPanel::labelClick(int idx)
{
	lastCheckedMap = idx;
	lastCheckState = false;
	emit labelclicked(idx);
}

QHBoxLayout* UserDefineMapPanel::createCheckBox(int idx, const QString& mapName)
{
	LayerCheckBox* checkboxA = new LayerCheckBox(this, idx);
	ClickableLabel* labelA = new ClickableLabel(this, idx, mapName);

	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(checkboxA);
	hbox->addWidget(labelA);
	connect(checkboxA, SIGNAL(clicked(int)), this, SLOT(checkClick(int)));
	connect(labelA,    SIGNAL(clicked(int)), this, SLOT(labelClick(int)));

	// list에 넣는다.
	CheckLabelItemUD* item = new CheckLabelItemUD;
	item->mapNo = idx;
	item->mapName = mapName;
	item->checkbox = checkboxA;
	item->label = labelA;
	list.append(item);

	return hbox;
}

/**
 * User defined map list
 */
void UserDefineMapPanel::createUDMCheckBox(AMap* m)
{
	list.clear();

	if (vbox != NULL) {
		clearLayout(vbox);
		delete vbox;
	}
	vbox = NULL;

	map = m;
	if (map->getUDMap(0) == NULL) return;

	vbox = new QVBoxLayout;
	vbox->setSpacing(2);

	for (int i=0; i<map->udmListCount(); i++) {
		QString mapName = map->getUDMName(i);
		vbox->addLayout(createCheckBox(i, mapName));
	}
	vbox->addStretch();
	setLayout(vbox);
}

void UserDefineMapPanel::selectAll()
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItemUD* item = list[i];
		item->checkbox->setCheckState(Qt::Checked);
	}
}

void UserDefineMapPanel::setCheck(const QString& sname, LayerVisible visible)
{
	CheckLabelItemUD* item = find(sname);
	if (item != NULL) {
		Qt::CheckState cs;

		if (visible == Visible) cs = Qt::Checked;
		else if(visible == PartiallyVisible) cs = Qt::PartiallyChecked;
		else cs = Qt::Unchecked;

		item->checkbox->setCheckState(cs);
	}
}

CheckLabelItemUD* UserDefineMapPanel::find(const QString& sname)
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItemUD* item = list[i];
		if (item->mapName == sname) return item;
	}

	return NULL;
}
