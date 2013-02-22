/*
 * CalcAir.cpp
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */
#include <iostream>
#include <QString>
#include "usermathutil.h"
#include "CalcAir.h"

using namespace usermathutils;

double CalcAir::toBearing(double x) {
	return mod(toDeg(x), 360);
}

double CalcAir::toFinalBearing(double x) {
	return 180-mod((toDeg(x)), 360);
}

// Decimal degree lat, lon
double CalcAir::greatCircleDistance(double lat1, double lon1, double lat2, double lon2)
{
	double R = EarthRadius;
	double dLat = toRad(lat2 - lat1);
	double dLon = toRad(lon2 - lon1);

	double Lat1 = toRad(lat1);
	double Lat2 = toRad(lat2);

	double a = sin(dLat/2) * sin(dLat/2) + cos(Lat1) * cos(Lat2) * sin(dLon/2) * sin(dLon/2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));

	return R * c;
}

double CalcAir::cosineLawDistance(double lat1, double lon1, double lat2, double lon2)
{
	double Lat1 = toRad(lat1);
	double Lat2 = toRad(lat2);

	double d = acos(sin(Lat1) * sin(Lat2) + cos(Lat1) * cos(Lat2) * cos(toRad(lon2 - lon1))) * EarthRadius;

	return d;
}

QPointF CalcAir::midPoint(double lat1, double lon1, double lat2, double lon2)
{
	double dLon = toRad(lon2 - lon1);

	double Lat1 = toRad(lat1);
	double Lon1 = toRad(lon1);
	double Lat2 = toRad(lat2);

	double bx = cos(Lat2) * cos(dLon);
	double by = cos(Lat2) * sin(dLon);
	double lat3 = atan2(sin(Lat1) + sin(Lat2), sqrt((cos(Lat1) + bx) * (cos(Lat1) + bx) + by * by));
	double lon3 = Lon1 + atan2(by, cos(Lat1) + bx);

	return QPointF(toDeg(lat3), toDeg(lon3));
}

// GreatCircleDestination
QPointF CalcAir::greatCircleDestPosition(double startLat, double startLon, double bearing, double distance)
{
	double Lat1 = toRad(startLat);
	double Lon1 = toRad(startLon);
	double Bearing = toRad(bearing);

	double DR = distance / EarthRadius;

	double Lat2 = asin(sin(Lat1) * cos(DR) + cos(Lat1) * sin(DR) * cos(Bearing));
	double Lon2 = Lon1 + atan2(sin(Bearing) * sin(DR) * cos(Lat1), cos(DR) - sin(Lat1) * sin(Lat2));
	Lon2 = mod(Lon2 + PI, 2 * PI) - PI;

	return QPointF(toDeg(Lat2), toDeg(Lon2));
}

double CalcAir::rhumbDistance(double startLat, double startLon, double endLat, double endLon)
{
	double Lat1 = toRad(startLat);
	double Lat2 = toRad(endLat);
	double dLat = toRad(endLat - startLat);
	double dLon = toRad(endLon - startLon);

	double dPhi = log(tan(Lat2/2 + FOURTHPI) / tan(Lat1 / 2 + FOURTHPI));
	double q = (fabs(dLat) > 1e-10) ? dLat / dPhi : cos(Lat1);
	if (dLon > PI) dLon = 2 * PI - dLon;
	double d = sqrt(dLat * dLat + q * q * dLon * dLon);

	return d * EarthRadius;
}

double CalcAir::bearingRhumb(double lat1, double lon1, double lat2, double lon2)
{
	double Lat1 = toRad(lat1);
	double Lat2 = toRad(lat2);
	double dLon = toRad(lon2 - lon1);
	double dPhi = log(tan(Lat2/2 + FOURTHPI) / tan(Lat1/2 + FOURTHPI));

	if (fabs(dLon) > PI) dLon = (dLon > 0) ? -(2*PI - dLon) : (2*PI + dLon);

	return toBearing(atan2(dLon, dPhi));
}

