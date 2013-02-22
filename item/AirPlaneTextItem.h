/*
 * AirPlaneTextItem.h
 *
 *  Created on: 2012. 3. 12.
 *      Author: JMS
 *  Description : Airplane의 텍스트 정보를 출력한다.
 */

#ifndef AIRPLANETEXTITEM_H_
#define AIRPLANETEXTITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../lib/LatLonConvert.h"
#include "../lib/Log424.h"
#include "../lib_layer/MapDefine.h"
#include "../lib/MapUtil.h"
#include "../lib/CalcAir.h"
#include "../lib/LatLonBound.h"
#include "AirPlaneItem.h"

class LinkItem;

class AirPlaneTextItem  : public QGraphicsItem {
public:
	enum { Type = 1000 };
	AirPlaneTextItem();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	void setScreenConvertClass(LatLonConvert *convert) { vp = convert; }
	void setVisible(bool visible) { isShow = visible; }
	void setLog(Log424* logs) {
		log = logs;
	}
	//QPainterPath shape() const;
	QRectF outlineRect() const;
	void addLink(LinkItem* link);
	QPointF getCurrentPoint();
	void setAirplanePlace(AirPlaneItem* airplane) { this->airplane = airplane; }
	int type() const { return Type; }
	void setCurrentPosition(QPointF position) {
		//qDebug() << "setCurrentPosition called...";
		currentPosition = position;
		cur_latlon_p = vp->screenToDecimal(position.toPoint());
		curPoint.lat = _ca.LatDecimalToDMS(cur_latlon_p.x());
		curPoint.lon = _ca.LatDecimalToDMS(cur_latlon_p.y());
		curPoint.p   = cur_latlon_p;
	}; // setPos(position);}
	void setMoving(bool m) { ismoving = m; };
	bool isMoving() { return ismoving; };
	void setSSR(QString s) { ssr = s; };
	void setCallsign(QString s) { callsign = s; };
	void setTrackNo(QString s) { trackNo = s; };
	void setAlert(QString s) { alert = s; };
	void setColor(QColor color) { selectColor = color; };
	void setNumber(int num) { myNumber = num; };
	int getNumber() { return myNumber; };
	QString getSSR() { return ssr; }
	QString getCallsign() { return callsign; }
	QString getTrackNo() { return trackNo; }
	QColor getColor() { return selectColor; }
private:
	LatLonConvert *vp;
	CalcAir  _ca;
	Log424* log;
	bool isShow;
	QString aid;
	QString speed;
	QString msg;
	QSet<LinkItem *> links;
	AirPlaneItem* airplane;
	QPointF currentPosition;		// Mouse Point
	QPointF cur_latlon_p;			// lat_lon convert point
	APoint  curPoint;
	bool ismoving;
	int boundingHeight;
	QString ssr;						// SSR
	QString callsign;					// Callsign
	QString trackNo;					// Track Num
	QString alert;						// Alert
	QColor  selectColor;
	int roundness(double size) const;
	int myNumber;						// track print number
	QRectF mRectf;
protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif /* AIRPLANETEXTITEM_H_ */
