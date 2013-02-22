/*
 * AUserLayerItem.cpp
 *
 *  Created on: 2012. 2. 22.
 *      Author: HIST002
 */

#include "AUserLayerItem.h"


void AUserLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (layerVisible() == false) return;



	QVector<CartesianXY> dataxy;
	LatLonBound bound;
	LatLonConvert* vp = ad->viewport();

	// User map
	//for (int i=0; i<_list.size(); i++) {
		AUserLayerId* layerid = userLayer;  //_list[i];
		if (layerid->visible == false) return;
		dataxy.clear();
		bound.initialize();
		QString line = QString("LAYER:%1:%2").arg(layerid->id).arg(layerid->attr);
		LayerProperty property(line);

		for (int j=0; j<layerid->bndrylist.size(); j++) {
			AUserbndry* bndry = layerid->bndrylist[j];
			CartesianXY cxy;
			cxy.bndry_via = bndry->bndry_via;
			QPoint visualpoint = vp->latlonToScreen(bndry->latlon.p);
			cxy.mxy = visualpoint;
			cxy.xyz = vp->cartesian();
			bound.setPosition(cxy.mxy);
			cxy.lat = bndry->latlon.p.x();
			cxy.lon = bndry->latlon.p.y();
			if (bndry->bndry_via == QChar('C')) {
				cxy.mxy = visualpoint;
				cxy.arc_centerxy = visualpoint;
				cxy.arc_dist = (bndry->arc_dist);
			}else if(bndry->bndry_via == QChar('L') || bndry->bndry_via == QChar('R')) {
				cxy.arc_centerxy = vp->latlonToScreen(bndry->arc_center_latlon.p);
				cxy.arc_dist = bndry->arc_dist;
				cxy.arc_bearing = bndry->arc_bearing;
			}else if(bndry->bndry_via == QChar('A')) {
				cxy.arc_centerxy = vp->latlonToScreen(bndry->arc_center_latlon.p);
				cxy.arc_dist = bndry->arc_dist;
				cxy.arc_bearing = bndry->arc_bearing;
				bound.setPosition(cxy.arc_centerxy);
			}
			dataxy.append(cxy);
		}

		if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면..
			painter->setBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
		}
		if (bound.inRect(vp->srcRect()) && dataxy.size() > 0) {
			if (layerid->drawtype == QChar('L')) {
				painter->setPen(property.getPen());
				ad->drawUserLine(painter, dataxy);
			}else if(layerid->drawtype == QChar('C')) {
				painter->setPen(property.getPen());
				painter->setBrush(property.getBrush());
				if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면..
					painter->setBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
				}
				ad->drawUserCircle(painter, dataxy);
			}else if(layerid->drawtype == QChar('E')) {
				painter->setPen(property.getPen());
				painter->setBrush(property.getBrush());
				if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면..
					painter->setBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
				}
				ad->drawUserEllipse(painter, dataxy);
			}else if(layerid->drawtype == QChar('R')) {
				painter->setPen(property.getPen());
				painter->setBrush(property.getBrush());
				if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면..
					painter->setBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
				}
				ad->drawUserRectangle(painter, dataxy);
			}else if(layerid->drawtype == QChar('P')) {
				painter->setPen(property.getPen());
				painter->setBrush(property.getBrush());
				if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면..
					painter->setBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
				}
				ad->drawPath3(painter, dataxy, QChar('P'));
			}else if(layerid->drawtype == QChar('G')) {
				painter->setPen(property.getPen());
				painter->setBrush(property.getBrush());
				if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면..
					painter->setBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
				}
				ad->drawPath(painter, dataxy, QChar('G'));
			}else if(layerid->drawtype == QChar('T')) {
				QString str = property.getSymbol();
				painter->setPen(property.fontColor());
				painter->setFont(property.getFont());
				ad->drawUserText(painter, dataxy, str);
			}else if(layerid->drawtype == QChar('S')) {  // symbol
				QString filename = QString("%1/%2").arg(_symboldir).arg(property.getSymbol());
				if (QFile::exists(filename)) {
					ad->drawUserSymbol(painter, dataxy, filename);
				}else {
					logprint(QString("user symbol %1 is not found").arg(filename));
				}
			}else if(layerid->drawtype == QChar('A')) {	// Arc
				painter->setPen(property.getPen());
				if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면..
					painter->setBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
				}
				ad->drawUserArc(painter, dataxy);
			}else {
				;
			}

			if (textVisible() == true) {
				QPoint c = bound.center();
				painter->setPen(Qt::white);
				ad->drawTextAtCenter(painter, c, layerid->id);
				painter->setPen(_lp.getPen());
			}
		}
	//}
}

