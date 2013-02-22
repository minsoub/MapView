/*
 * GeoData.h
 *
 *  Created on: 2012. 1. 16.
 *      Author: HIST002
 */

#ifndef GEODATA_H_
#define GEODATA_H_


// this file contains some contstants related geo
const double PI = 3.14159265;
const double FOURTHPI = (PI / 4);
const double deg2rad  = (PI / 180);
const double rad2deg  = (180.0 / PI);
const double EarthRadius = 6371000;  // meter earth's mean radius
const double EarthRadius_div_90 = (EarthRadius/90);

typedef struct tagGartesian {
	double x;
	double y;
	double z;
}Cartesian;

//typedef struct tagCoordinate {
//	QString lat;
//	QString lon;
//	QPointF p;
//	QPointF screen_p;    // convert p to screen point
//	int     bndry_idx;
//	QChar   bndry_via;
//}Coordinate;
//
//typedef struct QVector<Coordinate *> CoordList;
//
//typedef struct tagLayerId2 {
//	QString   id;
//	QChar     drawType;
//	CoordList coordList;
//}Layer;



typedef struct tagCartesianXY {
	Cartesian xyz;
	double lat, lon;
	QChar bndry_via;
	QPoint mxy;
	QPoint arc_centerxy;
	double len;
	double arc_dist;
	double arc_bearing;
}CartesianXY;

//typedef struct QVector<Layer *> LayerList;
#endif /* GEODATA_H_ */
