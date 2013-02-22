/*
 * MapConvertFunc.h
 *
 *  Created on: 2012. 1. 18.
 *      Author: HIST002
 */

#ifndef MAPCONVERTFUNC_H_
#define MAPCONVERTFUNC_H_

#include "usermathutil.h"
//#include "../GeoData.h"

using namespace usermathutils;



static double toDD(double degree,double min,double sec)
{
	double deg1,min1,sec1;
	deg1 = fabs(round(degree, 6));
	min1 = fabs(round(min,    6));
	sec1 = fabs(round(sec,    6));
	return round(deg1+(min1/60)+(sec1/3600), 6);
}



// N39001234 or E125001234 -> double
static double strToDD(const QString& dms)
{
	double deg,min,sec;
	QChar sign;
	if(dms.length() == 9 || dms.length() == 10){
		;
	}else{
		return 0.0;
	}
	sign = dms[0];
	if((sign == QChar('N') || sign == QChar('S'))&& dms.length()==9){
		deg = dms.mid(1,2).toDouble();
		min = dms.mid(3,2).toDouble();
		sec = dms.mid(5,4).toDouble()/100;
	}else if((sign == QChar('E') || sign == QChar('W'))&& dms.length()==10){
		deg = dms.mid(1,3).toDouble();
		min = dms.mid(4,2).toDouble();
		sec = dms.mid(6,4).toDouble()/100;
	}else{
		return 0.0;
	}

	double dd = toDD(deg,min,sec);

	if(sign == QChar('S') || sign == QChar('W')){
		return (dd * -1.0);
	}else{
		return dd;
	}
}

// N35001234E125001234 -> decimal degree
static QPointF toDD(const QString& latlon)
{
	//std::cout << "latlon length : " << latlon.length() << "\n";
	if (latlon.length() != 19) {
		return QPointF(0.0, 0.0);
	}

	QString lat1 = latlon.mid(0, 9);
	QString lon1 = latlon.mid(9, 10);

	double dd_lat = strToDD(lat1);
	double dd_lon = strToDD(lon1);

	//std::cout << "dd_lat : " << dd_lat << ", dd_lon : " << dd_lon << "\n";
	return QPointF(dd_lat, dd_lon);
}

#endif /* MAPCONVERTFUNC_H_ */