void AUserLayerItem::updateInfo()
{
	prepareGeometryChange();
}
QRectF AUserLayerItem::boundingRect() const
{
	AUserLayerId* layerid = userLayer;
	QString tp = layerid->drawtype;
	QRect rect;
	QVector<QPoint> dataxy;
	dataxy.clear();
	LatLonConvert* vp = ad->viewport();

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
	if (tp == "A" && dataxy.count() == 2)
	{
		QPoint center = dataxy[0];
		QPoint p2 = dataxy[1];
		int w = qMax(center.x(), p2.x()) - qMin(center.x(), p2.x());
		int h = qMax(center.y(), p2.y()) - qMin(center.y(), p2.y());
		QRect rect2 = QRect(center.x() - w, center.y() - h, w*2, h*2);
		dataxy.clear();
		dataxy.append(rect2.topLeft());
		dataxy.append(rect2.bottomRight());
	}

	rect.setTopLeft(dataxy[0]);
	rect.setBottomRight(dataxy[1]);

	//_log->print(QString("BoundingRect : (width, height) = (%1, %2)").arg(rect.width()).arg(rect.height()));

	//_log->print(QString("bound Rect width : %1").arg(rect.width()));

	return rect;
}

void AUserLayerItem::updateMove(QPoint center)
{
	QChar dt = userLayer->drawtype;
	LatLonConvert* vp = ad->viewport();


	QRect rect = boundingRect().toRect();
	QRect prev_rect = rect;

	rect.moveCenter(center);


	if (dt == QChar('L') || dt == QChar('R') || dt == QChar('E') || dt == QChar('T')) {
		AUserbndry* bndry1 = new AUserbndry;
		AUserbndry* bndry2 = new AUserbndry;
		QPoint p1 = rect.topLeft();
		QPoint p2 = rect.bottomRight();

		_log->print(QString("Rect width : %1").arg(rect.width()));

		QString s1 = vp->screenToLatLon(p1);
		QString s2 = vp->screenToLatLon(p2);

		bndry1->latlon.lat = s1.left(9);
		bndry1->latlon.lon = s1.right(10);
		bndry1->latlon.p = vp->screenToDecimal(p1);
		bndry1->bndry_via = QChar('G');
		userLayer->bndrylist.replace(0, bndry1);  //.append(bndry1);

		bndry2->latlon.lat = s2.left(9);
		bndry2->latlon.lon = s2.right(10);
		bndry2->latlon.p = vp->screenToDecimal(p2);
		bndry2->bndry_via = QChar('G');
		userLayer->bndrylist.replace(1, bndry2);  // .append(bndry2);
	}else if(dt == QChar('C')) {
		AUserbndry* bndry1 = new AUserbndry;
		QPoint centerPoint = rect.center();
		QString centerLatLon = vp->screenToLatLon(centerPoint);		// center
		// 지름을 넣는다.
		double d_meter_radius = vp->pixelToMeter(rect.width());
		double d_haeri = UnitChange::meterToHaeri(d_meter_radius);

		bndry1->latlon.lat = centerLatLon.left(9);
		bndry1->latlon.lon = centerLatLon.right(10);
		bndry1->latlon.p = vp->screenToDecimal(centerPoint.x(), centerPoint.y());
		bndry1->arc_center_latlon.lat = centerLatLon.left(9);
		bndry1->arc_center_latlon.lon = centerLatLon.right(10);
		bndry1->arc_center_latlon.p = vp->screenToDecimal(centerPoint.x(), centerPoint.y());
		bndry1->arc_dist = d_haeri;
		bndry1->bndry_via = QChar('C');

		userLayer->bndrylist.replace(0, bndry1);   // .append(bndry1);
	}else if(dt == QChar('P') || dt == QChar('G')) {
		// 포인트 보정
		// 사각형의 중심점에 대한 크기 변화 체크
		QPoint c = prev_rect.center();	// 과거의 중심점
		QPoint absP(c.x() - rect.center().x(), c.y() - rect.center().y());

		for (int i=0; i<userLayer->bndrylist.count(); i++) {
			AUserbndry* bndry = userLayer->bndrylist[i];
			QPoint p = vp->latlonToScreen(bndry->latlon.p);
			p.setX(p.x() - absP.x());
			p.setY(p.y() - absP.y());
			QString s = vp->screenToLatLon(p);
			bndry->latlon.lat = s.left(9);
			bndry->latlon.lon = s.right(10);
			bndry->latlon.p = vp->screenToDecimal(p.x(), p.y());
			bndry->bndry_via = QChar('G');
			userLayer->bndrylist.replace(i, bndry);
		}

	}else if(dt == QChar('S')) {	// symbol
		QPoint p1 = rect.center();
		QString s1 = vp->screenToLatLon(p1);

		AUserbndry* bndry1 = new AUserbndry;
		bndry1->latlon.lat = s1.left(9);
		bndry1->latlon.lon = s1.right(10);
		bndry1->latlon.p = vp->screenToDecimal(p1.x(), p1.y());
		bndry1->bndry_via = QChar('S');
		userLayer->bndrylist.replace(0,bndry1);

#ifndef QT_NO_DEBUG
		_log->print(QString("symbol finished : %1").arg(bndry1->bndry_via));
#endif
	}else if(dt == QChar('A')) {		// Arc
		// 포인트 보정
		// 사각형의 중심점에 대한 크기 변화 체크
		QPoint c = center;	// 과거의 중심점
		QPoint absP(c.x() - rect.center().x(), c.y() - rect.center().y());
		for (int i=0; i<userLayer->bndrylist.count(); i++) {
			AUserbndry* bndry = userLayer->bndrylist[i];
			QPoint p = vp->latlonToScreen(bndry->latlon.p);
			p.setX(p.x() - absP.x());
			p.setY(p.y() - absP.y());
			QString s = vp->screenToLatLon(p);
			bndry->latlon.lat = s.left(9);
			bndry->latlon.lon = s.right(10);
			bndry->latlon.p = vp->screenToDecimal(p.x(), p.y());
			bndry->arc_center_latlon.lat = s.left(9);
			bndry->arc_center_latlon.lon = s.right(10);
			bndry->arc_center_latlon.p = vp->screenToDecimal(p.x(), p.y());
			bndry->bndry_via = QChar('A');
			//bndry->arc_bearing = ud->getStartAngle();
			//bndry->arc_dist = ud->getEndAngle();
			userLayer->bndrylist.replace(i, bndry);
			if (i == 1) break;
		}
	}
}

