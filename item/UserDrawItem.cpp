/*
 * UserDrawItem.cpp
 *
 *  Created on: 2012. 3. 2.
 *      Author: HIST002
 */
#include <iostream>
#include "../lib/AirDraw.h"
#include "UserDrawItem.h"

double getAngleDegree(int w, int h)
{
	double angleRadian = 0;
	if( w == 0 && h == 0) {
		angleRadian = 0;
	}else if( w > 0) {
		if (h < 0) { 		// 1
			angleRadian = atan((double)(h*-1)/(double)w);
		}else if(h > 0) {	// 4
			angleRadian = atan((double)h/(double)w);
			angleRadian = (2*PI) - angleRadian;
		}else if(h == 0) {
			angleRadian = 0;
		}
	}else if(w < 0) {
		if (h < 0) {
			angleRadian = atan((double)(h*-1)/(double)(w*-1));
			angleRadian = (PI) - angleRadian;
		}else if(h > 0) {	// 3
			angleRadian = atan((double)h/(double)(w*-1));
			angleRadian = (PI) + angleRadian;
		}else if(h == 0) {
			angleRadian = (PI);
		}
	}
	return angleRadian * rad2deg;
}

void UserDrawItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (jobtype == standby) {
		;
	}else {
		draw(painter);
	}
}

void UserDrawItem::updateInfo()
{
	prepareGeometryChange();
}
QRectF UserDrawItem::boundingRect() const
{
	//qreal adjust = 0.5;
	//LatLonConvert* vp = ad->viewport();
	// std::cout << "width : " << convert->srcRect().width() << ", height : " << convert->srcRect().height() << "\n";

	//QRectF rect = QRectF(-convert->srcRect().width()/2 - adjust, -convert->srcRect().height()/2 - adjust,
	//		convert->srcRect().width() * 1.0, convert->srcRect().height() * 1.0);
	//QRectF rect = QRectF(adjust, adjust, vp->srcRect().width() * 1.0, vp->srcRect().height() * 1.0);

	return rect;
}

void UserDrawItem::addPoint(const QPoint& p)
{
	QPoint newP = p;
	pointList.append(newP);
	minPoint.setX(qMin(p.x(), minPoint.x()));
	minPoint.setY(qMin(p.y(), minPoint.y()));
	maxPoint.setX(qMax(p.x(), maxPoint.x()));
	maxPoint.setY(qMax(p.y(), maxPoint.y()));
}

/**
 * Min, Max 2를 계산한다.
 */
void UserDrawItem::calcMinMax2(const QPoint& p)
{
	minPoint2.setX(qMin(p.x(), minPoint.x()));
	minPoint2.setY(qMin(p.y(), minPoint.y()));
	maxPoint2.setX(qMax(p.x(), maxPoint.x()));
	maxPoint2.setY(qMax(p.y(), maxPoint.y()));
}

void UserDrawItem::initialize()
{
	pointList.clear();
	rect = QRect(0, 0, 0, 0);

	minPoint = QPoint(INT_MAX, INT_MAX);
	maxPoint = QPoint(INT_MIN, INT_MIN);
	minPoint2 = QPoint(INT_MAX, INT_MAX);
	maxPoint2 = QPoint(INT_MIN, INT_MIN);
	pointCount = 0;
	jobtype    = standby;
	update();
}

/**
 * 사용자 그리기 시작 메소드 - 마우스가 클릭되었을 때 수행된다.
 */
