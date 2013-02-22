/*
 * AUserLayerItemMng.cpp
 *
 *  Created on: 2012. 3. 16.
 *      Author: HIST002
 */

#include "AUserLayerItemMng.h"

/**
 * 사용자 레이어 정보를 데이터베이스에서 쿼리하여 리스트에 등록한다.
 */
bool AUserLayerItemMng::query(QSqlQuery* q)
{
	_lasterror = QString("");
	AUserLayerItem* item;
	AUserLayerId* layerid;
	int count = 0;
#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg("USERLAYER"));
#endif

	QString prev = QString("");
	QSqlError sqlerror;
	QString sql = QString(
			"SELECT                                                                 "
			"       A.MAP_ID,    A.MAP_TP,      A.ATTR,           B.BNDRY_IDX,      "
			"       B.LAT,       B.LON,         B.ARC_CENTER_LAT, B.ARC_CENTER_LON, "
			"       B.ARC_DIST,  B.ARC_BEARING, B.BNDRY_VIA                         "
			"  FROM TB_USERMAP A, TB_USERMAPBNDRY B                                 "
			" WHERE A.MAP_ID = B.MAP_ID                                             "
			" ORDER BY A.MAP_ID, B.BNDRY_IDX                                        "
			);
	q->exec(sql);
	sqlerror = q->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		_lasterror = sqlerror.text();
		logprint(QString("AUserLayerItem query error : %1 (%2)").arg(sqlerror.text()).arg(sql));
		return false;
	}

	while(q->next()) {
		QString map_id = q->value(0).toString();
		QString map_tp = q->value(1).toString();
		QString attr = q->value(2).toString();
		QString bndry_idx = q->value(3).toString();
		QString lat = q->value(4).toString();
		QString lon = q->value(5).toString();
		QString arc_center_lat = q->value(6).toString();
		QString arc_center_lon = q->value(7).toString();
		QString arc_dist = q->value(8).toString();
		QString arc_bearing = q->value(9).toString();
		QString bndry_via = q->value(10).toString();

		QString key = map_id;
		if (key != prev) {
			layerid = new AUserLayerId;
			item    = new AUserLayerItem;
			item->setLog(_log);
			item->setAirdraw(ad);
			layerid->id = map_id;
			layerid->drawtype = map_tp[0];
			layerid->attr = attr;
			item->setUserLayer(layerid);
			_list.append(item);
		}
		if (layerid != NULL) {
			AUserbndry* bndry = new AUserbndry;
			bndry->bndry_idx = bndry_idx.toInt();
			bndry->bndry_via = bndry_via[0];
			bndry->latlon.lat = lat;
			bndry->latlon.lon = lon;
			bndry->latlon.p = _ca.toDD(lat+lon);
			bndry->arc_center_latlon.lat = arc_center_lat;
			bndry->arc_center_latlon.lon = arc_center_lon;
			bndry->arc_bearing = arc_bearing.toDouble();
			bndry->arc_dist = arc_dist.toDouble();

			layerid->bndrylist.append(bndry);
		}
		prev = key;
		count++;
	}
	logprint(QString("query usermap done %1 id read").arg(idCount()));
	return true;
}

bool AUserLayerItemMng::query(const QString& dbname)
{
	if (dbname.length() < 1) return false;
	QSqlQuery* q = new QSqlQuery(QSqlDatabase::database(dbname));
	return query(q);
}

