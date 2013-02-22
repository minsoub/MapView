/*
 * DirBearing.cpp
 *
 *  Created on: 2012. 3. 6.
 *      Author: HIST002
 */

#include "DirBearing.h"

DirBearing::DirBearing() {
	// TODO Auto-generated constructor stub
	setZValue(1000);
	setFlag(ItemIgnoresTransformations, true);
	textColor = QColor(Qt::white);
	lineColor = QColor(Qt::white);
}

void DirBearing::setScreenConvertClass(LatLonConvert *vp)
{

	this->vp = vp;
}

void DirBearing::updateInfo()
{
	prepareGeometryChange();
}
QRectF DirBearing::boundingRect() const
{
	qreal adjust = 0.0;

	QRectF rect = QRectF(adjust, adjust,
	vp->srcRect().width() * 1.0, vp->srcRect().height() * 1.0);

	return rect;
}

void DirBearing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	draw(painter);
}

void DirBearing::initialize()
{
	rectLine = QRect(0, 0, 0, 0);
	rectText = QRect(0, 0, 50, 40);
	rectStartCross = QRect(0, 0, 0, 0);
	font.setFamily("Times");
	font.setPointSizeF(10.0);
}

double DirBearing::getAngleDegree(int w, int h)
{
	double angleRadian = 0;
	if (w == 0 && h == 0) {
		angleRadian = 0;
	}else if(w > 0) {
		if (h < 0) {	// 1
			angleRadian = atan((double)(h*-1)/(double)w);
		}else if(h > 0) {	// 4
			angleRadian = atan((double)h/(double)w);
			angleRadian = (2*PI) - angleRadian;
		}else if(h == 0) {
			angleRadian = 0;
		}
	}else if(w < 0) {
		if (h < 0) {	// 2
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

void DirBearing::updateRegion()
{
	update();
}

void DirBearing::mPress(QMouseEvent* event)
{
	QPoint p = event->pos();
	if (event->button() == Qt::LeftButton) {
		this->setCursor(Qt::CrossCursor);
		initialize();
		rectLine.setTopLeft(p);
		rectLine.setBottomRight(p);
		rectStartCross = QRect(p.x() - 2, p.y() - 2, 5, 5);
		startpoint = endpoint = p;
		jobtype = ing;
	}
}

void DirBearing::mMove(QMouseEvent* event, const QString& dist, const QString& bearing)
{
	if (jobtype != ing) return;
	QPoint p = event->pos();
	disttext = dist;
	bearingtext = bearing;

	updateRegion();

	endpoint = p;
	rectLine.setBottomRight(p);
	text = QString("Distance:%1\nBearing:%2").arg(disttext).arg(bearingtext);
	QFontMetrics m(font);
	QRect r = m.boundingRect(text);
	rectText = QRect(p.x() - 1, p.y() - 1, r.width(), r.height()+12);

	updateRegion();
}

void DirBearing::mRelease()
{
	if (jobtype != ing) return;
	this->unsetCursor();

	updateRegion();
	jobtype = finish;
}

void DirBearing::draw(QPainter* painter)
{
	if (jobtype != ing) return;

	painter->setPen(QPen(textColor, 1));
	painter->drawLine(startpoint, endpoint);

	// Draw cross
	turtle.setPoint(startpoint);
	QPoint p1 = turtle.up(2);
	turtle.back();
	QPoint p2 = turtle.down(2);
	turtle.back();
	painter->drawLine(p1, p2);
	p1 = turtle.left(2);
	turtle.back();
	p2 = turtle.right(2);
	painter->drawLine(p1, p2);

	// Text
	painter->setFont(font);

	painter->drawText(rectText, Qt::AlignCenter, text);

}
