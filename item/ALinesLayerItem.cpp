/*
 * ALinesLayerItem.cpp
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */
#include <iostream>
#include "ALinesLayerItem.h"

/**
 * Line Layer 를 생성해서 파일 스트림으로 보낸다.
 */
void ALinesLayerItem::print(QTextStream& out, AMapconf& mapconf) {
	QString name = shortName().toUpper();
	QString s;
	qDebug() << QString("LAYER:%1:%2").arg(name).arg(mapconf.dftvalue(name));

	out << QString("LAYER:%1:%2").arg(name).arg(mapconf.dftvalue(name)) << "\n";
	for (int i=0; i<_list.count();i++) {
		ALayerId* layerid = _list[i];
		QChar drawtype = QChar('P');
		if (layerid->id == "RKRR") drawtype = QChar('G');
		if (name == "HOLD") drawtype = QChar('G');
		s = QString("ID:%1:%2:%3").arg(layerid->id).arg(layerid->bndrylist.count()).arg(drawtype);
		out << s << "\n";
		for (int j=0; j<layerid->bndrylist.count(); j++) {
			ABndry *p = layerid->bndrylist[j];
			if (p->bndry_via == QChar('L') || p->bndry_via == QChar('R')) {
				s = QString("%1:%2%3:%4%5:%6:%7")
						.arg(p->bndry_via)
						.arg(p->latlon.lat).arg(p->latlon.lon)
						.arg(p->arc_center_latlon.lat).arg(p->arc_center_latlon.lon)
						.arg(p->arc_dist)
						.arg(p->arc_bearing);
				out << s << "\n";
			}else {
				s = QString("%1:%2%3").arg(p->bndry_via).arg(p->latlon.lat).arg(p->latlon.lon);
				out << s << "\n";
			}
		}
	}
	out << QString("ENDLAYER") << "\n";
	logprint(QString("write %1 done").arg(name));
}

bool ALinesLayerItem::query(QSqlQuery* q, const QString& sql)
{
	if (layerType() == Layer_Runway) {
		return queryRunway(q, sql);
	}else if(layerType() == Layer_Hold) {
		return queryHold(q, sql);
	}else if(layerType() == Layer_Sid || layerType() == Layer_Star || layerType() == Layer_Apch) {
		return querySid(q, sql);
	}

	int count = 0;
	QSqlError sqlerror;
	q->exec(sql);

#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg(shortName()));
#endif

	//_list.clear();

	QString prev = QString("");
	ALayerId* layerid;

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
			_list.append(layerid);
		}
		if (layerid != NULL) {
			layerid->id = id;
			ABndry* bndry = new ABndry;
			bndry->bndry_idx = bndry_idx.toInt();
			bndry->bndry_via = bndry_via[0];
			bndry->latlon.lat = lat;
			bndry->latlon.lon = lon;
			bndry->latlon.p   = _ca.toDD(QString("%1%2").arg(lat).arg(lon));	// decimal degree convert
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
	logprint(QString("query %1 done %2 id read").arg(shortName().arg(count)));

	return true;
}

bool ALinesLayerItem::queryRunway(QSqlQuery* q, const QString& sql)
{
	QSqlError sqlerror;
	QString prev = QString("");
	ALayerId* layerid;

	q->exec(sql);

	sqlerror = q->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		logprint(QString("ALinesLayerItem query error :  %1 (%2)").arg(sqlerror.text()).arg(sql));
		return false;
	}

