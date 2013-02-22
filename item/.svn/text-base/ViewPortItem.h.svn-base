/*
 * ViewPortItem.h
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#ifndef VIEWPORTITEM_H_
#define VIEWPORTITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../lib/LatLonConvert.h"
#include "../lib/AirDraw.h"

class ViewPortItem : public QGraphicsItem{
public:
	enum { Type = 11 };
	int type() const { return Type; }
	ViewPortItem();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	void setScreenConvertClass(LatLonConvert *vp) { this->vp = vp; }
	void setAirDraw(AirDraw* air) { this->air = air; }
private:
	LatLonConvert *vp;
	AirDraw* air;
};

#endif /* VIEWPORTITEM_H_ */
