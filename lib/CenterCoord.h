/*
 * CenterCoord.h
 *
 *  Created on: 2012. 1. 18.
 *      Author: HIST002
 */

#ifndef CENTERCOORD_H_
#define CENTERCOORD_H_

#include <QtCore>

class CenterCoord {
public:
	CenterCoord() { pcenter = QPoint(0, 0); }
	CenterCoord(const QPoint& center_xy) { pcenter = center_xy; }
	CenterCoord(const int& width, const int& height);
	void setCenter(const QPoint& p) { pcenter = p; }
	void setCenter(const int x, const int y) { pcenter = QPoint(x, y); }
	int center_x() { return pcenter.x(); }
	int center_y() { return pcenter.y(); }
	QPoint center() { return pcenter; }

	int toLogicX(const int physic_x);
	int toLogicY(const int physic_y);
	QPoint toLogicXY(const QPoint& p);
	QPoint toLogicXY(const int physic_x, const int physic_y);

	int toPhysicX(const int logic_x);
	int toPhysicY(const int logic_y);

	double toPhysicX(const double logic_x);
	double toPhysicY(const double logic_y);

	QPoint toPhysicXY(const QPoint& logic_p);
	QPoint toPhysicXY(const int logic_x, const int logic_y);
private:
	QPoint pcenter;
};

#endif /* CENTERCOORD_H_ */
