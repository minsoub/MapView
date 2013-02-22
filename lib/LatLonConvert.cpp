/*
 * LatLonConvert.cpp
 *
 *  Created on: 2012. 1. 19.
 *      Author: HIST002
 */
#include <iostream>
#include <math.h>
#include "LatLonConvert.h"


LatLonConvert::LatLonConvert() {
	// TODO Auto-generated constructor stub
	wonJum = QPointF(0.0, 0.0);
	screenRect = QRect(0, 0, 600, 600);
	meterPerPixel = EarthRadius / 600;
	cc.setCenter(screenRect.width()/2, screenRect.height()/2);
}

LatLonConvert::LatLonConvert(const QPointF& wonjum, const QRect& displaybound, double meterperpixel)
{
	wonJum = wonjum;
	screenRect = displaybound;
	meterPerPixel = meterperpixel;
	cc.setCenter(screenRect.center());
}

LatLonConvert::LatLonConvert(const QPointF& wonjum, int screenwidth, int screenheight, double meterperpixel)
{
	wonJum = wonjum;
	screenRect = QRect(0, 0, screenwidth, screenheight);
	meterPerPixel = meterperpixel;
	cc.setCenter(screenRect.center());
}

LatLonConvert::LatLonConvert(const QString& wonjum, int screenwidth, int screenheight, double meterperpixel)
{
	QPointF  p = ca.toDD(wonjum);
	LatLonConvert(p, screenwidth, screenheight, meterperpixel);
}

LatLonConvert::LatLonConvert(double north, double greenich, int screenwidth, int screenheight, double meterperpixel)
{
	northGreenich.setNorth(north);
	northGreenich.setGreenich(greenich);
	wonJum.setX(northGreenich.lat());
	wonJum.setY(northGreenich.lon());

	screenRect = QRect(0, 0, screenwidth, screenheight);
	meterPerPixel = meterperpixel;
	cc.setCenter(screenRect.center());
}

double LatLonConvert::baseWJ(double wj, double dy)
{
	int iwj = (int) (wj * 10);
	int idy = (int) (dy * 10);
	int iwj10 = (int) (iwj / idy * idy);
	return ((double)iwj10 / 10.0);
}

double LatLonConvert::mppToDegree()
{
	double degree = pixelToDegree(qMin(srcHeight(), srcHeight()));

	double dy = 10.0;
	if (degree < 1) {
		dy = 0.1;
	}else if(degree < 4) {
		dy = 0.5;
	}else if(degree < 8) {
		dy = 1.0;
	}else if(degree < 40) {
		dy = 5.0;
	}else {
		dy = 10.0;
	}
	return dy;
}

void LatLonConvert::setScreen00(const QPoint& xy)
{
	if (screenRect.contains(xy)) {
		cc.setCenter(xy);
	}
}

void LatLonConvert::setScreen00(int x, int y)
{
	if (screenRect.contains(x, y)) {
		cc.setCenter(x, y);
	}
}


QPoint  LatLonConvert::latlonToScreen(const QPointF& decimal_latlon )
{
	QPointF d = QPointF(decimal_latlon.x(), decimal_latlon.y() - wonJum.y());

	ca.LatLonToCartesian(d, &xyz);

	double pixelUnit = 1/meterPerPixel;

    //  vp distence
	double r1  = sqrt(xyz.z * xyz.z + xyz.y * xyz.y);

	//편평화   cicle face length  2*pi*R
	double r2 = EarthRadius*asin(r1/EarthRadius);
	double bojung_r =  1;
	if( r1 != 0 ) bojung_r = r2/r1;
	//else bojung_r = r2/r1;
	double y = xyz.y * pixelUnit * bojung_r;
	double z = xyz.z * pixelUnit * bojung_r;
	int   y1 = cc.toPhysicX((int)y);
	int   z1 = cc.toPhysicY((int)z);

	//std::cout << "latlonToScreen y1 : " << y1 << ", z1 : " << z1 << "\n";

	return QPoint(y1,z1);
}

QPointF  LatLonConvert::latlonToScreen2(const QPointF& decimal_latlon )
{
	QPointF d = QPointF(decimal_latlon.x(), decimal_latlon.y() - wonJum.y());

	ca.LatLonToCartesian(d, &xyz);

	double pixelUnit = 1/meterPerPixel;

    //  vp distence
	double r1  = sqrt(xyz.z * xyz.z + xyz.y * xyz.y);

	//편평화   cicle face length  2*pi*R
	double r2 = EarthRadius*asin(r1/EarthRadius);
	double bojung_r =  1;
	if( r1 != 0 ) bojung_r = r2/r1;
	//else bojung_r = r2/r1;
	double y = xyz.y * pixelUnit * bojung_r;
	double z = xyz.z * pixelUnit * bojung_r;
	double   y1 = cc.toPhysicX(y);
	double   z1 = cc.toPhysicY(z);

	//std::cout << "latlonToScreen y1 : " << y1 << ", z1 : " << z1 << "\n";

	return QPointF(y1,z1);
}