QPointF CalcAir::rhumbDestPosition(double startLat, double startLon, double bearing, double distance)
{
	double Lat1 = toRad(startLat);
	double Lon1 = toRad(startLon);
	double d = distance / EarthRadius;

	double Bearing = toRad(bearing);

	double Lat2 = Lat1 + d * cos(Bearing);
	double dLat = Lat2 - Lat1;
	double dPhi = log(tan(Lat2/2 + FOURTHPI) / tan(Lat1/2 + FOURTHPI));
	double q = (fabs(dLat) > 1e-10) ? dLat / dPhi : cos(Lat1);
	double dLon = d * sin(Bearing) / q;

	if (fabs(Lat2) > PI/2) Lat2 = Lat2 > 0 ? PI - Lat2 : -(PI - Lat2);
	double m = (2*PI);
	double Lon2 = modf((Lon1 + dLon + PI), &m) - PI;

	return QPointF(toDeg(Lat2), toDeg(Lon2));
}

double CalcAir::toDD(double degree, double min, double sec)
{
	double deg1, min1, sec1;
	deg1 = fabs(round(degree, 6));
	min1 = fabs(round(min, 6));
	sec1 = fabs(round(sec, 6));

	return round(deg1+(min1/60) + (sec1/3600), 6);
}

double CalcAir::strToDD(const QString& dms)
{
	double deg, min, sec;
	QChar sign;
	if (dms.length() == 9 || dms.length() == 10) {
		;
	}else {
		return 0.0;
	}
	sign = dms[0];
	if ((sign == QChar('N') || sign == QChar('S')) && dms.length() == 9) {
		deg = dms.mid(1, 2).toDouble();
		min = dms.mid(3, 2).toDouble();
		sec = dms.mid(5, 4).toDouble() / 100;
	}else if((sign == QChar('E') || sign == QChar('W')) && dms.length() == 10) {
		deg = dms.mid(1, 3).toDouble();
		min = dms.mid(4, 2).toDouble();
		sec = dms.mid(6, 4).toDouble() / 100;
	}else {
		return 0.0;
	}

	double dd = toDD(deg, min, sec);

	if (sign == QChar('S') || sign == QChar('W')) {
		return (dd * -1.0);			// where is variable??
	}else {
		return dd;
	}
}

QPointF CalcAir::toDD(const QString& latlon)
{
	if (latlon.length() != 19) {
		return QPointF(0.0, 0.0);
	}
	QString lat1 = latlon.mid(0, 9);
	QString lon1 = latlon.mid(9, 10);

	double dd_lat = strToDD(lat1);
	double dd_lon = strToDD(lon1);

	return QPointF(dd_lat, dd_lon);
}

QPointF CalcAir::toRadian(const QString& latlon)
{
	QPointF f = toDD(latlon);
	double lat = toRad(f.x());
	double lon = toRad(f.y());
	return QPointF(lat, lon);
}

QPointF CalcAir::toRadian(const QPointF& ddLatLon)
{
	return QPointF(toRad(ddLatLon.x()), toRad(ddLatLon.y()));
}

QString CalcAir::latToDMS(const QString& lat)
{
	QString lat_deg, lat_min, lat_sec1, lat_sec2;
	QChar signLat = lat[0];

	lat_deg = lat.mid(1, 2);
	lat_min = lat.mid(3, 2);
	lat_sec1 = lat.mid(5, 2);
	lat_sec2 = lat.mid(7, 2);

	return QString("%1%2:%3:%4.%5").arg(signLat).arg(lat_deg).arg(lat_min).arg(lat_sec1).arg(lat_sec2);

}

QString CalcAir::lonToDMS(const QString& lon)
{
	QString lon_deg, lon_min, lon_sec1, lon_sec2;
	QChar signLon = lon[0];

	lon_deg = lon.mid(1, 3);
	lon_min = lon.mid(4, 2);
	lon_sec1 = lon.mid(6, 2);
	lon_sec2 = lon.mid(8, 2);

	return QString("%1%2:%3:%4.%5").arg(signLon).arg(lon_deg).arg(lon_min).arg(lon_sec1).arg(lon_sec2);
}