#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg(shortName()));
#endif

	int count = 0;
	//_list.clear();
	while(q->next()) {
		QString ad_id = q->value(0).toString();
		QString rway_no = q->value(1).toString();
		QString len = q->value(2).toString();
		QString width = q->value(3).toString();
		QString abearing = q->value(4).toString();
		QString bbearing = q->value(5).toString();
		QString alat = q->value(6).toString();
		QString alon = q->value(7).toString();
		QString blat = q->value(8).toString();
		QString blon = q->value(9).toString();

		QString key = QString("%1_%2").arg(ad_id).arg(rway_no);

		if (key != prev) {
			layerid = new ALayerId;
			layerid->id = QString("%1_%2").arg(ad_id).arg(rway_no);
			layerid->drawtype = 'G';
			_list.append(layerid);
		}

		if (layerid != NULL) {
			QString latlonA = QString("%1%2").arg(alat).arg(alon);
			QString latlonB = QString("%1%2").arg(blat).arg(blon);
			double bearingAB = _ca.bearing(latlonA, latlonB);
			double bearingBA = _ca.bearing(latlonB, latlonA);
			double distance  = UnitChange::feetToMeter(width.toDouble()/2);

			QPointF newA1 = _ca.newPoint(latlonA, fmod((bearingAB+90), 360), distance);
			QPointF newA2 = _ca.newPoint(latlonA, fmod((bearingAB-90), 360), distance);

			QPointF newB1 = _ca.newPoint(latlonB, fmod((bearingBA+90), 360), distance);
			QPointF newB2 = _ca.newPoint(latlonB, fmod((bearingBA-90), 360), distance);
			QString A1 = _ca.toDMS(newA1);
			QString A2 = _ca.toDMS(newA2);
			QString B1 = _ca.toDMS(newB1);
			QString B2 = _ca.toDMS(newB2);

			ABndry* bndry = new ABndry;
			bndry->bndry_via = QChar('G');
			bndry->latlon.lat = A1.mid(0, 9);
			bndry->latlon.lon = A1.mid(9, 10);
			layerid->bndrylist.append(bndry);

			bndry = new ABndry;
			bndry->bndry_via = QChar('G');
			bndry->latlon.lat = A2.mid(0, 9);
			bndry->latlon.lon = A2.mid(9, 10);
			layerid->bndrylist.append(bndry);

			bndry = new ABndry;
			bndry->bndry_via = QChar('G');
			bndry->latlon.lat = B1.mid(0, 9);
			bndry->latlon.lon = B1.mid(9, 10);
			layerid->bndrylist.append(bndry);

			bndry = new ABndry;
			bndry->bndry_via = QChar('G');
			bndry->latlon.lat = B2.mid(0, 9);
			bndry->latlon.lon = B2.mid(9, 10);
			layerid->bndrylist.append(bndry);

			// 처음점과 같게 하려구
			bndry = new ABndry;
			bndry->bndry_via = QChar('G');
			bndry->latlon.lat = A1.mid(0, 9);
			bndry->latlon.lon = A1.mid(9, 10);
			layerid->bndrylist.append(bndry);
		}
		prev = key;
		count++;
	}
	logprint(QString("query %1 done %2 id read").arg(shortName()).arg(count));

	return true;
}

bool ALinesLayerItem::queryHold(QSqlQuery* q, const QString& sql)
{
	QSqlError sqlerror;
	QString prev = QString("");
	ALayerId* layerid;

	q->exec(sql);

	sqlerror = q->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		logprint(QString("ALinesLayerItem query error : %1 (%2)").arg(sqlerror.text()).arg(sql));
		return false;
	}

#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg(shortName()));
#endif
	int count = 0;
	_list.clear();

	while(q->next()) {
		QString ad_id = q->value(0).toString();
		QString dup_id = q->value(1).toString();
		QString inb_hld_crs = q->value(2).toString();
		QString direction = q->value(3).toString();
		QString len = q->value(4).toString();
		QString lat = q->value(5).toString();
		QString lon = q->value(6).toString();

		QString key = QString("%1_%2").arg(ad_id).arg(dup_id);
		if (key != prev) {
			layerid = new ALayerId;
			layerid->id = QString("%1_%2").arg(ad_id).arg(dup_id);
			_list.append(layerid);
		}
		if (layerid != NULL) {
			QString vs_latlonBase = QString("%1%2").arg(lat).arg(lon);			// 기준점
			double vd_distance1 = UnitChange::haeriToMeter(len.toDouble());		// 기준점으로부터의 거리
			double vd_Ind_hold_crc = inb_hld_crs.toDouble();					// DB 각도
			double vd_bearing1 = 0;

			vd_Ind_hold_crc -= 8;

			if (vd_Ind_hold_crc < 0) {
				vd_Ind_hold_crc += 360;
			}
			if (vd_Ind_hold_crc < 180) {
				vd_bearing1 = vd_Ind_hold_crc + 180;
			}else {
				vd_bearing1 = vd_Ind_hold_crc - 180;
			}
			QPointF vp_newA1 = _ca.newPoint(vs_latlonBase, fmod(vd_bearing1, 360), vd_distance1);
			QString vs_latlon1 = _ca.toDMS(vp_newA1);

			// 좌표 2 + Arc (기준점 <-> 좌표 2) 중심점
			QChar vc_arc_bndry_via = QChar('R');
			if (direction == "L") vc_arc_bndry_via = QChar('L');

			double vd_diameter = 4;				// 4NM(원의 지름) and 기준점으로부터의 거리
			double vd_distance2 = UnitChange::haeriToMeter(vd_diameter);
			double vd_bearing2 = 0;

			if (direction == "R") {
				vd_bearing2 = vd_bearing1 + 270;
			}else {
				vd_bearing2 = vd_bearing1 + 90;
			}
			QPointF vp_newA2 = _ca.newPoint(vs_latlonBase, fmod(vd_bearing2, 360), vd_distance2);
			QString vs_latlon2 = _ca.toDMS(vp_newA2);

			QPointF vp_newArcCenter1 = _ca.mid(vs_latlonBase, vs_latlon2);
			QString vs_latlonArcCenter1 = _ca.toDMS(vp_newArcCenter1);

			// 좌표 3 + Arc (좌표 3 <-> 좌표 1)
			QPointF vp_newA3 = _ca.newPoint(vs_latlon2, fmod(vd_bearing1, 360), vd_distance1);
			QString vs_latlon3 = _ca.toDMS(vp_newA3);

			QPointF vp_newArcCenter2 = _ca.mid(vs_latlon3, vs_latlon1);
			QString vs_latlonArcCenter2 = _ca.toDMS(vp_newArcCenter2);

			// Point (기준점)
//			ABndry* bndry = new ABndry;
//			bndry->bndry_via = QChar('G');
//			bndry->latlon.lat = vs_latlonBase.mid(0, 9);
//			bndry->latlon.lon = vs_latlonBase.mid(9, 10);
//			layerid->bndrylist.append(bndry);

            //Point (좌표_1)
            ABndry* bndry  = new ABndry;
            bndry->bndry_via = QChar('G');
            bndry->latlon.lat =  vs_latlon1.mid(0,9);
            bndry->latlon.lon =  vs_latlon1.mid(9,10);
            layerid->bndrylist.append(bndry);

			// Arc (기준점 <-> Arc1)
			bndry = new ABndry;
			bndry->bndry_via = vc_arc_bndry_via;
			bndry->latlon.lat = vs_latlonBase.mid(0, 9);
			bndry->latlon.lon = vs_latlonBase.mid(9, 10);
			bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonBase.mid(0, 9)).arg(vs_latlonBase.mid(9, 10)));
			bndry->arc_center_latlon.lat = vs_latlonArcCenter1.mid(0, 9);
			bndry->arc_center_latlon.lon = vs_latlonArcCenter1.mid(9, 10);
			bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonArcCenter1.mid(0,9)).arg(vs_latlonArcCenter1.mid(9, 10)));
			bndry->arc_bearing = _ca.bearing(bndry->arc_center_latlon.p, bndry->latlon.p);  //90;   // fmod(vd_bearing2, 360);
			bndry->arc_dist = vd_diameter/2;			// 2NM(원의 지름)
			bndry->multi_cd = "";
			layerid->bndrylist.append(bndry);

			// Point (좌표 3)
