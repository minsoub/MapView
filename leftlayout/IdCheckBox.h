/*
 * IdCheckBox.h
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */

#ifndef IDCHECKBOX_H_
#define IDCHECKBOX_H_
#include <QCheckBox>
#include "../lib_layer/MapDefine.h"

class IdCheckBox : public QCheckBox {
	Q_OBJECT
public:
	IdCheckBox(int layerType, const QString& id, QWidget* parent=0);
	int layerType() { return layertype; };
	const QString idName() { return idname; };
private:
	int layertype;
	QString idname;
signals:
	void clicked(int, const QString&, bool checked);
private slots:
	void slotClicked();
};

#endif /* IDCHECKBOX_H_ */
