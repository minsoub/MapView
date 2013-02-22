/*
 * LeftPanel.cpp
 *
 *  Created on: 2012. 1. 16.
 *      Author: JMS
 *  Description : Map Editor 의 왼쪽 판넬을 구성한다.
 */

#include <iostream>
#include "LeftPanel.h"

LeftPanel::LeftPanel(QWidget *widget): QWidget(widget) {
	// TODO Auto-generated constructor stub

	QVBoxLayout* mainBox = new QVBoxLayout;
	tabWidget = new QTabWidget;
	QWidget* tab1 = new QWidget;
	QWidget* tab2 = new QWidget;

	// Tab1 define
	QVBoxLayout* tab1Box = new QVBoxLayout;

	buttonSelectAll = new QPushButton(tr("&Select All"));
	buttonUnSelectAll = new QPushButton(tr("&Unselect All"));
	connect(buttonSelectAll,   SIGNAL(clicked()),  this, SLOT(emitmaplayerselectall()));
	connect(buttonUnSelectAll, SIGNAL(clicked()),  this, SLOT(emitmaplayerunselectall()));


	QHBoxLayout* h1 = new QHBoxLayout;
	h1->addWidget(buttonSelectAll);
	h1->addWidget(buttonUnSelectAll);
	tab1Box->addLayout(h1);

	maplayerpanel = new MapLayerPanel;
	connect(maplayerpanel,   SIGNAL(labelclicked()),    this, SLOT(emitmaplayerchanged()));
	connect(maplayerpanel,   SIGNAL(checkboxclicked()), this, SLOT(emitmaplayervisiblechanged()));


	saTop = new QScrollArea;
	saTop->setWidgetResizable(true);
	saTop->setWidget(maplayerpanel);		// 스크롤 지역에 위젯 추가

	layerdetailspanel = new LayerDetailsPanel;
	connect(layerdetailspanel, SIGNAL(clicked()), this, SLOT(emitlayerdetailclicked()));
	layerdetailspanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layerdetailspanel->clearList();
	layerdetailspanel->refresh();
	layerdetailspanel->resize(200, 700);

	saBottom = new QScrollArea;
	saBottom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	saBottom->setWidget(layerdetailspanel);

	splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(saTop);
	splitter->addWidget(saBottom);
	splitter->setStretchFactor(0, 1);

	tab1Box->addWidget(splitter);

	// Tab2 define - User Defined Map List
	QVBoxLayout* tab2Box = new QVBoxLayout;
	udmappanel = new UserDefineMapPanel;
	connect(udmappanel,  SIGNAL(labelclicked(const int)), this, SLOT(emitudmaplayerchanged_UD(const int)));
	connect(udmappanel,  SIGNAL(checkboxclicked(const int)), this, SLOT(emitudmapvisiblechanged_UD(const int)));

	saTopUser = new QScrollArea;
	saTopUser->setWidgetResizable(true);
	saTopUser->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	saTopUser->setWidget(udmappanel);
	tab2Box->addWidget(saTopUser);

	buttonSelectAllUser = new QPushButton(tr("&Select All"));
	buttonUnSelectAllUser = new QPushButton(tr("&Unselect All"));
	connect(buttonSelectAllUser, SIGNAL(clicked()), this, SLOT(emitmaplayerselectall_UD()));
	connect(buttonUnSelectAllUser, SIGNAL(clicked()), this, SLOT(emitmaplayerunselectall_UD()));

	QHBoxLayout* h2 = new QHBoxLayout;
	h2->addWidget(buttonSelectAllUser);
	h2->addWidget(buttonUnSelectAllUser);
	tab2Box->addLayout(h2);

	maplayerpanel_UD = new MapLayerPanel;
	connect(maplayerpanel_UD, SIGNAL(labelclicked()),  this, SLOT(emitmaplayerchanged_UD()));
	connect(maplayerpanel_UD, SIGNAL(checkboxclicked()), this, SLOT(emitmaplayervisiblechanged_UD()));

	saCenterUser = new QScrollArea;
	saCenterUser->setWidgetResizable(true);
	saCenterUser->setWidget(maplayerpanel_UD);

	layerdetailspanel_UD = new LayerDetailsPanel;
	connect(layerdetailspanel_UD, SIGNAL(clicked()), this, SLOT(emitlayerdetailclicked_UD()));
	layerdetailspanel_UD->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layerdetailspanel_UD->resize(200, 700);

	saBottomUser = new QScrollArea;
	saBottomUser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	saBottomUser->setWidget(layerdetailspanel_UD);

	splitterUser = new QSplitter(Qt::Vertical);
	splitterUser->addWidget(saCenterUser);
	splitterUser->addWidget(saBottomUser);
	splitterUser->setStretchFactor(0, 1);

	tab2Box->addWidget(splitterUser);

	// QTabWidget layer add
	tab1->setLayout(tab1Box);
	tab2->setLayout(tab2Box);
	tabWidget->addTab(tab1, tr("Layer"));
	tabWidget->addTab(tab2, tr("User Defined Layer"));
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changedTabWidget(int)));

	mainBox->addWidget(tabWidget);
	setLayout(mainBox);
	setWindowTitle(tr("Layer selector"));
}

