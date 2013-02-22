/*
 * AirDraw.cpp
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */
#include <iostream>
#include <math.h>
#include <QPoint>
#include <QRect>
#include <QVector>
#include <QFile>
#include "AirDraw.h"

void AirDraw::drawNumber1(QPainter* painter, const QPoint& p, double d)
{
	drawText1(painter, p, QString("%1").arg(d, 7, 'f', 3));
}

void AirDraw::drawText1(QPainter* painter, const QPoint& p, const QString& text)
{
	QRect textbox;		// 숫자를 그릴 박스
	QString text2 = text.trimmed();
	painter->setFont(QFont("Times", 8));
	textbox.setRect(p.x(), p.y(), 10*text2.length(), 10);
	painter->drawText(textbox, Qt::AlignLeft|Qt::AlignVCenter, text2);
}

void AirDraw::drawTextAtCenter(QPainter* painter, const QPoint& c, const QString& text)
{
	QRect textbox;		// 숫자를 그릴 박스
	QString text2 = text.trimmed();
	painter->setFont(QFont("Times", 8));

	QFontMetrics m = painter->fontMetrics();
	QRect rect1 = m.boundingRect(text2);
	textbox = QRect(c.x() - rect1.width() / 2, c.y() - rect1.height()/2, rect1.width(), rect1.height());

	painter->drawText(textbox, Qt::AlignLeft | Qt::AlignVCenter, text2);
}

// polyline = coast
void AirDraw::drawLine2(QPainter* painter, QVector<CartesianXY> &dataxy)
{
	bool prev_visible, prev_inrect;
	bool now_visible, now_inrect;

	int index = 0;

	if (dataxy.count() < 2) {
		return;
	}

	QVector<QPoint> data2;

	Cartesian prev_cartesian, now_cartesian;
	QPoint prev_xy, now_xy;

	prev_xy = dataxy[0].mxy;
	prev_cartesian = dataxy[0].xyz;
	index = 1;
	while(index < dataxy.count()) {
		now_xy = dataxy[index].mxy;
		now_cartesian = dataxy[index].xyz;

		prev_visible = (prev_cartesian.x < 0) ? false : true;
		now_visible = (now_cartesian.x < 0) ? false : true;
		prev_inrect = (vp->srcRect().contains(prev_xy)) ? true : false;
		now_inrect = (vp->srcRect().contains(now_xy)) ? true : false;

		if (prev_cartesian.x < 0 && now_cartesian.x < 0) {
			prev_xy = now_xy;
			prev_cartesian = now_cartesian;
			index++;
			continue;
		}

		if (prev_inrect == false && now_inrect == false) {
			if (gu.isIntersect(vp->srcRect(), prev_xy, now_xy) == 1) {
				data2.append(prev_xy);
				data2.append(now_xy);
				QPolygon latPoints(data2.count());
				for (int i=0; i<data2.count(); i++) {
					latPoints[i] = data2[i];
				}
				painter->drawPolyline(latPoints);
				data2.clear();
			}else {
				///
			}
		}else if(prev_inrect == false && now_inrect == true) {  // 안으로 들어옴
			data2.append(prev_xy);
		}else if(prev_inrect == true && now_inrect == true) {
			data2.append(prev_xy);
		}else if(prev_inrect == true && now_inrect == false) {
			data2.append(prev_xy);
			data2.append(now_xy);
			QPolygon latPoints(data2.count());
			for (int i=0; i<data2.count(); i++) {
				latPoints[i] = data2[i];
			}
			painter->drawPolyline(latPoints);
			data2.clear();
		}else {
			//
		}
		prev_xy = now_xy;
		prev_cartesian = now_cartesian;
		index++;
	}
	if (data2.count() > 1) {
		data2.append(now_xy);
		QPolygon latPoints(data2.count());
		for (int i=0; i<data2.count(); i++) {
			latPoints[i] = data2[i];
		}
		painter->drawPolyline(latPoints);
	}
}

// for latlon
bool AirDraw::drawLine3(QPainter* painter, QVector<QPoint>& dataxy)
{
	bool prev_inrect = false;
	bool now_inrect = false;

	int index = 0;
	bool drawed = false;

	if (dataxy.count() < 2) {
		return false;
	}
	QVector<QPoint> data2;

	QPoint prev_xy, now_xy;

	prev_xy = dataxy[0];
	index = 1;

	drawCount = 0;
	drawStartPoint = QPoint(-1, -1);
	drawEndPoint = QPoint(-1, -1);

	while(index < dataxy.count()) {
		now_xy = dataxy[index];

		prev_inrect = (vp->srcRect().contains(prev_xy)) ? true : false;
		now_inrect  = (vp->srcRect().contains(now_xy)) ? true : false;

		if (prev_inrect == false && now_inrect == false) {
			prev_xy = now_xy;
			index++;
			continue;
		}else if(prev_inrect == false && now_inrect == true) {	// 안으로 들어옴
			data2.append(prev_xy);
			data2.append(now_xy);
		}else if(prev_inrect == true && now_inrect == true) {
			data2.append(prev_xy);
		}else if(prev_inrect == true && now_inrect == false) {	// 밖으로 나오는 것
			data2.append(prev_xy);
			data2.append(now_xy);
			break;
		}
		prev_xy = now_xy;
		index++;
	}
	if (now_inrect == true) {
		data2.append(now_xy);
	}
	if (data2.count() > 1) {
		drawed          = true;
		drawCount       = data2.count();
		drawStartPoint  = data2[1];
		drawEndPoint    = data2[drawCount-1];
		drawCenterPoint = data2[0];
		QPolygon latPoints(data2.count());
		for (int i=0; i<data2.count(); i++) {
			latPoints[i] = data2[i];
		}
		painter->drawPolyline(latPoints);
	}
	return drawed;
}

