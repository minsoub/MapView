/*
 * MapLayerPanel.h
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 *  Description
 *      맵 레이어 판넬을 정의한다.
 */

#ifndef MAPLAYERPANEL_H_
#define MAPLAYERPANEL_H_

#include <QtGui>
#include "../lib_layer/LayerCheckBox.h"
#include "../lib_layer/ClickableLabel.h"
#include "../lib_layer/LayerDefine.h"
#include "../AMap.h"

typedef struct _CheckLableItem {
	int layerno;
	QString layername;
	LayerCheckBox* checkbox;
	ClickableLabel* label;
} CheckLabelItem;

class MapLayerPanel : public QWidget {
	Q_OBJECT
public:
	MapLayerPanel(QWidget* widget=0);
	int lastLayer() { return lastCheckedLayer; }
	bool lastCheck() { return lastCheckState; }
	void setCheck(int t, LayerVisible b);
	void setCheck(const QString& line);
	void selectAll();
	void unselectAll();
	QString getVisibleString();
	void createParentCheckBox(AMap* m);				// checkbox create
	void createParentCheckBox_UD(AMap* m, int idx);	// User defined map layer checkbox create
	void setLatCheckedLayer(int layertype) { lastCheckedLayer = layertype; }
	void clearAllCheckBox();
	void setCheckLayer(int idx, bool visible, LayerVisible allidvisible)
	{
		lastCheckedLayer = list[idx]->layerno;
		lastCheckState = visible;
		setCheck(lastCheckedLayer, allidvisible);
	}
	int getCheckboxListCount() { return list.count(); }
	LayerVisible allLayerState() { return alllayervisible; }
	void checkAllLayerState();
private:
	LayerDefine lyrdef;
	int lastCheckedLayer;
	bool lastCheckState;
	QList<CheckLabelItem*> list;

	QHBoxLayout* createCheckBox(int t);
	CheckLabelItem* find(int t);
	CheckLabelItem* find(const QString& sname);
	QVBoxLayout* vbox;
	AMap* map;
	LayerVisible alllayervisible;
	void clearLayout(QLayout *l);
signals:
	void checkboxclicked();
	void labelclicked();
	void maplayerselectall(bool b);
	void checkStateChanged(int layertype);
public slots:
	void checkClick(int layertype);
	void labelClick(int layertype);
};

#endif /* MAPLAYERPANEL_H_ */