QPoint LatLonConvert::latlonToScreen(const QString& latlon)
{
	QPointF p = ca.toDD(latlon);
	return latlonToScreen(p);
}

QPointF LatLonConvert::screenToDecimal(int screenX, int screenY)
{
	// 원점 보정
	double y2 = cc.toLogicX(screenX);
	double z2 = cc.toLogicY(screenY);
	y2 = y2 * meterPerPixel;
	z2 = z2 * meterPerPixel;

	// 편평화 역함수 Screen Size
	double r2 = sqrt(y2 * y2 + z2 * z2);
	double theta = (r2 / EarthRadius);
	double r1 = sin(theta) * EarthRadius;

	double y1 = y2 * (r1/r2);     // earth cover pointer
	double z1 = z2 * (r1/r2);
	double x1 = EarthRadius * cos(theta);

	// 위도보정 : rotate vp to 0 원점 dx
	double Rxz = sqrt(x1*x1 + z1*z1);
	double alpha = asin(z1 / Rxz);
	double beta = deg2rad * wonJum.x() + alpha;

	// cartesian struct
	xyz.z = Rxz * sin(beta);
	xyz.x = Rxz * cos(beta);
	xyz.y = y1;

	QPointF p = ca.CartesianToLatLon(&xyz);

	return QPointF(p.x(), p.y() + wonJum.y());

}
QPointF LatLonConvert::screenToDecimal(const QPoint& screenXY)
{
	return screenToDecimal(screenXY.x(), screenXY.y());
}

QString LatLonConvert::screenToLatLon(const QPoint& screenXY)
{
	QPointF p = screenToDecimal(screenXY);
	return ca.toDMS(p);
}

QString LatLonConvert::screenToLatLon(int screenX,int screenY)
{
	return screenToLatLon(QPoint(screenX,screenY));
}

bool LatLonConvert::isGu()
{
	QPoint n = latlonToScreen(QPointF(+85.0, wonJum.y()));
	QPoint s = latlonToScreen(QPointF(-85.0, wonJum.y()));

	if (screenRect.contains(n) || screenRect.contains(s)) return true;
	if (scrDaegak() > pixelRadius()) return true;

	return false;
}

double LatLonConvert::scrDaegak()
{
	return sqrt((srcHeight()/2) * (srcHeight()/2) + (srcWidth()/2) * (srcWidth()/2));
}

double LatLonConvert::topNorth()
{
	if (isGu()) {
		return northGreenich.northDegree(90);
	}else {
		double d = pixelToDegree((int)scrDaegak());
		double np = northGreenich.northDegree(d);

		double dy = mppToDegree();
		return baseWJ(np, dy) + dy;
	}
}
double LatLonConvert::bottomNorth()
{
	if (isGu()) {
		return northGreenich.southDegree(90);
	}else {
		double d = pixelToDegree((int)scrDaegak());
		double np = northGreenich.southDegree(d);
		double dy = mppToDegree();
		return baseWJ(np, dy) - dy;
	}
}
double LatLonConvert::leftGreenich()
{
	if (isGu()) {
		return northGreenich.westDegree(180);
	}else {

		double d = pixelToDegree((int)scrDaegak());
		NorthGreenichPoint p1, p2;
		p1.set(north(), greenich());
		p1.moveNorth(d);
		p1.moveWest(d);
		p2.set(north(), greenich());
		p2.moveSouth(d);
		p2.moveWest(d);

		double gp = qMin(p1.greenich(), p2.greenich());
		gp = northGreenich.westDegree(d);

		double dy = mppToDegree();
		double min = baseWJ(gp, dy) - dy;
		return min;
	}
}
double LatLonConvert::rightGreenich()
{
	if (isGu()) {
		return northGreenich.eastDegree(180);
	}else {
		double d = pixelToDegree((int)scrDaegak());
		NorthGreenichPoint p1, p2;
		p1.set(north(), greenich());
		p1.moveEast(d);
		p1.moveNorth(d);
		p2.set(north(), greenich());
		p2.moveEast(d);
		p2.moveSouth(d);
		double gp = qMax(p1.greenich(), p2.greenich());
		gp = northGreenich.eastDegree(d);

		double dy = mppToDegree();
		double max =  baseWJ(gp, dy) + dy + dy;
		return max;
	}
}
//screen p1과 p2사이의 거리
double LatLonConvert::distance(const QPoint& p1,const QPoint& p2)
{
	QPointF pf1 = screenToDecimal(p1.x(),p1.y());
	QPointF pf2 = screenToDecimal(p2.x(),p2.y());
	double dist = ca.cl_distance(pf1,pf2);
	return dist;
}

