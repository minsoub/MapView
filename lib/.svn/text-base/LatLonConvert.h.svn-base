/*
 * LatLonConvert.h
 *
 *  Created on: 2012. 1. 19.
 *      Author: HIST002
 */

#ifndef LATLONCONVERT_H_
#define LATLONCONVERT_H_

#include <QtCore>
#include "CenterCoord.h"
#include "NorthGreenichPoint.h"
#include "CalcAir.h"
#include "MapConvertFunc.h"

class LatLonConvert {
public:
	CenterCoord cc;

	LatLonConvert();
	LatLonConvert(const QPointF& wonjum, const QRect& displaybound, double meterperpixel);
	LatLonConvert(const QPointF& wonjum, int screenwidth, int screenheight, double meterperpixel);
	LatLonConvert(const QString& wonjum, int screenwidth, int screenheight, double meterperpixel);
	LatLonConvert(double north, double greenich, int screenwidth, int screenheight, double meterperpixel);
	CalcAir* calAir() { return &ca; }
	void moveNorthPoint(double newpoint) {
		northGreenich.setNorth(newpoint);
		wonJum.setX(northGreenich.north());
		wonJum.setY(northGreenich.greenich());
		ca.setWonjum(wonJum);
	}
	void moveGreenichPoint(double newpoint) {
		northGreenich.setGreenich(newpoint);
		wonJum.setX(northGreenich.north());
		wonJum.setY(northGreenich.greenich());
		ca.setWonjum(wonJum);
	}
	double north() { return northGreenich.north(); }
	double greenich() { return northGreenich.greenich(); }
	QRect srcRect() { return screenRect; }
	int   srcWidth() { return screenRect.width(); }
	int   srcHeight() { return screenRect.height(); }
	double mpp() { return meterPerPixel; }
	Cartesian cartesian() { return xyz; }
	QPoint screenCenter() { return cc.center(); }
	void setScreenCenter(QPoint p) { cc.setCenter(p); }
	QPointF wonjum() { return wonJum; }

	void setWonJum(QPointF wonJum) {
		wonJum = wonJum;
		ca.setWonjum(wonJum);
	};
	void setWonJum(const QString& wonjum) { setWonJum(ca.toDD(wonjum)); }
	void setWonjumNorthGreenich(const QString& wonjumNorthGreenich) {
		setWonjumNorthGreenich(ca.toDD(wonjumNorthGreenich));
	};
	void setWonjumNorthGreenich(const QPointF& wonjumNorthGreenich) {
		northGreenich.setNorth(wonjumNorthGreenich.x());
		northGreenich.setGreenich(wonjumNorthGreenich.y());
		wonJum.setX(northGreenich.lat());
		wonJum.setY(northGreenich.lon());
		ca.setWonjum(wonJum);
	};
	void setScreenRect(const QRect& newBound) { screenRect = newBound; cc.setCenter(screenRect.center()); };
	void setScreenRect(int x, int y, int w, int h) { screenRect = QRect(x, y, w, h); cc.setCenter(screenRect.center()); };
	void setMeterPerPixel(double mpp) { meterPerPixel = mpp; }
	void setScreen00(const QPoint& xy);
	void setScreen00(int x, int y);

	QPoint latlonToScreen(const QString& latlon);
	QPoint latlonToScreen(const QPointF& decimal_latlon );
	QPointF latlonToScreen2(const QPointF& decimal_latlon );

	QPointF screenToDecimal(int screenX, int screenY);
	QPointF screenToDecimal(const QPoint& screenXY);

	QString screenToLatLon(int screenX,int screenY);
	QString screenToLatLon(const QPoint& screenXY);

	double pixelRadius() { return EarthRadius / meterPerPixel * PI/2; }
	double pixelToDegree(int pixel){return ca.toDeg(pixelToRadian(pixel));}
	double pixelToRadian(int pixel) { return ((meterPerPixel*pixel) / (EarthRadius)); }

	double pixelToMeter(int pixel){return meterPerPixel*pixel;}

	double meterToPixel(double meter){return meter/meterPerPixel;}
	double meterToRadian(double meter){return meter/EarthRadius;}
	double meterToDegree(double meter){return ca.toDeg(meterToRadian(meter));}

	double radianToMeter(double radian){return radian*EarthRadius;}
	double radianToPixel(double radian){return meterToPixel(radianToMeter(radian));}

	double degreeToMeter(double degree){return ca.toRad(degree)*EarthRadius;}
	double degreeToPixel(double degree){return meterToPixel(degreeToMeter(degree));}

	bool   isGu();
	double mppToDegree();
	double baseWJ(double x, double y);

	double leftGreenich();
	double rightGreenich();
	double topNorth();
	double bottomNorth();

	double distance(const QPoint& p1,const QPoint& p2); //cosdist
	double bearing(const QPoint& p1,const QPoint& p2);

	QString toString();

	// call from GenerateView
	QString toDMSHuman(const QPointF& latlonDecDeg) {
		return ca.toDMSHuman(latlonDecDeg);
	}

//	QString latToDMS(const QString& lat);
//	QString lonToDMS(const QString& lon);
//	QString LatDecimalToDMS(double latdecimal);
//	QString LonDecimalToDMS(double londecimal);
//	void LatLonToCartesian(const QPointF p);
//	void setCartesian(Cartesian *cartesian);
//	void setCenterCoord(CenterCoord *centerCoord);
//	void setScreenCenter(const QPoint& xy);
//	void setScreenRect(QRect screenRect) { this->screenRect = screenRect; }
//	void setNorthGreenich(NorthGreenichPoint *northGreenich) { this->northGreenich = northGreenich; }
//	bool  isIntersect(const QRect& screen, const QPoint& p1, const QPoint& p2);
//	QPointF CartesianToLatlon();
//	void setWonJumX(double north) { wonJum.setX(north); }
//	void setWonJumY(double greenich) { wonJum.setY(greenich); }
//	QString toDMSHuman(const QPointF& latlonDecDeg);
//

private:
	QRect screenRect;
	double meterPerPixel;
	QPointF wonJum;
	CalcAir ca;
	Cartesian xyz;
	NorthGreenichPoint northGreenich;

	double scrDaegak();
	double betweenDegree();
};

#endif /* LATLONCONVERT_H_ */
