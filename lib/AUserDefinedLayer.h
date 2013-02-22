/*
 * AUserDefinedLayer.h
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */

#ifndef AUSERDEFINEDLAYER_H_
#define AUSERDEFINEDLAYER_H_

#include "../lib_layer/ALayer.h"
#include "../lib_layer/MapDefine.h"

class AUserDefinedLayer {
public:
	AUserDefinedLayer(const QString& _id);
	~AUserDefinedLayer() { idList.clear(); }
	QString Id() { return id; }
	int IdCount() { return idList.count(); }
	QString idName(int idx) {
		if (idx < 0 || idx >= idList.count()) return "";
		return idList[idx];
	}
	QString getId() { return id; }
	bool isAll;
	void addId(const QString& name);
	void assignRealLayer(ALayer* layer) { realLayer = layer; }
	void removeIds();
	int realLayerIdCount() { return realLayer->idCount(); }
	QString realLayerIdName(int idx) {
		if (idx < 0 || idx >= realLayer->idCount()) return "";
		return realLayer->getId(idx);
	}
	LayerType layerType() { return realLayer->layerType(); }
	ALayer* getLayer() { return realLayer; }
	LayerVisible allIdState() { checkAllIdState(); return allidvisible; }
private:
	QString id;		// layerid
	QVector<QString> idList;
	ALayer* realLayer;
	LayerVisible allidvisible;		// 모든 id의 상태

	void checkAllIdState();
};

#endif /* AUSERDEFINEDLAYER_H_ */
