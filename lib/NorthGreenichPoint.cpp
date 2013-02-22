/*
 * NorthGreenichPoint.cpp
 *
 *  Created on: 2012. 1. 25.
 *      Author: HIST002
 */
#include <math.h>
#include "NorthGreenichPoint.h"

double NorthGreenichPoint::incNorth(double d)
{
	double north = northPoint;
	north += d;
	if (north >= 360) {
		north = fmod(north, 360);
	}
	return north;
}

double NorthGreenichPoint::incGreenich(double d)
{
	double greenich = greenichPoint;
	greenich += d;
	if (greenich >= 360) {
		greenich = fmod(greenich, 360);
	}
	return greenich;
}

double NorthGreenichPoint::decNorth(double d)
{
	double north = northPoint;
	north -= d;
	if (north < 0) {
		north = 360 + north;
	}
	return north;
}

double NorthGreenichPoint::decGreenich(double d)
{
	double greenich = greenichPoint;
	greenich -= d;
	if (greenich < 0) {
		greenich = 360 + greenich;
	}
	return greenich;
}

double NorthGreenichPoint::northToLat(double np)
{
	double realLat = -999;
	if (np >= 0 && np <= 90) {
		realLat = np;
	}else if(np > 90 && np <= 270) {
		realLat = 180 - np;
	}else if(np > 270 && np < 360) {
		realLat = -360 + np;
	}else if(np == -0) {
		realLat = 0;
	}
	return realLat;
}

double NorthGreenichPoint::greenichToLon(double gp)
{
	double realLon = -999;
	if (gp >= 0 && gp <= 180) {
		realLon = gp;
	}else if(gp > 180 && gp < 360) {
		realLon = gp - 360;
	}else if(gp == -0) {
		realLon = 0;
	}
	return realLon;
}


