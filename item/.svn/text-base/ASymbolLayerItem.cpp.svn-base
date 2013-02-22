/*
 * ASymbolLayerItem.cpp
 *
 *  Created on: 2012. 2. 21.
 *      Author: HIST002
 */

#include "ASymbolLayerItem.h"

void ASymbolLayerItem::draw(QPainter* painter)
{
	//qDebug() << "layervisible() " << layerVisible();
	if (layerVisible() == false) return;

	QString imageFile = QString("%1/%2").arg(_symboldir).arg(_lp.getSymbol());
	if (!QFile::exists(imageFile)) {
		logprint(QString("%1 imagefile name: %1 not found").arg(shortName()).arg(imageFile));
		return;
	}else {
		//qDebug() << QString("%1 imagefile found").arg(imageFile);
		//logprint(QString("%1 imagefile found").arg(imageFile));
	}
	QVector<CartesianXY> dataxy;
	LatLonBound bound;

	LatLonConvert* vp = ad->viewport();

	QPixmap pixmap;
	pixmap.load(imageFile, "XPM");
	bound.initialize();

	//qDebug() << "list size : " << _list.size();
	for (int i=0; i<_list.size(); i++) {
		ALayerId* layerid = _list[i];
//		if (layerid->id == "RKJY")
//			qDebug() << "layerid : " << layerid->id << ", layerid->visible : " << layerid->visible;

		if (layerid->visible == false) continue;
		for (int j=0; j<layerid->bndrylist.size(); j++) {
			ABndry* bndry = layerid->bndrylist[j];
			QPoint p = vp->latlonToScreen(bndry->latlon.p);
			bound.setPosition(p);
			QRect pixmapRect = pixmap.rect();
			QRect painterRect = QRect(p.x() - pixmapRect.width()/2, p.y() - pixmapRect.height()/2,
							pixmap.width(), pixmap.height());
			bound.setRect(painterRect);
			if (bound.inRect(vp->srcRect())) {
				painter->drawPixmap(painterRect, pixmap);
			}
		}
	}
}
