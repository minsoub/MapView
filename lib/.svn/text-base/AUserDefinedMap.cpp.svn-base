/*
 * AUserDefinedMap.cpp
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */

#include "AUserDefinedMap.h"

AUserDefinedMap::AUserDefinedMap(const QString& id) {
	// TODO Auto-generated constructor stub
	Id = id;
	visible = false;
}

void AUserDefinedMap::addLayer(const QString& layerid)
{
	AUserDefinedLayer* newlayer = new AUserDefinedLayer(layerid);
	layerList.append(newlayer);
}

void AUserDefinedMap::addId(const QString& layerid, const QString& id)
{
	for (int i=0; i<layerList.count(); i++) {
		AUserDefinedLayer* newlayer = layerList[i];
		if (newlayer->getId() == layerid) {
			newlayer->addId(id);
		}
	}
}


void AUserDefinedMap::setLayerVisible(int t, LayerVisible visible)
{
	ALayer* layer = findLayer((LayerType) t);
	if (layer != NULL) {
		if (visible == Unvisible) {	// 모두 unvisible이 아니면 layer는 visible
			//qDebug() << "Unvisible....";
			layer->setLayerVisible(false);
		}
		layer->setLayerVisible(true);

//		qDebug() << "layer id Count : " << layer->idCount();
//		for (int i=0; i<layer->idCount(); i++) {
//			ALayerId* layerid = layer->getLayerId(i);
//			//if (layerid->id == "Ad_Civil")
//				qDebug() << "layerid : " << layerid->id << ", layerid->visible : " << layerid->visible;
//
//				qDebug() << "bndrylist size : " << layerid->bndrylist.size();
//		}

		return;
	}
}

ALayer* AUserDefinedMap::findLayer(const QString& name)
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i]->getLayer();
		if (layer->shortName().toUpper() == name.toUpper()) {
			return layer;
		}
	}
	return NULL;
}

ALayer* AUserDefinedMap::findLayer(LayerType t)
{
	// 0 : not define
	if (t == Layer_Unknown) return NULL;

	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i]->getLayer();
		if (layer->layerType() == t) {
			return layer;
		}
	}
	return NULL;
}

void AUserDefinedMap::setAllIdVisible(int t, bool b)
{
	if (t < MaxLayerCount) {
		ALayer* layer = findLayer((LayerType) t);
		if (layer != NULL) {
			//qDebug() << "AUserDefinedMap::setAllIdVisible found layer : " << layer->toString();
			layer->setAllIdVisible(b);
		}
	}
}

void AUserDefinedMap::idList(int t, QStringList& list)
{
	if (t < MaxLayerCount) {
		ALayer* layer = findLayer((LayerType) t);
		if (layer != NULL)
			layer->fillId(list);
	}
}

/**
 * 모든 레이어의 visible을 세팅한다.
 */
void AUserDefinedMap::setAllLayerVisible(bool b)
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i]->getLayer();
		layer->setLayerVisible(b);
		layer->setAllIdVisible(b);		// 모든 id도 같이
	}
}

void AUserDefinedMap::draw(QPainter* painter, AirDraw* ad)
{
	if (!visible) return;

	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i]->getLayer();
		layer->update();		// draw call
	}
}

/**
 * layer의 특정 id만의 visible을 설정한다.
 */
void AUserDefinedMap::setIdVisible(int t, const QString& id, bool b)
{
	if (t < MaxLayerCount) {
		ALayer* layer = findLayer((LayerType) t);

		if (layer != NULL) {
			layer->setIdVisible(id, b);
		}
	}
}

void AUserDefinedMap::setSymboldir(const QString& symboldir)
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i]->getLayer();
		if (layer->classType() == ClassSymbol) {
			ASymbolLayerItem* symbollayer = (ASymbolLayerItem*) layer;
			symbollayer->setSymbolDir(symboldir);
		}
	}
}

void AUserDefinedMap::checkAllLayerState()
{
	LayerVisible nowstate, prevstate;
	nowstate = prevstate = Visible;
	// 모두 check 되었는가?
	bool moduvisible = true;

	for (int i=0; i<layerList.count(); i++) {
		if (!layerList[i]->getLayer()->layerVisible()) {
			moduvisible = false;
			break;
		}
	}

	if (moduvisible) {
		allLayerVisibleState = Visible;
		return;
	}

	// 모두 uncheck 되었는가?
	bool moduunvisible = true;
	for (int i=0; i<layerList.count(); i++) {
		if (layerList[i]->getLayer()->layerVisible()) {
			moduunvisible = false;
			break;
		}
	}
	if (moduunvisible) {
		allLayerVisibleState = Unvisible;
		return;
	}

	// 부분적으로
	allLayerVisibleState = PartiallyVisible;
	return;
}
