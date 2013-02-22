/*
 * AreaLayerItem.cpp
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */

#include "AreaLayerItem.h"

void AreaLayerItem::print(QTextStream& out, AMapconf& mapconf) {
	QString name = shortName().toUpper();
	out << QString("LAYER:%1:%2").arg(name).arg(mapconf.dftvalue(name)) << "\n";
	QString s;

	for (int i=0; i<_list.count(); i++) {
		ALayerId* layerid = _list[i];
		QString multi_cd;
		if (layerid->multi_cd.trimmed().length() < 1) {
			multi_cd = "";
		}else {
			multi_cd = QString("_%1").arg(layerid->multi_cd);
		}

		// check map_type C or P
		QString map_type = QString("G");
		if (layerid->bndrylist.count() > 0) {
			ABndry* p = layerid->bndrylist[0];
			if (p->bndry_via == QChar('C')) map_type = "C";
		}
		s = QString("ID:%1%2:%3:%4").arg(layerid->id).arg(multi_cd).arg(layerid->bndrylist.count()).arg(map_type);
		out << s << "\n";

		for (int j=0; j<layerid->bndrylist.count(); j++)
		{
			ABndry* p = layerid->bndrylist[j];
			if (p->bndry_via == QChar('G') || p->bndry_via == QChar('H')) {
				s = QString("%1:%2%3").arg(p->bndry_via).arg(p->latlon.lat).arg(p->latlon.lon);
				out << s << "\n";
			}else if(p->bndry_via == QChar('L') || p->bndry_via == QChar('R')) {
				s = QString("%1:%2%3:%4%5:%6:%7")
						.arg(p->bndry_via)
						.arg(p->latlon.lat).arg(p->latlon.lon)
						.arg(p->arc_center_latlon.lat).arg(p->arc_center_latlon.lon)
						.arg(p->arc_dist)
						.arg(p->arc_bearing);
				out << s << "\n";
			}else if(p->bndry_via == QChar('C')) {
				s = QString("%1:%2%3:%4")
						.arg(p->bndry_via)
						.arg(p->arc_center_latlon.lat)
						.arg(p->arc_center_latlon.lon)
						.arg(p->arc_dist);
				out << s << "\n";
			}else {
				logprint(QString("%1 error bndry_via is not in (G H R L C): %1").arg(name).arg(p->bndry_via));
			}
		}
	}
	out << QString("ENDLAYER") << "\n";
	logprint(QString("write %1 done").arg(name));
}

bool AreaLayerItem::query(QSqlQuery* q, const QString& sql)
{
	// MSAW, MVA Layer
	if (layerType() == Layer_Msaw || layerType() == Layer_Mva) {
		return queryMsaw(q, sql);
	}
	int count = 0;
	QSqlError sqlerror;
	q->exec(sql);

	sqlerror = q->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		logprint(QString("AreaLayerItem query error : %1 (%2)").arg(sqlerror.text()).arg(sql));
		return false;
	}
#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg(shortName()));
#endif
	_list.clear();
	QString prev = QString("");
	ALayerId* layerid;

	while(q->next()) {
		QString id = q->value(0).toString();
		QString bndry_idx = q->value(1).toString();
		QString bndry_via = q->value(2).toString();
		QString lat       = q->value(3).toString();
		QString lon       = q->value(4).toString();
		QString arc_center_lat = q->value(5).toString();
		QString arc_center_lon = q->value(6).toString();
		QString arc_bearing    = q->value(7).toString();
		QString arc_dist       = q->value(8).toString();
		QString multi_cd       = q->value(9).toString();
		QString key            = id + multi_cd;
		if (key != prev) {
			layerid = new ALayerId;
			layerid->id = id;
			layerid->multi_cd = multi_cd;
			layerid->drawtype = QChar('G');
			layerid->visible = true;
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
		prev = key;
		count++;
	}
	logprint(QString("query %1 done %2 id read").arg(shortName()).arg(count));
	return true;
}

bool AreaLayerItem::queryMsaw(QSqlQuery* q, const QString& sql)
{
	int count = 0;

	QSqlError sqlerror;
	q->exec(sql);

	sqlerror = q->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		logprint(QString("AreaLayerItem query error : %1 ( %2 ) ").arg(sqlerror.text()).arg(sql));
		return false;
	}

