/*
 * ViewPortItem.cpp
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#include "ViewPortItem.h"

ViewPortItem::ViewPortItem() {
	// TODO Auto-generated constructor stub

}

void ViewPortItem::updateInfo()
{
	prepareGeometryChange();
}
QRectF ViewPortItem::boundingRect() const
{
	qreal adjust = 1;

	QRectF rect = QRectF(adjust, adjust+5,
			vp->srcRect().width() * 1.0, vp->srcRect().height() * 1.0);

	return rect;
}

void ViewPortItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	air->displayViewPortInfo(painter);
}
