/*
 * ALinesLayerItem.h
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */

#ifndef ALINESLAYERITEM_H_
#define ALINESLAYERITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../lib_layer/ALayer.h"
#include "../lib/AMapconf.h"
#include "../lib/UnitChange.h"
#include "../lib/LatLonBound.h"
#include "../lib/MapUtil.h"


class ALinesLayerItem : public ALayer {
public:
	enum { Type = 2 };
	int type() const { return Type; }
	ALinesLayerItem(LayerType t) : ALayer(t)
	{
		_classtype = ClassLines;
	}

	ALinesLayerItem &operator= (ALinesLayerItem &tmp) {
		//this->clear();
	   //for(int i=0;i<_list.count();i++){
		 //  ALayerId* newLayerId = tmp.getLayerId(i);
		 //  this->appendLayerId(newLayerId);
	    //}
	   return *this;
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void print(QTextStream& out, AMapconf& mapconf);
	bool query(QSqlQuery* q, const QString& sql);
	void read(QTextStream& in, int& lineNo);
	void updateInfo();
   virtual ALinesLayerItem* clone()  {
	   ALinesLayerItem* newLinesLayer= new ALinesLayerItem(_layertype);
      *newLinesLayer = *this;
      newLinesLayer->clear();
      newLinesLayer->_lp = this->_lp;
      for (int i=0; i<_list.count(); i++) {
		   const ALayerId* newLayerId = this->getLayerId(i);
		   newLinesLayer->appendLayerId(newLayerId);
        }

      return newLinesLayer;
    };
	bool queryRunway(QSqlQuery* q, const QString& sql);
	bool queryHold(QSqlQuery* q, const QString& sql);
	bool querySid(QSqlQuery* q, const QString& sql);			// SID, STAR, APCH Layer
private:

};

#endif /* ALINESLAYERITEM_H_ */