/**
 * 맵 상단 왼쪽편에 원점과 픽셀당 크기를 텍스트로 입력한다.
 */
void AirDraw::displayViewPortInfo(QPainter* painter)
{
	QString wonjum = QString("WJ:%1,%2").arg(vp->wonjum().x(), 7, 'f', 3)
			.arg(vp->wonjum().y(), 7, 'f', 3);
	painter->setPen(QPen(Qt::white, 1));
	drawText1(painter, QPoint(10, 10), QString("%1 ").arg(wonjum.trimmed()));
	drawText1(painter, QPoint(10, 20), QString("%1 m/px").arg((int)vp->mpp()));
}

// compass bearing draw
void AirDraw::drawBearingCircle(QPainter* painter)
{
	drawBearingCircle(painter, Qt::blue, Qt::red);
}

void AirDraw::drawBearingCircle(QPainter* painter, const QColor& circle_color, const QColor& text_color)
{
	// CalcAir ca;
	Turtle turtle;
	int box_h = 10;
	int box_w = 20;

	QString turtlecmds[24] = {
			"L10", "L10", "L10", "L10", 		 // 0, 15, 30, 45
			"L15", "L20,U5", "L15,U5", "L20,U5", // 60, 75, 90, 105
			"L20,U5", "L20,U5", "L10,U10", "L10,U10", // 120, 135, 150, 165
			"L10,U10", "L10,U10", "L10,U10", "L8,U10", // 180, 195, 210, 225
			"U5", "U5", "U5", "U4", 	// 240, 255, 270, 285
			"U5", "U5", "L10", "L10"	// 300, 315, 330, 345
	};
	int r = qMin(vp->srcWidth(), vp->srcHeight()) / 2;

	QPoint center = vp->screenCenter();
	QRect  rect = QRect(center.x() - r, center.y() - r, r*2, r*2);

	painter->setPen(QPen(circle_color, 1));
	painter->drawEllipse(rect);

	painter->setPen(QPen(text_color, 1));

	QRect textbox;		// 숫자를 그릴 박스
	painter->setFont(QFont("Times", 8));
	for (int i=0,j=0; i<360; i+=15) {
		int x1 = (int)floor(r*0.98 * sin(ca.toRad(i)));
		int y1 = (int)floor(r*0.98 * cos(ca.toRad(i)));
		int x2 = (int)floor(r * sin(ca.toRad(i)));
		int y2 = (int)floor(r * cos(ca.toRad(i)));
		QPoint point1 = QPoint(center.x() + x1, center.y() - y1);
		QPoint point2 = QPoint(center.x() + x2, center.y() - y2);
		painter->drawLine(point1, point2);
		turtle.setPoint(point1);
		turtle.moveCommand(turtlecmds[j++]);
		textbox.setRect(turtle.x(), turtle.y(), box_w, box_h);

		painter->drawText(textbox, Qt::AlignHCenter | Qt::AlignVCenter, QString("%1").arg(i));
	}
}

// This method paint Cross line.
void AirDraw::drawCross(QPainter* painter)
{
	drawCross(painter, Qt::darkRed);
}
// This method paint Cross line with the color
void AirDraw::drawCross(QPainter* painter, const QColor& color)
{
	painter->setPen(QPen(color, 1));
	QPoint p1, p2;
	p1 = QPoint(0, vp->srcHeight()/2);
	p2 = QPoint(vp->srcWidth(), vp->srcHeight()/2);
	painter->drawLine(p1, p2);

	p1 = QPoint(vp->srcWidth()/2, 0);
	p2 = QPoint(vp->srcWidth()/2, vp->srcHeight());
	painter->drawLine(p1, p2);
}

void AirDraw::drawLatLon1Text(QPainter* painter, double latlon, int type)
{
	QString s;
	QPoint p;
	switch(latlonTextMode) {
	case Center :
		if ((type % 2) == 1) return;
		p = drawStartPoint;
		break;
	case TwoEdge:
		p = drawEndPoint;
		break;
	case LeftEdge:
		if (type % 2 == 1) return;
		p = drawEndPoint;
		break;
	case RightEdge :
		if (type % 2 == 0) return;
		p = drawEndPoint;
		break;
	default:
		return;
	}

	s = QString("%1").arg(latlon, 7, 'f', 1);
	int textLength = 30;
	int textHeight = 10;
	if (p.x() < 0) p.setX(1);
	if (p.x() > (vp->srcWidth() - textLength)) p.setX(vp->srcWidth() - textLength);

	if (p.y() < 0) p.setY(1);
	if (p.y() > vp->srcHeight() - textHeight) p.setY(vp->srcHeight() - textHeight);

	drawText1(painter, p, QString("[%1]").arg(s.trimmed()));
}

