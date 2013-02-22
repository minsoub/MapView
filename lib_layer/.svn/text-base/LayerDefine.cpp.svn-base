/*
 * LayerDefine.cpp
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */

#include "LayerDefine.h"

LayerDefine::LayerDefine() {
	// TODO Auto-generated constructor stub
	add( Layer_Coast, "Coast" , "Coast",GroupLayer_None); //-- 0
	add( Layer_Fir, "Fir" , "Fir",GroupLayer_None); //-- 1
	add( Layer_Kadiz, "Kadiz" , "Kadiz",GroupLayer_None); //-- 2
	add( Layer_Sector, "Sector" , "Sector",GroupLayer_None); //-- 3
	add( Layer_Tca, "Tca" , "Tca",GroupLayer_None); //-- 4
	add( Layer_Ra, "Ra" , "Ra",GroupLayer_None); //-- 5
	add( Layer_Da, "Da" , "Da",GroupLayer_None); //-- 6
	add( Layer_Pa, "Pa" , "Pa",GroupLayer_None); //-- 7
	add( Layer_Aa, "Aa" , "Aa",GroupLayer_None); //-- 8
	add( Layer_Moa, "Moa" , "Moa",GroupLayer_None); //-- 9
	add( Layer_Msaw, "Msaw" , "Msaw",GroupLayer_None); //-- 10
	add( Layer_Cata, "Cata" , "Cata",GroupLayer_None); //-- 11
    add( Layer_Ad_Civil, "Ad_Civil" , "Ad_Civil",GroupLayer_None); //-- 12
    add( Layer_Ad_Mil, "Ad_Mil" , "Ad_Mil",GroupLayer_None); //-- 13
    add( Layer_Ad_Joint, "Ad_Joint" , "Ad_Joint",GroupLayer_None); //-- 14
	add( Layer_Runway, "Runway" , "Runway",GroupLayer_None); //-- 15
    add( Layer_Rep_Fix, "Rep_Fix" , "Rep_Fix",GroupLayer_None); //-- 16
    add( Layer_Fix, "Fix" , "Fix",GroupLayer_None); //-- 17
    add( Layer_T_Fix, "T_Fix" , "T_Fix",GroupLayer_None); //-- 18
    add( Layer_Vortac, "Vortac" , "Vortac",GroupLayer_None); //-- 19
    add( Layer_Vordme, "Vordme" , "Vordme",GroupLayer_None); //-- 20
    add( Layer_Ndb, "Ndb" , "Ndb",GroupLayer_None); //-- 21
	add( Layer_Route, "Route" , "Route",GroupLayer_None); //-- 22
    add( Layer_Hold, "Hold" , "Hold",GroupLayer_None); //-- 23
    add( Layer_Sensor, "Sensor" , "Sensor",GroupLayer_None); //-- 24
    add( Layer_Sid, "Sid" , "Sid",GroupLayer_None); //-- 25
    add( Layer_Star, "Star" , "Star",GroupLayer_None); //-- 26
    add( Layer_Apch, "Apch" , "Apch",GroupLayer_None); //-- 27
    add( Layer_Airspace, "Airspace" , "Airspace", GroupLayer_None); //-- 28
    add( Layer_Vfr_Rp, "Vfr_Rp" , "Vfr_Rp",GroupLayer_None); //-- 29
    add( Layer_Obstacles, "Obstacles" , "Obstacles",GroupLayer_None); //-- 30
    add( Layer_Vfr_Cp, "Vfr_Cp" , "Vfr_Cp",GroupLayer_None); //-- 31
    add( Layer_Vfr_Route, "Vfr_Route" , "Vfr_Route",GroupLayer_None); //-- 32
    add( Layer_Mva, "Mva" , "Mva",GroupLayer_None); //-- 33
    add( Layer_User, "User" , "User",GroupLayer_None); //-- 34
}

LayerDefine::~LayerDefine() {
	// TODO Auto-generated destructor stub
	list.clear();
}


int LayerDefine::layerNo(LayerType t)
{
	for (int i=0; i<list.count(); i++) {
		LayerItem* item = list[i];
		if (item->layerType == t) {
			return i;
		}
	}
	return -1;
}
int LayerDefine::layerType(int no)
{
	if (no >= 0 && no < list.count()) {
		LayerItem *item = list[no];
		return item->layerType;
	}
	return Layer_Unknown;
}
int LayerDefine::layerType(const QString& shortname)
{
	for (int i=0; i<list.count(); i++) {
		LayerItem* item = list[i];
		if (shortname == item->shortName) {
			return item->layerType;
		}
	}
	return Layer_Unknown;
}
QString LayerDefine::shortName(int no) const
{
	if (no >= 0 && no < list.count()) {
		LayerItem* item = list[no];
		return item->shortName;
	}
	return QString("");
}
QString LayerDefine::shortName(LayerType t) const
{
	for (int i=0; i<list.count(); i++) {
		LayerItem* item = list[i];
		if (item->layerType == t) {
			return item->shortName;
		}
	}
	return QString("");
}
QString LayerDefine::fullName(int no) const
{
	if (no >= 0 && no < list.count()) {
		LayerItem* item = list[no];
		return item->fullName;
	}
	return QString("");
}
QString LayerDefine::fullName(LayerType t) const
{
	for (int i=0; i<list.count(); i++) {
		LayerItem* item = list[i];
		if (item->layerType == t) {
			return item->fullName;
		}
	}
	return QString("");
}
int LayerDefine::count()
{
	return list.count();
}
//QVector<LayerType>* LayerDefine::getGroupMembers(int t)
//{
//
//}

void LayerDefine::add(LayerType t, const QString& sn, const QString& fn, GroupLayerType gt)
{
	LayerItem* item = new LayerItem;
	item->layerType = t;
	item->shortName = sn;
	item->fullName = fn;
	item->groupLayer = gt;
	list.append(item);
}