#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg(shortName()));
#endif
	_list.clear();
	QString prev = QString("");
	ALayerId* layerid;
	while(q->next()) {
		QString id = q->value(0).toString();
		QString bndry_idx = q->value(1).toString();
		QString bndry_via = q->value(2).toString();
		QString lat = q->value(3).toString();
		QString lon = q->value(4).toString();
		QString arc_AZ0 = q->value(5).toString();
		QString arc_AZ1 = q->value(6).toString();
		QString arc_RMIN = q->value(7).toString();
		QString arc_RMAX = q->value(8).toString();
		QString multi_cd = q->value(9).toString();
		QString key = id + multi_cd;
		if (key != prev) {
			layerid = new ALayerId;
			layerid->id = id;
			layerid->multi_cd = "";
			layerid->drawtype = QChar('G');
			layerid->visible = true;
			_list.append(layerid);
		}
		if (layerid != NULL) {
			if (multi_cd == "P") {		// MSAW SafetyPolygon
				ABndry* bndry = new ABndry;
				bndry->bndry_idx = bndry_idx.toInt();
				bndry->bndry_via = bndry_via[0];
				bndry->latlon.lat = lat;
				bndry->latlon.lon = lon;
				bndry->latlon.p = _ca.toDD(QString("%1%2").arg(lat).arg(lon));
				bndry->arc_center_latlon.lat = lat;
				bndry->arc_center_latlon.lon = lon;
				bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(lat).arg(lon));
				bndry->arc_bearing = arc_RMIN.toDouble();
				bndry->arc_dist = arc_RMAX.toDouble();
				bndry->multi_cd = multi_cd;

				layerid->bndrylist.append(bndry);
			}
			else if(multi_cd == "S") {   // MSAW SafetySenstor, MVA Layer
				double vd_bearing_AZ0 = arc_AZ0.toDouble();			// DB 각도
				double vd_bearing_AZ1 = arc_AZ1.toDouble();         // DB 각도
				double vd_distance_RMIN = UnitChange::haeriToMeter(arc_RMIN.toDouble());	// 기준점으로 부터의 거리
				double vd_distance_RMAX = UnitChange::haeriToMeter(arc_RMAX.toDouble());

				QString vs_latlonA = QString("%1%2").arg(lat).arg(lon);		// 기준점
				QPointF vp_newB = _ca.newPoint(vs_latlonA, fmod(vd_bearing_AZ0, 360), vd_distance_RMIN);	// 좌표 B
				QString vs_latlonB = _ca.toDMS(vp_newB);

				QPointF vp_newC = _ca.newPoint(vs_latlonA, fmod(vd_bearing_AZ0, 360), vd_distance_RMAX);	// 좌표 C
				QString vs_latlonC = _ca.toDMS(vp_newC);

				QPointF vp_newD = _ca.newPoint(vs_latlonA, fmod(vd_bearing_AZ1, 360), vd_distance_RMAX);	// 좌표 D
				QString vs_latlonD = _ca.toDMS(vp_newD);

				QPointF vp_newE = _ca.newPoint(vs_latlonA, fmod(vd_bearing_AZ1, 360), vd_distance_RMIN);	// 좌표 E
				QString vs_latlonE = _ca.toDMS(vp_newE);

				if (vd_distance_RMIN == 0) {
					if (abs(vd_bearing_AZ0 - vd_bearing_AZ1) == 360) {
						// 360도이면 원그리기
						// Point(A)
						ABndry* bndry = new ABndry;
						bndry->bndry_via = QChar('C');
						bndry->latlon.lat = vs_latlonA.mid(0, 9);
						bndry->latlon.lon = vs_latlonA.mid(9, 10);
						bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonA.mid(0, 9)).arg(vs_latlonA.mid(9,10)));
						bndry->arc_center_latlon.lat = vs_latlonA.mid(0, 9);
						bndry->arc_center_latlon.lon = vs_latlonA.mid(9, 10);
						bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonA.mid(0, 9)).arg(vs_latlonA.mid(9, 10)));
						bndry->arc_bearing = 0;
						bndry->arc_dist = arc_RMAX.toDouble() * 2;		// NM (원의 지름)
						bndry->multi_cd = "";
						layerid->bndrylist.append(bndry);
					}else {
						// A - C - D
						// Point (A)
						ABndry* bndry = new ABndry;
						bndry->bndry_via = QChar('G');
						bndry->latlon.lat = vs_latlonA.mid(0, 9);
						bndry->latlon.lon = vs_latlonA.mid(9, 10);
						layerid->bndrylist.append(bndry);

						// Point (C)
						bndry = new ABndry;
						bndry->bndry_via = QChar('R');
						bndry->latlon.lat = vs_latlonC.mid(0, 9);
						bndry->latlon.lon = vs_latlonC.mid(9, 10);
						bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonC.mid(0, 9)).arg(vs_latlonC.mid(9, 10)));
						bndry->arc_center_latlon.lat = vs_latlonA.mid(0, 9);
						bndry->arc_center_latlon.lon = vs_latlonA.mid(9, 10);
						bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonA.mid(0,9)).arg(vs_latlonA.mid(9,10)));
						bndry->arc_bearing = 0;
						bndry->arc_dist = 0;		// 4NM (원의 지름)
						bndry->multi_cd = "";
						layerid->bndrylist.append(bndry);

						// Point (D)
						bndry = new ABndry;
						bndry->bndry_via = QChar('G');
						bndry->latlon.lat = vs_latlonD.mid(0, 9);
						bndry->latlon.lon = vs_latlonD.mid(9, 10);
						layerid->bndrylist.append(bndry);
					}
				}else {
					// B - C - D - E 순
					// Point (B)
					ABndry* bndry = new ABndry;
					bndry->bndry_via = QChar('G');
					bndry->latlon.lat = vs_latlonB.mid(0, 9);
					bndry->latlon.lon = vs_latlonB.mid(9, 10);
					layerid->bndrylist.append(bndry);

					if (abs(vd_bearing_AZ0 - vd_bearing_AZ1) == 360) {
						// 360도이면 작은원부터 그리기
						// Point (E)
						bndry = new ABndry;
						bndry->bndry_via = QChar('R');
						bndry->latlon.lat = vs_latlonE.mid(0, 9);
						bndry->latlon.lon = vs_latlonE.mid(9, 10);
						bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonE.mid(0, 9)).arg(vs_latlonE.mid(9, 10)));
						bndry->arc_center_latlon.lat = vs_latlonA.mid(0, 9);
						bndry->arc_center_latlon.lon = vs_latlonA.mid(9, 10);
						bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonA.mid(0,9)).arg(vs_latlonA.mid(9,10)));
						bndry->arc_bearing = 0;
						bndry->arc_dist = 0;		// 4NM (원의 지름)
						bndry->multi_cd = "";
						layerid->bndrylist.append(bndry);

						// Point (D)
						bndry = new ABndry;
						bndry->bndry_via = QChar('G');
						bndry->latlon.lat = vs_latlonD.mid(0, 9);
						bndry->latlon.lon = vs_latlonD.mid(9, 10);
						layerid->bndrylist.append(bndry);

						// Point (C)
						bndry = new ABndry;
						bndry->bndry_via = QChar('L');
						bndry->latlon.lat = vs_latlonC.mid(0, 9);
						bndry->latlon.lon = vs_latlonC.mid(9, 10);
						bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonC.mid(0, 9)).arg(vs_latlonC.mid(9,10)));
						bndry->arc_center_latlon.lat = vs_latlonA.mid(0, 9);
						bndry->arc_center_latlon.lon = vs_latlonA.mid(9, 10);
						bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonA.mid(0,9)).arg(vs_latlonA.mid(9,10)));
						bndry->arc_bearing = 0;
						bndry->arc_dist = 0;	// 4NM (원의 지름)
						bndry->multi_cd = "";
						layerid->bndrylist.append(bndry);
					}else {
						// Point (C)
						bndry = new ABndry;
						bndry->bndry_via = QChar('R');
						bndry->latlon.lat = vs_latlonC.mid(0, 9);
						bndry->latlon.lon = vs_latlonC.mid(9, 10);
						bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonC.mid(0, 9)).arg(vs_latlonC.mid(9,10)));
						bndry->arc_center_latlon.lat = vs_latlonA.mid(0, 9);
						bndry->arc_center_latlon.lon = vs_latlonA.mid(9, 10);
						bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonA.mid(0,9)).arg(vs_latlonA.mid(9,10)));
						bndry->arc_bearing = 0;
						bndry->arc_dist = 0;	// 4NM (원의 지름)
						bndry->multi_cd = "";
						layerid->bndrylist.append(bndry);

						// Point (D)
						bndry = new ABndry;
						bndry->bndry_via = QChar('G');
						bndry->latlon.lat = vs_latlonD.mid(0, 9);
						bndry->latlon.lon = vs_latlonD.mid(9, 10);
						layerid->bndrylist.append(bndry);

						// Point (E)
						bndry = new ABndry;
						bndry->bndry_via = QChar('L');
						bndry->latlon.lat = vs_latlonE.mid(0, 9);
						bndry->latlon.lon = vs_latlonE.mid(9, 10);
						bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonE.mid(0, 9)).arg(vs_latlonE.mid(9,10)));
						bndry->arc_center_latlon.lat = vs_latlonA.mid(0, 9);
						bndry->arc_center_latlon.lon = vs_latlonA.mid(9, 10);
						bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonA.mid(0,9)).arg(vs_latlonA.mid(9,10)));
						bndry->arc_bearing = 0;
						bndry->arc_dist = 0;	// 4NM (원의 지름)
						bndry->multi_cd = "";
						layerid->bndrylist.append(bndry);
					}
				}

			}
		}
		prev = key;
		count++;
	}

	logprint(QString("query %1 done %2 id read").arg(shortName()).arg(count));

	return true;

}

