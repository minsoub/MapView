/*
 * AirPlaneTextItem.cpp
 *
 *  Created on: 2012. 3. 12.
 *      Author: JMS
 */
#include <iostream>
#include "AirPlaneTextItem.h"

AirPlaneTextItem::AirPlaneTextItem() {
	// TODO Auto-generated constructor stub
	isShow = false;
	ismoving = false;
	selectColor = Qt::white;
	setFlag(ItemIgnoresTransformations, true);
   setFlag(QGraphicsItem::ItemIsMovable);
   setFlag(QGraphicsItem::ItemIsSelectable);
   setFlag(QGraphicsItem::ItemIsFocusable);
   QGraphicsItem::setAcceptDrops(true);

   setZValue(999);
   setSelected(false);
	//setDragMode(QGraphicsItem::ItemIsMovable);
	//setFlag(ItemSendsGeometryChanges);
	//setCacheMode(DeviceCoordinateCache);
	//aid = "KAL100";
	//speed = "N100";

	//msg = aid+"\n"+speed;

	//setSelected(true);


	currentPosition = QPointF(0, 0);
	boundingHeight  = 78;		// default

	mRectf = QRectF(0, 0, 100, boundingHeight);
}
/**
 * 두직선의 교차점을 구한다.
 */
inline static bool getIntersectPoint(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF* result)
{
	double t;
	double s;
	double under = (p4.y()-p3.y())*(p2.x()-p1.x())-(p4.x()-p3.x())*(p2.y()-p1.y());
	if(under==0) return false;

	double _t = (p4.x()-p3.x())*(p1.y()-p3.y()) - (p4.y()-p3.y())*(p1.x()-p3.x());
	double _s = (p2.x()-p1.x())*(p1.y()-p3.y()) - (p2.y()-p1.y())*(p1.x()-p3.x());

	t = _t/under;
	s = _s/under;
	if(t<0.0 || t>1.0 || s<0.0 || s>1.0) return false;
	if(_t==0 && _s==0) return false;

	result->setX(p1.x() + t * (double)(p2.x()-p1.x()));
	result->setY(p1.y() + t * (double)(p2.y()-p1.y()));

	return true;
}


/**
 * 출력 데이터의 현재 포인터를 리턴한다.
 */
QPointF AirPlaneTextItem::getCurrentPoint()
{
	//return boundingRect().center();

//	if (curPoint.lat != "") {
//		qDebug() << "AirPlaneTextItem::getCurrentPoint() "
//				<< QString(" currentPosition (x, y) = (%1, %2) ").arg(curPoint.p.x()).arg(curPoint.p.y())
//				<< QString(" decimal point (x, y) = (%1, %2) ").arg(vp->latlonToScreen(curPoint.p).x()).arg(vp->latlonToScreen(curPoint.p).y());
		//return vp->latlonToScreen(curPoint.p);
	//}

	QRectF bound = boundingRect();  // this->sceneBoundingRect();	// coordinate position of parent's
	QPointF pos  = bound.center();  // vp->latlonToScreen(curPoint.p);  // this->pos();               // currentPosition;

	QPointF cc  = airplane->getCurrentPoint();
	QPointF xy1 = bound.topLeft();
	QPointF xy2 = bound.topRight();
	QPointF xy3 = bound.bottomLeft();
	QPointF xy4 = bound.bottomRight();

	bool chk;
	QPointF result;
	chk = getIntersectPoint(xy1, xy2, pos, cc, &result);
	if (chk == true) {
		return result;
	}
	chk = getIntersectPoint(xy2, xy4, pos, cc, &result);
	if (chk == true) {
		return result;
	}
	chk = getIntersectPoint(xy3, xy4, pos, cc, &result);
	if (chk == true) {
		return result;
	}
	chk = getIntersectPoint(xy1, xy3, pos, cc, &result);
	if (chk == true) {
		return result;
	}
	return QPointF(0, 0);
}

/**
 * Data Block 을 출력한다.
 */
void AirPlaneTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* *widget */)
{
	//qDebug() << "AirPlaneTextItem called....";

	if (!isShow) return;

	// 데이터 블럭 출력 옵션에 따라서 출력한다.
	if (airplane->getReportOption()->blockCount > 0) {
		if (myNumber != 1) {		// first data
			//qDebug() << "blockCount : " << airplane->getReportOption()->blockCount;
			//qDebug() << "myNumber   : " << myNumber;
			//qDebug() << "cal        : " << (myNumber / airplane->getReportOption()->blockCount);
			if (myNumber % airplane->getReportOption()->blockCount != 0) {
				return;
			}
		}
	}

	// Altitude와 Speed가 같다면 계속적으로 데이터 블럭을 표현할 필요가 없다.
	//if (airplane->getTrackData().alt == airplane->getTrackData().prev_alt
	//		&& airplane->getTrackData().spd == airplane->getTrackData().prev_spd) {
	//	return;
	//}
	// 위치 정보가 없다면 그리지 않는다.
	if (airplane->getTrackData().lat == 0.0) {
		return;
	}

	QPointF position;

	if (curPoint.lat == "") {
		position = QPointF(airplane->getCurrentPoint().x()+70, airplane->getCurrentPoint().y()+70);
		currentPosition = position;
		cur_latlon_p = vp->screenToDecimal(position.toPoint());
		curPoint.lat = _ca.LatDecimalToDMS(cur_latlon_p.x());
		curPoint.lon = _ca.LatDecimalToDMS(cur_latlon_p.y());
		curPoint.p   = cur_latlon_p;
	}else {
		position = vp->latlonToScreen(curPoint.p);
	}

	//qDebug() << QString("AirPlaneTextItem::paint pos (%1, %2)").arg(position.x()).arg(position.y());


	LatLonBound bound;

	//log->print(QString("AirPlaneTextItem paint method : currentPosition (x, y) = (%1, %2), pos (x, y) = (%3, %4)")
	//		.arg(curPoint.p.x()).arg(curPoint.p.y())
	//		.arg(position.x()).arg(position.y()));

	bound.setPosition(position.toPoint());

	if (bound.inRect(vp->srcRect())) {

		//qDebug() << "AirPlaneTextItem painting.....";
		QPen pen(Qt::white);
		QColor textColor = selectColor;

		if (option->state & QStyle::State_Sunken) {		// item이 선택되었다면.. - State_Sunken
			painter->setBrush(QBrush(Qt::gray));
			pen.setStyle(Qt::DotLine);
		}
		painter->setPen(pen);


		msg = "";
		//////////////////////////////////////////////////////////////
		// 경보 상태가 있다면...

		//////////////////////////////////////////////////////////////
		int found = 0;
		int tmpHeight = 15;
		if (airplane->getReportOption()->trackNumber && airplane->getTrackData().type == 0) {	// track data
			msg += QString("%1").arg(trackNo);
		}else {
			msg += "     ";
		}
		if (airplane->getReportOption()->ssr && airplane->getTrackData().type == 0) {		// ReportOption check
			msg += QString("/%1").arg(ssr)+"\n";
		}else {
			msg += "    \n";
		}
		tmpHeight += 15;

		// 하강, 상승
		QString climb;
		if (airplane->getTrackData().climb > 0) {		// 상승
			climb = "^";
		}else if(airplane->getTrackData().climb == 0) {  // 수평비행
			climb = "-";
		}else {
			climb = "V";
		}
		QString cfl;
		if (airplane->getTrackData().cfl == 0) {
			cfl = "";
		}else {
			cfl = QString("%1").arg(airplane->getTrackData().cfl);
		}
		// 고도 | 상승,하강 | 배정고도 | 속도
		found = 0;
		QString tmp = "";
		if (airplane->getReportOption()->modec) {
			msg += QString("%1 %2 ").arg(airplane->getTrackData().alt).arg(climb);
			found = 1;
		}else {
			msg += "    ";
		}
		if (airplane->getReportOption()->assignedFL && airplane->getTrackData().type == 0) {
			msg += QString( "%1 ").arg(cfl);
			found = 1;
		}else {
			msg += "   ";
		}
		if (airplane->getReportOption()->velocity) {
			msg += QString(" /%1 \n").arg((int)airplane->getTrackData().spd);
			found = 1;
		}else {
			msg += " /  \n";
		}
		tmpHeight += 15;

		if (callsign != "" && airplane->getReportOption()->callsing) {
			msg += callsign  + "/ ";  // + QString(" %1").arg(airplane->getTrackData().wt_type);
		}

//		// 기종과 목적 공항
//		if (!airplane->getTrackData().actp.trimmed().isEmpty() && airplane->getTrackData().type == 0) {
//			if (airplane->getReportOption()->trackNumber || callsign != "" && airplane->getReportOption()->callsing || found == 1) {
//				msg += "\n";
//			}
//			msg += QString("%1     %2").arg(airplane->getTrackData().actp).arg(airplane->getTrackData().arr_ad);
//			found = 2;
//			tmpHeight += 15;
//		}


		boundingHeight = tmpHeight+5;
		//qDebug() << msg;
		QRectF rect = boundingRect();   // (position.x(), position.y(), 90, 48);  // boundingRect();  // outlineRect();
		rect.setX(position.x());
		rect.setY(position.y());

		painter->drawRect(rect);
		painter->setPen(textColor);
		painter->drawText(rect, Qt::AlignCenter, msg);
		//this->setPos(position);
	}
}

