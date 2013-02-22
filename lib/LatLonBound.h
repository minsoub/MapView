/*
 * LatLonBound.h
 *
 *  Created on: 2012. 1. 19.
 *      Author: HIST002
 */

#ifndef LATLONBOUND_H_
#define LATLONBOUND_H_

#include <QPoint>
#include <QRect>

class LatLonBound {
public:
	LatLonBound();
	void initialize();
	void setPosition(const QPoint &p);
	void setRect(const QRect& rect);
	bool inRect(const QRect& rect);
	QPoint center() {
		QRect rect = QRect(minP, maxP);
		return rect.center();
	}
private:
	double leftlon;
	double rightlon;
	double toplat;
	double bottomlat;
	QPoint minP;
	QPoint maxP;
};

#endif /* LATLONBOUND_H_ */
