/*
 * MapDefine.h
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */

#ifndef MAPDEFINE_H_
#define MAPDEFINE_H_

#include <QPointF>
#include <QVector>
#include <QString>

enum LayerType {
	Layer_Unknown = -1,
	Layer_Coast = 0, Layer_Fir, Layer_Kadiz,
	Layer_Sector, Layer_Tca,
	Layer_Ra, Layer_Da, Layer_Pa, Layer_Aa, Layer_Moa,
	Layer_Msaw, Layer_Cata,
	Layer_Ad_Civil, Layer_Ad_Mil, Layer_Ad_Joint,
	Layer_Runway,
	Layer_Rep_Fix, Layer_Fix, Layer_T_Fix,
	Layer_Vortac, Layer_Vordme, Layer_Ndb,
	Layer_Route, Layer_Hold, Layer_Sensor,
	Layer_Sid, Layer_Star, Layer_Apch, Layer_Airspace,
	Layer_Vfr_Rp, Layer_Obstacles, Layer_Vfr_Cp,
	Layer_Vfr_Route, Layer_Mva,
	Layer_User
};

enum GroupLayerType {
	GroupLayer_None, GroupLayer_Airport = 77,
	GroupLayer_Waypoint=88, GroupLayer_Navaids = 99
};

enum {MaxLayerCount = 40};
enum {TuMyungDo = 63};
enum LayerVisible {
	Unvisible = 0,
	PartiallyVisible = 1,
	Visible = 2
};

typedef struct tagLayerItem {
	int layerType;
	QString fullName;
	QString shortName;
	GroupLayerType groupLayer;
} LayerItem;

typedef struct tagLatLon {
	QString lat;
	QString lon;
} ALatLon;
typedef struct tagAPoint {
	QString lat;
	QString lon;
	QPointF p;
} APoint;

typedef struct tagMsb {
	QPointF p1,p2; //lefttop, rightbottom
	ALatLon latlon1,latlon2;  //lefttop,rightbottom
} AMsb;

//mapconf
typedef struct tagMapconf {
	QString line_type;
	QString line_width;
	QString line_color;
	QString fill_pattern;
	QString fill_color;
	QString font;
	QString font_size;
	QString font_color;
	QString symbol;
	QString layer_id;
	QString scope;
	QString disp;
} AMapConf;

//mapdefault
typedef struct tagMapDefault{
	QString bg_color;
	QString rng;
	QString mpp;
	QString grid_color;
	QString cps_color;
	QString log_yn;
	QString log_file;
	QString center_lat;
	QString center_lon;
	QString vw_cps;
	QString vw_latlon;
} AMapDefault;

typedef struct tagMapLayer {
	QString layer_id;
	QString disp;
} AMapLayer;

typedef struct tagLayerAttr {
	QString linetype;
	QString linewidth;
	QString linecolor;
	QString fillpattern;
	QString fillcolor;
	QString fontname;
	QString fontsize;
	QString fontcolor;
	QString symbol;
}ALayerAttr;

//
//Bndry : layerid의 점들
//
typedef struct tagBndry {
	int bndry_idx;
	QChar bndry_via;
	APoint latlon;
	APoint arc_center_latlon;
	qreal arc_dist;
	qreal arc_bearing;
	QString multi_cd;
} ABndry;
typedef QVector<ABndry*> ABndryList;

//
//LayerId 구조체
//Layer중 1개를 의미한다
//이것들을 클래스로 만들것인가?
//
typedef struct tagLayerId {
	QString id;
	QChar drawtype;
	AMsb msb;
	QString multi_cd;
	bool visible;
	ABndryList bndrylist;
} ALayerId;

typedef struct QVector<ALayerId*> ALayerIdList;

typedef struct tagPointLayerId {
	QString id;
	QChar drawtype;
	AMsb msb;
	QString multi_cd;
	bool visible;
	APoint point;
}APointLayerId;

typedef struct QVector<APointLayerId*> APointLayerIdList;

//auserlayer 구성품
typedef struct tagUsermapbndry{
	int bndry_idx;
	QChar bndry_via;
	APoint latlon;
	APoint arc_center_latlon;
	qreal arc_bearing;
	qreal arc_dist;
} AUserbndry;
typedef struct QVector<AUserbndry*> AUserbndryList;

typedef struct tagUserLayer {
	QString id;
	QString attr;
	QChar drawtype;
	AMsb msb;
	bool visible;
	bool idtextvisible;
	AUserbndryList bndrylist;
} AUserLayerId;



#endif /* MAPDEFINE_H_ */