void LeftPanel::setLayerVisible(const QString& line)
{
	// Set layer visible
	maplayerpanel->setCheck(line);

	// Set ID visible
	for (int i=0; i<line.length(); i++) {
		ALayer* layer = map->findLayer((LayerType)i);
		if (layer != NULL) {
			map->setAllIdVisible(i, layer->layerVisible());
		}
	}
	map->setAllIdVisible(Layer_User, map->userLayer()->layerVisible());
}

void LeftPanel::setMap(AMap* m)
{
	map = m;
}

/**
 * layerdetail에 해당 id를 보여준다.
 * maplayerpanel의 label이 클릭되었을 때 해당 layer의 각 id를 보여준다.
 * 이 때 각 id는 visible 여부를 가지고 있다.
 */
void LeftPanel::displayDetails(int t)
{
	QStringList list;
	if (map == NULL) return;
	map->idList(t, list);
	layerdetailspanel->setLayerType(t);
	layerdetailspanel->clearList();

	for (int i=0; i<list.count(); i++) {
		QString idname;
		bool visible = false;
		QStringList tmp = list[i].split(":");
		if (tmp.count() == 2) {
			idname = tmp[0];
			visible = tmp[1] == "1";
		}
		layerdetailspanel->add(t, idname, visible);
	}
	layerdetailspanel->refresh();
}

/**
 * Select all or Unselect all
 */
void LeftPanel::emitmaplayerselectall()
{
	maplayerpanel->selectAll();
	map->setAllLayerVisible(true);

	// detail panel을 다시 보여준다.
	int lastChoicedLayer = maplayerpanel->lastLayer();
	displayDetails((LayerType)lastChoicedLayer);

	// detail도 모두 check
	QString s = maplayerpanel->getVisibleString();
	emit changed(s);
}

/**
 * Unselectall click
 */
void LeftPanel::emitmaplayerunselectall()
{
	maplayerpanel->unselectAll();
	map->setAllLayerVisible(false);

	qDebug() << "debug1";
	// detail panel을 다시 보여준다.
	int lastChoicedLayer = maplayerpanel->lastLayer();
	displayDetails((LayerType)lastChoicedLayer);
	qDebug() << "debug2";
	QString s = maplayerpanel->getVisibleString();
	qDebug() << "debug3";
	emit changed(s);
}

/**
 * check가 클릭시 특정 maplayer가 선택되고 visible이 모두 변경됨
 */
void LeftPanel::emitmaplayervisiblechanged()
{
	LayerVisible layervisible = Unvisible;

	int lastChoicedLayer = maplayerpanel->lastLayer();
	bool visible = maplayerpanel->lastCheck();

	if (map == NULL) return;

	if (visible == true) {		// 그 레이어의 모든 id를 visible 세팅
		layervisible = Visible;
	}
	map->setLayerVisible(lastChoicedLayer, layervisible);
	map->setAllIdVisible(lastChoicedLayer, visible);
	displayDetails((LayerType)lastChoicedLayer);

	QString s = maplayerpanel->getVisibleString();
	emit changed(s);
}

/**
 * maplayer가 변경되었다면 해당 레이어의 ID를 모두 표시한다.
 */
void LeftPanel::emitmaplayerchanged()
{
	int lastChoicedLayer = maplayerpanel->lastLayer();

	// detail을 변경한다.
	if (map != NULL && lastChoicedLayer != Layer_Unknown) {
		displayDetails((LayerType)lastChoicedLayer);
	}else {
		layerdetailspanel->clearList();
		layerdetailspanel->refresh();
	}
	QString s = maplayerpanel->getVisibleString();
	emit changed(s);
}

/**
 * detail id가 클릭되었을 때
 */