void AirDraw::drawLatLines(QPainter* painter)
{
	log = NULL;

	QVector<double> drawedLines;
	double last = 0;		// last line

	// latitude - longitude
	double dy = vp->mppToDegree();		// 경위도의 변화정도
	double wj = vp->north();
	double dw = vp->baseWJ(wj, dw);

	// paint latitude
	double lat = dw + dy;
	if (log != NULL) log->print(QString(">>>> dy:%1,wj:%2,dw:%3,lat:%4").arg(dy).arg(wj).arg(dw).arg(lat));

	NorthGreenichPoint baseNGP;
	baseNGP.set(lat, vp->greenich());

	double topNorth = vp->topNorth();
	double bottomNorth = vp->bottomNorth();

	// 위쪽으로 위도 그리기
	drawedLines.clear();
	if (log != NULL) log->print(QString("lat draw start to %1 -> %2").arg(baseNGP.north()).arg(topNorth));

	double distance = topNorth - baseNGP.north();
	if (topNorth < baseNGP.north()) distance += 360;

	while(distance >= 0) {
		lat = baseNGP.lat();
		if (drawedLines.indexOf(lat) < 0) {
			drawLat1(painter, lat);
			drawedLines.append(lat);
			if (log != NULL) log->print(QString("lower draw lat: %1").arg(lat));
		}
		last = baseNGP.north();
		baseNGP.moveNorth(dy);
		distance -= dy;
	}

	// 아랫쪽으로 위도 그리기
	baseNGP.set(dw, vp->greenich());
	if (log != NULL) log->print(QString("lat draw start to %1->%2").arg(baseNGP.north()).arg(bottomNorth));
	distance = baseNGP.north() - bottomNorth;
	if (bottomNorth > baseNGP.north()) distance += 360;

	while(distance >= 0) {
		lat = baseNGP.lat();
		if (drawedLines.indexOf(lat) < 0) {
			drawLat1(painter, lat);
			drawedLines.append(lat);
			if (log != NULL) log->print(QString("lower draw lat : %1").arg(lat));
		}
		baseNGP.moveSouth(dy);
		distance -= dy;
	}
}

void AirDraw::drawLonLines(QPainter* painter)
{
	double dy = vp->mppToDegree();		// 경위도의 변화정도

	// 경도 그리기
	double wj = vp->greenich();
	double dw = vp->baseWJ(wj, dy);

	double lon = dw + dy;

	NorthGreenichPoint baseNGP;
	baseNGP.set(vp->north(), lon);

	double leftGreenich = vp->leftGreenich();
	double rightGreenich = vp->rightGreenich();

	// 오른쪽으로 경도 그리기
	double distance = rightGreenich - baseNGP.greenich();
	if (rightGreenich < baseNGP.greenich()) distance += 360;

	while(distance >= 0) {
		lon = baseNGP.lon();
		drawLon1(painter, lon);

		baseNGP.moveEast(dy);
		distance -= dy;
	}

	baseNGP.set(vp->north(), dw);

	// 왼쪽으로 경도 그리기
	distance = baseNGP.greenich() - leftGreenich;
	if (leftGreenich > baseNGP.greenich()) distance += 360;

	while(distance >= 0) {
		lon = baseNGP.lon();
		drawLon1(painter, lon);

		baseNGP.moveWest(dy);
		distance -= dy;
	}
}

void AirDraw::drawLatLon1(QPainter *painter)
{
	drawLonLines(painter);
	drawLatLines(painter);

	// Circle
	if (vp->isGu()) {
		QPoint center = vp->screenCenter();
		int r2 = (int)vp->pixelRadius();
		QRect rect = QRect(center.x() - r2, center.y() - r2, r2 * 2, r2 * 2);
		painter->drawEllipse(rect);
	}
}

void AirDraw::drawLon1(QPainter* painter, double lon)
{
	// Make points
	QVector<QPoint> datas;
	QRect textbox1;

	datas.clear();

	double dy = vp->mppToDegree();
	if (dy > 1) { dy = 1; }

	NorthGreenichPoint baseNGP(vp->north(), vp->greenich());

	double top = vp->topNorth() + dy;
	double bottom = vp->bottomNorth() - dy;

	// 위쪽으로
	double distance = top - baseNGP.north();
	if (baseNGP.north() > top) distance += 360;

	while(distance >= 0) {
		QPoint logic_scr = vp->latlonToScreen(QPointF(baseNGP.lat(), lon));

		Cartesian c = vp->cartesian();
		if (c.x >= 0) {
			datas.append(logic_scr);
		}else {
			if (datas.count() > 1) {
				drawLine3(painter, datas);
				if (drawCount > 0) drawLatLon1Text(painter, lon, 10);
			}
			if (datas.count() > 0) datas.clear();
		}
		baseNGP.moveNorth(dy);
		distance -= dy;
	}

	if (datas.count() > 1) {
		drawLine3(painter, datas);
		if (drawCount > 0) drawLatLon1Text(painter, (lon), 10);
	}
	datas.clear();

	baseNGP.set(vp->north(), vp->greenich());

	distance = baseNGP.north() - bottom;
	if (distance < 0) distance += 360;

	while(distance >= 0) {
		QPoint logic_scr = vp->latlonToScreen(QPointF(baseNGP.lat(), lon));
		Cartesian c = vp->cartesian();
		if (c.x >= 0) {
			datas.append(logic_scr);
		}else {
			if (datas.count() > 1) {
				drawLine3(painter, datas);
				if (drawCount > 0) drawLatLon1Text(painter, (lon), 11);
			}
			if (datas.count() > 0) datas.clear();
		}
		baseNGP.moveSouth(dy);
		distance -= dy;
	}

	if (datas.count() > 1) {
		drawLine3(painter, datas);
		if (drawCount > 0) drawLatLon1Text(painter, lon, 11);
	}
}

