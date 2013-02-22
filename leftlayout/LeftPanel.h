/*
 * LeftPanel.h
 *
 *  Created on: 2012. 1. 16.
 *      Author: JMS
 *  Description : Map Editor 의 왼쪽 판넬을 구성한다.
 */

#ifndef LEFTPANEL_H_
#define LEFTPANEL_H_

#include <QtGui>
#include "MapLayerPanel.h"
#include "MapLayerDetailPanel.h"
#include "UserDefineMapPanel.h"
#include "LayerDetailsPanel.h"
#include "../lib_layer/MapDefine.h"


class LeftPanel : public QWidget {
	Q_OBJECT
public:
	LeftPanel(QWidget *widget=0);
	void setLayerVisible(const QString& line);
	void setLayerVisible_UD();
	void setMap(AMap* m);
	void displayDetails(int t);
	void displayParentCheckBoxList(AMap* m);	// maplayerpanel checkbox create
	void displayUDMCheckBoxList(AMap* m);		// UserDefinedMap checkbox create
	void detailsCheckAllIdState() { layerdetailspanel->checkAllIdState(); }
	AUserDefinedMap* getUserDefinedMap() {
		if (udMap == NULL) return NULL;
		return udMap;
	}
	void setTab(int idx) { tabWidget->setCurrentIndex(idx); }
	void setUserDefinedTabEnabled(bool enable) { tabWidget->setTabEnabled(1, enable); }
	void maplayervisiblechanged_UD();
private:

	QTabWidget*  tabWidget;
	QPushButton* buttonSelectAll;
	QPushButton* buttonUnSelectAll;
	QScrollArea* saTop;
	QSplitter*   splitter;
	QScrollArea* saBottom;

	QPushButton* buttonSelectAllUser;
	QPushButton* buttonUnSelectAllUser;
	QScrollArea* saTopUser;
	QScrollArea* saCenterUser;
	QSplitter*   splitterUser;
	QScrollArea* saBottomUser;

	AMap* map;
	AUserDefinedMap* udMap;			// User Defined Map

	MapLayerPanel* maplayerpanel;
	LayerDetailsPanel* layerdetailspanel;
	UserDefineMapPanel* udmappanel;
	MapLayerPanel* maplayerpanel_UD;
	LayerDetailsPanel* layerdetailspanel_UD;


	void displayDetails_UD(int t);

signals:
	void changed(const QString& s);
	void emitlayerdetailclicked(int, const QString& id, LayerVisible layervisible, bool idvisible);
	void emitlayerdetailclicked_UD(int, const QString& id, LayerVisible layervisible, bool idvisible);
	void signalTabChanged(int);
	void signalUDMapVisibleChanged_UD();
private slots:
	void changedTabWidget(int);
	void emitmaplayervisiblechanged();
	void emitmaplayervisiblechanged_UD();
	void emitudmaplayerchanged_UD(const int idx);
	void emitudmapvisiblechanged_UD(const int idx);
public slots:
	void changeLastSelectLayer(LayerType t);
	void emitmaplayerselectall();
	void emitmaplayerunselectall();
	void emitmaplayerchanged();
	void emitlayerdetailclicked();
	void emitmaplayerselectall_UD();
	void emitmaplayerunselectall_UD();
	void emitmaplayerchanged_UD();
	void emitlayerdetailclicked_UD();

};

#endif /* LEFTPANEL_H_ */
