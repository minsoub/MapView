/*
 * BearingCircleItem.h
 *
 *  Created on: 2012. 1. 26.
 *      Author: HIST002
 */

#ifndef BEARINGCIRCLEITEM_H_
#define BEARINGCIRCLEITEM_H_
#include <QtGui>
#include <QGraphicsItem>
#include "../lib/LatLonConvert.h"

class BearingCircleItem : public QGraphicsItem {
public:
	enum { Type = 7 };
	int type() const { return Type; }
	BearingCircleItem();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void updateInfo();
	QRectF boundingRect() const;
	void setScreenConvertClass(LatLonConvert *vp);
	void setVisible(bool visible) { isShow = visible; }
private:
	LatLonConvert *vp;
	bool   isShow;
	void drawBearingCircle(QPainter *painter);
};

#endif /* BEARINGCIRCLEITEM_H_ */
