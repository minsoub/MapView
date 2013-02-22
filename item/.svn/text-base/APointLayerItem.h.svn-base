/*
 * APointLayerItem.h
 *
 *  Created on: 2012. 2. 21.
 *      Author: HIST002
 */

#ifndef APOINTLAYERITEM_H_
#define APOINTLAYERITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../lib_layer/ALayer.h"
#include "../lib/AMapconf.h"
#include "../lib/UnitChange.h"
#include "../lib/LatLonBound.h"
#include "../lib/MapUtil.h"

class APointLayerItem : public ALayer {
public:
	enum { Type = 3 };
	int type() const { return Type; }
	APointLayerItem(LayerType t) : ALayer(t)
	{
		_classtype = ClassArea;
	}
	APointLayerItem &operator= (APointLayerItem &tmp) {
//		this->clear();
//	   for(int i=0;i<_list.count();i++){
//		   const ALayerId* newLayerId = tmp.getLayerId(i);
//		   this->appendLayerId(newLayerId);
//	    }
	   return *this;
	}
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	void print(QTextStream& out, AMapconf& mapconf);
	bool query(QSqlQuery* q, const QString& sql);
	void read(QTextStream& in, int& lineNo);
	virtual APointLayerItem* clone() {
		APointLayerItem* newPointLayer = new APointLayerItem(_layertype);
      *newPointLayer = *this;
      newPointLayer->clear();
      newPointLayer->_lp = this->_lp;
	   for(int i=0;i<_list.count();i++){
		   const ALayerId* newLayerId = this->getLayerId(i);
		   newPointLayer->appendLayerId(newLayerId);
	    }
      return newPointLayer;
    }

};

#endif /* APOINTLAYERITEM_H_ */