void AirDraw::drawLat1(QPainter* painter, double lat)
{
	QVector<QPoint> datas;

	double dy = vp->mppToDegree();

	if (dy > 1) { dy = 1; }

	NorthGreenichPoint baseNGP;
	baseNGP.set(vp->north(), vp->greenich());
	double left = vp->leftGreenich();
	double right = vp->rightGreenich();

	double distance = right - baseNGP.greenich();
	if (distance < 0) distance += 360;

	while(distance >= 0) {
		QPoint logic_scr = vp->latlonToScreen(QPointF(lat, baseNGP.lon()));
		if (vp->cartesian().x >= 0) {
			datas.append(logic_scr);
		}else {
			if (datas.count() > 1) {
				drawLine3(painter, datas);
				if (drawCount > 0) drawLatLon1Text(painter, lat, 20);
			}
			if (datas.count() > 0) datas.clear();
		}
		baseNGP.moveEast(dy);
		distance -= dy;
	}
	if (datas.count() > 1) {
		drawLine3(painter, datas);
		if (drawCount > 0) drawLatLon1Text(painter, lat, 20);
	}
	datas.clear();
	baseNGP.set(vp->north(), vp->greenich());
	distance = baseNGP.greenich() - left;
	if (distance < 0) distance += 360;
	while(distance >= 0) {
		QPoint logic_scr = vp->latlonToScreen(QPointF(lat, baseNGP.lon()));
		if (vp->cartesian().x >= 0) {
			datas.append(logic_scr);
		}else {
			if (datas.count() > 1) {
				drawLine3(painter, datas);
				if (drawCount > 0) drawLatLon1Text(painter, lat, 2);
			}
			if (datas.count() > 0) datas.clear();
		}
		baseNGP.moveWest(dy);
		distance -= dy;
	}
	if (datas.count() > 1) {
		drawLine3(painter, datas);
		if (drawCount > 0) drawLatLon1Text(painter, lat, 2);
	}
}

void AirDraw::drawRway(QPainter* painter, const QPoint& p1, const QPoint& p2)
{
	painter->drawLine(p1, p2);
}

void AirDraw::drawAirCircle(QPainter* painter, const QPoint& p, double radius)
{
	QPoint intP1 = p;
	double meter = UnitChange::haeriToMeter(radius);		// Haeri radius * 1855.325 => meter

	int dist_pixel = (int) vp->meterToPixel(meter);
	QRect rect = QRect(intP1.x() - (dist_pixel/2), intP1.y() - (dist_pixel/2), dist_pixel, dist_pixel);   // dist_pixel : 원의 지름

	painter->drawEllipse(rect);
}

void AirDraw::drawAirPolygon(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	QPolygon latPoints(dataxy.count());
	for (int i=0; i<dataxy.count(); i++) {
		latPoints[i] = dataxy[i].mxy;
	}
	painter->drawPolygon(latPoints);
}

/**
 * Polyline 을 그린후 넘어온 데이터를 clear 한다.
 */
void AirDraw::drawLineAndClear(QPainter* painter, QVector<QPoint>& points)
{
	if (points.count() < 1) return;
	QPolygon latPoints(points.count());
	//std::cout << "drawLineAndClear called............point count : " << points.count() << "\n";
	//log->print("drawLineAndClear called........point count : " + points.count());
	for (int i=0; i<points.count(); i++) {
		//log->print(QString(" point x, y ( %1, %2 ) ").arg(points[i].x()).arg(points[i].y()));
		latPoints[i] = points[i];
	}
	painter->drawPolyline(latPoints);
	points.clear();
}

void AirDraw::drawPathPolygon (QPainter* painter, QVector<CartesianXY>& dataxy)
{
	QPolygon latPoints(dataxy.count());
	for (int i=0; i<dataxy.count(); i++) {
		latPoints[i] = dataxy[i].mxy;
	}
	painter->drawPolygon(latPoints);
}

void AirDraw::drawUserLine(QPainter* painter, QVector<CartesianXY>& dataxy)
{

	if (dataxy.count() < 2) return;
	QPoint p1 = (dataxy[0].mxy);
	QPoint p2 = (dataxy[1].mxy);

	painter->drawLine(p1, p2);
}

void AirDraw::drawUserCircle(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	drawAirCircle(painter, dataxy[0].mxy, dataxy[0].arc_dist);
}

void AirDraw::drawUserEllipse(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	if (dataxy.count() < 2) return;
	QPoint p1 = (dataxy[0].mxy);
	QPoint p2 = (dataxy[1].mxy);
	QRect rect;
	rect.setTopLeft(p1);
	rect.setBottomRight(p2);
	painter->drawEllipse(rect);
}

void AirDraw::drawUserRectangle(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	if (dataxy.count() < 2) return;
	QPoint p1 = (dataxy[0].mxy);
	QPoint p2 = (dataxy[1].mxy);
	QRect rect;
	rect.setTopLeft(p1);
	rect.setBottomRight(p2);
	painter->drawRect(rect);
}

void AirDraw::drawUserPolyline(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	drawLine2(painter, dataxy);
}

void AirDraw::drawUserPolygon(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	drawAirPolygon(painter, dataxy);
}

void AirDraw::drawUserText(QPainter* painter, QVector<CartesianXY>& dataxy, const QString& str)
{
	//if (dataxy.count() < 2) return;
	QString text2 = str.trimmed();
	QPoint p1 = (dataxy[0].mxy);
	QPoint p2 = (dataxy[1].mxy);

	QFontMetrics m = painter->fontMetrics();
	QRect rect1 = m.boundingRect(text2);
	QRect rect = QRect(p1.x(), p1.y(), rect1.width(), rect1.height());

	rect1 = rect.normalized().adjusted(0, 0, -1, -1);
	painter->drawText(rect1, Qt::AlignLeft | Qt::AlignVCenter, text2);
}

void AirDraw::drawUserSymbol(QPainter* painter, QVector<CartesianXY>& dataxy, const QString& filename)
{
	QPixmap pixmap;
	if (dataxy.count() < 1) return;

	if (!QFile::exists(filename)) {
		log->print(QString("User Symbol : %1 not found").arg(filename));
		return;
	}
	pixmap.load(filename);
	QPoint p = (dataxy[0].mxy);
	QRect pixmapRect = pixmap.rect();
	QRect painterRect = QRect(p.x() - pixmapRect.width()/2, p.y()-pixmapRect.height()/2, pixmap.width(), pixmap.height());
	pixmapRect = painterRect.normalized().adjusted(0, 0, -1, -1);
	painter->drawPixmap(pixmapRect, pixmap);
}

