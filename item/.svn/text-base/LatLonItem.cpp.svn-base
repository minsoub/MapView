/*
 * LatLonItem.cpp
 *
 *  Created on: 2012. 1. 25.
 *      Author: HIST002
 */

#include <iostream>
#include "LatLonItem.h"
#include "../lib/NorthGreenichPoint.h"

LatLonItem::LatLonItem() {
	// TODO Auto-generated constructor stub
	isShow = false;
}

void LatLonItem::setScreenConvertClass(LatLonConvert *convert)
{
	this->convert = convert;
}
void LatLonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	if (isShow) {
		painter->setPen(QPen(QColor(127, 127, 127), 1));
		drawLatLon(painter);
	}
}
void LatLonItem::drawLatLon(QPainter* painter)
{
	drawLonLines(painter);
	drawLatLines(painter);

	// need circle
	if (convert->isGu()) {
		QPoint center = convert->screenCenter();
		int r2 = (int)convert->pixelRadius();
		QRect rect = QRect(center.x() - r2, center.y() - r2, r2*2, r2*2);
		painter->drawEllipse(rect);
	}
}
void LatLonItem::drawLonLines(QPainter* painter)
{
	// 경위도
	double dy = convert->mppToDegree();		// 경위도 변환정도

	// 경도 그리기
	double wj = convert->greenich();
	double dw = convert->baseWJ(wj, dy);

	double lon = dw + dy;

	NorthGreenichPoint baseNGP;
	baseNGP.set(convert->north(), lon);

	double leftGreenich = convert->leftGreenich();
	double rightGreenich = convert->rightGreenich();

	// 오른쪽으로 경도 그리기
	double distance = rightGreenich - baseNGP.greenich();
	if (rightGreenich < baseNGP.greenich()) distance += 360;

	while(distance >= 0) {
		lon = baseNGP.lon();
		drawLon(painter, lon);
		baseNGP.moveEast(dy);
		distance -= dy;
	}

	baseNGP.set(convert->north(), dw);

	// 왼쪽으로 경도 그리기
	distance = baseNGP.greenich() - leftGreenich;
	if (leftGreenich > baseNGP.greenich()) distance += 360;

	while(distance >= 0) {
		lon = baseNGP.lon();
		drawLon(painter, lon);
		baseNGP.moveWest(dy);
		distance -= dy;
	}
}
void LatLonItem::drawLatLines(QPainter* painter)
{
	QVector<double> drawedLines;
	double last = 0;		// Last Line
	int num=0;

	// 경위도
	double dy = convert->mppToDegree();		// 경위도의 변환정도
	double wj = convert->north();
	double dw = convert->baseWJ(wj, dy);

	// 위도 그리기
	double lat = dw + dy;

	NorthGreenichPoint baseNGP;
	baseNGP.set(lat, convert->greenich());

	double topNorth    = convert->topNorth();
	double bottomNorth = convert->bottomNorth();

	// 위쪽으로 위도 그리기
	drawedLines.clear();

	double distance = topNorth - baseNGP.north();
	if (topNorth < baseNGP.north()) distance += 360;

//	std::cout << "distance : " << distance << "\n";
	while(distance >= 0) {
		lat = baseNGP.lat();
		if (drawedLines.indexOf(lat) < 0) {
			drawLat(painter, lat);
			drawedLines.append(lat);
		}
		last = baseNGP.north();
		baseNGP.moveNorth(dy);
		distance -= dy;
//		std::cout << "distance loop : " << distance << "\n";
		num++;
	}

	// 아래쪽으로 위도 그리기
	baseNGP.set(dw, convert->greenich());
	distance = baseNGP.north() - bottomNorth;
	if (bottomNorth > baseNGP.north()) distance += 360;

	while(distance >= 0) {
		lat = baseNGP.lat();
		if (drawedLines.indexOf(lat) < 0) {
			drawLat(painter, lat);
			drawedLines.append(lat);
		}
		baseNGP.moveSouth(dy);
		distance -= dy;
		num++;
	}

//	std::cout << "Loop count : " << num << "\n";
}
void LatLonItem::drawLon(QPainter* painter, double lon)
{
	QVector<QPoint> datas;
	QRect textBox;

	datas.clear();

	double dy = convert->mppToDegree();
	if (dy >1) { dy = 1; }

	NorthGreenichPoint baseNGP(convert->north(), convert->greenich());

	double top = convert->topNorth() + dy;
	double bottom = convert->bottomNorth() - dy;

	double distance = top - baseNGP.north();
	if (baseNGP.north() > top) distance += 360;

	while(distance >= 0) {
		QPoint logic_scr = convert->latlonToScreen(QPointF(baseNGP.lat(), lon));

		Cartesian c = convert->cartesian();
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
		if (drawCount > 0) drawLatLon1Text(painter, lon, 10);
	}
	datas.clear();

	baseNGP.set(convert->north(), convert->greenich());
	distance = baseNGP.north() - bottom;
	if (distance < 0) distance += 360;
	while(distance >= 0) {
		QPoint logic_scr = convert->latlonToScreen(QPointF(baseNGP.lat(), lon));
		Cartesian c = convert->cartesian();
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
		if (drawCount > 0) drawLatLon1Text(painter, (lon), 11);
	}
}
void LatLonItem::drawLat(QPainter* painter, double lat)
{
	QVector<QPoint> datas;

	double dy = convert->mppToDegree();

	if (dy > 1) { dy = 1; }

	NorthGreenichPoint baseNGP;
	baseNGP.set(convert->north(), convert->greenich());
	double left  = convert->leftGreenich();
	double right = convert->rightGreenich();

//	std::cout << "north : " << convert->north() << "\n";
//	std::cout << "greenich : " << convert->greenich() << "\n";
//	std::cout << "left : " << left << "\n";
//	std::cout << "right : " << right << "\n";

	double distance = right - baseNGP.greenich();
	if (distance < 0) distance += 360;

//	std::cout << "distance 1 : " << distance << "\n";
//	std::cout << "dy 2 : " << dy << "\n";



	while(distance >= 0) {
		QPoint logic_scr = convert->latlonToScreen(QPointF(lat, baseNGP.lon()));
		if (convert->cartesian().x >= 0) {
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
//		std::cout << "distance while : " << distance << "\n";
	}
	if (datas.count() > 1) {
		drawLine3(painter, datas);
		if (drawCount > 0) drawLatLon1Text(painter, lat, 20);
	}
	datas.clear();


	baseNGP.set(convert->north(), convert->greenich());
	distance = baseNGP.greenich() - left;
	if (distance < 0) distance += 360;

//	std::cout << "distance 2 : " << distance << "\n";
//	std::cout << "dy 2 : " << dy << "\n";

	while(distance >= 0) {
		QPoint logic_scr = convert->latlonToScreen(QPointF(lat, baseNGP.lon()));
		if (convert->cartesian().x >= 0) {
			datas.append(logic_scr);
		}else {
			if (datas.count() > 1) {
				drawLine3(painter, datas);
				if (drawCount > 0) drawLatLon1Text(painter, lat, 21);
			}
			if (datas.count() > 0) datas.clear();
		}
		baseNGP.moveWest(dy);
		distance -= dy;
//		std::cout << "distance while 2: " << distance << "\n";
	}
	if (datas.count() > 1) {
		drawLine3(painter, datas);
		if (drawCount > 0) drawLatLon1Text(painter, lat, 21);
	}
}


bool LatLonItem::drawLine3(QPainter *painter, QVector<QPoint>& dataxy)
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
	drawEndPoint   = QPoint(-1, -1);

	while(index < dataxy.count()) {
		now_xy = dataxy[index];

		prev_inrect = (convert->srcRect().contains(prev_xy)) ? true : false;
		now_inrect  = (convert->srcRect().contains(now_xy))  ? true : false;

		if (prev_inrect == false && now_inrect == false) {
			prev_xy = now_xy;
			index++;
			continue;
		}else if(prev_inrect == false && now_inrect == true) {  // 안으로 들어옴
			data2.append(prev_xy);
			data2.append(now_xy);
		}else if(prev_inrect == true && now_inrect == true) {
			data2.append(prev_xy);
		}else if(prev_inrect == true && now_inrect == false) { // 밖으로 나오는 것
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
		drawed = true;
		drawCount = data2.count();
		drawStartPoint = data2[1];
		drawEndPoint = data2[drawCount-1];
		drawCenterPoint = data2[0];
		QPolygon latPoints(data2.count());
		for (int i=0; i<data2.count(); i++) {
			latPoints[i] = data2[i];
		}
		painter->drawPolyline(latPoints);
	}
	return drawed;
}

void LatLonItem::drawLatLon1Text(QPainter* painter, double latlon, int type)
{
	QString s;
	QPoint p;

	p = drawEndPoint;

	s = QString("%1").arg(latlon, 7, 'f', 1);
	int textLength = 30;
	int textHeight = 10;
	if (p.x() < 0) p.setX(1);
	if (p.x() > ( convert->srcWidth() - textLength)) p.setX(convert->srcWidth() - textLength);

	if (p.y() < 0) p.setY(1);
	if (p.y() > convert->srcHeight() - textHeight) p.setY(convert->srcHeight() - textHeight);

	drawText1(painter, p, QString("[%1]").arg(s.trimmed()));
}
void LatLonItem::drawText1(QPainter *painter, const QPoint& p, const QString& text)
{
	QRect textBox;
	QString text2 = text.trimmed();
	painter->setFont(QFont("Times", 8));
	textBox.setRect(p.x(), p.y(), 10*text2.length(), 10);
	painter->drawText(textBox, Qt::AlignLeft | Qt::AlignVCenter, text2);
}

void LatLonItem::updateInfo()
{
	prepareGeometryChange();
}
QRectF LatLonItem::boundingRect() const
{
	qreal adjust = 0.5;

	QRectF rect = QRectF(adjust, adjust,
			convert->srcRect().width() * 1.0, convert->srcRect().height() * 1.0);

	return rect;
}
