/*
 * DistanceLinkItem.h
 *
 *  Created on: 2012. 6. 12.
 *      Author: root
 */

#ifndef DISTANCELINKITEM_H_
#define DISTANCELINKITEM_H_

#include <QtGui>
#include <QGraphicsLineItem>
#include "AirPlaneItem.h"
#include "../lib/LatLonBound.h"
#include "../lib/UnitChange.h"
#include "../lib/Turtle.h"

class DistanceLinkItem : public QGraphicsLineItem {
public:
	enum { Type = 1002 };
	DistanceLinkItem(AirPlaneItem* fromItem, AirPlaneItem* toItem);
	void setLog(Log424* logs) { log = logs; }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	int type() const { return Type; }
	void setVisible(bool b) { isShow = b; };
protected:
    //QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	AirPlaneItem*     source;
	AirPlaneItem* dest;
	Log424* log;
   QPointF sourcePoint;
   QPointF destPoint;
	QString disttext;
	QString bearingtext;
	QString text;
	QColor textColor;
	QColor lineColor;
	Turtle turtle;
	QFont font;
   bool isShow;
};

#endif /* DISTANCELINKITEM_H_ */
