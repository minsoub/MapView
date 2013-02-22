/*
 * MapLayerPanel.cpp
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */
#include <cmath>
#include "MapLayerPanel.h"

MapLayerPanel::MapLayerPanel(QWidget *widget): QWidget(widget) {
	// TODO Auto-generated constructor stub
	lastCheckedLayer = Layer_Coast;
	vbox = NULL;
}

void MapLayerPanel::clearLayout(QLayout *l)
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

/**
 * 생성된 모드 체크박스를 제거한다.
 */
void MapLayerPanel::clearAllCheckBox()
{
	list.clear();

	if (vbox != NULL)
	{
		clearLayout(vbox);
		delete vbox;
	}
	vbox = NULL;
}

/**
 * User Defined Map Layer checkbox 생성
 */
void MapLayerPanel::createParentCheckBox_UD(AMap* m, int idx)
{
	clearAllCheckBox();
	map = m;

	if (map == NULL) return;

	vbox = new QVBoxLayout;
	vbox->setSpacing(2);

	AUserDefinedMap* udm = map->getUDMap(idx);
	if (udm != NULL) {
		for (int i=0; i < udm->LayerCount(); i++) {
			LayerType layerType_UD = udm->layer(i)->layerType();
			vbox->addLayout(createCheckBox(layerType_UD));
		}
	}
	vbox->addStretch();
	setLayout(vbox);
}

/**
 * create checkbox
 */
void MapLayerPanel::createParentCheckBox(AMap* m)
{
	clearAllCheckBox();

	map = m;
	vbox = new QVBoxLayout;
	vbox->setSpacing(2);

	for (int i=0; i<map->layerCount(); i++) {
		ALayer* layer = map->layers(i);

		if (map->isMapFileLayer(layer->shortName().toUpper()))
		{
			//std::cout << "createParentCheckBox layer name : " << layer->shortName().toStdString() << "\n";
			vbox->addLayout(createCheckBox(layer->layerType()));
		}
	}
	vbox->addLayout(createCheckBox(Layer_User));
	vbox->addStretch();
	setLayout(vbox);
}

void MapLayerPanel::selectAll()
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItem* item = list[i];
		item->checkbox->setCheckState(Qt::Checked);
	}
}

void MapLayerPanel::unselectAll()
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItem* item = list[i];
		item->checkbox->setCheckState(Qt::Unchecked);
	}
}

/**
 * If the checkbox is clicked
 */
void MapLayerPanel::checkClick(int layertype)
{
	lastCheckedLayer = layertype;
	lastCheckState = false;
	CheckLabelItem* item = find(layertype);
	if (item != NULL) {
		lastCheckState = item->checkbox->checkState();
		if (lastCheckState) item->checkbox->setCheckState(Qt::Checked);
	}

	checkAllLayerState();
	emit checkboxclicked();
}

/**
 * If the label is clicked
 */
void MapLayerPanel::labelClick(int layertype)
{
	lastCheckedLayer = layertype;
	lastCheckState   = false;

	emit labelclicked();
}

void MapLayerPanel::setCheck(int t, LayerVisible visible)
{
	CheckLabelItem* item = find(t);
	if (item != NULL) {
		Qt::CheckState cs;

		if (visible == Visible) cs = Qt::Checked;
		else if(visible == PartiallyVisible) cs = Qt::PartiallyChecked;
		else cs = Qt::Unchecked;

		item->checkbox->setCheckState(cs);
	}
}

void MapLayerPanel::setCheck(const QString& line)
{
	unselectAll();

	for (int i=0; i<lyrdef.count(); i++) {
		int t = lyrdef.layerType(i);
		CheckLabelItem* item = find(t);
		if (item == NULL) continue;
		if (line[i] == QChar('1')) {
			item->checkbox->setCheckState(Qt::Checked);
		}else {
			item->checkbox->setCheckState(Qt::Unchecked);
		}
	}
}

CheckLabelItem* MapLayerPanel::find(int t)
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItem* item = list[i];
		if (item->layerno == t) return item;
	}
	return NULL;
}

CheckLabelItem* MapLayerPanel::find(const QString& sname)
{
	for (int i=0; i<list.count(); i++) {
		CheckLabelItem* item = list[i];
		if (item->layername == sname) return item;
	}
	return NULL;
}

QHBoxLayout* MapLayerPanel::createCheckBox(int t)
{
	QString sname;
	QString fname;
	if (t == 77) {		// Airport
		sname = "AIRPORT";
		fname = "AIRPORT";
	}else if(t == 88) {	// Waypoint
		sname = "WAYPOINT";
		fname = "WAYPOINT";
	}else if(t == 99) {
		sname = "NAVAIDS";
		fname = "WAYPOINT";
	}else {
		sname = lyrdef.shortName(t).toUpper();
		fname = lyrdef.fullName(t);
	}
	int no = t;

	LayerCheckBox* checkboxA = new LayerCheckBox(this, no);
	ClickableLabel* labelA   = new ClickableLabel(this, no, sname);

	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(checkboxA);
	hbox->addWidget(labelA);

	connect(checkboxA,  SIGNAL(clicked(int)), this, SLOT(checkClick(int)));
	connect(labelA,     SIGNAL(clicked(int)), this, SLOT(labelClick(int)));

	// list에 넣는다.
	CheckLabelItem* item = new CheckLabelItem;
	item->layerno = no;
	item->layername = sname;
	item->checkbox = checkboxA;
	item->label = labelA;
	list.append(item);

	return hbox;
}

/**
 * Visible string을 리턴한다.
 */
QString MapLayerPanel::getVisibleString()
{
	QString s = QString(lyrdef.count(), QChar('0'));

	for (int i=0; i<lyrdef.count(); i++) {
		int t = lyrdef.layerType(i);
		CheckLabelItem* item = find(t);
		if (item != NULL && item->checkbox->checkState() == Qt::Checked) {
			s[t] = QChar('1');
		}
	}

	return s;
}

void MapLayerPanel::checkAllLayerState()
{
	LayerVisible nowstate, prevstate;
	nowstate = prevstate = Visible;

	// 부분적으로 체크되었는가?
	bool moduPartially = true;
	for (int i=0; i<list.count(); i++) {
		CheckLabelItem* cb = list[i];
		if (cb->checkbox->checkState() == Qt::PartiallyChecked) {
			moduPartially = false;
			break;
		}
	}
	if (!moduPartially) {
		alllayervisible = PartiallyVisible;
		return;
	}

	// 모두 체크되었는가?
	bool moduvisible = true;
	for (int i=0; i<list.count(); i++) {
		CheckLabelItem* cb = list[i];
		if (cb->checkbox->checkState() == Qt::Unchecked) {
			moduvisible = false;
			break;
		}
	}
	if (moduvisible) {
		alllayervisible = Visible;
		return;
	}

	// 모두 Uncheck되었는가?
	bool moduunvisible = true;
	for (int i=0; i<list.count(); i++) {
		CheckLabelItem* cb = list[i];
		if (cb->checkbox->checkState() == Qt::Checked) {
			moduunvisible = false;
			break;
		}
	}
	if (moduunvisible) {
		alllayervisible = Unvisible;
		return;
	}
	alllayervisible = PartiallyVisible;
	return;
}
