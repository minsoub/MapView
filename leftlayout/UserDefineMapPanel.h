/*
 * UserDefineMapPanel.h
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */

#ifndef USERDEFINEMAPPANEL_H_
#define USERDEFINEMAPPANEL_H_

#include <QtGui>
#include "../lib/CheckClickLabel.h"
#include "../lib_layer/LayerCheckBox.h"
#include "../AMap.h"

typedef struct _CheckLabelItemUD {
	int mapNo;
	QString mapName;
	LayerCheckBox* checkbox;
	ClickableLabel* label;
} CheckLabelItemUD;

class UserDefineMapPanel : public QWidget {
	Q_OBJECT
public:
	UserDefineMapPanel(QWidget* widget=0);
	void createUDMCheckBox(AMap* m);
	int lastUDMap() { return lastCheckedMap; }
	bool lastCheck() { return lastCheckState; }
	int getUDMapListCount() { return list.count(); }
	void selectAll();
	void setCheck(const QString& sname, LayerVisible b);
signals:
	void checkboxclicked(const int idx);
	void labelclicked(const int idx);
public slots:
	void checkClick(int idx);
	void labelClick(int idx);
private:
	QList<CheckLabelItemUD*> list;
	QVBoxLayout* vbox;
	AMap* map;
	int lastCheckedMap;		// 마지막 선택된 Map
	bool lastCheckState;	// 마지막 체크 상태

	void clearLayout(QLayout* l);
	QHBoxLayout* createCheckBox(int idx, const QString& mapName);
	CheckLabelItemUD* find(int t);
	void unselectAll();
	CheckLabelItemUD* find(const QString& sname);
};

#endif /* USERDEFINEMAPPANEL_H_ */
