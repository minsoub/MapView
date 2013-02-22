/*
 * AMap.h
 *
 *  Created on: 2012. 2. 24.
 *      Author: HIST002
 */

#ifndef AMAP_H_
#define AMAP_H_

#include <QtSql>
#include <QVector>
#include <QTextStream>
#include <QStringList>
#include "lib/Log424.h"
#include "lib_layer/MapDefine.h"
#include "lib/AMapconf.h"
#include "item/APointLayerItem.h"
#include "item/ALinesLayerItem.h"
#include "item/AHoldLayerItem.h"
#include "item/AreaLayerItem.h"
#include "item/ASymbolLayerItem.h"
#include "item/AUserLayerItem.h"
#include "item/AUserLayerItemMng.h"
#include "item/AUserDefinedMapList.h"

class AMap {
public:
	AMap(Log424& log, AirDraw* air);
	AMap(Log424& log);
	~AMap();
	ALayer* findLayer(LayerType t);
	ALayer* findLayer(const QString& name);
	QString magicString();
	void getDataFromDb(const QSqlDatabase& db);
	void print(QTextStream& out);
	void write(const QString& fileName);
	void read(const QString& fileName);
	void clear();
	AUserLayerItemMng* userLayer() { return userlayerList; }
	ALayer* layers(int idx) { if (idx < 0 || idx >= layerList.count()) return NULL; return layerList[idx]; }
	int layerCount() { return layerList.count(); }
	void setSymboldir(const QString& symboldir);
	void getUserDataFromDb(const QSqlDatabase& db);		// User map
	void changeUidName(const QString& oldid, const QString& newid);
	void idList(int t, QStringList& list);			// version 2
	void setAllLayerVisible(bool b);				// 모든 layer의 visible을 세팅
	void setLayerVisible(int t, LayerVisible visible);	// layer자체 visible로 만든다.
	void setAllIdVisible(int t, bool b);				// layer의 모든 id의 visible을 b로 세팅
	void setIdVisible(int t, const QString& id, bool b);	// 레이어의 id를 찾아서 visible set
	void setTextVisible(bool b);
	bool getTextVisible() { return textvisible; }
	const QColor bgcolor() { return mapconf.bg_color(); }
	QPointF defaultWonjum();
	bool isMapFileLayer(const QString& layer_id) { return mapconf.isMapFileLayer(layer_id); }
	void clearMapconf() { mapconf.clear(); }
	void draw(QPainter *painter, AirDraw* ad);

	// user defined map
	void CopyMapToUserDefinedMap();
	int udmListCount() {
		if(udmList == NULL) return 0;
		return udmList->count();
	}
	QString getUDMName(int idx) { return udmList->getMapName(idx); }
	AUserDefinedMap* getUDMap(int idx) {
		if(udmList == NULL) return NULL;
		return udmList->getMap(idx);
	}
	void initMap(Log424& log);
private:
	bool textvisible;
	Log424& log;
	AMsb msb;
	AMapconf mapconf;			// Map default
	QVector<ALayer*> layerList;
	//AUserLayerItem* userlayer;
	AUserLayerItemMng* userlayerList;
	AUserDefinedMapList* udmList;
	AirDraw *air;

};

#endif /* AMAP_H_ */