void LeftPanel::emitlayerdetailclicked()
{
	int t = layerdetailspanel->layerType();
	QString id = layerdetailspanel->clickedId();
	bool visible = layerdetailspanel->visibleState();
	LayerVisible allvisible = layerdetailspanel->allIdState();

	map->setLayerVisible(t, allvisible);
	maplayerpanel->setCheck(t, allvisible);

	emit emitlayerdetailclicked(t, id, allvisible, visible);
}

/**
 * maplayer panel과 layerdetail을 수정한다.
 */
void LeftPanel::changeLastSelectLayer(LayerType t)
{
	maplayerpanel->setCheck(t, Visible);
}

/**
 * 상단 CheckBox 생성
 */
void LeftPanel::displayParentCheckBoxList(AMap* m)
{
	maplayerpanel->createParentCheckBox(m);
}


void LeftPanel::displayUDMCheckBoxList(AMap* m)
{
	if (udMap != NULL) {
		maplayerpanel_UD->clearAllCheckBox();
		layerdetailspanel_UD->clearAllCheckBox();
		udMap = NULL;
	}
	udmappanel->createUDMCheckBox(m);			// UserDefined Map List 생성
}

void LeftPanel::setLayerVisible_UD()
{
	LayerVisible allidvisible = Visible;
	bool visible = true;
	int lastChoicedLayer;
	udmappanel->selectAll();			// 전체 맵 선택

	for (int idx=0; idx < udmappanel->getUDMapListCount(); idx++)
	{
		udMap = map->getUDMap(idx);			// Set UserDefined Map
		udMap->setVisible(visible);
		maplayerpanel_UD->createParentCheckBox_UD(map, idx);		// UserDefined Map's Layer 생성
		emit signalUDMapVisibleChanged_UD();						// UserDefinedMap 변경됨 => MainLayout -> MapCanvas에 맵 전달

		for (int i=0; i<maplayerpanel_UD->getCheckboxListCount(); i++)
		{
			maplayerpanel_UD->setCheckLayer(i, visible, allidvisible);
			lastChoicedLayer = maplayerpanel_UD->lastLayer();
			udMap->setLayerVisible(lastChoicedLayer, allidvisible);
			udMap->setAllIdVisible(lastChoicedLayer, visible);
			displayDetails_UD((LayerType)lastChoicedLayer);
		}
	}
}

/**
 * UserDefined Map 탭에서 라벨을 클릭했을 때 호출되는 Slot
 */
void LeftPanel::emitudmaplayerchanged_UD(const int idx)
{
	LayerVisible allidvisible;
	udMap = map->getUDMap(idx);			// Set UserDefined Map
	bool visible;

	maplayerpanel_UD->createParentCheckBox_UD(map, idx);		// UserDefined Map's Layer 생성

	emit signalUDMapVisibleChanged_UD();						   // UserDefinedMap 변경됨 => MainLayout->MapCanvas에 맵 전달

	for (int i=0; i<maplayerpanel_UD->getCheckboxListCount(); i++)
	{
		visible = udMap->layer(i)->getLayer()->layerVisible();
		allidvisible = udMap->layer(i)->allIdState();
		maplayerpanel_UD->setCheckLayer(i, visible, allidvisible);
		emitmaplayerchanged_UD();
	}
}

/**
 * 체크박스 클릭 : UserDefined Map ==> Layer 생성
 */
void LeftPanel::emitudmapvisiblechanged_UD(const int idx)
{
	LayerVisible allidvisible = Unvisible;
	bool visible = udmappanel->lastCheck();

	if (visible) allidvisible = Visible;

	udMap = map->getUDMap(idx);		// Set UserDefined Map
	udMap->setVisible(visible);

	maplayerpanel_UD->createParentCheckBox_UD(map, idx);		// UserDefined Map's Layer 생성
	emit signalUDMapVisibleChanged_UD();		// UserDefinedMap 변경됨 => MainLayout -> MapCanvas에 맵 전달

	// User Defined Map 에 선택된 Layer를 출력하도록 메소드를 호출한다.
	for (int i=0; i<maplayerpanel_UD->getCheckboxListCount(); i++)
	{
		maplayerpanel_UD->setCheckLayer(i, visible, allidvisible);
		maplayervisiblechanged_UD();		// Layer select
	}
}

/**
 * 특정 maplayer가 선택되고 visible이 모두 변경됨
 */
