/*
 * DistanceLinkItem.cpp
 *
 *  Created on: 2012. 6. 12.
 *      Author: root
 */
#include <iostream>
#include "DistanceLinkItem.h"

DistanceLinkItem::DistanceLinkItem(AirPlaneItem* fromItem, AirPlaneItem* toItem) {
	// TODO Auto-generated constructor stub
	source = fromItem;
	dest   = toItem;
	isShow = true;
	//source->addLink(this);
	//dest->addLink(this);

	//setFlag(QGraphicsItem::ItemIsSelectable);
	//setFlag(ItemIgnoresTransformations, true);
	setZValue(0);

	//setColor(Qt::white);
	//adjust();
	textColor = QColor(Qt::white);
	lineColor = QColor(Qt::white);
}

void DistanceLinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

	if (!isShow) return;

	// 데이터 블럭 출력 옵션에 따라서 출력한다.
//	if (source->getReportOption()->blockCount > 0) {
//		if (dest->getNumber() != 1) {		// first data
//			//qDebug() << "blockCount : " << source->getReportOption()->blockCount;
//			//qDebug() << "myNumber   : " << dest->getNumber();
//			//qDebug() << "cal        : " << (dest->getNumber() / source->getReportOption()->blockCount);
//			if (dest->getNumber() % source->getReportOption()->blockCount != 0) {
//				return;
//			}
//		}
//	}


	// 위치 정보가 없다면 그리지 않는다.
	if (source->getTrackData().lat == 0.0) {
		return;
	}

	QPen pen(Qt::white);
	painter->setPen(pen);
	QPointF pos = dest->getCurrentPoint();

	if (pos.x() == 0 && pos.y() == 0) {
		// not painting
	}else {
		painter->drawLine(QLineF(source->getCurrentPoint(), dest->getCurrentPoint()));

		QRect rectLine;
		QRect rectText;
		rectLine.setTopLeft(source->getCurrentPoint().toPoint());
		rectLine.setBottomRight(dest->getCurrentPoint().toPoint());
		font.setFamily("Times");
		font.setPointSizeF(10.0);

		QPoint sp = source->getCurrentPoint().toPoint();
		double d = source->getView()->distance(sp, dest->getCurrentPoint().toPoint());
		d = UnitChange::meterToHaeri(d);
		disttext = QLocale(QLocale::English).toString(d, 'f', 2);
		bearingtext = QString("%1").arg(source->getView()->bearing(sp, dest->getCurrentPoint().toPoint()), 0, 'f', 2);


		text = QString("%1NM/%2").arg(disttext).arg(bearingtext);
		QFontMetrics m(font);
		QRect r = m.boundingRect(text);
		rectText = QRect(dest->getCurrentPoint().x() - 1, dest->getCurrentPoint().y() - 1, r.width(), r.height()+12);

		// Text
		painter->setFont(font);

		painter->drawText(rectText, Qt::AlignCenter, text);
	}
}
//void LinkItem::adjust()
//{
//    if (!source || !dest)
//        return;
//
//    //QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
//    QLineF line(source->getCurrentPoint(), dest->getCurrentPoint());
//    qreal length = line.length();
//
//    //log->print(QString("LinkItem adjust length : %1").arg(length));
//    prepareGeometryChange();
//
//    if (length > qreal(20.)) {
//        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
//        sourcePoint = line.p1() + edgeOffset;
//        destPoint = line.p2() - edgeOffset;
//    } else {
//        sourcePoint = destPoint = line.p1();
//    }
//}
//
//QRectF LinkItem::boundingRect() const
//{
//    if (!source || !dest)
//        return QRectF();
//
//    qreal penWidth = 1;
//    qreal extra = (penWidth ) / 2.0;
//
//    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
//                                      destPoint.y() - sourcePoint.y()))
//        .normalized()
//        .adjusted(-extra, -extra, extra, extra);
//}
//
//void LinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
//{
//    if (!source || !dest)
//        return;
//
//    QLineF line(sourcePoint, destPoint);
//
//    log->print(QString("sourcePoint (x, y) = (%1, %2)").arg(sourcePoint.x()).arg(sourcePoint.y()));
//    log->print(QString("destPoint (x, y) = (%1, %2)").arg(destPoint.x()).arg(destPoint.y()));
//
//    if (qFuzzyCompare(line.length(), qreal(0.)))
//        log->print("LinkItem qFuzzyCompare called..........1");
//        return;
//
//    // Draw the line itself
//    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//    painter->drawLine(line);
//
//}