void AUserLayerItem::updateMove(QPoint center, QRect rect)
{
	QChar dt = userLayer->drawtype;
	LatLonConvert* vp = ad->viewport();




	if (dt == QChar('L') || dt == QChar('R') || dt == QChar('E') || dt == QChar('T')) {
		AUserbndry* bndry1 = new AUserbndry;
		AUserbndry* bndry2 = new AUserbndry;
		QPoint p1 = rect.topLeft();
		QPoint p2 = rect.bottomRight();

		_log->print(QString("Rect width : %1").arg(rect.width()));

		QString s1 = vp->screenToLatLon(p1);
		QString s2 = vp->screenToLatLon(p2);

		bndry1->latlon.lat = s1.left(9);
		bndry1->latlon.lon = s1.right(10);
		bndry1->latlon.p = vp->screenToDecimal(p1);
		bndry1->bndry_via = QChar('G');
		userLayer->bndrylist.replace(0, bndry1);  //.append(bndry1);

		bndry2->latlon.lat = s2.left(9);
		bndry2->latlon.lon = s2.right(10);
		bndry2->latlon.p = vp->screenToDecimal(p2);
		bndry2->bndry_via = QChar('G');
		userLayer->bndrylist.replace(1, bndry2);  // .append(bndry2);
	}else if(dt == QChar('C')) {
		AUserbndry* bndry1 = new AUserbndry;
		QPoint centerPoint = rect.center();
		QString centerLatLon = vp->screenToLatLon(centerPoint);		// center
		// 지름을 넣는다.
		double d_meter_radius = vp->pixelToMeter(rect.width());
		double d_haeri = UnitChange::meterToHaeri(d_meter_radius);

		bndry1->latlon.lat = centerLatLon.left(9);
		bndry1->latlon.lon = centerLatLon.right(10);
		bndry1->latlon.p = vp->screenToDecimal(centerPoint.x(), centerPoint.y());
		bndry1->arc_center_latlon.lat = centerLatLon.left(9);
		bndry1->arc_center_latlon.lon = centerLatLon.right(10);
		bndry1->arc_center_latlon.p = vp->screenToDecimal(centerPoint.x(), centerPoint.y());
		bndry1->arc_dist = d_haeri;
		bndry1->bndry_via = QChar('C');

		userLayer->bndrylist.replace(0, bndry1);   // .append(bndry1);
	}else if(dt == QChar('P') || dt == QChar('G')) {
		// 포인트 보정
		// 사각형의 중심점에 대한 크기 변화 체크
		QPoint c = center;	// 과거의 중심점
		QPoint absP(c.x() - rect.center().x(), c.y() - rect.center().y());
		for (int i=0; i<userLayer->bndrylist.count(); i++) {
			AUserbndry* bndry = userLayer->bndrylist[i];
			QPoint p = vp->latlonToScreen(bndry->latlon.p);
			p.setX(p.x() - absP.x());
			p.setY(p.y() - absP.y());
			QString s = vp->screenToLatLon(p);
			bndry->latlon.lat = s.left(9);
			bndry->latlon.lon = s.right(10);
			bndry->latlon.p = vp->screenToDecimal(p.x(), p.y());
			bndry->bndry_via = QChar('G');
			userLayer->bndrylist.replace(i, bndry);
		}

	}else if(dt == QChar('S')) {	// symbol
		QPoint p1 = rect.center();
		QString s1 = vp->screenToLatLon(p1);

		AUserbndry* bndry1 = new AUserbndry;
		bndry1->latlon.lat = s1.left(9);
		bndry1->latlon.lon = s1.right(10);
		bndry1->latlon.p = vp->screenToDecimal(p1.x(), p1.y());
		bndry1->bndry_via = QChar('S');
		userLayer->bndrylist.replace(0,bndry1);

#ifndef QT_NO_DEBUG
		_log->print(QString("symbol finished : %1").arg(bndry1->bndry_via));
#endif
	}else if(dt == QChar('A')) {		// Arc
		// 포인트 보정
		// 사각형의 중심점에 대한 크기 변화 체크
		QPoint c = center;	// 과거의 중심점
		QPoint absP(c.x() - rect.center().x(), c.y() - rect.center().y());
		for (int i=0; i<userLayer->bndrylist.count(); i++) {
			AUserbndry* bndry = userLayer->bndrylist[i];
			QPoint p = vp->latlonToScreen(bndry->latlon.p);
			p.setX(p.x() - absP.x());
			p.setY(p.y() - absP.y());
			QString s = vp->screenToLatLon(p);
			bndry->latlon.lat = s.left(9);
			bndry->latlon.lon = s.right(10);
			bndry->latlon.p = vp->screenToDecimal(p.x(), p.y());
			bndry->arc_center_latlon.lat = s.left(9);
			bndry->arc_center_latlon.lon = s.right(10);
			bndry->arc_center_latlon.p = vp->screenToDecimal(p.x(), p.y());
			bndry->bndry_via = QChar('A');
			//bndry->arc_bearing = ud->getStartAngle();
			//bndry->arc_dist = ud->getEndAngle();
			userLayer->bndrylist.replace(i, bndry);
			if (i == 1) break;
		}
	}

	//update();
}
