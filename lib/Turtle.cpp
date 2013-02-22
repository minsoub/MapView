/*
 * Turtle.cpp
 *
 *  Created on: 2012. 1. 26.
 *      Author: HIST002
 */

#include "Turtle.h"
#include <QStringList>
#include <math.h>

QPoint Turtle::left(int d)
{
	prev = now;
	now.setX(now.x() - d);

	return now;
}

QPoint Turtle::right(int d)
{
	prev = now;
	now.setX(now.x() + d);

	return now;
}

QPoint Turtle::up(int d)
{
	prev = now;
	now.setY(now.y() - d);

	return now;
}

QPoint Turtle::down(int d)
{
	prev = now;
	now.setY(now.y() + d);

	return now;
}

QPoint Turtle::back()
{
	now = prev;

	return now;
}

QPoint Turtle::polar(int r, double decimal_theta)
{
	double torad = 3.14159265 / 180;
	double x = now.x() + (r * cos(torad * decimal_theta));
	double y = now.y() - (r * sin(torad * decimal_theta));
	prev = now;
	now.setX((int)floor(x));
	now.setY((int)floor(y));

	return now;
}

QPoint Turtle::moveCommand(const QString& cmd)
{
	QStringList list = cmd.split(',');
	QString d = 0;

	for (int i=0; i<list.size(); i++) {
		QString s = list[i];
		char ch = s[0].toAscii();
		switch(ch) {
		case 'L':
		case 'W':
			prev = now;
			d = s.mid(1);
			now = left(d.toInt());
			break;
		case 'R':
		case 'E':
			prev = now;
			d = s.mid(1);
			now = right(d.toInt());
			break;
		case 'N':
		case 'U':
			prev = now;
			d = s.mid(1);
			now = up(d.toInt());
			break;
		case 'D':
		case 'S':
			prev = now;
			d = s.mid(1);
			now = down(d.toInt());
			break;
		default:
			;
		}
	}
	return now;
}


