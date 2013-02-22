/*
 * Turtle.h
 *
 *  Created on: 2012. 1. 26.
 *      Author: HIST002
 */

#ifndef TURTLE_H_
#define TURTLE_H_

#include <QPoint>
#include <QString>

class Turtle {
public:
	Turtle() { Turtle(QPoint(0, 0)); }
	Turtle(QPoint p) { now = p; prev = now; }
	Turtle(int x, int y) { now = QPoint(x, y); prev = now; }

	void setPoint(const QPoint &p) { now = prev = p; }
	void setPoint(int x, int y) { now = prev = QPoint(x, y); }
	int x() { return now.x(); }
	int y() { return now.y(); }
	QPoint left(int d=1);
	QPoint right(int d=1);
	QPoint up(int d = 1);
	QPoint down(int d = 1);
	QPoint west(int d=1) { return left(d); }
	QPoint east(int d=1) { return right(d); }
	QPoint north(int d=1) { return right(d); }
	QPoint south(int d=1) { return right(d); }
	QPoint back();
	QPoint polar(int r, double decimal_theta);
	QPoint moveCommand(const QString& cmd);

private:
	QPoint prev;
	QPoint now;
};

#endif /* TURTLE_H_ */