//screen p1과 p2사이의  bearing
double LatLonConvert::bearing(const QPoint& p1,const QPoint& p2)
{
	QPointF pf1 = screenToDecimal(p1.x(),p1.y());
	QPointF pf2 = screenToDecimal(p2.x(),p2.y());
	double bearing = ca.bearing(pf1,pf2);
	return bearing;
}

QString LatLonConvert::toString()
{
	QString s = QString("screenRect(%1,%2,%3,%4)")
			.arg(screenRect.left())
			.arg(screenRect.top())
			.arg(screenRect.right())
			.arg(screenRect.bottom());
	QString w = QString("latlon WonJum(%1,%2)(%3)")
				.arg(wonJum.x(),6,'f',4).arg(wonJum.y(),6,'f',4)
				.arg(ca.toDMS(wonJum));
	QString sw = QString("screen WonJum(%1,%2)")
				.arg(cc.center_x())
				.arg(cc.center_y());
	QString c = QString("Cartesian(%1,%2,%3)")
				.arg(xyz.x,6,'f',4)
				.arg(xyz.y,6,'f',4)
				.arg(xyz.z,6,'f',4);
	QString mpp = QString("mpp(%1)").arg(meterPerPixel);
	QString m = QString("minNorth:%1 maxNorth:%2 minGreenich:%3 maxGreenich:%4")
				.arg(topNorth())
				.arg(bottomNorth())
				.arg(leftGreenich())
				.arg(rightGreenich());
	return (QString("viewport info:")+s+"\n"+ w + "\n" + sw+"\n" + c + "\n" + m+"\n"+mpp);
}














