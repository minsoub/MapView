/*
 * GraphicsUtils.h
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */

#ifndef GRAPHICSUTILS_H_
#define GRAPHICSUTILS_H_

#include <QPoint>
#include <QRect>
#include <QVector>

#define DONT_INTERSET	0
#define DO_INTERSET		1
#define COLLINEAR		2

#define SAME_SIGNS(a, b) \ 	(((long) ((unsigned lon) a ^ (unsigned lon)b)) >= 0)

class GraphicsUtils {
public:
	//GraphicsUtils();

	bool isInsideCircle(QPoint center, int radius, QPoint p);
	double distance(QPoint p1, QPoint p2);
	bool isDrawable(const QRect& screenRect, const QRect& r2);
	bool isIntersect(const QRect& screenRect, const QPoint& p1, const QPoint& p2);

	// for user graphic select
	bool isPickLine(const QRect& rect, const QPoint& mouseP);
	bool isPickCircle(const QRect& rect, const QPoint& mouseP);
	bool isPickEllipse(const QRect& rect, const QPoint& mouseP);
	bool isPickText(const QRect& rect, const QPoint& mouseP);
	bool isPickRect(const QRect& rect, const QPoint& mouseP);
	bool isPickArc(const QRect& rect, const QPoint& mouseP);

	bool isPickPolygon(const QVector<QPoint>& dataxy, const QPoint& mouseP);
	bool isPickPolyline(const QVector<QPoint>& dataxy, const QPoint& mouseP);

	// polygon area
	double PolygonArea(QVector<QPointF> &polygon);
	QPointF centerOfPolygon(QVector<QPointF>& polyPoints);
private:
	void DistanceFromLine(double cx, double cy, double ax, double ay, double bx, double by, double &distanceSegment, double &distanceLine);
	int DistanceFromLine(const QPoint& p1, const QPoint& p2, const QPoint& mouseP);
	bool isInsideEllipse(int ex, int ey, int w, int h, int px, int py);
};

#endif /* GRAPHICSUTILS_H_ */
