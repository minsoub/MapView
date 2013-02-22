/*
 * AHoldLayerItem.cpp
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#include "AHoldLayerItem.h"


void AHoldLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (layerVisible() == false) return;

	QVector<CartesianXY> dataxy;
	LatLonBound bound;

	LatLonConvert* vp = ad->viewport();
	painter->setPen(_lp.getPen());
	painter->setBrush(_lp.getBrush());

	for (int i=0; i<_list.size(); i++) {
		ALayerId* layerid = _list[i];
		if (layerid->visible == false) continue;
		dataxy.clear();
		bound.initialize();
		for (int j=0; j<layerid->bndrylist.size(); j++) {
			ABndry* bndry = layerid->bndrylist[j];
			CartesianXY cxy;
			QPoint visualpoint = vp->latlonToScreen(bndry->latlon.p);
			cxy.bndry_via = bndry->bndry_via;
			cxy.xyz = vp->cartesian();
			cxy.mxy = visualpoint;
			bound.setPosition(visualpoint);
			cxy.lat = bndry->latlon.p.x();
			cxy.lon = bndry->latlon.p.y();
			if (bndry->bndry_via == QChar('C')) {
				cxy.arc_centerxy = visualpoint;
				cxy.arc_dist = bndry->arc_dist;
			}else if(bndry->bndry_via == QChar('L') || bndry->bndry_via == QChar('R')) {
				cxy.arc_centerxy = vp->latlonToScreen(bndry->arc_center_latlon.p);
				cxy.arc_dist = bndry->arc_dist;
				cxy.arc_bearing = bndry->arc_bearing;
				bound.setPosition(cxy.arc_centerxy);
			}
			dataxy.append(cxy);
		}
		if (bound.inRect(vp->srcRect())) {
			ad->drawPath2(painter, dataxy, layerid->drawtype);
		}
	}
}
