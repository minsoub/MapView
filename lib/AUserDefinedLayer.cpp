/*
 * AUserDefinedLayer.cpp
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */

#include "AUserDefinedLayer.h"

AUserDefinedLayer::AUserDefinedLayer(const QString& _id) {
	// TODO Auto-generated constructor stub
	id = _id;
	isAll = false;
	realLayer = NULL;
	allidvisible = Unvisible;
}

void AUserDefinedLayer::addId(const QString& name)
{
	if (name == "ALL") { isAll = true; return; }
	idList.append(name);
}

void AUserDefinedLayer::removeIds()
{
	if (realLayer == NULL) return;

	QVector<QString> deleteIdList;

	for (int i=0; i<realLayer->idCount(); i++) {
		QString id = realLayer->getId(i);
		if (idList.indexOf(id) < 0) {
			deleteIdList.append(id);
		}
	}

	for (int i=0; i<deleteIdList.count(); i++) {
		int idx = realLayer->findIndex(deleteIdList[i]);
		realLayer->deleteId(idx);
	}
}

void AUserDefinedLayer::checkAllIdState()
{
	if (realLayer == NULL) return;
	LayerVisible nowstate, prevstate;
	nowstate = prevstate = Visible;

	// 모두 check 되었는가?
	bool moduvisible = true;
	for (int i=0; i<realLayer->idCount(); i++) {
		if (!realLayer->getIdVisible(i)) {
			moduvisible = false;
			break;
		}
	}
	if (moduvisible) {
		allidvisible = Visible;
		return;
	}
	// 모두 uncheck 되었는가?
	bool moduunvisible = true;
	for (int i=0; i<realLayer->idCount(); i++) {
		if (realLayer->getIdVisible(i)) {
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