void UserDrawItem::mPress(QMouseEvent* event)
{
	if (userdrawtype == Select) return;

	QPoint p = event->pos();
	switch(userdrawtype) {
	case Line:
	case Rectangle:
	case Circle:
	case Ellipse:
		if (event->button() != Qt::LeftButton) return;
		if (pointCount == 0) {
			//widget->setCursor(Qt::CrossCursor);
			setCursor(Qt::CrossCursor);
			rect.setTopLeft(p);
			rect.setBottomRight(p);
			updateRegion();
			pointCount++;
			jobtype = ing;
		}
		break;
	case Polyline:
	case Polygon:
	{
		if (event->button() == Qt::LeftButton) {
			//widget->setCursor(Qt::CrossCursor);
			setCursor(Qt::CrossCursor);
			addPoint(p);
			rect.setTopLeft(p);
			rect.setBottomRight(p);
			updateRegion();
			pointCount++;
			jobtype = ing;
		}else if(event->button() == Qt::RightButton) {
			addPoint(p);
			updateRegion();
			jobtype = finish;
			//widget->unsetCursor();
			unsetCursor();
			pointCount = 0;
		}
	}
		break;
	case Text:
		if (event->button() == Qt::LeftButton) {
			//widget->setCursor(Qt::CrossCursor);
			setCursor(Qt::CrossCursor);
			QFont font = property.getFont();
			QFontMetrics m(font);
			QRect rect1 = m.boundingRect(text);
			rect = QRect(p.x(), p.y(), rect1.width(), rect1.height());
			updateRegion();
			jobtype = ing;
			pointCount = 1;
		}
		break;
	case Symbol:
		if (event->button() == Qt::LeftButton) {
			//widget->setCursor(Qt::CrossCursor);
			setCursor(Qt::CrossCursor);
			QRect rect1 = pixmap.rect();
			rect = QRect(p.x() - (rect1.width()/2), p.y() - (rect1.height()/2), rect1.width(), rect1.height());
			updateRegion();
			jobtype = ing;
			pointCount = 1;
		}
		break;
	case Arc:
	{
		if (pointCount < 1) {
			addPoint(p);
			pointCount = 1;
		}else {
			pointCount++;
			addPoint(p);

			int w = p.x() - pointList[0].x();
			int h = p.y() - pointList[0].y();

			startAngle = getAngleDegree(w, h) - 180;
			endAngle = 180 * ((event->button() == Qt::LeftButton) ? 1 : -1);	// 시계방향 - minus
		}
	}
		break;
	default:
		return;
	}
}

void UserDrawItem::mMove(QMouseEvent* event)
{
	if (userdrawtype == Select) return;
	QPoint p = event->pos();

	switch(userdrawtype) {
	case Line:
	case Rectangle:
	case Ellipse:
		if (pointCount > 0) {
			updateRegion();
			rect.setBottomRight(p);
			updateRegion();
			jobtype = ing;
		}
		break;
	case Circle:
		if (pointCount > 0) {
			updateRegion();
			rect.setBottomRight(p);
			int m = qMax(rect.width(), rect.height());
			rect.setSize(QSize(m, m));
			updateRegion();
			jobtype = ing;
		}
		break;
	case Polyline:
	case Polygon:
	{
		updateRegion();
		rect.setBottomRight(p);
		calcMinMax2(p);		// 마우스 움직이는 것을 포함
		updateRegion();
		jobtype = ing;
	}
		break;
	case Text:
	{
		if (pointCount > 0) {
			updateRegion();
			rect = QRect(p.x(), p.y(), rect.width(), rect.height());
			updateRegion();
			jobtype = ing;
		}
	}
		break;
	case Symbol:
	{
		if (pointCount > 0) {
			updateRegion();
			QRect rect1 = pixmap.rect();
			rect = QRect(p.x() - (rect1.width()/2), p.y() - (rect1.height()/2), rect1.width(), rect1.height());
			updateRegion();
			jobtype = ing;
		}
	}
		break;
	case Arc:
	{
		// not use....
		std::cout << "mMove Arc type called............\n";
	}
		break;
	default:
		break;
	}
}

void UserDrawItem::mRelease(QMouseEvent* event)
{
	if (userdrawtype == Select) return;
	QPoint p = event->pos();

	switch(userdrawtype) {
	case Line:
	case Rectangle:
	case Circle:
	case Ellipse:
		if (pointCount == 1) {
			//widget->unsetCursor();
			unsetCursor();
			jobtype = finish;
			pointCount = 0;
		}
		break;
	case Polyline:
	{
		;
	}
		break;
	case Polygon:
		break;
	case Text:
	{
		//widget->unsetCursor();
		unsetCursor();
		jobtype = finish;
		pointCount = 0;
	}
		break;
	case Symbol:
	{
		//widget->unsetCursor();
		unsetCursor();
		jobtype = finish;
		pointCount = 0;
	}
		break;
	case Arc:
	{
		if (pointCount == 2) {
			//widget->unsetCursor();
			unsetCursor();
			jobtype = finish;
			pointCount = 0;
		}
	}
		break;
	default:
		break;
	}
}

