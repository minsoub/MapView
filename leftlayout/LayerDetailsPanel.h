/*
 * LayerDetailsPanel.h
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */

#ifndef LAYERDETAILSPANEL_H_
#define LAYERDETAILSPANEL_H_

#include <QtGui>
#include "../lib_layer/MapDefine.h"
#include "IdCheckBox.h"

typedef QVector<IdCheckBox*> VectorCheckBox;

class LayerDetailsPanel : public QWidget {
	Q_OBJECT
public:
	LayerDetailsPanel(QWidget *parent=0);
	void refresh();
	void add(int type, const QString& id, bool checked = false);
	void clearList();
	void setLayerType(int t) { layertype = t; };
	int layerType() { return layertype; };
	const QString clickedId() { return clickedid; };
	bool visibleState() { return visiblestate; };
	LayerVisible allIdState() { return allidvisible; };
	void checkAllIdState();
	void clearAllCheckBox() {
		clearList();
		clearAllWidgets();
	};
private:
	QVBoxLayout* vboxMain;
	int layertype;
	VectorCheckBox* list;
	QString clickedid;
	QLabel* labelNoId;
	bool visiblestate;
	LayerVisible allidvisible;		// 모든 id의 상태가 어떤가

	const QString getLayerName(int type);
	void clearAllWidgets();
	void clearLayout(QLayout *l);

signals:
	void clicked();
public slots:
	void setCheckStateAllWidget(bool b);
private slots:
	void emitClick(int, const QString&, bool visible);
};

#endif /* LAYERDETAILSPANEL_H_ */
