/*
 * AUserLayerItemMng.h
 *
 *  Created on: 2012. 3. 16.
 *      Author: HIST002
 */

#ifndef AUSERLAYERITEMMNG_H_
#define AUSERLAYERITEMMNG_H_

#include <QtSql>
#include <QPainter>
#include <QtGui>

#include "../lib_layer/LayerDefine.h"
#include "../lib/Log424.h"
#include "../lib/CalcAir.h"
#include "../lib/AMapconf.h"
#include "../lib/AirDraw.h"
#include "../lib_layer/MsbBound.h"
#include "../lib_layer/LayerProperty.h"
#include "../lib_layer/MapDefine.h"
#include "../lib_layer/ALayer.h"
#include "../lib/MapUtil.h"
#include "../lib/LatLonBound.h"
#include "AUserLayerItem.h"

class AUserLayerItemMng {
public:
	AUserLayerItemMng() {};

	bool query(QSqlQuery* q);
	bool query(const QString& dbname);
	void read(QTextStream& in, int& lineNo);
	bool updateDB(const QString& dbname);
	QString lasterror()const { return _lasterror;}

	QString symboldir() const{ return _symboldir; }
	void setSymbolDir(const QString& symboldir) {
		for (int i=0; i<_list.count(); i++) {
			AUserLayerItem* item = _list[i];
			item->setSymboldir(symboldir);
		}
	}
	void deleteId(const QString& uid);
	void clear() { _list.clear(); }
	void changeName(const QString& oldid, const QString& newid);
	QString nextIdName();
	void fillId(QStringList& list);
	void fillIdType(QStringList& list);
	void setAllIdVisible(bool b);
	void setIdVisible(const QString& id, bool b);

	QString attr(const QString& idName);
	void setAttr(const QString& id, const QString& attr);

	QString drawType(const QString& idName);
	void drawSelected(AirDraw* ad, QPainter* painter, const QString& selectedUid);
	QString selectWithMousePosition(AirDraw* ad, QPoint mouseP) const;
	int idCount() { return _list.count(); }
	void print(QTextStream& out);
	void logprint(const QString& msg) { if(!_log) return; _log->print(msg); };
	void setLog(Log424& log) { _log = &log; };
	void setAirdraw(AirDraw* air) { ad = air; };
	void setLayerVisible(bool b) {
		for (int i=0; i<_list.count(); i++) {
			AUserLayerItem* item = _list[i];
			item->setLayerVisible(b);
		}
	};
	bool layerVisible() { return _visible; };
	void setTextVisible(bool b) {
		for (int i=0; i<_list.count(); i++) {
			AUserLayerItem* item = _list[i];
			item->setTextVisible(b);
		}
	};
	bool textVisible() { return _textvisible; };
	void update() {
		for (int i=0; i<_list.count(); i++) {
			AUserLayerItem* item = _list[i];
			item->update();
		}
	};
	int layerCount() { return _list.count(); };
	QVector<AUserLayerItem*> getUserList() { return _list; };
	AUserLayerItem* append(AUserLayerId* um) {
		AUserLayerItem* item = new AUserLayerItem;
		item->setUserLayer(um);
		item->setLog(_log);
		item->setAirdraw(ad);
		_list.append(item);

		return item;
	};
private:
	// QVector<AUserLayerId*> _list;
	QVector<AUserLayerItem*> _list;
	AUserLayerId* find(const QString& id);
	int findIndex(const QString& id);
	QString _lasterror;
	AirDraw* ad;
	bool _visible;
	bool _textvisible;
	QString _symboldir;
protected:
	CalcAir _ca;
	Log424* _log;
};

#endif /* AUSERLAYERITEMMNG_H_ */