// 35.12345 => N35001234
QString CalcAir::LatDecimalToDMS(double latdecimal)
{
	double d = fabs(latdecimal);
	int deg = (int)floor(d);
	int min = (int)floor((d - deg) * 60);

	int sec = (int)floor((((d - deg) * 60 - min) * 100/ 60) * 3600);
	QChar sign = QChar('N');
	if (latdecimal < 0) {
		sign = QChar('S');
	}

	return QString("%1%2%3%4").arg(sign).arg(deg, 2, 'f', 0, QChar('0')).arg(min, 2, 'f', 0, '0').arg(sec, 4, 'f', 0, '0');
}

QString CalcAir::LonDecimalToDMS(double londecimal)
{
	double d = fabs(londecimal);
	int deg = (int)floor(d);
	int min = (int)floor((d - deg) * 60);
	int sec = (int)floor((((d - deg)*60 - min)*100/60)*3600);
	QChar sign = QChar('E');
	if (londecimal < 0) {
		sign = QChar('W');
	}

	return QString("%1%2%3%4").arg(sign).arg(deg, 3, 'f', 0, QChar('0')).arg(min, 2, 'f', 0, '0').arg(sec, 4, 'f', 0, '0');
}

// N35001234 -> 35도 00분 12.34초
QString CalcAir::toDMS(const QString& latlon)
{
	if (latlon.length() != 19) {
		return QString("xxxxXxxxx");
	}
	QString lat1 = latlon.mid(0, 9);
	QString lon1 = latlon.mid(9, 10);
	QString lat_dms = latToDMS(lat1);
	QString lon_dms = lonToDMS(lon1);

	return QString("%1,%2").arg(lat_dms).arg(lon_dms);
}

QString CalcAir::toDMS(const QPointF& latlonDecDeg)
{
	QString lat = LatDecimalToDMS(latlonDecDeg.x());
	QString lon = LonDecimalToDMS(latlonDecDeg.y());

	return QString("%1%2").arg(lat).arg(lon);
}

QString CalcAir::toDMSHuman(const QPointF& latlonDecDeg)
{
	QString lat = LatDecimalToDMS(latlonDecDeg.x());
	QString lon = LonDecimalToDMS(latlonDecDeg.y());
	QString lat1 = latToDMS(lat);
	QString lon1 = lonToDMS(lon);

	return QString("%1,%2").arg(lat1).arg(lon1);
}

QString CalcAir::toDMSHuman(const QString& latlon)
{
	QString lat = latlon.mid(0, 9);
	QString lon = latlon.mid(9, 10);
	QString lat1 = latToDMS(lat);
	QString lon1 = lonToDMS(lon);

	return QString("%1,%2").arg(lat1).arg(lon1);
}

// return distance two point
double CalcAir::gc_distance(const QString& latlon1, const QString& latlon2)
{
	QPointF p1 = toDD(latlon1);
	QPointF p2 = toDD(latlon2);

	return greatCircleDistance(p1.x(), p1.y(), p2.x(), p2.y());
}

// return cosine Law distance
double CalcAir::cl_distance(const QString& latlon1, const QString& latlon2)
{
	QPointF p1 = toDD(latlon1);
	QPointF p2 = toDD(latlon2);

	return cosineLawDistance(p1.x(), p1.y(), p2.x(), p2.y());
}

double CalcAir::cl_distance(const QPointF& ddp1, const QPointF& ddp2)
{
	return cosineLawDistance(ddp1.x(), ddp1.y(), ddp2.x(), ddp2.y());
}

QPointF CalcAir::mid(const QString& latlon1, const QString& latlon2)
{
	QPointF p1 = toDD(latlon1);
	QPointF p2 = toDD(latlon2);

	return midPoint(p1.x(), p1.y(), p2.x(), p2.y());
}