void AirDraw::drawUserArc(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	if (dataxy.count() < 2) return;

	QPoint p0 = dataxy[0].mxy;
	QPoint p1 = dataxy[1].mxy;

	int w = p1.x() - p0.x();
	int h = p1.y() - p0.y();
	double vd_distance = vp->meterToPixel(vp->distance(p1, p0));

	// 두 선의 중점에서 반지름만큼 x, y로 이동한 점(사각형의 시작점)에서 width, height(두점사이의 거리)인 사각형
	QRect rect = QRect((p1.x() - (w/2)) - (vd_distance/2), (p1.y() - (h/2)) - (vd_distance/2), vd_distance, vd_distance);

	double startAngle = dataxy[1].arc_bearing;
	double endAngle = dataxy[1].arc_dist;
	int angle1 = (int)startAngle*16;
	int angle2 = (int)endAngle*16;

	painter->drawArc(rect, angle1, angle2);
}

void AirDraw::drawRectWithCenter(QPainter* painter, const QPoint& center, int w)
{
	QRect rect;
	QPoint p1 = QPoint(center.x() - w, center.y() - w);
	QPoint p2 = QPoint(center.x() + w, center.y() + w);
	rect.setTopLeft(p1);
	rect.setBottomRight(p2);
	painter->drawRect(rect);
}

void AirDraw::drawSelectedRect(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	QRect rect;
	QPoint minP = QPoint(INT_MAX, INT_MAX);
	QPoint maxP = QPoint(INT_MIN, INT_MIN);

	QPen pen = QPen(Qt::white);
	QBrush brush = QBrush(Qt::white, Qt::NoBrush);
	painter->setPen(pen);
	painter->setBrush(brush);

	for (int i=0; i<dataxy.count(); i++) {
		QPoint p = dataxy[i].mxy;
		minP.setX(qMin(p.x(), minP.x()));
		minP.setY(qMin(p.y(), minP.y()));
		maxP.setX(qMax(p.x(), maxP.x()));
		maxP.setY(qMax(p.y(), maxP.y()));
	}
	QPoint p1 = minP;
	QPoint p2 = QPoint(maxP.x(), minP.y());
	QPoint p3 = maxP;
	QPoint p4 = QPoint(minP.x(), maxP.y());

	drawRectWithCenter(painter, p1, 2);
	drawRectWithCenter(painter, p2, 2);
	drawRectWithCenter(painter, p3, 2);
	drawRectWithCenter(painter, p4, 2);

	// Out rect
	rect.setTopLeft(p1);
	rect.setBottomRight(p3);
	painter->drawRect(rect);
}

void AirDraw::drawSelectedRect(QPainter* painter, QVector<QPoint>& dataxy)
{
	QRect rect;
	QPoint minP = QPoint(INT_MAX, INT_MAX);
	QPoint maxP = QPoint(INT_MIN, INT_MIN);

	QPen pen = QPen(Qt::white);
	QBrush brush = QBrush(Qt::white, Qt::NoBrush);
	painter->setPen(pen);
	painter->setBrush(brush);

	for (int i=0; i<dataxy.count(); i++) {
		QPoint p = dataxy[i];
		minP.setX(qMin(p.x(), minP.x()));
		minP.setY(qMin(p.y(), minP.y()));
		maxP.setX(qMax(p.x(), maxP.x()));
		maxP.setY(qMax(p.y(), maxP.y()));
	}
	QPoint p1 = minP;
	QPoint p2 = QPoint(maxP.x(), minP.y());
	QPoint p3 = maxP;
	QPoint p4 = QPoint(minP.x(), maxP.y());

	drawRectWithCenter(painter, p1, 2);
	drawRectWithCenter(painter, p2, 2);
	drawRectWithCenter(painter, p3, 2);
	drawRectWithCenter(painter, p4, 2);

	// Out rect
	rect.setTopLeft(p1);
	rect.setBottomRight(p3);
	painter->drawRect(rect);
}

bool AirDraw::findWithMouse(const QString& tp, QVector<QPoint>& dataxy, const QPoint& mouseP)
{
	QRect rect;
	if (dataxy.count() < 2) return false;
	rect.setTopLeft(dataxy[0]);
	rect.setBottomRight(dataxy[1]);

	if (tp == "L") {
		return gu.isPickLine(rect, mouseP);
	}else if(tp == "C") {
		return gu.isPickCircle(rect, mouseP);
	}else if(tp == "R") {
		return gu.isPickRect(rect, mouseP);
	}else if(tp == "E") {
		return gu.isPickEllipse(rect, mouseP);
	}else if(tp == "T") {
		return gu.isPickText(rect, mouseP);
	}else if(tp == "P") {
		return gu.isPickPolyline(dataxy, mouseP);
	}else if(tp == "G") {
		return gu.isPickPolygon(dataxy, mouseP);
	}else if(tp == "S") {
		return gu.isPickRect(rect, mouseP);
	}else if(tp == "A") {
		return gu.isPickArc(rect, mouseP);
	}else {
		return false;
	}
}

