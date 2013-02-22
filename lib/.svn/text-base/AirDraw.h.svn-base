/*
 * AirDraw.h
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */

#ifndef AIRDRAW_H_
#define AIRDRAW_H_

#include <QPainter>
#include <QRect>
#include "../lib/GraphicsUtils.h"
#include "../lib_layer/LayerProperty.h"
#ifndef LATLONCONVERT_H_
#include "../lib/LatLonConvert.h"
//#define LATLONCONVERT_H_
#endif
#include "Turtle.h"
#include "UnitChange.h"

class AirDraw {
public:
	AirDraw(LatLonConvert* v, Log424* log424) { vp = v; log = log424; latlonTextMode = TwoEdge; }
	AirDraw(LatLonConvert* v) { vp = v; log = NULL; latlonTextMode = TwoEdge; }
	GraphicsUtils* gutil() { return &gu; }

	LatLonConvert* viewport() { return vp; }
	void drawText1(QPainter* painter, const QPoint& p, const QString& text);
	void drawTextAtCenter(QPainter* painter, const QPoint& c, const QString& text);

	void changeViewPort(LatLonConvert* v) { vp = v; }
	void setLog(Log424* logfile) { log = logfile; }
	void unsetLog() { log = NULL; }

	void drawLine2(QPainter* painter, QVector<CartesianXY>& dataxy);
	bool drawLine3(QPainter* painter, QVector<QPoint>& dataxy);
	void drawLatLon1(QPainter* painter);
	void drawLatLon1Text(QPainter* painter, double latlon, int type);

	void drawBearingCircle(QPainter* painter);
	void drawBearingCircle(QPainter* painter, const QColor& circle_color, const QColor& text_color);
	void drawCross(QPainter* painter);
	void drawCross(QPainter* painter, const QColor& color);
	void displayViewPortInfo(QPainter* painter);
	void drawRway(QPainter* painter, const QPoint& p1, const QPoint& p2);

	void drawAirCircle(QPainter* painter, const QPoint& p, double radius);
	void drawAirPolygon(QPainter* painter, QVector<CartesianXY>& dataxy);

	void drawPathPolyline(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawPathPolygon(QPainter* painter, QVector<CartesianXY>& dataxy);

	// User drawing
	void drawUserLine(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawUserCircle(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawUserEllipse(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawUserRectangle(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawUserPolyline(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawUserPolygon(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawUserText(QPainter* painter, QVector<CartesianXY>& dataxy, const QString& str);
	void drawUserSymbol(QPainter* painter, QVector<CartesianXY>& dataxy, const QString& filename);
	void drawUserArc(QPainter* painter, QVector<CartesianXY>& dataxy);

	// select
	void drawRectWithCenter(QPainter* painter, const QPoint& center, int w);
	void drawSelectedRect(QPainter* painter, QVector<CartesianXY>& dataxy);
	void drawSelectedRect(QPainter* painter, QVector<QPoint>& dataxy);
	bool findWithMouse(const QString& tp, QVector<QPoint>& dataxy, const QPoint& mouseP);

	void drawPath(QPainter* painter, QVector<CartesianXY>& dataxy, QChar maptype = QChar('L'));
	void drawPath2(QPainter* painter, QVector<CartesianXY>& dataxy, QChar maptype = QChar('L'));	// Hold Layer [ draw arc create ]
	void drawPath3(QPainter* painter, QVector<CartesianXY>& dataxy, QChar maptype = QChar('L'));	// UserLayer Manual Coord.

	// for user edition
	QVector<CartesianXY>* getDataXY() { return &userdataxy; }
	void drawAUsermap(QPainter* painter);
	void setAUserDrawtype(const QChar& c) { userdrawtype = c; }
	LatLonConvert* getViewPort() { return vp; }
private:
	enum LLTextMode { NoDispaly, Center, TwoEdge, LeftEdge, RightEdge };
	LatLonConvert* vp;
	CalcAir ca;
	Log424* log;
	GraphicsUtils gu;

	QPoint polyMin, polyMax;		// Polyline을 그렸을 때의 Min, Max
	QPoint polyFirst, polyLat;		// Polyline을 그렸을 때의 Min, Max
	int polyCnt;					// Polyline을 그렸을 때 실제로 그린 점의 개수

	LLTextMode latlonTextMode;
	int drawCount;					// 점을 그린 개수
	QPoint drawStartPoint, drawEndPoint, drawCenterPoint;

	// for User Edition
	QVector<CartesianXY> userdataxy;
	QChar userdrawtype;

	double minLon, maxLon, minLat, maxLat;

	void drawNumber1(QPainter* painter, const QPoint& p, double d);

	void drawLon1(QPainter* painter, double lon);
	void drawLat1(QPainter* painter, double lat);
	void drawLatLines(QPainter* painter);
	void drawLonLines(QPainter* painter);
	void drawLineAndClear(QPainter* painter, QVector<QPoint>& points);
};

#endif /* AIRDRAW_H_ */
