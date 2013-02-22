/*
 * UserDrawItem.h
 *
 *  Created on: 2012. 3. 2.
 *      Author: HIST002
 */

#ifndef USERDRAWITEM_H_
#define USERDRAWITEM_H_

#include <QtGui>
#include "../lib_layer/LayerProperty.h"
#include "../rightlayout/EditDefine.h"
#include "../lib/CalcAir.h"
#include "../lib/AirDraw.h"
/**
 * 한개의 사용자 그리기 작업의 데이터와 함수
 */
class UserDrawItem  : public QGraphicsItem {
public:
	enum { Type = 10 };
	int type() const { return Type; }
	UserDrawItem() {
		userdrawtype = Select;
		property.setLineColor(Qt::white);
		property.setFillColor(Qt::white);
		//setFlag(QGraphicsItem::ItemIsSelectable);
		//setFlag(ItemIgnoresTransformations, true);
		setZValue(-1);
	};
	UserDrawItem(QWidget*  qwidget) {
		widget = qwidget;
		userdrawtype = Select;
		property.setLineColor(Qt::white);
		property.setFillColor(Qt::white);
		//setFlag(QGraphicsItem::ItemIsSelectable);
		//setFlag(ItemIgnoresTransformations, true);
		setZValue(-1);
	};
	void addPoint(const QPoint& p);
	void calcMinMax2(const QPoint& p);
	void initialize();
	QRect getRect() { return rect; }

	DrawType type() { return userdrawtype; }
	void setDrawType(DrawType dt) { userdrawtype = dt; }

	void mPress(QMouseEvent* event);
	void mMove(QMouseEvent* event);
	void mRelease(QMouseEvent* event);
	void updateRegion();
	void draw(QPainter* painter);
	void drawAUsermap(QPainter* painter);		// 사용자 편집 그리기

	bool isFinish() { return jobtype == finish ? true : false; };
	void setText(const QString& t) { text = t; update(); };
	void setSymbol(const QString& t);
	QString getText() const { return text; }
	QString getSymbol() const { return symbolFile; }

	void setProperty(LayerProperty* p) { property = *p; }
	QChar drawTypeChar();
	QString layerString() { return property.layerString(); }

	QVector<QPoint>* getPointList() { return &pointList; }
	double getStartAngle() { return startAngle; }
	double getEndAngle() { return endAngle; }

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void updateInfo();
	void setAirDraw(AirDraw* airdraw) { ad = airdraw; }
private:
	enum JobType { standby, ing, finish };
	DrawType userdrawtype;
	QWidget* widget;
	QVector<QPoint> pointList;
	int pointCount;
	QRect rect;
	QRect smallrect;			// for arc
	double startAngle, endAngle;

	QString text;
	QString symbolFile;
	LayerProperty property;
	QPoint minPoint, maxPoint;
	QPoint minPoint2, maxPoint2;

	JobType jobtype;
	QPixmap pixmap;

	AirDraw* ad;

	void drawText1(QPainter* painter);

signals:
	void finishDraw();
};

#endif /* USERDRAWITEM_H_ */