//void LatLonConvert::setCartesian(Cartesian *cartesian)
//{
//	this->cartesian = cartesian;
//}
//// MapCanvas 클래스로 부터 meterPerPixel 데이터를 받아온다.
//void LatLonConvert::setMeterPerPixel(double meterPerPixel)
//{
//	this->meterPerPixel = meterPerPixel;
//}
//
//void LatLonConvert::setCenterCoord(CenterCoord *centerCoord)
//{
//	this->centerCoord = centerCoord;
//}
//
//void LatLonConvert::setScreenCenter(const QPoint& xy)
//{
//	if (screenRect.contains(xy)) {
//		centerCoord->setCenter(xy);
//	}
//}
//
//// decimal latlon p -> x,y,z
//// p 37.2323,127.1212  ==> 0.2323, 0.1212
//// p1
//// WGS84->xyz(cartesian)
//void  LatLonConvert::LatLonToCartesian(const QPointF p)
//{
//	QPointF p1 = QPointF( deg2rad * p.x(), deg2rad * p.y() );
//	double q0 = wonJum.x();
//	double q1 = deg2rad * q0;
//
//	cartesian->x = EarthRadius * cos(p1.x()) * cos(p1.y());
//	cartesian->y = EarthRadius * cos(p1.x()) * sin(p1.y());
//
//	double z = EarthRadius * sin(p1.x());
//
//	double x = cartesian->x;
//	double r1 = sqrt(z * z + x * x );
//	double beta;
//
//	beta = asin(z/r1);
//	if( x < 0 ) {   // invusable area
//	    beta = PI - beta;
//	}
//	double alpha = beta - q1;
//	double z1 = r1 * sin(alpha);
//	x = r1 * cos(alpha);
//
//	cartesian->x = x;
//
//	if( x < 0 ) {  z1 = 0 - z1; }
//	cartesian->z = z1;
//
//	//std::cout << "cartesian z : " << cartesian->z << "\n";
//
//	return;
//}
//
//
//bool  LatLonConvert::isIntersect(const QRect& screen, const QPoint& p1, const QPoint& p2)
//{
//	long x1, y1, x2, y2;
//	long x3, y3, x4, y4;
//	long x,  y;
//	int check;
//
//	x3 = p1.x();
//	y3 = p1.y();
//	x4 = p2.x();
//	y4 = p2.y();
//
//	x1 = screen.x();
//	y1 = screen.y();
//	x2 = screen.width();
//	y2 = 0;
//	check = GuHanLibs::lines_intersect(x1, y1, x2, y2, x3, y3, x4, y4, &x, &y);
//	if (check == 1) return true;
//
//	x1 = screen.width();
//	y1 = 0;
//	x2 = x1;
//	y2 = screen.height();
//	check = GuHanLibs::lines_intersect(x1, y1, x2, y2, x3, y3, x4, y4, &x, &y);
//	if (check == 1) return true;
//
//	x1 = screen.width();
//	y1 = screen.height();
//	x2 = 0;
//	y2 = screen.height();
//	check = GuHanLibs::lines_intersect(x1, y1, x2, y2, x3, y3, x4, y4, &x, &y);
//	if (check == 1) return true;
//
//	x1 = 0;
//	y1 = screen.height();
//	x2 = 0;
//	y2 = 0;
//	check = GuHanLibs::lines_intersect(x1, y1, x2, y2, x3, y3, x4, y4, &x, &y);
//	if (check == 1) return true;
//
//	return false;
//}
//
//
//
//QPointF LatLonConvert::CartesianToLatlon()
//{
//	double x1, y1, z1;
//	x1 = cartesian->x;
//	y1 = cartesian->y;
//	z1 = cartesian->z;
//
//	double theta = asin(z1/EarthRadius);
//	double phi   = atan(y1/x1);
//	if (x1 < 0) phi = phi + 180 * deg2rad;
//
//	double lat = theta * rad2deg;
//	double lon = phi   * rad2deg;
//	return QPointF(lat, lon);
//}
//
//QString LatLonConvert::latToDMS(const QString& lat)
//{
//	QString lat_deg, lat_min, lat_sec1, lat_sec2;
//	QChar signLat = lat[0];
//
//	lat_deg = lat.mid(1, 2);
//	lat_min = lat.mid(3, 2);
//	lat_sec1 = lat.mid(5, 2);
//	lat_sec2 = lat.mid(7, 2);
//
//	return QString("%1%2:%3:%4.%5").arg(signLat).arg(lat_deg).arg(lat_min).arg(lat_sec1).arg(lat_sec2);
//}
//QString LatLonConvert::lonToDMS(const QString& lon)
//{
//	QString lon_deg, lon_min, lon_sec1, lon_sec2;
//	QChar signLon = lon[0];
//
//	lon_deg  = lon.mid(1, 4);
//	lon_min  = lon.mid(4, 2);
//	lon_sec1 = lon.mid(6, 2);
//	lon_sec2 = lon.mid(8, 2);
//
//	return QString("%1%2:%3:%4.%5").arg(signLon).arg(lon_deg).arg(lon_min).arg(lon_sec1).arg(lon_sec2);
//}
//double LatLonConvert::pixelToRadian(int pixel)
//{
//	return (meterPerPixel*pixel)/(EarthRadius);
//}
//
//
//
//
//double LatLonConvert::pixelRadius()
//{
//	return EarthRadius / meterPerPixel * PI / 2;
//}
//
//double LatLonConvert::north()
//{
//	return northGreenich->north();
//}
//double LatLonConvert::greenich()
//{
//	return northGreenich->greenich();
//}
//
//
//
//QString LatLonConvert::toDMSHuman(const QPointF& latlonDecDeg)
//{
//	QString lat = LatDecimalToDMS(latlonDecDeg.x());
//	QString lon = LonDecimalToDMS(latlonDecDeg.y());
//	QString lat1 = latToDMS(lat);
//	QString lon1 = lonToDMS(lon);
//
//	return QString("%1,%2").arg(lat1).arg(lon1);
//}
//
//QString LatLonConvert::LatDecimalToDMS(double latdecimal)
//{
//	double d = fabs(latdecimal);
//	int deg = (int)floor(d);
//	int min = (int)floor((d - deg) * 60);
//	int sec = (int)floor((((d-deg)*60-min)*100/60)*3600);
//	QChar sign = QChar('N');
//	if (latdecimal < 0) {
//		sign = QChar('S');
//	}
//	return QString("%1%2%3%4").arg(sign)
//			.arg(deg, 2, 'f', 0, QChar('0'))
//			.arg(min, 2, 'f', 0, '0')
//			.arg(sec, 4, 'f', 0, '0');
//}
//QString LatLonConvert::LonDecimalToDMS(double londecimal)
//{
//	double d = fabs(londecimal);
//	int deg = (int)floor(d);
//	int min = (int)floor((d - deg) * 60);
//	int sec = (int)floor((((d-deg)*60-min)*100/60)*3600);
//	QChar sign = QChar('E');
//	if (londecimal < 0) {
//		sign = QChar('W');
//	}
//	return QString("%1%2%3%4").arg(sign)
//			.arg(deg, 3, 'f', 0, QChar('0'))
//			.arg(min, 2, 'f', 0, '0')
//			.arg(sec, 4, 'f', 0, '0');
//}


