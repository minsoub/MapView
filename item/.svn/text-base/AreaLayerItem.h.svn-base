/*
 * AreaLayerItem.h
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */

#ifndef AREALAYERITEM_H_
#define AREALAYERITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../lib_layer/ALayer.h"
#include "../lib/AMapconf.h"
#include "../lib/UnitChange.h"
#include "../lib/LatLonBound.h"
#include "../lib/MapUtil.h"
//MapConvertFunc

class AreaLayerItem : public ALayer{
public:
	enum { Type = 4 };
	int type() const { return Type; }
	AreaLayerItem(LayerType t) : ALayer(t)
	{
		_classtype = ClassArea;
	}
	AreaLayerItem &operator= (AreaLayerItem &tmp) {
//		this->clear();
//	   for(int i=0;i<_list.count();i++){
//		   const ALayerId* newLayerId = tmp.getLayerId(i);
//		   this->appendLayerId(newLayerId);
//	    }
	    return *this;
	}
	~AreaLayerItem() { };
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	void print(QTextStream& out, AMapconf& mapconf);
	bool query(QSqlQuery* q, const QString& sql);
	void read(QTextStream& in, int& lineNo);
	AreaLayerItem* clone() {
		AreaLayerItem* newAreaLayer = new AreaLayerItem(_layertype);
		*newAreaLayer = *this;
		newAreaLayer->_lp = this->_lp;
	   for (int i=0; i<_list.count(); i++) {
		   const ALayerId* newLayerId = this->getLayerId(i);
		   newAreaLayer->appendLayerId(newLayerId);
		   //qDebug() << "clone ALayerId true, false : " << newLayerId->visible;
	    }
		return newAreaLayer;
	}
private:
	bool queryMsaw(QSqlQuery* q, const QString& sql);
};

#endif /* AREALAYERITEM_H_ */
