/*
 * AirPlaneItem.cpp
 *
 *  Created on: 2012. 3. 12.
 *      Author: JMS
 */

#include "AirPlaneItem.h"

AirPlaneItem::AirPlaneItem() {
	// TODO Auto-generated constructor stub
	isShow = false;
	air_idx = 0;
	symbol   = "";
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(ItemIgnoresTransformations, false);
	//setFlag(ItemSendsGeometryChanges);
	//setCacheMode(DeviceCoordinateCache);
	setZValue(1000);
	orderno = -1;
	//setColor(Qt::white);
}
/**
 * 현재 그려진 비행 데이터의 포인터를 리턴한다.
 */
QPointF AirPlaneItem::getCurrentPoint()
{
	//return pos();

	//qDebug() << dataxy.count();

	if (dataxy.count() > 0) {
		APoint ap = dataxy[0];

		QPoint x = vp->latlonToScreen(ap.p);

		return x;
	}else {
		return QPointF(0,0);
	}
}

QPointF AirPlaneItem::getPreviousPoint()
{
//	if (dataxy.count() > ( air_idx - 1) && (air_idx - 1) > -1) {
//		APoint ap = dataxy[air_idx-1];
//
//		QPoint x = vp->latlonToScreen(ap.p);
//
//		return x;
//	}else {
		APoint ap = dataxy[air_idx];

		QPoint x = vp->latlonToScreen(ap.p);
		return x;
//	}
}
//void AirPlaneItem::advance(int step)
//{
//	log->print("advance.. called....");
//
//    if (!step)
//        return;
//
//    log->print("advance.. called....");
//    air_idx++;
//    update();
//
//   // this->setPos();
//}

/**
 * Pixmap 데이터를 미리 로드한다.
 * 항적데이터가 PSR only, SSR only, Coasting 인지 확인해서 심벌을 달리 해야 한다.
 */
void AirPlaneItem::setLoad()
{
	QString symboldir = QString("%1/images").arg(ConfigParser::getInstance().envMapDir());

	QDir dir(symboldir);
	if (!dir.exists()) return;

	if (orderno == 1) {
		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg("startsymbol.xpm");
		icon.load(fullname);
		return;
	}
	if (trackData.psr == "0" && trackData.ssr == "1") {       // PSR only
		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg("psr_only.xpm");
		icon.load(fullname);
	}else if (trackData.psr == "1" && trackData.ssr == "0") { // SSR only
		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg("ssr_only.xpm");
		icon.load(fullname);
	}else if(trackData.cst == "1") {									// Coasting
		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg("coasting_only.xpm");
		icon.load(fullname);
	}else {
		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg(symbol);
		icon.load(fullname);
	}
}

/**
 * Track 데이터를 아이콘으로 출력한다.
 */
void AirPlaneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */* *widget*/)
{
	//qDebug() << isShow;

	if (!isShow) return;

	if (dataxy.count() == 0) return;

	APoint ap = dataxy[0];

	if (trackData.lat == 0.0) {		// 위치 정보가 없다면 그리지 않는다.
		return;
	}

	QPixmap icon2;
	int size = 0;
	//QPixmap batang(QSize(icon.width()+2, icon.height()+2));
   //batang.fill(QColor(0, 0, 0));

	// mpp가 50일 때 제일 큰 상태이고 46000일 때 제일 작은 상태이다.
	// default size : 15라고 했을 때
	if (vp->mpp() > 1000.0) {
		size = 1;
	}else if(vp->mpp() <= 50.0){
		size = 15;
	}else {
		if (vp->mpp() <=1000.0 && vp->mpp() > 900.0) {
			size = 2;
		}else if (vp->mpp() <=900.0 && vp->mpp() > 800.0) {
			size = 3;
		}else if (vp->mpp() <=800.0 && vp->mpp() > 700.0) {
			size = 4;
		}else if (vp->mpp() <=700.0 && vp->mpp() > 600.0) {
			size = 5;
		}else if (vp->mpp() <=600.0 && vp->mpp() > 500.0) {
			size = 6;
		}else if (vp->mpp() <=500.0 && vp->mpp() > 400.0) {
			size = 7;
		}else if (vp->mpp() <=400.0 && vp->mpp() > 300.0) {
			size = 8;
		}else if (vp->mpp() <=300.0 && vp->mpp() > 200.0) {
			size = 9;
		}else if (vp->mpp() <=200.0 && vp->mpp() > 100.0) {
			size = 10;
		}else if (vp->mpp() <=100.0 && vp->mpp() > 90.0) {
			size  = 11;
		}else if (vp->mpp() <=90.0 && vp->mpp() > 80.0) {
			size = 12;
		}else if (vp->mpp() <=80.0 && vp->mpp() > 70.0) {
			size = 13;
		}else if (vp->mpp() <=70.0 && vp->mpp() > 60.0) {
			size  = 14;
		}else {
			size  = 15;
		}
	}
	icon2 = icon.scaled(QSize(size, size),  Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	//QPainter painter(&batang);


	QPoint x = vp->latlonToScreen(ap.p);

	LatLonBound bound;
	bound.setPosition(x);
	if (!bound.inRect(vp->srcRect())) {
		return;
	}

	//painter->initFrom(this);
	painter->drawPixmap(x.x() - (size/2), x.y() - (size/2), icon2);

	//log->print(QString("AirPlaneItem paint method : currentPosition (x, y) = (%1, %2), pos (x, y) = (%3, %4)")
	//		.arg(ap.p.x()).arg(ap.p.y())
	//		.arg(x.x()).arg(x.y()));

}
void AirPlaneItem::addLink(LinkItem* link)
{
	links.insert(link);
}

void AirPlaneItem::updateInfo()
{
	prepareGeometryChange();
}
QRectF AirPlaneItem::boundingRect() const
{
	qreal adjust = -0.5;
	QRectF rect = QRectF(adjust, adjust, 40, 40);
	return rect;
}

/**
 * TrackData를 받아서 비행 데이터를 구성한다.
 */
void AirPlaneItem::setTrackData(TrackData tData)
{
	trackData = tData;

	APoint latlon;
	QString lat = _ca.LatDecimalToDMS(tData.lat);
	QString lon = _ca.LonDecimalToDMS(tData.lon);

	latlon.lat = lat;
	latlon.lon = lon;
	latlon.p = QPointF(tData.lat, tData.lon);   // _ca.toDD(list[1]);
	dataxy.append(latlon);
}


void AirPlaneItem::test_read()
{
	QString fileName = "D:/ams.map";
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		log->print(QString("file %1 open error").arg(fileName));
		return;
	}

	int lineNo = 0;
	QTextStream in(&file);
	while(!in.atEnd()){
		QString line = in.readLine();
		QStringList list = line.split(":");

		if (line.length() < 1) continue;
		lineNo++;

		if(list.count() >= 2 && list[0] == "LAYER") {
			QString layername = list[1].trimmed().toUpper();
			if (list[0] == "LAYER" && layername == "COAST") {

				while(!in.atEnd()) {
					line = in.readLine();
					list = line.split(":");
					if(list[0] == "ID" && list[1] == "MAIN"){
						int cnt = (list[2]).toInt();
						for(int i=0;i<cnt;i++){
							line = in.readLine();
							list = line.split(":");
							lineNo++;
							APoint latlon;
							latlon.lat = LLU::lat(list[1]);
							latlon.lon = LLU::lon(list[1]);
							latlon.p = _ca.toDD(list[1]);
							dataxy.append(latlon);
						}
						break;
					}
				}
				break;
			}
		}
	}

	file.close();
}