void UserDrawItem::updateRegion()
{
	if (userdrawtype == Select) return;

	switch(userdrawtype) {
	case Line:
	case Rectangle:
	case Circle:
	case Ellipse:
	{
		QRect rect1 = rect.normalized();
		if (pointCount == 1) {
			//widget->update(rect1);
			update(rect1);
		}
	}
		break;
	case Polygon:
	case Polyline:
	{
		QRect rect1 = QRect(minPoint2, maxPoint2);
		QRect rect2 = rect1.normalized();

		if (pointCount >= 1) {
			//widget->update(rect2);
			update(rect2);
			//update();
		}
	}
		break;
	case Text:
	{
		QRect rect1 = rect.normalized();
		//widget->update(rect1);
		update(rect1);
	}
		break;
	case Symbol:
	{
		//widget->update(rect.normalized());
		update(rect.normalized());
	}
		break;
	case Arc:
	{
		QRect rect1 = rect.normalized();
		if (pointCount == 2) {
			//widget->update(rect1);
			update(rect1);
		}
	}
		break;
	default:
		break;
	}
}

void UserDrawItem::draw(QPainter* painter)
{
	if (userdrawtype == Select) return;

	// painter debug
	//std::cout << property.toString().toStdString();

	painter->setPen(property.getPen());
	painter->setBrush(property.getBrush());
	switch(userdrawtype) {
	case Line:
	{
		QPoint p1, p2;
		p1 = rect.topLeft();
		p2 = rect.bottomRight();
		painter->drawLine(p1, p2);
	}
		break;
	case Polyline:
	{
		QPoint p1, p2;
		p1 = rect.topLeft();
		p2 = rect.bottomRight();
		QPolygon latPoints(pointList.count() + 1);
		int i;
		for (i=0; i<pointList.count(); i++) {
			latPoints[i] = pointList[i];
		}
		latPoints[i] = p2;
		painter->drawPolyline(latPoints);
	}
		break;
	case Polygon:
	{
		QPoint p1, p2;
		p1 = rect.topLeft();
		p2 = rect.bottomRight();
		QPolygon latPoints(pointList.count() + 1);
		int i;
		for (i = 0; i<pointList.count(); i++) {
			latPoints[i] = pointList[i];
		}
		latPoints[i] = p2;
		painter->drawPolygon(latPoints);
	}
		break;
	case Rectangle:
	{
		painter->drawRect(rect.normalized().adjusted(0, 0, -1, -1));
	}
		break;
	case Circle:
	case Ellipse:
	{
		painter->drawEllipse(rect.normalized().adjusted(0, 0, -1, -1));
	}
		break;
	case Text:
		painter->setPen(property.fontColor());
		painter->setFont(property.getFont());
		drawText1(painter);
		break;
	case Symbol:
		painter->drawPixmap(rect, pixmap);
		break;
	case Arc:
	{
		if (pointCount == 0) break;

		if (pointCount == 2) {
			painter->setPen(QPen(QColor(255, 0, 0), 2));
			QRect rectpie = rect;
			int angle1 = (int)startAngle * 16;
			int angle2 = (int)endAngle * 16;

			// arc ....
		}
	}
		break;
	default:
		break;
	}
}

void UserDrawItem::drawText1(QPainter* painter)
{
	QString text2 = text.trimmed();
	QRect rect1 = rect.normalized().adjusted(0, 0, -1, -1);
	painter->drawText(rect1, Qt::AlignLeft | Qt::AlignVCenter, text2);
}

QChar UserDrawItem::drawTypeChar()
{
	QChar ch;
	switch(userdrawtype) {
	case Line:
		ch = QChar('L');
		break;
	case Polyline:
		ch = QChar('P');
		break;
	case Polygon:
		ch = QChar('G');
		break;
	case Rectangle:
		ch = QChar('R');
		break;
	case Circle:
		ch = QChar('C');
		break;
	case Ellipse:
		ch = QChar('E');
		break;
	case Text:
		ch = QChar('T');
		break;
	case Symbol:
		ch = QChar('S');
		break;
	case Arc:
		ch = QChar('A');
		break;
	case Manual:
		ch = QChar('M');
		break;
	default:
		ch = QChar('X');
		break;
	}

	return ch;
}

void UserDrawItem::setSymbol(const QString& t)
{
	symbolFile = t;
	pixmap.load(symbolFile);
	update();
}