//			bndry = new ABndry;
//			bndry->bndry_via = QChar('G');
//			bndry->latlon.lat = vs_latlon3.mid(0, 9);
//			bndry->latlon.lon = vs_latlon3.mid(9, 10);
//			layerid->bndrylist.append(bndry);

			// Point (좌표 2)
            bndry  = new ABndry;
            bndry->bndry_via = QChar('G');
            bndry->latlon.lat =  vs_latlon2.mid(0,9);
            bndry->latlon.lon =  vs_latlon2.mid(9,10);
            layerid->bndrylist.append(bndry);

			// Arc (좌표 3 <-> 좌표 1)
			bndry = new ABndry;
			bndry->bndry_via = vc_arc_bndry_via;
			bndry->latlon.lat = vs_latlon3.mid(0, 9);
			bndry->latlon.lon = vs_latlon3.mid(9, 10);
			bndry->latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlon3.mid(0, 9)).arg(vs_latlon3.mid(9, 10)));
			bndry->arc_center_latlon.lat = vs_latlonArcCenter2.mid(0, 9);
			bndry->arc_center_latlon.lon = vs_latlonArcCenter2.mid(9, 10);
			bndry->arc_center_latlon.p = _ca.toDD(QString("%1%2").arg(vs_latlonArcCenter2.mid(0, 9)).arg(vs_latlonArcCenter2.mid(9, 10)));
			bndry->arc_bearing = _ca.bearing(bndry->arc_center_latlon.p, bndry->latlon.p);  // 90;  // fmod(vd_bearing2, 360);
			bndry->arc_dist = vd_diameter/2; // 2NM(원의 반지름)
			bndry->multi_cd = "";
			layerid->bndrylist.append(bndry);
		}
		prev = key;
		count++;
	}
	logprint(QString("query %1 done %2 id read").arg(shortName()).arg(count));

	return true;
}
/**
 * SID, START, APCH query
 */