double CalcAir::bearing(double lat1, double lon1, double lat2, double lon2)
{
	double Lat1 = toRad(lat1);
	double Lat2 = toRad(lat2);
	double dLon = toRad(lon2 - lon1);

	double y = sin(dLon) * cos(Lat2);
	double x = cos(Lat1) * sin(Lat2) - sin(Lat1)*cos(Lat2)*cos(dLon);

	return toBearing(atan2(y, x));
}

double CalcAir::final_bearing(double lat1, double lon1, double lat2, double lon2)
{
	double Lat1 = toRad(lat1);
	double Lat2 = toRad(lat2);
	double dLon = toRad(lon2 - lon1);

	double y = sin(dLon) * cos(Lat2);
	double x = cos(Lat1) * sin(Lat2) - sin(Lat1) * cos(Lat2) * cos(dLon);

	return toFinalBearing(atan2(y, x));
}

double CalcAir::bearing(const QPointF& p1, const QPointF& p2)
{
	return bearing(p1.x(), p1.y(), p2.x(), p2.y());
}

double CalcAir::bearing(const QString& latlon1, const QString& latlon2)
{
	QPointF p1 = toDD(latlon1);
	QPointF p2 = toDD(latlon2);

	return bearing(p1.x(), p1.y(), p2.x(), p2.y());
}

double CalcAir::final_bearing(const QString& latlon1, const QString& latlon2)
{
	QPointF p1 = toDD(latlon1);
	QPointF p2 = toDD(latlon2);

	return final_bearing(p1.x(), p1.y(), p2.x(), p2.y());
}

QPointF CalcAir::newPoint(const QString& latlon1, double bearing, double distance)
{
	QPointF orgPos = toDD(latlon1);
	return greatCircleDestPosition(orgPos.x(), orgPos.y(), bearing, distance);
}

QPointF CalcAir::newPoint(const QPointF& latlon1, double bearing, double distance)
{
	QPointF orgPos = latlon1;
	return greatCircleDestPosition(orgPos.x(), orgPos.y(), bearing, distance);
}

QPointF CalcAir::newPointRhumb(const QString& latlon1, double bearing, double distance)
{
	QPointF orgPos = toDD(latlon1);
	return rhumbDestPosition(orgPos.x(), orgPos.y(), bearing, distance);
}

void CalcAir::LatLonToCartesian(const QPointF p, Cartesian* cartesian)
{
	QPointF p1 = QPointF(deg2rad * (p.x()), deg2rad * p.y());
	double q0 = wonJum.x();
	double q1 = deg2rad * q0;

	cartesian->x = EarthRadius * cos(p1.x()) * cos(p1.y());
	cartesian->y = EarthRadius * cos(p1.x()) * sin(p1.y());

	double z = EarthRadius * sin(p1.x());

	double x = cartesian->x;
	double r1 = sqrt(z * z + x * x);
	double beta;

	beta = asin(z/r1);
	if (x < 0) {		// invisuable area
		beta = PI - beta;
	}
	double alpha = beta - q1;
	double z1 = r1 * sin(alpha);
	x = r1 * cos(alpha);

	cartesian->x = x;

	if (x < 0) { z1 = 0 - z1; }
	cartesian->z = z1;

	return;
}

void CalcAir::LatLonToCartesian(const QString& latlon, Cartesian* cartesian)
{
	QPointF p1 = toDD(latlon);
	LatLonToCartesian(p1, cartesian);

	return;
}

// Cartesian to LatLon
QPointF CalcAir::CartesianToLatLon(const Cartesian* cartesian)
{
	double x1, y1, z1;
	x1 = cartesian->x;
	y1 = cartesian->y;
	z1 = cartesian->z;

	double theta = asin(z1/EarthRadius);
	double phi = atan(y1/x1);
	if (x1 < 0) phi = phi + 180 * deg2rad;

	double lat = toDeg(theta);
	double lon = toDeg(phi);

	return QPointF(lat, lon);
}
