/*
 * LatLonBound.cpp
 *
 *  Created on: 2012. 1. 19.
 *      Author: HIST002
 */

#include <limits.h>
#include "LatLonBound.h"

LatLonBound::LatLonBound() {
	// TODO Auto-generated constructor stub

}

void LatLonBound::initialize()
{
	leftlon = rightlon = toplat = bottomlat = 0.0;
	minP = QPoint(INT_MAX, INT_MAX);
	maxP = QPoint(INT_MIN, INT_MIN);
}

void LatLonBound::setPosition(const QPoint& p)
{
	minP.setX(qMin(p.x(), minP.x()));
	minP.setY(qMin(p.y(), minP.y()));
	maxP.setX(qMax(p.x(), maxP.x()));
	maxP.setY(qMax(p.y(), maxP.y()));
}

void LatLonBound::setRect(const QRect& rect)
{
	minP.setX(qMin(rect.left(),   minP.x()));
	minP.setY(qMin(rect.top(),    minP.y()));
	maxP.setX(qMax(rect.right(),  maxP.x()));
	maxP.setY(qMax(rect.bottom(), maxP.y()));
}

bool LatLonBound::inRect(const QRect& rect)
{
	if (maxP.y() < rect.top() || minP.y() > rect.bottom() || minP.x() > rect.right() || maxP.x() < rect.left())
		return false;

	return true;
}
