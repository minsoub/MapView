/*
 * AirPlaneItem.h
 *
 *  Created on: 2012. 3. 12.
 *      Author: JMS
 *  Description : 비행기 에뮬을 화면에 출력한다.
 */

#ifndef AIRPLANEITEM_H_
#define AIRPLANEITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "../lib/LatLonConvert.h"
#include "../lib/Log424.h"
#include "../lib_layer/MapDefine.h"
#include "../lib/MapUtil.h"
#include "../lib/CalcAir.h"
#include "../lib/ConfigParser.h"
#include "../lib/LatLonBound.h"
#include "../trackrpt/TrackData.h"
#include "../trackrpt/ReportOption.h"

class LinkItem;

class AirPlaneItem  : public QGraphicsItem {
public:
	enum { Type = 999 };
	AirPlaneItem();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	int type() const { return Type; }
	void setScreenConvertClass(LatLonConvert *convert) { vp = convert; }
	void setVisible(bool visible) { isShow = visible; }
	void setLog(Log424* logs) { log = logs; }
	void test_read();
	void setIndex(int airIndex) { air_idx = airIndex; }
	void addLink(LinkItem* lnk);
	void setTrackData(TrackData tData);
	void setSymbol(QString idx) { symbol = idx; }
	QPixmap getSymbol() { return icon; }
	void setLoad();
	TrackData getTrackData() { return trackData; }
	QPointF getCurrentPoint();
	QPointF getPreviousPoint();
	LatLonConvert* getView() { return vp; }
	void setReportOption(ReportOption *opt) { option = opt; }
	ReportOption* getReportOption() { return option; }
	void setNumber(int num) { orderno = num; };
private:
	LatLonConvert *vp;
	QVector<APoint> dataxy;
	QSet<LinkItem *> links;
	TrackData   trackData;
	CalcAir  _ca;
	Log424* log;
	bool isShow;
	int air_idx;		   // 비행자료 index
	QPointF currentPosition;
	QString symbol;
	QPixmap icon;
	ReportOption *option;
	int orderno;			// track order number
protected:
    //void advance(int step);
};

#endif /* AIRPLANEITEM_H_ */
