/*
 * LinkItem.h
 *
 *  Created on: 2012. 3. 12.
 *      Author: JMS
 */

#ifndef LINKITEM_H_
#define LINKITEM_H_

#include <QtGui>
#include <QGraphicsLineItem>
#include "AirPlaneItem.h"
#include "AirPlaneTextItem.h"
#include "../lib/LatLonBound.h"


class LinkItem : public QGraphicsLineItem {
public:
	enum { Type = 1001 };
	LinkItem(AirPlaneItem* fromItem, AirPlaneTextItem* toItem);
	void setLog(Log424* logs) { log = logs; }
	void trackNodes();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	//void adjust();
	int type() const { return Type; }
	void setVisible(bool b) { isShow = b; };
protected:
    //QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	AirPlaneItem*     source;
	AirPlaneTextItem* dest;
	Log424* log;
   QPointF sourcePoint;
   QPointF destPoint;
   bool isShow;
};

#endif /* LINKITEM_H_ */
