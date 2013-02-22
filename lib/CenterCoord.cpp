/*
 * CenterCoord.cpp
 *
 *  Created on: 2012. 1. 18.
 *      Author: HIST002
 */

#include "CenterCoord.h"

int CenterCoord::toLogicX(const int physic_x)
{
	return physic_x - pcenter.x();
}

int CenterCoord::toLogicY(const int physic_y)
{
	return pcenter.y() - physic_y;
}

QPoint CenterCoord::toLogicXY(const int physic_x, const int physic_y)
{
	return toLogicXY(QPoint(physic_x, physic_y));
}

QPoint CenterCoord::toLogicXY(const QPoint& physic_p)
{
	int x = toLogicX(physic_p.x());
	int y = toLogicY(physic_p.y());

	return QPoint(x, y);
}

int CenterCoord::toPhysicX(const int logic_x)
{
	return ( pcenter.x() + logic_x );
}

int CenterCoord::toPhysicY(const int logic_y)
{
	return ( pcenter.y() - logic_y );
}

double CenterCoord::toPhysicX(const double logic_x)
{
	return ( pcenter.x() + logic_x );
}

double CenterCoord::toPhysicY(const double logic_y)
{
	return ( pcenter.y() - logic_y );
}

QPoint CenterCoord::toPhysicXY(const int logic_x, const int logic_y)
{
	return toPhysicXY(QPoint(logic_x, logic_y));
}

QPoint CenterCoord::toPhysicXY(const QPoint& logic_p)
{
	int new_x = toPhysicX(logic_p.x());
	int new_y = toPhysicY(logic_p.y());

	return QPoint(new_x, new_y);
}

