/*
 * AUserDefinedMap.h
 *
 *  Created on: 2012. 2. 23.
 *      Author: HIST002
 */

#ifndef AUSERDEFINEDMAP_H_
#define AUSERDEFINEDMAP_H_

#include "AUserDefinedLayer.h"
#include "../lib_layer/MapDefine.h"
#include "../lib_layer/ALayer.h"
#include "../lib/Log424.h"

#include "../item/APointLayerItem.h"
#include "../item/ALinesLayerItem.h"
//#include "../item/AHoldLayerItem.h"
#include "../item/AreaLayerItem.h"
#include "../item/ASymbolLayerItem.h"
#include "../item/AUserLayerItem.h"

class AUserDefinedMap {
public:
	AUserDefinedMap(const QString& id);
	~AUserDefinedMap() { layerList.clear(); }
	QString ID() { return Id; }
	int LayerCount() { return layerList.count(); }
	AUserDefinedLayer* layer(int i) {
		if (i < 0 || i >= layerList.count()) return NULL;
		return layerList[i];
	}
	void setId(const QString& id) { Id = id; }
	void addLayer(const QString& layerid);
	void addLayer(AUserDefinedLayer* newlayer) { layerList.append(newlayer); }
	void addId(const QString& layerid, const QString& id);

	void setLayerVisible(int t, LayerVisible visible);
	void setAllIdVisible(int t, bool b);
	ALayer* findLayer(const QString& name);
	ALayer* findLayer(LayerType t);
	void idList(int t, QStringList& list);
	void setAllLayerVisible(bool b);
	void draw(QPainter *painter, AirDraw* ad);
	void setIdVisible(int t, const QString& id, bool b);
	void setSymboldir(const QString& symboldir);
	LayerType getLayerType(int idx) { return layerList[idx]->layerType(); }
	void setVisible(bool b) { visible = b; }
	bool getVisible() { return visible; }
	LayerVisible allLayerState() { checkAllLayerState(); return allLayerVisibleState; }
private:
	QString Id;
	bool visible;
	QVector<AUserDefinedLayer*> layerList;
	LayerVisible allLayerVisibleState;		// 모든 layer의 상태가 어떤가
	void checkAllLayerState();
};

#endif /* AUSERDEFINEDMAP_H_ */
