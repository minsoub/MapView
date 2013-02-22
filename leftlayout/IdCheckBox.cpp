/*
 * IdCheckBox.cpp
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */
#include <QtGui>
#include "IdCheckBox.h"

IdCheckBox::IdCheckBox(int layerType, const QString& id, QWidget* parent):QCheckBox(id, parent){
	// TODO Auto-generated constructor stub
	layertype = layerType;
	idname = id;

	connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void IdCheckBox::slotClicked() {
	bool b = checkState() == Qt::Checked;
	emit clicked(layertype, idname, b);
}
