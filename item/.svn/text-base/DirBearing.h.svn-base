/*
 * DirBearing.h
 *
 *  Created on: 2012. 3. 6.
 *      Author: HIST002
 */

#ifndef DIRBEARING_H_
#define DIRBEARING_H_

#include <QtGui>
#include "../lib/Turtle.h"
#include "../lib/LatLonConvert.h"

class DirBearing : public QGraphicsItem {
public:
	enum { Type = 8 };
	int type() const { return Type; }
	DirBearing();
	QPoint startPoint() { return startpoint; }
	void initialize();
	QRect getLineRect() { return rectLine; }
	QRect getLineText() { return rectText; }
	bool isFinish() { return jobtype == finish ? true : false; }
	void mPress(QMouseEvent* event);
	void mMove(QMouseEvent* event, const QString& dist, const QString& bearing);
	void mRelease();
	void draw(QPainter* painter);
	void updateRegion();
	void setText(const QString& dist, const QString& bearing) { disttext = dist; bearingtext = bearing; }

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	void setScreenConvertClass(LatLonConvert *vp);
private:
	enum JobType { ing, finish };
	JobType jobtype;
	QPoint startpoint, endpoint;
	QRect rectStartCross;
	QRect rectLine;
	QRect rectText;
	QString disttext;
	QString bearingtext;
	QString text;
	QColor textColor;
	QColor lineColor;
	Turtle turtle;
	QFont font;
	double getAngleDegree(int w, int h);
	LatLonConvert* vp;
};

#endif /* DIRBEARING_H_ */