void AreaLayerItem::read(QTextStream& in, int& lineNo)
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
			for (int i=0; i<cnt; i++) {
				line = in.readLine();
				ABndry* bndry = new ABndry;
				bndry->bndry_idx = i + 1;
				list = line.split(":");
				QChar ch = list[0][0];
				bndry->bndry_via = ch;
				if (ch == QChar('G') || ch == QChar('H')) {
					bndry->latlon.lat = LLU::lat(list[1]);
					bndry->latlon.lon = LLU::lon(list[1]);
					bndry->latlon.p = _ca.toDD(list[1]);
					layerid->bndrylist.append(bndry);
				}else if(ch == QChar('L') || ch == QChar('R')) {
					bndry->latlon.lat = LLU::lat(list[1]);
					bndry->latlon.lon = LLU::lon(list[1]);
					bndry->latlon.p = _ca.toDD(list[1]);
					bndry->arc_center_latlon.lat = LLU::lat(list[2]);
					bndry->arc_center_latlon.lon = LLU::lon(list[2]);
					bndry->arc_center_latlon.p   = _ca.toDD(list[2]);
					bndry->arc_dist = list[3].toDouble();
					bndry->arc_bearing = list[4].toDouble();
					layerid->bndrylist.append(bndry);
				}else if(ch == QChar('C')) {
					bndry->latlon.lat = LLU::lat(list[1]);
					bndry->latlon.lon = LLU::lon(list[1]);
					bndry->latlon.p = _ca.toDD(list[1]);
					bndry->arc_center_latlon.lat = LLU::lat(list[1]);
					bndry->arc_center_latlon.lon = LLU::lon(list[1]);
					bndry->arc_dist = list[2].toDouble();
					layerid->bndrylist.append(bndry);
				}else {
					logprint(QString("%1 : error should one of G,H,L,R").arg(ch));
				}
			}
		}
	}
}

void AreaLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
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
			ad->drawPath(painter, dataxy, layerid->drawtype);

			if (textVisible() == true) {
				QPoint c = bound.center();
				painter->setPen(Qt::white);
				ad->drawTextAtCenter(painter, c, layerid->id);
				painter->setPen(_lp.getPen());
			}
		}
	}
}

/**
 * Prepares the item for a geometry change. Call this function before changing the bounding rect of
 * an item to keep QGraphicsScene's index up to date
 */
void AreaLayerItem::updateInfo()
{
	prepareGeometryChange();
}

QRectF AreaLayerItem::boundingRect() const
{
	qreal adjust = 0.5;
	LatLonConvert* vp = ad->viewport();
	QRectF rect = QRectF(adjust, adjust, vp->srcRect().width() * 1.0, vp->srcRect().height() * 1.0);

	return rect;
}