void AUserLayerItemMng::read(QTextStream& in, int& lineNo)
{
	QStringList list;
	QString line;

	while(true) {
		line = in.readLine();
		lineNo++;
		if (line == "ENDLAYER") break;
		list = line.split(":");
		if (list[0] == "ID") {
			AUserLayerItem* item  = new AUserLayerItem;
			AUserLayerId* layerid = new AUserLayerId;
			item->setUserLayer(layerid);
			item->setLog(_log);
			item->setAirdraw(ad);
			_list.append(item);

			layerid->id = list[1];
			layerid->drawtype = list[3][0];
			QString a = QString("");
			for (int k = 4; k<list.count(); k++) {
				a += list[k] + ":";
			}
			layerid->attr = a;
			layerid->msb.p1 = QPoint(90, 180);	// msb 초기화
			layerid->msb.p2 = QPoint(-90, -180);
			int cnt = (list[2]).toInt();
			for (int i=0; i<cnt; i++) {
				line = in.readLine();
				lineNo++;
				list = line.split(":");
				AUserbndry* bndry = new AUserbndry;
				QChar ch = list[0][0];
				bndry->bndry_via = ch;
				bndry->latlon.lat = LLU::lat(list[1]);
				bndry->latlon.lon = LLU::lon(list[1]);
				bndry->latlon.p = _ca.toDD(list[1]);
				if (ch == QChar('A')) {
					bndry->arc_center_latlon.lat = LLU::lat(list[2]);
					bndry->arc_center_latlon.lon = LLU::lon(list[2]);
					bndry->arc_center_latlon.p = _ca.toDD(list[2]);
					bndry->arc_bearing = list[3].toDouble();		// startAngle
					bndry->arc_dist = list[4].toDouble();			// endAngle
				}else if(ch == QChar('C')) {
					bndry->arc_center_latlon.lat = LLU::lat(list[1]);
					bndry->arc_center_latlon.lon = LLU::lon(list[1]);
					bndry->arc_center_latlon.p = _ca.toDD(list[1]);
					bndry->arc_dist = list[2].toDouble();			// endAngle
				}else if(ch == QChar('L') || ch == QChar('R')) {
					bndry->arc_center_latlon.lat = LLU::lat(list[2]);
					bndry->arc_center_latlon.lon = LLU::lon(list[2]);
					bndry->arc_center_latlon.p = _ca.toDD(list[2]);
					bndry->arc_dist = list[3].toDouble();
					bndry->arc_bearing = list[4].toDouble();
				}
				layerid->msb.p1.setX(qMin(layerid->msb.p1.x(), bndry->latlon.p.x()));
				layerid->msb.p1.setY(qMin(layerid->msb.p1.y(), bndry->latlon.p.y()));
				layerid->msb.p2.setX(qMax(layerid->msb.p2.x(), bndry->latlon.p.x()));
				layerid->msb.p2.setY(qMax(layerid->msb.p2.y(), bndry->latlon.p.y()));
				layerid->bndrylist.append(bndry);
			}
		}
	}
	logprint(QString("read usermap done, id count: %1").arg(_list.count()));
}

/**
 * DB에 내용을 저장한다
 * 기존에 DB에 있던 내용들 모두 삭제됨
 */
bool AUserLayerItemMng::updateDB(const QString& dbname)
{
	if(dbname.length() < 1) return false;
	_lasterror = QString("");

	// main process
	QSqlError sqlerror;
	QSqlDatabase::database(dbname).transaction();
	QSqlQuery* query = new QSqlQuery(QSqlDatabase::database(dbname));

	QString sql = "DELETE FROM TB_USERMAPBNDRY";
	query->exec(sql);

	if (query->lastError().type() != QSqlError::NoError) {
		QSqlDatabase::database(dbname).rollback();
		logprint(QString("UserLayer update db error : %1").arg(query->lastError().text()));
		return false;
	}

	sql = "DELETE FROM TB_USERMAP";
	query->exec(sql);

	for (int i=0; i<_list.count(); i++) {
		AUserLayerItem* item = _list[i];
		AUserLayerId* layerid = item->getUserLayer();

		sql = QString("INSERT INTO TB_USERMAP (   "
				" MAP_ID, MAP_TP, ATTR) VALUES ('%1', '%2', '%3') ")
				.arg(layerid->id)
				.arg(layerid->drawtype)
				.arg(layerid->attr);
		query->exec(sql);
		if (query->lastError().type() != QSqlError::NoError) {
			QSqlDatabase::database(dbname).rollback();
			logprint(QString("UserLayer update db error : %1").arg(query->lastError().text()));
			return false;
		}

		for (int j=0; j<layerid->bndrylist.count(); j++) {
			AUserbndry* bndry = layerid->bndrylist[j];
			sql = QString(" INSERT INTO TB_USERMAPBNDRY (   "
					" MAP_ID,  BNDRY_IDX,  LAT, LON,        "
					" ARC_CENTER_LAT, ARC_CENTER_LON,       "
					" ARC_DIST, ARC_BEARING, BNDRY_VIA      "
					" ) VALUES (                            "
					"'%1','%2','%3','%4','%5','%6',round(%7,1),round(%8,1),'%9')")
					.arg(layerid->id)
					.arg(j+1)
					.arg(bndry->latlon.lat)
					.arg(bndry->latlon.lon)
					.arg(bndry->arc_center_latlon.lat)
					.arg(bndry->arc_center_latlon.lon)
					.arg(bndry->arc_dist)
					.arg(bndry->arc_bearing)
					.arg(bndry->bndry_via);
			query->exec(sql);
			if (query->lastError().type() != QSqlError::NoError) {
				QSqlDatabase::database(dbname).rollback();
				logprint(QString("UserLayer update db error : %1").arg(query->lastError().text()));
				return false;
			}
		}
	}
	QSqlDatabase::database(dbname).commit();
	return true;
}

/**
 * User Layer 리스트에 등록된 정보를 프린트한다.
 */
