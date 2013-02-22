/*
 * LayerCheckBox.h
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */

#ifndef LAYERCHECKBOX_H_
#define LAYERCHECKBOX_H_

#include <QCheckBox>

class LayerCheckBox : public QCheckBox
{
	Q_OBJECT

public:
	LayerCheckBox(QWidget* parent=0, int layerNo = -1):QCheckBox(parent)
	{
		layerno = layerNo;

		connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
		setText(QString(""));
		setMaximumWidth(16);
		setMaximumHeight(16);
	}

	int layerType() { return layerno; }
	int layerNo() { return layerno; }
private:
	int layerno;
signals:
	void clicked(int);
private slots:
	void slotClicked() { emit clicked(layerno); }
};
#endif /* LAYERCHECKBOX_H_ */
