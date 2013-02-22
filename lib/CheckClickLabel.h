/*
 * CheckClickLabel.h
 *
 *  Created on: 2012. 2. 24.
 *      Author: HIST002
 */

#ifndef CHECKCLICKLABEL_H_
#define CHECKCLICKLABEL_H_

#include <QtGui>
#include "../lib_layer/ClickableLabel.h"
#include "../lib_layer/LayerCheckBox.h"


class CheckClickLabel : public QWidget {
	Q_OBJECT
public:
	CheckClickLabel(QWidget* parent, int LayerNo, QString& text);
	bool visibleState() { return (checkbox->checkState() == Qt::Checked); }
	int layerNo() { return layerno; }
	int layerType() { return layerno; }
	QString text() const { return layername; }
	void setCheckState(Qt::CheckState cs) { checkbox->setCheckState(cs); }
	Qt::CheckState checkState() { return checkbox->checkState(); }
	QSize sizeHint() const;
public slots:
	void labelclick(int layerno);
	void checkclick(int layerno);
signals:
	void labelclicked(int layerno);
	void checkclicked(int layerno);
private:
	LayerCheckBox* checkbox;
	ClickableLabel* label;
	int layerno;
	QString layername;
};

#endif /* CHECKCLICKLABEL_H_ */