QRectF AirPlaneTextItem::outlineRect() const
{
	const int Padding = 8;
	QFontMetricsF metrics = qApp->font();
	QRectF rect = metrics.boundingRect(msg);


	//rect.setHeight(38);
	//rect.setWidth(80);

	//rect.adjust(-Padding, -Padding, +Padding, +Padding);
	//rect.translate(-rect.center());

	//qDebug() << "outlineRect rect (x, y) : " << rect.x() << rect.y();
	return rect;
}

void AirPlaneTextItem::updateInfo()
{
	prepareGeometryChange();
}

QRectF AirPlaneTextItem::boundingRect() const
{

	QPointF position;
	if (curPoint.lat == "") {
		position = QPointF(airplane->getCurrentPoint().x()+70, airplane->getCurrentPoint().y()+70);
//		currentPosition = position;
//		cur_latlon_p = vp->screenToDecimal(position.toPoint());
//		curPoint.lat = _ca.LatDecimalToDMS(cur_latlon_p.x());
//		curPoint.lon = _ca.LatDecimalToDMS(cur_latlon_p.y());
//		curPoint.p   = cur_latlon_p;
	}else {
		position = vp->latlonToScreen(curPoint.p);
	}

	qreal adjust = -0.5;
	QRectF rect = QRectF(position.x(), position.y(), 100, boundingHeight);

	//qDebug() << "rect (x, y) : " << rect.x() << rect.y();
	//qDebug() << "rect (w, h) : " << rect.width() << rect.height();

	//qDebug() << "boundingRect : " << rect;

	return rect;

//	//qDebug() << QString("boundingRect pos (%1, %2)").arg(pos().x()).arg(pos().y());
//	const int Margin = 1;
//	//qDebug() << s.width() << s.height() << s.bottomLeft().x() << s.bottomLeft().y() << s.topLeft().x() << s.topLeft().y();
//
//	//this->prepareGeometryChange();
//
//
//	return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

//QPainterPath AirPlaneTextItem::shape() const
//{
//	QRectF rect = outlineRect();
//
//	QPainterPath path;
//	path.addRoundRect(rect, roundness(rect.width()), roundness(rect.height()));
//
//	return path;
//}

int AirPlaneTextItem::roundness(double size) const
{
	const int Diameter = 12;
	return 100 * Diameter / int(size);
}

void AirPlaneTextItem::addLink(LinkItem* link)
{
	links.insert(link);
}

