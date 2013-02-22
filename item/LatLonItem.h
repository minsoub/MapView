/*
 * LatLonItem.h
 *
 *  Created on: 2012. 1. 25.
 *      Author: HIST002
 */

#ifndef LATLONITEM_H_
#define LATLONITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../lib/LatLonConvert.h"

class LatLonItem : public QGraphicsItem {
public:
	enum { Type = 9 };
	int type() const { return Type; }
	LatLonItem();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	void setScreenConvertClass(LatLonConvert *convert);
	void setVisible(bool visible) { isShow = visible; }
private:
	LatLonConvert *convert;
	QPoint drawStartPoint, drawEndPoint, drawCenterPoint;
	int drawCount;
	bool isShow;
	void drawLatLon(QPainter* painter);
	void drawLonLines(QPainter* painter);
	void drawLatLines(QPainter* painter);
	void drawLat(QPainter* painter, double line);
	void drawLon(QPainter* painter, double line);
	void drawLatLon1Text(QPainter* painter, double latlon, int type);
	void drawText1(QPainter *painter, const QPoint& p, const QString& text);
	bool drawLine3(QPainter *painter, QVector<QPoint>& dataxy);
};

#endif /* LATLONITEM_H_ */