void AirDraw::drawPathPolyline(QPainter* painter, QVector<CartesianXY>& dataxy)
{
	int step = 10;
	bool prev_inrect, now_inrect;
	QVector<QPoint> tmpdata;
	QChar bndry_via = dataxy[0].bndry_via;
	tmpdata.append(dataxy[0].mxy);

	//std::cout << "drawPathPolyline called.............\n";
	for (int i=1; i<dataxy.count(); i++) {
		if (bndry_via == QChar('H') && dataxy[i-1].lat == dataxy[i].lat) {
			// 스크린 거리가 10픽셀단위로 점을 생성
			// lineTo path에 넣는다.
			int d = dataxy[i].mxy.x() - dataxy[i-1].mxy.x();
			int makepointcnt = abs(d) / step;
			if(makepointcnt > 1) {
				double lon_d = dataxy[i].lon - dataxy[i-1].lon;
				double lon_dx = lon_d / makepointcnt;

				for (int k=1; k<makepointcnt; k++) {
					QPointF np = QPointF(dataxy[i-1].lat, dataxy[i-1].lon + (lon_dx * k));
					QPoint visualPoint = vp->latlonToScreen(np);
					tmpdata.append(visualPoint);
				}
			}
		}
		tmpdata.append(dataxy[i].mxy);
		bndry_via = dataxy[i].bndry_via;
	}

	QVector<QPoint> tmpdata2;
	prev_inrect = (vp->srcRect().contains(tmpdata[0])) ? true : false;
	for (int i=1; i<tmpdata.count(); i++) {
		now_inrect = (vp->srcRect().contains(tmpdata[i])) ? true : false;
		if (now_inrect == true) {
			if (prev_inrect == false || i == 1) {
				tmpdata2.append(tmpdata[i-1]);
			}
			tmpdata2.append(tmpdata[i]);
		}else {
			if (prev_inrect == true) {
				tmpdata2.append(tmpdata[i]);
				drawLineAndClear(painter, tmpdata2);
			}else {
				if (gu.isIntersect(vp->srcRect(), tmpdata[i-1], tmpdata[i]) == 1) {
					tmpdata2.append(tmpdata[i-1]);
					tmpdata2.append(tmpdata[i]);
					drawLineAndClear(painter, tmpdata2);
				}
			}
		}
		prev_inrect = now_inrect;
	}
	drawLineAndClear(painter, tmpdata2);
}

/*
 * Map Type define
 *	G : polyGon (마지막 좌표에서 처음 좌표로 연결)
 *	P : Polyline
 *	C : Circle
 *	E : Ellipse
 *	R : Rectangle
 *	L : Line
 *	T : Text
 *	S : Point & Symbol
 *
 *	Bndry Via define :	현재 포인트에서 다음 포인트로 어떻게 그릴 지를 결정 (Circle의 경우는 본 Sub-Token 내용 무시)
 *	G : Great Circle (일반 직선) : 일반좌표가 뒤따라옴
 *	H : Rhumb Line (현재 포인트와 다음 포인트가 동일한 위도일 경우, 직선이 아니라 위도선을 따라가는 약간의 곡선 형태가 됨) : 일반좌표가 뒤따라옴
 *	L : Counter Clockwise Arc (반시계방향으로 호를 그림) : 일반좌표에 ARC좌표가 뒤따라옴. 일반좌표와 ARC좌표간에 콜론(:) 으로 구분
 *	R : Clockwise Arc (시계방향으로 호를 그림) : 일반좌표에 ARC좌표가 뒤따라옴. 일반좌표와 ARC좌표간에 콜론(:) 으로 구분
 *
*/
void AirDraw::drawPath(QPainter* painter, QVector<CartesianXY>& dataxy, QChar drawtype)
{
	QPainterPath path;
	int step = 10;
	if (drawtype != QChar('C') && dataxy.count() < 2) {
		return;
	}
	if (dataxy.count() == 1 && dataxy[0].bndry_via == QChar('C')) {
		return drawAirCircle(painter, dataxy[0].mxy, dataxy[0].arc_dist);
	}
	if (drawtype == QChar('P')) {
		return drawPathPolyline(painter, dataxy);
	}
	if (drawtype == QChar('G')) {
		dataxy.append(dataxy[0]);	// 마지막에 첫 번째 포인트를 넣는다.
	}
	path.moveTo(dataxy[0].mxy);		// 첫 번째 포인트로 이동한다.

	for (int i=1; i<dataxy.count(); i++) {	// 다음 index 부터 데이터를 읽음.
		QChar bndry_via = dataxy[i].bndry_via;
		if (dataxy[i-1].bndry_via == QChar('H') && dataxy[i-1].lat == dataxy[i].lat) {
			// 스크린 거리가 10픽셀단위로 점을 생성
			// lineTo path에 넣는다.
			int d = dataxy[i].mxy.x() - dataxy[i-1].mxy.x();
			int makepointcnt = abs(d) / step;
			if (makepointcnt > 1) {
				double lon_d = dataxy[i].lon - dataxy[i-1].lon;
				double lon_dx = lon_d / makepointcnt;
				for (int k=1; k<makepointcnt; k++) {
					QPointF np = QPointF(dataxy[i-1].lat, dataxy[i-1].lon + (lon_dx * k));
					QPoint visualPoint = vp->latlonToScreen(np);
					path.lineTo(visualPoint);
				}
			}
		}

		if (bndry_via == QChar('H')) {
			path.lineTo(dataxy[i].mxy);
		}else if(dataxy[i].bndry_via == QChar('G')) {
			path.lineTo(dataxy[i].mxy);
		}else if(bndry_via == QChar('L')) {
			path.lineTo(dataxy[i].mxy);
			QPoint p0 = dataxy[i].arc_centerxy;
			QPoint p1 = dataxy[i].mxy;
			QPoint p2 = p1;
			if ((i+1) >= dataxy.count()) { p2 = dataxy[0].mxy; }
			else { p2 = dataxy[i+1].mxy; }

			double dx = p1.x() - p0.x();
			double dy = p1.y() - p0.y();
			dy = 0 - dy;
			double dr = sqrt(dx*dx + dy*dy);
			double dx2 = p2.x() - p0.x();
			double dy2 = p2.y() - p0.y();
			dy2 = 0 - dy2;
			QRectF rect = QRectF(p0.x() - dr, p0.y()-dr, dr*2, dr*2);

			if (dx == 0) dx = 0.000000001;
			double startAngle = atan(dy/dx)*rad2deg;
			if (dx < 0) startAngle += 180;

			if (dx2 == 0) dx2 = 0.000000001;
			double endAngle = atan(dy2/dx2)*rad2deg;
			if (dx2 < 0) endAngle += 180;

			double roundAngle = fmod((720 + endAngle - startAngle), 360);
			path.arcTo(rect, startAngle, (roundAngle));	// Right wise
		}else if(bndry_via == QChar('R')) {
			path.lineTo(dataxy[i].mxy);
			QPoint p0 = dataxy[i].arc_centerxy;
			QPoint p1 = dataxy[i].mxy;
			QPoint p2 = p1;
			if ((i+1) >= dataxy.count()) { p2 = dataxy[0].mxy; }
			else { p2 = dataxy[i+1].mxy; }

			double dx = p1.x() - p0.x();
			double dy = p1.y() - p0.y();
			dy = 0 - dy;
			double dr = sqrt(dx*dx + dy*dy);
			double dx2 = p2.x() - p0.x();
			double dy2 = p2.y() - p0.y();
			dy2 = 0 - dy2;
			QRectF rect = QRectF(p0.x() - dr, p0.y() - dr, dr*2, dr*2);

			if (dx == 0) dx = 0.000000001;
			double startAngle = atan(dy/dx) * rad2deg;
			if (dx < 0) startAngle += 180;

			if (dx2 == 0) dx2 = 0.000000001;
			double endAngle = atan(dy2/dx2) * rad2deg;
			if (dx2 < 0) endAngle += 180;

			double roundAngle = fmod((720 + endAngle - startAngle), 360);
			// arcTo : QRectF, startAngle, sweepLength
			path.arcTo(rect, startAngle, (-1)*(360-roundAngle));		// Right wise
			//log->print(QString("Start angle : %1").arg(startAngle));
		}else if(bndry_via == QChar('C')) {
			if (log != NULL) log->print(QString("xy:%1,%2, dist:%3").arg(dataxy[i].mxy.x()).arg(dataxy[i].mxy.y()).arg(dataxy[i].arc_dist));
			drawAirCircle(painter, dataxy[i].mxy, dataxy[i].arc_dist);		// db의 arc_dist는 원의 반지름임
		}else {
			path.lineTo(dataxy[i].mxy);
		}
	}
	painter->drawPath(path);
}


