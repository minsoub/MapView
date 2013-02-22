/*
 * CalcAir.h
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */

#ifndef CALCAIR_H_
#define CALCAIR_H_

#include <QPointF>
#include "../GeoData.h"

class CalcAir {
public:
	//CalcAir();

	double toRad(double x) { return x*deg2rad; }
	double toDeg(double x) { return x*rad2deg; }
	QPointF toDD(const QString& latlon);		// N35001234E125001234 -> decimal degree
	QPointF toRadian(const QString& latlon);	// N35001234E125001234 -> radian
	QPointF toRadian(const QPointF& ddLatLon);
	QString toDMS(const QString& latlon);
	QString toDMS(const QPointF& latlonDecDeg);
	QString toDMSHuman(const QPointF& latlonDecDeg);
	QString toDMSHuman(const QString& latlon);
	double gc_distance(const QString& latlon1, const QString& latlon2);
	double cl_distance(const QString& latlon1, const QString& latlon2);
	double cl_distance(const QPointF& ddp1, const QPointF& ddp2);
	QPointF mid(const QString& latlon1, const QString& latlon2);
	double bearing(double lat1, double lon1, double lat2, double lon2);
	double bearing(const QString& latlon1, const QString& latlon2);
	double bearing(const QPointF& p1, const QPointF& p2);
	double final_bearing(double lat1, double lon1, double lat2, double lon2);
	double final_bearing(const QString& latlon1, const QString& latlon2);
	QPointF newPoint(const QString& latlon1, double bearing, double distance);
	QPointF newPoint(const QPointF& latlon1, double bearing, double distance);
	QPointF newPointRhumb(const QString& latlon1, double bearing, double distance);

	double rhumbDistance(double startLat, double startLon, double endLat, double endLon);
	double rhumbDistance(const QString& latlon1, const QString& latlon2);
	double rhumbBearing(const QString& latlon1, const QString& latlon2);
	QPointF rhumbNewPoint(const QString& latlon1, double bearing, double distance);

	void setWonjum(const QPointF& p) { wonJum = p; }

	void LatLonToCartesian(const QPointF p, Cartesian* cartesian);
	void LatLonToCartesian(const QString& latlon, Cartesian* cartesian);
	QPointF CartesianToLatLon(const Cartesian* cartesian);
	QString LatDecimalToDMS(double latdecimal);
	QString LonDecimalToDMS(double londecimal);
private:
	QPointF wonJum;
	double toBearing(double x);
	double toFinalBearing(double x);
	double strToDD(const QString& dms);
	double toDD(double degree, double min, double sec);
	QString latToDMS(const QString& lat);
	QString lonToDMS(const QString& lon);


	// lat, lon is decimal degree
	double greatCircleDistance(double lat1, double lon1, double lat2, double lon2);
	double cosineLawDistance(double lat1, double lon1, double lat2, double lon2);
	QPointF midPoint(double lat1, double lon1, double lat2, double lon2);
	QPointF greatCircleDestPosition(double startLat, double startLon, double bearing, double distance);
	double bearingRhumb(double lat1, double lon1, double lat2, double lon2);
	QPointF rhumbDestPosition(double startLat, double startLon, double bearing, double distance);
};

#endif /* CALCAIR_H_ */
