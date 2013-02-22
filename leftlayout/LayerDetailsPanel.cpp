/*
 * LayerDetailsPanel.cpp
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */
#include <iostream>
#include <QtGui>

#include "LayerDetailsPanel.h"

LayerDetailsPanel::LayerDetailsPanel(QWidget* parent):QWidget(parent) {
	// TODO Auto-generated constructor stub
	vboxMain = NULL;
	list = NULL;
	setWindowTitle(tr("layerid selector"));
}

const QString LayerDetailsPanel::getLayerName(int type)
{
	QString retval = "";

	switch(type) {
	case GroupLayer_Airport:
		retval = "AIRPORT";
		break;
	case GroupLayer_Waypoint:
		retval = "WAYPOINT";
		break;
	case GroupLayer_Navaids:
		retval = "NAVAIDS";
		break;
	case Layer_Coast:
		retval = "COAST";
		break;
	case Layer_Fir:
		retval = "FIR";
		break;
	case Layer_Kadiz:
		retval = "KADIZ";
		break;
	case Layer_Sector:
		retval = "SECTOR";
		break;
	case Layer_Tca:
		retval = "TCA";
		break;
	case Layer_Ra:
		retval = "RA";
		break;
	case Layer_Da:
		retval = "DA";
		break;
	case Layer_Pa:
		retval = "PA";
		break;
	case Layer_Aa:
		retval = "AA";
		break;
	case Layer_Moa:
		retval = "MOA";
		break;
	case Layer_Msaw:
		retval = "MSAW";
		break;
	case Layer_Cata:
		retval = "CATA";
		break;
	case Layer_Ad_Civil:
		retval = "AD_CIVIL";
		break;
	case Layer_Ad_Joint:
		retval = "AD_JOINT";
		break;
	case Layer_Runway:
		retval = "RUNWAY";
		break;
	case Layer_Rep_Fix:
		retval = "REP_FIX";
		break;
	case Layer_Fix:
		retval = "FIX";
		break;
	case Layer_T_Fix:
		retval = "T_FIX";
		break;
	case Layer_Vortac:
		retval = "VORTAC";
		break;
	case Layer_Vordme:
		retval = "VORDME";
		break;
	case Layer_Ndb:
		retval = "NDB";
		break;
	case Layer_Route:
		retval = "ROUTE";
		break;
	case Layer_Hold:
		retval = "HOLD";
		break;
	case Layer_Sensor:
		retval = "SENSOR";
		break;
	case Layer_Sid:
		retval = "SID";
		break;
	case Layer_Star:
		retval = "STAR";
		break;
	case Layer_Apch:
		retval = "APCH";
		break;
    case Layer_Airspace:
            retval = "AIRSPACE";
            break;
    case Layer_Vfr_Rp:
            retval = "VFR_RP";
            break;
    case Layer_Obstacles:
            retval = "OBSTACLES";
            break;
    case Layer_Vfr_Cp:
            retval = "VFR_CP";
            break;
    case Layer_Vfr_Route:
            retval = "VFR_ROUTE";
            break;
    case Layer_Mva:
            retval = "MVA";
            break;
	case Layer_User:
		retval = "USER";
		break;
	default:
		retval = "";
	}

	return retval;
}

void LayerDetailsPanel::clearLayout(QLayout* l)
{
	if (l == NULL) return;
	QLayoutItem* child;
	while((child = l->takeAt(0)) != 0) {
		if (child->layout()) {
			clearLayout((QLayout*)child->layout());
		}
		child->widget()->hide();
		delete child;
	}
}

void LayerDetailsPanel::clearAllWidgets()
{
	clearLayout(vboxMain);
	if (vboxMain != NULL)
		delete vboxMain;
	vboxMain = NULL;
}

void LayerDetailsPanel::clearList()
{
	if (list != NULL) list->clear();
}

void LayerDetailsPanel::add(int type, const QString& id, bool checked)
{
	layertype = type;
	if (list == NULL) {
		list = new VectorCheckBox;
	}
	IdCheckBox* cb = new IdCheckBox(type, id);
	connect(cb, SIGNAL(clicked(int, const QString&, bool)), this, SLOT(emitClick(int, const QString&, bool)));
	if (checked) cb->setCheckState(Qt::Checked);
	list->append(cb);
}

void LayerDetailsPanel::refresh()
{
	if (list == NULL) return;
	clearAllWidgets();
	if (vboxMain == NULL) {
		vboxMain = new QVBoxLayout;
	}
	QString title = getLayerName(layertype);
	QGroupBox* group = new QGroupBox(title);
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->setSpacing(0);
	for (int i=0; i<list->count(); i++) {
		vbox->addWidget(list->at(i));
	}
	if (list->count() == 0) {
		labelNoId = new QLabel("<font color=\"red\">No id!</font>");
		vbox->addWidget(labelNoId);
	}
	vbox->addStretch();
	group->setLayout(vbox);
	vboxMain->addWidget(group);
	vboxMain->update();
	int height = list->count() * 20;
	if(height < 700) height = 700;
	resize(200, height);
	setLayout(vboxMain);
}

void LayerDetailsPanel::emitClick(int t, const QString& id, bool visible)
{
	layertype = t;
	clickedid = id;
	visiblestate = visible;
	checkAllIdState();
	emit clicked();
}

/**
 * 현재 모든 리스트의 체크 상태를 바꾼다.
 */
void LayerDetailsPanel::setCheckStateAllWidget(bool b)
{
	if (list == NULL) return;
	for (int i=0; i<list->count(); i++) {
		IdCheckBox* cb = list->at(i);
		cb->setCheckState(Qt::Unchecked);
		if (b) cb->setCheckState(Qt::Checked);
	}
	clearAllWidgets();
	refresh();
}

/**
 * 모두 체크되었는지 Un체크되었는지 부분적으로 check되었는지 판단
 * allidvisible을 세팅한다.
 */
void LayerDetailsPanel::checkAllIdState()
{
	if (list == NULL) return;
	LayerVisible nowstate, prevstate;
	nowstate = prevstate = Visible;

	// 모두 check 되었는가?
	bool moduvisible = true;
	for (int i=0; i<list->count(); i++) {
		IdCheckBox* cb = list->at(i);
		if (cb->checkState() == Qt::Unchecked) {
			moduvisible = false;
			break;
		}
	}
	if (moduvisible) {
		allidvisible = Visible;
		return;
	}

	// 모두 Uncheck되었는가?
	bool moduunvisible = true;
	for (int i=0; i<list->count(); i++) {
		IdCheckBox* cb = list->at(i);
		if (cb->checkState() == Qt::Checked) {
			moduunvisible = false;
			break;
		}
	}
	if (moduunvisible) {
		allidvisible = Unvisible;
		return;
	}

	// 부분적으로
	allidvisible = PartiallyVisible;
	return;
}