void AUserLayerItemMng::print(QTextStream& out)
{
	if (_list.count() < 1) {
		return;
	}
	QString s;
	out << QString("LAYER:USERMAP") << "\n";
	for (int i=0; i<_list.count();i++) {
		AUserLayerItem* item  = _list[i];
		AUserLayerId* layerid = item->getUserLayer();

		s = QString("ID:%1:%2:%3:%4").arg(layerid->id).arg(layerid->bndrylist.count())
				.arg(layerid->drawtype).arg(layerid->attr);
		out << s << "\n";
		for (int j=0; j<layerid->bndrylist.count(); j++) {
			AUserbndry* p = layerid->bndrylist[j];
			if (p->bndry_via == QChar('A')) { // ARC
				s = QString("%1:%2%3:%4%5:%6:%7")
						.arg(p->bndry_via).arg(p->latlon.lat).arg(p->latlon.lon)
						.arg(p->arc_center_latlon.lat).arg(p->arc_center_latlon.lon)
						.arg(p->arc_dist).arg(p->arc_bearing);
			}else if(p->bndry_via == QChar('C')) {
				s = QString("%1:%2%3:%4")
						.arg(p->bndry_via)
						.arg(p->latlon.lat).arg(p->latlon.lon)
						.arg(p->arc_dist);
			}else if(p->bndry_via == QChar('L') || p->bndry_via == QChar('R')) {
				s = QString("%1:%2%3:%4%5:%6:%7")
						.arg(p->bndry_via).arg(p->latlon.lat).arg(p->latlon.lon)
						.arg(p->arc_center_latlon.lat).arg(p->arc_center_latlon.lon)
						.arg(p->arc_dist).arg(p->arc_bearing);
			}else {	// G, H
				s = QString("%1:%2%3").arg(p->bndry_via).arg(p->latlon.lat).arg(p->latlon.lon);
			}
			out << s << "\n";
		}
	}
	out << QString("ENDLAYER") << "\n";
	logprint(QString("write %1 done").arg("USERMAP"));
}




int AUserLayerItemMng::findIndex(const QString& id)
{
	for (int i=0; i<_list.count(); i++) {
		AUserLayerItem* item = _list[i];
		AUserLayerId* layerid = item->getUserLayer();
		if (layerid->id.toLower().trimmed() == id.toLower().trimmed()) {
			return i;
		}
	}
	return -1;
}

AUserLayerId* AUserLayerItemMng::find(const QString& id)
{
	for (int i=0; i<_list.count(); i++) {
		AUserLayerItem* item = _list[i];
		AUserLayerId* layerid = item->getUserLayer();

		if (layerid->id.toLower().trimmed() == id.toLower().trimmed()) {
			return layerid;
		}
	}
	return NULL;
}

void AUserLayerItemMng::deleteId(const QString& uid)
{

	qDebug() << "UserLayerItem delete........";
	int i = findIndex(uid);
	if (i >= 0) {
		_list.remove(i);
	}
}

void AUserLayerItemMng::changeName(const QString& oldid, const QString& newid)
{
	AUserLayerId* layerid = find(oldid);
	if (layerid != NULL) {
		layerid->id = newid;
	}
}

QString AUserLayerItemMng::nextIdName()
{
	int i = _list.count() + 1;
	while(i<(i+10000)) {
		QString newid = QString("U-%1").arg(i);
		AUserLayerId* p = find(newid);
		if(p == NULL) {
			return newid;
		}
		i++;
	}
	return QString("Error");
}

/**
 * list에 ID와 표시여부를 : 로 묶어서 추가한다.
 */
void AUserLayerItemMng::fillId(QStringList& list)
{
	for (int i=0; i<_list.count(); i++) {
		AUserLayerItem* item = _list[i];
		AUserLayerId* layerid = item->getUserLayer();

		if (layerid->visible) {
			list.append(QString("%1:1").arg(layerid->id));
		}else {
			list.append(QString("%1:0").arg(layerid->id));
		}
	}
}

void AUserLayerItemMng::fillIdType(QStringList& list)
{
	for (int i=0; i<_list.count(); i++) {
		AUserLayerItem* item = _list[i];
		AUserLayerId* layerid = item->getUserLayer();

		list.append(QString("%1:%2").arg(layerid->id).arg(layerid->drawtype));
	}
}

void AUserLayerItemMng::setAllIdVisible(bool b)
{
	for (int i=0; i<_list.count(); i++) {
		AUserLayerItem* item = _list[i];
		AUserLayerId* layerid = item->getUserLayer();

		layerid->visible = b;
	}
}

QString AUserLayerItemMng::drawType(const QString& idName)
{
	AUserLayerId* layerid = find(idName);
	if (layerid != NULL) {
		return layerid->drawtype;
	}
	return QString("");
}

QString AUserLayerItemMng::attr(const QString& idName)
{
	AUserLayerId* layerid = find(idName);
	if (layerid != NULL) {
		return layerid->attr;
	}
	return QString("");
}