bool ALinesLayerItem::querySid(QSqlQuery* q, const QString& sql)
{
	int count =0 ;
	QSqlError sqlerror;
	q->exec(sql);

#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg(shortName()));
#endif
	QString prev = QString("");
	ALayerId* layerid;
	while(q->next())
	{
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
			_list.append(layerid);
		}
		if (layerid != NULL) {
			layerid->id = id;

			if (multi_cd == "D") {
				// 기준점
				QString vs_latlonBase = QString("%1%2").arg(lat).arg(lon);				// 기준점

				// 좌표 1
				double vd_distance1 = UnitChange::haeriToMeter(arc_dist.toDouble());	// 기준점으로부터의 거리
				double vd_bearing1  = arc_bearing.toDouble();								// DB Bearing

				QPointF vp_newA1    = _ca.newPoint(vs_latlonBase, fmod(vd_bearing1, 360), vd_distance1);
				QString vs_latlon1  = _ca.toDMS(vp_newA1);

				lat = vs_latlon1.mid(0,  9);
				lon = vs_latlon1.mid(9, 10);
			}

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

	logprint(QString("querySid %1 done %2 id read").arg(shortName()).arg(count));
	return true;
}

void ALinesLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	//std::cout << "ALineLayerItem paint called...........\n";
	//logprint("ALinesLayerItem paint called.....................");

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
		//_log->print(QString("Layer id : %1").arg(layerid->id));
		for (int j=0; j<layerid->bndrylist.size(); j++) {
			ABndry* bndry = layerid->bndrylist[j];
			CartesianXY cxy;
			QPoint visualPoint = vp->latlonToScreen(bndry->latlon.p);
			cxy.bndry_via = bndry->bndry_via;
			cxy.xyz = vp->cartesian();
			cxy.mxy = visualPoint;
			bound.setPosition(visualPoint);
			cxy.lat = bndry->latlon.p.x();
			cxy.lon = bndry->latlon.p.y();
			if (bndry->bndry_via == QChar('C')) {
				cxy.arc_centerxy = visualPoint;
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
			//std::cout << "ALineLayerItem paint bound.inRect called [" << layerid->drawtype.toAscii() << "]...........\n";
			//_log->print("Layer ID : " + layerid->id);
			ad->drawPath(painter, dataxy, layerid->drawtype);
		}
	}
}

void ALinesLayerItem::read(QTextStream& in, int& lineNo)
{
	QStringList list;
	QString line;
	while(!in.atEnd()){
		line = in.readLine();
		//std::cout << "read line : " << line.toStdString() << "\n";
		lineNo++;
		if(line == "ENDLAYER") break;
		list = line.split(":");
		if(list[0] == "ID"){
			ALayerId* layerid = new ALayerId;
			_list.append(layerid);
			layerid->id = list[1];
			layerid->drawtype = list[3][0];
			layerid->visible = true;
			int cnt = (list[2]).toInt();
			for(int i=0;i<cnt;i++){
				line = in.readLine();
				lineNo++;
				ABndry* bndry = new ABndry;
				bndry->bndry_idx = i+1;
				list = line.split(":");
				QChar ch = list[0][0];
				bndry->bndry_via = ch;
				if(ch == QChar('G')||ch == QChar('H')){
					bndry->latlon.lat = LLU::lat(list[1]);
					bndry->latlon.lon = LLU::lon(list[1]);
					bndry->latlon.p = _ca.toDD(list[1]);
					layerid->bndrylist.append(bndry);
				}else if(ch == QChar('L')||ch == QChar('R')){
					bndry->latlon.lat = LLU::lat(list[1]);
					bndry->latlon.lon = LLU::lon(list[1]);
					bndry->latlon.p = _ca.toDD(list[1]);
					bndry->arc_center_latlon.lat = LLU::lat(list[2]);
					bndry->arc_center_latlon.lon = LLU::lon(list[2]);
					bndry->arc_center_latlon.p = _ca.toDD(list[2]);
					bndry->arc_dist = list[3].toDouble();
					bndry->arc_bearing = list[4].toDouble();
					layerid->bndrylist.append(bndry);
				}else if(ch == QChar('C')){
					bndry->latlon.lat = LLU::lat(list[1]);
					bndry->latlon.lon = LLU::lon(list[1]);
					bndry->latlon.p = _ca.toDD(list[1]);
					bndry->arc_center_latlon.lat = LLU::lat(list[1]);
					bndry->arc_center_latlon.lon = LLU::lon(list[1]);
					bndry->arc_center_latlon.p = _ca.toDD(list[1]);
					bndry->arc_dist = list[2].toDouble();
					layerid->bndrylist.append(bndry);
				}else{
					logprint(QString("%1 : error should one of  G,H,L,R ").arg(ch));
				}
			}
		}
	}//end while
}

void ALinesLayerItem::updateInfo()
{
	prepareGeometryChange();
}

QRectF ALinesLayerItem::boundingRect() const
{
	qreal adjust = 0.5;
	LatLonConvert* vp = ad->viewport();
	// std::cout << "width : " << convert->srcRect().width() << ", height : " << convert->srcRect().height() << "\n";

	//QRectF rect = QRectF(-convert->srcRect().width()/2 - adjust, -convert->srcRect().height()/2 - adjust,
	//		convert->srcRect().width() * 1.0, convert->srcRect().height() * 1.0);
	QRectF rect = QRectF(adjust, adjust, vp->srcRect().width() * 1.0, vp->srcRect().height() * 1.0);

	return rect;
}