/*
 * Hold Layer - draw arc 생성을 위한 추가함수
 */
void AirDraw::drawPath2(QPainter* painter, QVector<CartesianXY>& dataxy, QChar drawtype)
{
	QPainterPath path;
	int step = 10;
	if (drawtype != QChar('C') && dataxy.count() < 2) {
		return;
	}
	if (dataxy.count() == 1 && dataxy[0].bndry_via == QChar('C')) {
		return drawAirCircle(painter, dataxy[0].mxy, dataxy[0].arc_dist);
	}
	if (drawtype == QChar('P')) {
		return drawPathPolyline(painter, dataxy);
	}
	if (drawtype == QChar('G')) {
		dataxy.append(dataxy[0]);
	}
	path.moveTo(dataxy[0].mxy);

	for (int i=1; i<dataxy.count(); i++) {
		QChar bndry_via = dataxy[i].bndry_via;
		if (dataxy[i-1].bndry_via == QChar('H') && dataxy[i-1].lat == dataxy[i].lat) {
			// 스크린 거리가 10픽셀단위로 점을 생성
			// lineTo path에 넣는다.
			int d = dataxy[i].mxy.x() - dataxy[i-1].mxy.x();
			int makepointcnt = abs(d) / step;
			if (makepointcnt > 1) {
				double lon_d = dataxy[i].lon - dataxy[i-1].lon;
				double lon_dx = lon_d / makepointcnt;
				for (int k=1; k<makepointcnt; k++) {
					QPointF np = QPointF(dataxy[i-1].lat, dataxy[i-1].lon + (lon_dx * k));
					QPoint visualPoint = vp->latlonToScreen(np);
					path.lineTo(visualPoint);
				}
			}
		}

		if (bndry_via == QChar('H')) {
			path.lineTo(dataxy[i].mxy);
		}else if(dataxy[i].bndry_via == QChar('G')) {
			path.lineTo(dataxy[i].mxy);
		}else if(bndry_via == QChar('R') || bndry_via == QChar('L')) {

			// Arc의 사각형 생성 (사각형의 중앙점 = 원점, Width = Height = 원의 지름)
			double vd_diameterMeter = UnitChange::haeriToMeter(dataxy[i].arc_dist * 2);		// 4NM(원의 지름)
			double vd_diameterPixel = vp->meterToPixel(vd_diameterMeter);

			// 사각형의 시작점 => 원점을 기준으로 대각선 방향에 위치함 (Width = Height = 원의 반지름)
			QRectF vr_rect = QRectF(dataxy[i].arc_centerxy.x(), dataxy[i].arc_centerxy.y(),
							-(vd_diameterPixel/2), -(vd_diameterPixel/2));

			// Arc의 시작각도 => 원점과 시작점의 각도
			double vd_startAngle = ca.bearing(vp->screenToLatLon(dataxy[i].arc_centerxy), vp->screenToLatLon(dataxy[i].mxy));
			vd_startAngle = -(vd_startAngle - 91);  // -(minus) ==> Qt는 시계방향일 경우 minus임, -90 + (-1) ==> Qt와 Airmap의 원점의 시작점 차이(90도), (-1)추가는 오차 적용

			double vd_spanAngle = 180;
			vd_spanAngle = vd_spanAngle * ((bndry_via == QChar('L')) ? 1 : -1);	// 시계방향(minus)

			QRectF vr_rectBase = QRectF(vr_rect.bottomRight().x(), vr_rect.bottomRight().y(), vd_diameterPixel, vd_diameterPixel);
			path.arcTo(vr_rectBase, fmod(vd_startAngle, 360), vd_spanAngle);
		}else if(bndry_via == QChar('C')) {
			if (log != NULL) log->print(QString("xy:%1,%2, dist: %3").arg(dataxy[i].mxy.x())
					.arg(dataxy[i].mxy.y()).arg(dataxy[i].arc_dist));
			drawAirCircle(painter, dataxy[i].mxy, dataxy[i].arc_dist);
		}else {
			path.lineTo(dataxy[i].mxy);
		}
	}
	painter->drawPath(path);
}

