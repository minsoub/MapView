/*
 * APointLayerItem.cpp
 *
 *  Created on: 2012. 2. 21.
 *      Author: HIST002
 */

#include "APointLayerItem.h"

void APointLayerItem::print(QTextStream& out, AMapconf& mapconf)
{
	QString name = shortName().toUpper();
	QString s;
	out << QString("LAYER:%1:%2").arg(name).arg(mapconf.dftvalue(name)) << "\n";
	for (int i=0; i<_list.count(); i++) {
		ALayerId* layerid = _list[i];
		if (layerid->bndrylist.count() < 1) continue;
		s = QString("ID:%1:1:S").arg(layerid->id);
		out << s << "\n";
		ABndry* bndry = layerid->bndrylist[0];
		s = QString("S:%1%2").arg(bndry->latlon.lat).arg(bndry->latlon.lon);
		out << s << "\n";
	}
	out << QString("ENDLAYER") << "\n";
	logprint(QString("write %1 done").arg(name));
}

bool APointLayerItem::query(QSqlQuery* q, const QString& sql)
{
	int count = 0;
	ALayerId* layerid;
	QSqlError sqlerror;

	q->exec(sql);

	sqlerror = q->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		logprint(QString("APointLayerItem query error :%1 (%2)").arg(sqlerror.text()).arg(sql));
		return false;
	}

#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg(shortName()));
#endif
	_list.clear();
	QString prev = QString("");
	while(q->next()) {
		QString id = q->value(0).toString();
		QString bndry_idx = q->value(1).toString();
		QString bndry_via = q->value(2).toString();
		QString lat = q->value(3).toString();
		QString lon = q->value(4).toString();

		QString arc_center_lat = q->value(5).toString();
		QString arc_center_lon = q->value(6).toString();
		QString arc_bearing = q->value(7).toString();
		QString arc_dist = q->value(8).toString();
		QString multi_cd = q->value(9).toString();
		if (id != prev) {
			layerid = new ALayerId;
			layerid->id = id;
			_list.append(layerid);
		}
		if (layerid != NULL) {
			ABndry* bndry = new ABndry;
			bndry->bndry_idx = bndry_idx.toInt();
			bndry->bndry_via = bndry_via[0];
			bndry->latlon.lat = lat;
			bndry->latlon.lon = lon;
			bndry->latlon.p = _ca.toDD(QString("%1%2").arg(lat).arg(lon));
			bndry->arc_center_latlon.lat = arc_center_lat;
			bndry->arc_center_latlon.lon = arc_center_lon;
			bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(arc_center_lat).arg(arc_center_lon));
			bndry->arc_bearing = arc_bearing.toDouble();
			bndry->arc_dist = arc_dist.toDouble();
			bndry->multi_cd = multi_cd;

			layerid->bndrylist.append(bndry);
		}
		prev = id;
		count++;
	}

	logprint(QString("query %1 done %2 id read").arg(shortName()).arg(count));

	return true;
}

void APointLayerItem::read(QTextStream& in, int& lineNo)
{
	QStringList list;
	QString line;
	while(!in.atEnd()) {
		line = in.readLine();
		lineNo++;
		if (line == "ENDLAYER") break;
		list = line.split(":");
		if (list[0] == "ID") {
			ALayerId* layerid = new ALayerId;
			_list.append(layerid);
			layerid->id = list[1];
			layerid->drawtype = list[3][0];
			layerid->visible = true;

			int cnt = (list[2]).toInt();
			ABndry* bndry = new ABndry;
			for (int i=0; i<cnt; i++) {
				line = in.readLine();
				lineNo++;
				list = line.split(":");
				QChar ch = list[0][0];
				bndry->latlon.lat = LLU::lat(list[1]);
				bndry->latlon.lon = LLU::lon(list[1]);
				bndry->latlon.p = _ca.toDD(list[1]);
				bndry->bndry_via = ch;
				layerid->bndrylist.append(bndry);
			}
		}
	}
}

void APointLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (layerVisible() == false) return;

	LatLonBound bound;
	LatLonConvert* vp = ad->viewport();

	for (int i=0; i<_list.size(); i++) {
		ALayerId* layerid = _list[i];
		if (layerid->visible == false) continue;
		for (int j=0; j<layerid->bndrylist.size(); j++) {
			ABndry* bndry = layerid->bndrylist[j];
			QPoint p = vp->latlonToScreen(bndry->latlon.p);
			bound.setPosition(p);
			QRect painterRect = QRect(p.x() - 5, p.y() - 5, 10, 10);
			bound.setRect(painterRect);
			if (bound.inRect(vp->srcRect())) {
				painter->drawRect(painterRect);
			}
		}
	}
}

void APointLayerItem::updateInfo()
{
	prepareGeometryChange();
}
QRectF APointLayerItem::boundingRect() const
{
	qreal adjust = 0.5;
	LatLonConvert* vp = ad->viewport();
	QRectF rect = QRectF(adjust, adjust, vp->srcRect().width() * 1.0, vp->srcRect().height() * 1.0);

	return rect;
}
