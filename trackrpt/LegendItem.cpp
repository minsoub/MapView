/*
 * LegendItem.cpp
 *
 *  Created on: 2012. 5. 3.
 *      Author: JMS
 *  Description : Print legend of preview screen.
 */

#include "LegendItem.h"
#include "../lib/GlobalColor.h"

LegendItem::LegendItem() {
	// TODO Auto-generated constructor stub
	setZValue(999);
}

LegendItem::LegendItem(int ims, QRectF size)
{
	setZValue(999);

	imgSize = ims, rect = size;
}
LegendItem::~LegendItem() {
	// TODO Auto-generated destructor stub
}

/**
 * Legend 데이터를 출력한다.
 */
void LegendItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* *widget */)
{
	QRectF rect = boundingRect();
	painter->setBrush(QBrush(Qt::white));
	painter->drawRect(rect);

	QPen pen(Qt::black);
	painter->setPen(pen);


	QFont font(qApp->font());
	font.setPointSize(10);
	font.setBold(true);
	painter->setFont(font);

	painter->drawText(QPoint((int)rect.x()+10, (int)rect.y()+30), "Legend : ");


	font.setPointSize(8);
	font.setBold(false);
	painter->setFont(font);

	int position = 55;

	QString msg;
	for (int i=0; i<model.size(); i++) {

		TrackDataModel data = model.at(i);

		msg = QString("%1 - %2 - %3 -").arg(data.ssr).arg(data.trackNo).arg(data.callsign);

		painter->drawText(QPoint((int)rect.x()+15, (int)rect.y()+position), msg);

		QFontMetricsF metrics = qApp->font();
		QRectF fontRect = metrics.boundingRect(msg);

		// Symbol
		QPixmap icon;
		QString symboldir = QString("%1/images").arg(ConfigParser::getInstance().envMapDir());

		QDir dir(symboldir);
		if (!dir.exists()) return;


		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg(data.symbol);
		icon.load(fullname);


		//QPixmap icon = item2->getSymbol();
		QPixmap batang(QSize(icon.width(), icon.height()));
		batang.fill(QColor(0, 0, 0));
		QPainter painterIcon(&batang);
		painterIcon.drawPixmap(0, 0, icon);


		painter->drawPixmap(QPoint((int)rect.x()+15+(int)fontRect.width(), (int)rect.y()+position-10), batang);

		// Color
		painter->drawText(QPoint((int)rect.x()+15+(int)fontRect.width()+(int)batang.width(), (int)rect.y()+position),
					" - " + data.colorName);   //getColorName(item->getColor()));

		position += 20;
}

//	QString msg = "";
//	msg += "Legend : \n";
//
//
//	for (int i=0; i<model.size(); i++) {
//		AirPlaneModel* data = model.at(i);
//		AirPlaneTextItem* item = data->getItem2();
//		msg += QString("%1 - %2 - %3 - Symbol - %4 \n").arg(item->getSSR()).arg(item->getTrackNo())
//						.arg(item->getCallsign()).arg(getColorName(item->getColor()));
//
//
//	}
//	painter->drawText(rect, Qt::AlignLeft, msg);
	//qDebug() << msg;

	//qDebug() << "rect : " << rect.width() << rect.height();
	//qDebug() << "rect(x, y) : " << rect.x() << rect.y();
}

QRectF LegendItem::boundingRect() const
{
	QPointF f;
	f.setY(0);
	if (rect.width() == 0) {
		f.setX(841);
	}else {
		f.setX(imgSize);
	}
	QRectF rect1 = QRectF(f.x(), f.y(), rect.width() == 0 ? 250 : rect.width()-imgSize, rect.height());

	//qDebug() << "1rect : " << rect1.width() << rect1.height() << "imgSize : " << imgSize;
	//qDebug() << "1rect(x, y) : " << rect1.x() << rect1.y();

	return rect1;
}


void LegendItem::setTrackData(QVector<TrackDataModel> data)
{
	model = data;
}

/**
 * return Color name
 */
QString LegendItem::getColorName(QColor color)
{
	for (int i=0; i<GlobalColorCount; i++) {
		if (color == userRGBColor[i]) {
			return userColor[i];
		}
	}
	return "";
}
