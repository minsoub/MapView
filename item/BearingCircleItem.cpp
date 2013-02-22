/*
 * BearingCircleItem.cpp
 *
 *  Created on: 2012. 1. 26.
 *      Author: HIST002
 */

#include "BearingCircleItem.h"
#include "../lib/Turtle.h"

BearingCircleItem::BearingCircleItem() {
	// TODO Auto-generated constructor stub
	setZValue(1000);
	setFlag(ItemIgnoresTransformations, true);
	isShow = false;
}

void BearingCircleItem::setScreenConvertClass(LatLonConvert *vp)
{

	this->vp = vp;
}

void BearingCircleItem::updateInfo()
{
	prepareGeometryChange();
}
QRectF BearingCircleItem::boundingRect() const
{
	qreal adjust = 0.0;

	QRectF rect = QRectF(adjust, adjust,
			vp->srcRect().width() * 1.0, vp->srcRect().height() * 1.0);

	return rect;
}

void BearingCircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	if (isShow)
		drawBearingCircle(painter);
}

void BearingCircleItem::drawBearingCircle(QPainter *painter)
{
	Turtle turtle;
	int boxH = 10;
	int boxW = 20;

	QString turtlecmds[24] = {
			"L10",     "L10",     "L10",     "L10",      // 0, 15, 30, 45
			"L15",     "L20,U5",  "L15,U5",  "L20,U5",   // 60, 75, 90, 105
			"L20,U5",  "L20,U5",  "L10,U10", "L10,U10",  // 120, 135, 150, 165
			"L10,U10", "L10,U10", "L10,U10", "L8,U10",   // 180, 195, 210, 225
			"U5",      "U5",      "U5",      "U4",       // 240, 255, 270, 284
			"U5",      "U5",      "L10",     "L10"       // 300, 315, 330, 345
	};

	int r = qMin(vp->srcWidth(), vp->srcHeight()) / 2;

	QPoint center = vp->screenCenter();
	QRect  rect   = QRect(center.x() - r, center.y() - r, r*2, r*2);

	painter->setPen(QPen(Qt::white, 1));
	painter->drawEllipse(rect);

	painter->setPen(QPen(Qt::white, 1));

	QRect textBox;
	painter->setFont(QFont("Times", 8));
	for (int i=0,j=0; i<360; i+=15) {
		int x1 = (int)floor(r * 0.98 * sin(i * deg2rad));
		int y1 = (int)floor(r * 0.98 * cos(i * deg2rad));
		int x2 = (int)floor(r * sin(i * deg2rad));
		int y2 = (int)floor(r * cos(i * deg2rad));

		QPoint point1 = QPoint(center.x() + x1, center.y() - y1);
		QPoint point2 = QPoint(center.x() + x2, center.y() - y2);
		painter->drawLine(point1, point2);
		turtle.setPoint(point1);
		turtle.moveCommand(turtlecmds[j++]);
		textBox.setRect(turtle.x(), turtle.y(), boxW, boxH);
		painter->drawText(textBox, Qt::AlignHCenter|Qt::AlignVCenter, QString("%1").arg(i));
	}
}



