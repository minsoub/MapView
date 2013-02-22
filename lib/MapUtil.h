/*
 * MapUtil.h
 *
 *  Created on: 2012. 2. 17.
 *      Author: HIST002
 */

#ifndef MAPUTIL_H_
#define MAPUTIL_H_

#include <QString>
#include <QPoint>
#include "../lib_layer/MapDefine.h"

class QSU {
public:
	QSU() {};
	static void qstrcpy(char* des, const QString& str);
};

// LatLon Utility
class LLU {
public:
	LLU() {};
	static QString lat(const QString& latlon);
	static QString lon(const QString& latlon);
};

// LayerAttrUtility
class LAU {
public:
	LAU() {};
	static void set(ALayerAttr& attr, const QStringList& list);
	static void set(ALayerAttr* attr, const QStringList& list);
	static QString getString(ALayerAttr& attr);
	static QString toString(ALayerAttr& attr);
};
#endif /* MAPUTIL_H_ */