void LeftPanel::maplayervisiblechanged_UD()
{
	if (udMap == NULL) return;

	LayerVisible layervisible = Unvisible;
	int lastChoicedLayer = maplayerpanel_UD->lastLayer();
	bool visible = maplayerpanel_UD->lastCheck();

	if (visible == true) {		// 그 레이어의 모든 visible 셋팅
		layervisible = Visible;
	}
	//qDebug() << "maplayervisiblechanged_UD() " << visible << layervisible << lastChoicedLayer;
	udMap->setLayerVisible(lastChoicedLayer, layervisible);
	udMap->setAllIdVisible(lastChoicedLayer, visible);
	displayDetails_UD((LayerType)lastChoicedLayer);

	QString s = maplayerpanel_UD->getVisibleString();
	emit changed(s);
}

/**
 * 특정 maplayer가 선택되고 visible이 모두 변경됨
 */
void LeftPanel::emitmaplayervisiblechanged_UD()
{
	if (udMap == NULL) return;

	LayerVisible layervisible = Unvisible;
	int lastChoicedLayer = maplayerpanel_UD->lastLayer();
	bool visible = maplayerpanel_UD->lastCheck();

	if (visible == true) {		// 그 레이어의 모든 visible 셋팅
		layervisible = Visible;
	}
	udMap->setLayerVisible(lastChoicedLayer, layervisible);
	udMap->setAllIdVisible(lastChoicedLayer, visible);
	displayDetails_UD((LayerType)lastChoicedLayer);

	LayerVisible alllayervisible = maplayerpanel_UD->allLayerState();
	udmappanel->setCheck(udMap->ID(), alllayervisible);

	QString s = maplayerpanel_UD->getVisibleString();
	emit changed(s);
}

void LeftPanel::displayDetails_UD(int t)
{
	QStringList list;
	if (udMap == NULL) return;
	udMap->idList(t, list);
	layerdetailspanel_UD->setLayerType(t);
	layerdetailspanel_UD->clearList();

	for (int i=0; i<list.count(); i++) {
		QString idname;
		bool visible = false;
		QStringList tmp = list[i].split(":");
		if (tmp.count() == 2) {
			idname = tmp[0];
			visible = tmp[1] == "1";
		}
		layerdetailspanel_UD->add(t, idname, visible);
	}
	layerdetailspanel_UD->refresh();
}

/**
 * User Define Map 판넬에서 select 버튼 클릭시 호출되는 Slot
 */
void LeftPanel::emitmaplayerselectall_UD()
{
	if (udMap == NULL) return;
	maplayerpanel_UD->selectAll();
	udMap->setAllLayerVisible(true);

	// detail panel을 다시 보여준다.
	int lastChoicedLayer = maplayerpanel_UD->lastLayer();
	displayDetails_UD((LayerType)lastChoicedLayer);

	// detail도 모두 check해준다.
	QString s = maplayerpanel_UD->getVisibleString();
	emit changed(s);
}

/**
 * unselectall 클릭시
 */
void LeftPanel::emitmaplayerunselectall_UD()
{
	if (udMap == NULL) return;
	maplayerpanel_UD->unselectAll();
	udMap->setAllLayerVisible(false);

	// detail panel을 다시 보여준다.
	int lastChoicedLayer = maplayerpanel_UD->lastLayer();
	displayDetails_UD((LayerType)lastChoicedLayer);

	QString s = maplayerpanel_UD->getVisibleString();
	emit changed(s);
}

/**
 * maplayer가 변경되었다면 해당하는 레이어의 ID를 모두 표시한다.
 */
void LeftPanel::emitmaplayerchanged_UD()
{
	int lastChoicedLayer = maplayerpanel_UD->lastLayer();

	// detail을 변경한다.
	if (udMap != NULL && lastChoicedLayer != Layer_Unknown) {
		displayDetails_UD((LayerType)lastChoicedLayer);
	}else {
		layerdetailspanel_UD->clearList();
		layerdetailspanel_UD->refresh();
	}
	QString s = maplayerpanel_UD->getVisibleString();
	emit changed(s);
}

/**
 * detail id가 클릭되었을 때
 */
void LeftPanel::emitlayerdetailclicked_UD()
{
	int t = layerdetailspanel_UD->layerType();
	QString id = layerdetailspanel_UD->clickedId();
	bool visible = layerdetailspanel_UD->visibleState();
	LayerVisible allvisible = layerdetailspanel_UD->allIdState();

	udMap->setLayerVisible(t, allvisible);
	maplayerpanel_UD->setCheck(t, allvisible);

	maplayerpanel_UD->checkAllLayerState();
	LayerVisible alllayervisible = maplayerpanel_UD->allLayerState();
	udmappanel->setCheck(udMap->ID(), alllayervisible);

	emit emitlayerdetailclicked_UD(t, id, allvisible, visible);
}

void LeftPanel::changedTabWidget(int idx)
{
	emit signalTabChanged(idx);
}