void AUserLayerItemMng::setAttr(const QString& id, const QString& attr)
{
	AUserLayerId* layerid = find(id);
	if (layerid != NULL) {
		layerid->attr = attr;
	}
}

void AUserLayerItemMng::setIdVisible(const QString& id, bool b)
{
	AUserLayerId* layerid = find(id);
	if (layerid != NULL) {
		layerid->visible = b;
	}
}



void AUserLayerItemMng::drawSelected(AirDraw* ad, QPainter* painter, const QString& selectedUid)
{
	AUserLayerId* layerid = find(selectedUid);
	if (layerid == NULL) return;
	LatLonConvert* vp = ad->viewport();

	QVector<QPoint> dataxy;
	AUserbndry* bndry;
	QString tp = layerid->drawtype;

	if (tp == "C") {	// Circle
		bndry = layerid->bndrylist[0];
		int w = (int)vp->meterToPixel(UnitChange::haeriToMeter(bndry->arc_dist))/2;
		QPoint center, p1, p2;
		center = vp->latlonToScreen(bndry->latlon.p);
		p1 = QPoint(center.x() - w, center.y() - w);
		p2 = QPoint(center.x() + w, center.y() + w);
		dataxy.append(p1);
		dataxy.append(p2);
	}else if(tp == "S") {	// Symbol
		bndry = layerid->bndrylist[0];
		QPoint center, p1, p2;
		center = vp->latlonToScreen(bndry->latlon.p);
		p1 = QPoint(center.x() - 5, center.y() - 5);
		p2 = QPoint(center.x() + 5, center.y() + 5);
		dataxy.append(p1);
		dataxy.append(p2);
	}else if(tp == "A" && layerid->bndrylist.size() == 2) { 	// Arc
		bndry = layerid->bndrylist[0];
		QPoint center, p2;
		center = vp->latlonToScreen(bndry->latlon.p);
		bndry = layerid->bndrylist[1];
		p2 = vp->latlonToScreen(bndry->latlon.p);

		int w = qMax(center.x(), p2.x()) - qMin(center.x(), p2.x());
		int h = qMax(center.y(), p2.y()) - qMin(center.y(), p2.y());
		QRect rect = QRect(center.x() - w, center.y() - h, w*2, h*2);
		dataxy.append(rect.topLeft());
		dataxy.append(rect.bottomRight());
	}else {
		for (int j=0; j<layerid->bndrylist.size(); j++) {
			bndry = layerid->bndrylist[j];
			QPoint p;
			p = vp->latlonToScreen(bndry->latlon.p);
			dataxy.append(p);
		}
	}
	ad->drawSelectedRect(painter, dataxy);
}

QString AUserLayerItemMng::selectWithMousePosition(AirDraw* ad, QPoint mouseP) const
{
	LatLonConvert* vp = ad->viewport();
	QVector<QPoint> dataxy;
	for (int i=0; i<_list.size(); i++) {
		AUserLayerItem* item = _list[i];
		AUserLayerId* layerid = item->getUserLayer();

		QString tp = layerid->drawtype;
		dataxy.clear();
		QRect rect;
		for (int j=0; j<layerid->bndrylist.size(); j++) {
			AUserbndry* bndry = layerid->bndrylist[j];
			QPoint mxy = vp->latlonToScreen(bndry->latlon.p);
			if (bndry->bndry_via == QChar('C')) {
				int w = (int)vp->meterToPixel(UnitChange::haeriToMeter(bndry->arc_dist))/2;
				QPoint mxy1 = QPoint(mxy.x() - w, mxy.y() - w);
				dataxy.append(mxy1);
				QPoint mxy2 = QPoint(mxy.x() + w, mxy.y() + w);
				dataxy.append(mxy2);
			}else if(bndry->bndry_via == QChar('S')) {
				QPoint mxy1 = QPoint(mxy.x() - 5, mxy.y() - 5);
				dataxy.append(mxy1);
				QPoint mxy2 = QPoint(mxy.x() + 5, mxy.y() + 5);
				dataxy.append(mxy2);
			}else {
				dataxy.append(mxy);
			}
		}
		// Arc는 커다란 사각형으로 선택한다.
		if (tp == "A" && dataxy.count() == 2) {
			QPoint center = dataxy[0];
			QPoint p2 = dataxy[1];
			int w = qMax(center.x(), p2.x()) - qMin(center.x(), p2.x());
			int h = qMax(center.y(), p2.y()) - qMin(center.y(), p2.y());
			QRect rect = QRect(center.x() - w, center.y() - h, w*2, h*2);
			dataxy.clear();
			dataxy.append(rect.topLeft());
			dataxy.append(rect.bottomRight());
		}
		if (ad->findWithMouse(tp, dataxy, mouseP)) {
			return layerid->id;
		}
	}
	return QString("");
}
