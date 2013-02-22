/*
 * AUserDefinedMapList.h
 *
 *  Created on: 2012. 2. 24.
 *      Author: HIST002
 */

#ifndef AUSERDEFINEDMAPLIST_H_
#define AUSERDEFINEDMAPLIST_H_

#include <QtSql>
#include <QVector>
#include <QTextStream>
#include <QStringList>
#include "../lib_layer/MapDefine.h"
#include "../lib_layer/ALayer.h"
#include "../lib/Log424.h"
#include "../lib/AUserDefinedMap.h"

class AUserDefinedMapList {
public:
	AUserDefinedMapList(Log424* log);
	AUserDefinedMapList();

	bool query(QSqlQuery* q);
	void print(QTextStream& out);
	void read(QTextStream& in, int& lineNo, const QString& mapid);
	void addMap(AUserDefinedMap* newmap) { mapList.append(newmap); }
	void addMap(const QString& mapid);
	AUserDefinedMap* getMap(int idx) {
		if (idx < 0 || idx >= mapList.count()) return NULL;
		return mapList[idx];
	}
	int count() { return mapList.count(); }
	void clear() { mapList.clear(); }
	QString getMapName(int idx) { return mapList[idx]->ID(); }
	void draw(QPainter* painter, AirDraw* ad);
protected:
    Log424* _log;
private:
	QVector<AUserDefinedMap*> mapList;
	QString _lasterror;
	void logprint(const QString& msg) { if (!_log) return; _log->print(msg); }
};

#endif /* AUSERDEFINEDMAPLIST_H_ */