/**
 * UserLayer의 (Manual Coord. Input) 상세그리기 폴리라인의 아크추가를 위해서 drawPath3추가
 */
void AirDraw::drawPath3(QPainter* painter, QVector<CartesianXY>& dataxy, QChar drawtype)
{
	QPainterPath path;
	int step = 10;

	if (drawtype != QChar('C') && dataxy.count() < 2) {
		return;
	}
	if (dataxy.count() == 1 && dataxy[0].bndry_via == QChar('C')) {
		return drawAirCircle(painter, dataxy[0].mxy, dataxy[0].arc_dist);
	}
	if (drawtype == QChar('P')) {
		//
	}
	if (drawtype == QChar('G')) {
		dataxy.append(dataxy[0]);
	}
	path.moveTo(dataxy[0].mxy);

	for (int i=1; i<dataxy.count(); i++) {
		QChar bndry_via = dataxy[i].bndry_via;
		if (dataxy[i-1].bndry_via == QChar('H') && dataxy[i-1].lat == dataxy[i].lat) {
			// 스크린 거리가 10픽셀단위로 점을 생성
			// lineTo path에 넣는다.
			int d = dataxy[i].mxy.x() - dataxy[i-1].mxy.x();
			int makepointcnt = abs(d) / step;
			if (makepointcnt > 1) {
				double lon_d = dataxy[i].lon - dataxy[i-1].lon;
				double lon_dx = lon_d / makepointcnt;
				for (int k=1; k<makepointcnt; k++) {
					QPointF np = QPointF(dataxy[i-1].lat, dataxy[i-1].lon + (lon_dx * k));
					QPoint visualPoint = vp->latlonToScreen(np);
					path.lineTo(visualPoint);
				}
			}
		}

		if (bndry_via == QChar('H')) {
			path.lineTo(dataxy[i].mxy);
		}else if(dataxy[i].bndry_via == QChar('G')) {
			path.lineTo(dataxy[i].mxy);
		}else if(bndry_via == QChar('L')) {
			path.lineTo(dataxy[i].mxy);
			QPoint p0 = dataxy[i].arc_centerxy;
			QPoint p1 = dataxy[i].mxy;
			QPoint p2 = p1;
			if ((i+1) >= dataxy.count()) { p2 = dataxy[0].mxy; }
			else { p2 = dataxy[i+1].mxy; }

			double dx = p1.x() - p0.x();
			double dy = p1.y() - p0.y();
			dy = 0 - dy;
			double dr = sqrt(dx*dx + dy*dy);
			double dx2 = p2.x() - p0.x();
			double dy2 = p2.y() - p0.y();
			dy2 = 0 - dy2;
			QRectF rect = QRectF(p0.x() - dr, p0.y() - dr, dr*2, dr*2);

			if (dx == 0) dx = 0.000000001;
			double startAngle = atan(dy/dx) * rad2deg;
			if (dx < 0) startAngle += 180;

			if (dx == 0) dx2 = 0.000000001;
			double endAngle = atan(dy2/dx2) * rad2deg;
			if (dx2 < 0) endAngle += 180;

			double roundAngle = fmod((720 + endAngle - startAngle), 360);
			path.arcTo(rect, startAngle, roundAngle);		// Right wise
		}else if(bndry_via == QChar('R')) {
			path.lineTo(dataxy[i].mxy);
			QPoint p0 = dataxy[i].arc_centerxy;
			QPoint p1 = dataxy[i].mxy;
			QPoint p2 = p1;
			if((i+1) >= dataxy.count()) { p2 = dataxy[0].mxy; }
			else { p2 = dataxy[i+1].mxy; }

			double dx = p1.x() - p0.x();
			double dy = p1.y() - p0.y();
			dy = 0 - dy;
			double dr = sqrt(dx*dx + dy*dy);
			double dx2 = p2.x() - p0.x();
			double dy2 = p2.y() - p0.y();
			dy2 = 0 - dy2;
			QRectF rect = QRectF(p0.x() - dr, p0.y() - dr, dr*2, dr*2);

			if (dx == 0) dx = 0.000000001;
			double startAngle = atan(dy/dx) * rad2deg;
			if (dx < 0) startAngle += 180;

			if (dx2 == 0) dx2 = 0.000000001;
			double endAngle = atan(dy2/dx2) * rad2deg;
			if (dx2 < 0) endAngle += 180;

			double roundAngle = fmod((720 + endAngle - startAngle), 360);
			path.arcTo(rect, startAngle, (-1)*(360-roundAngle));		// Right wise
		}else if(bndry_via == QChar('C')) {
			if (log != NULL) log->print(QString("xy:%1,%2, dist:%3").arg(dataxy[i].mxy.x())
					.arg(dataxy[i].mxy.y()).arg(dataxy[i].arc_dist));
			drawAirCircle(painter, dataxy[i].mxy, dataxy[i].arc_dist);	// db의 arc_dist는 원의 반지름임
		}else {
			path.lineTo(dataxy[i].mxy);
		}
	}
	painter->drawPath(path);
}

void AirDraw::drawAUsermap(QPainter* painter)
{
	painter->setPen(QPen(Qt::white, 1));
	drawPath(painter, userdataxy, userdrawtype);
}
