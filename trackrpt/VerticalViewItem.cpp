/*
 * VerticalViewItem.cpp
 *
 *  Created on: 2012. 5. 4.
 *      Author: JMS
 *  Description : paint item in Vertical View
 */

#include "VerticalViewItem.h"

const int timeLineCount = 10;			// 10개의 타임라인으로 구성
const int cap           = 25;			// empty with
const int widthDef      = 1000;     // width

VerticalViewItem::VerticalViewItem(QVector<TrackDataModel> m) {
	// TODO Auto-generated constructor stub
	qDebug() << "VerticalViewItem called....";
	model = m;
	time.clear();
	timeList.clear();
	mode  = 0;

	QString minTime = "";
	QString maxTime = "";

	qDebug() << "model size : " << model.size();

	for (int i=0; i<model.size(); i++) {
		// TrackDataModel
		for (int j=0; j<model[i].dataModel.size(); j++) {

			if (model[i].dataModel[j].alt == 0) continue;

			QString occur_dt = model[i].dataModel[j].occur_dt;		// datetime
			QString tm = occur_dt.right(8);

			if (time.size() == 0) {
				minTime = tm;
				maxTime = tm;
				time.append(tm);
			}else {
				// min, max
				if (minTime > tm) {
					minTime = tm;
				}
				if (maxTime < tm) {
					maxTime = tm;
				}
			}
		}
	}
	time.clear();

	// min, max를 구했으므로 시간 출력에 대해서 몇개로 나눌 것인가를 선택한다.
	QTime min = QTime::fromString(minTime, "hh:mm:ss");
	QTime max = QTime::fromString(maxTime, "hh:mm:ss");

	int sec = min.secsTo(max);		// 시간의 차이를 초로 계산.

	qDebug() << "sec : " << sec;
	plus = 0;
	if (sec == 0) {
		plus = 1;
	}else {
		plus = qCeil(sec / (1.0 * timeLineCount));				// 최대 10개의 라인으로 보일 때 초는 얼마가 되는가?
	}

	qDebug() << "plus : " << plus;
	QTime cur = min;
	int tmp = 0;
	for (int i=0; i<timeLineCount; i++) {				// 10개의 라인으로 구성하기 위해서 10번 반복해서 타임을 구성한다.
		tmp += plus;
		if (i == 0) {
			timeList.append(cur);
		}else {
			QTime t = cur.addSecs(tmp);
			timeList.append(t);
		}
	}

//	for (int i=0; i<timeLineCount; i++) {
//		qDebug() << "Time : " << timeList.at(i).toString("hh:mm:ss");
//	}
}

VerticalViewItem::~VerticalViewItem() {
	// TODO Auto-generated destructor stub
}

void VerticalViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QRectF rect = boundingRect();

	QString symboldir = QString("%1/images").arg(ConfigParser::getInstance().envMapDir());
	QDir dir(symboldir);
	if (!dir.exists()) return;

	QPen pen(Qt::black);
	painter->setPen(pen);

	QFont font(qApp->font());
	font.setPointSize(9);
	font.setBold(true);
	painter->setFont(font);

	QFontMetricsF metrics = qApp->font();
	QRectF fontRect;
	int maxData = 0;
	if (mode == 0) {
		maxData = getMaxAlt() * 25;	// feet
	}else {
		maxData = getMaxAlt();
	}

	qDebug() << maxData;

	if (mode == 0) {			// Altitude

		// 고도의 max 값을 구한다.
		if (maxData < 6) {
			painter->drawText(QPoint(20,  20), "Altitude");
			painter->drawText(QPoint(20,  40), " (Feet)");
			painter->drawText(QPoint(20, 100), "       6");
			painter->drawText(QPoint(20, 190), "       5");
			painter->drawText(QPoint(20, 280), "       4");
			painter->drawText(QPoint(20, 370), "       3");
			painter->drawText(QPoint(20, 460), "       2");
			painter->drawText(QPoint(20, 550), "       1");
		}else {

			int size = (int)(maxData / 6);
			QString t1 = QString("%1").arg(QString("%1").arg(size),     -8, ' ');
			QString t2 = QString("%1").arg(QString("%1").arg(size * 2), -8, ' ');
			QString t3 = QString("%1").arg(QString("%1").arg(size * 3), -8, ' ');
			QString t4 = QString("%1").arg(QString("%1").arg(size * 4), -8, ' ');
			QString t5 = QString("%1").arg(QString("%1").arg(size * 5), -8, ' ');
			QString t6 = QString("%1").arg(QString("%1").arg(maxData), -8, ' ');

			painter->drawText(QPoint(20,  20), "Altitude");
			painter->drawText(QPoint(20,  40), " (Feet)");
			painter->drawText(QPoint(20, 100), t6);
			painter->drawText(QPoint(20, 190), t5);
			painter->drawText(QPoint(20, 280), t4);
			painter->drawText(QPoint(20, 370), t3);
			painter->drawText(QPoint(20, 460), t2);
			painter->drawText(QPoint(20, 550), t1);
		}
		fontRect = metrics.boundingRect("Altitude  ");

	}else if(mode == 1) {	// Speed
		if (maxData < 6) {
			painter->drawText(QPoint(20,  20), "   Speed");
			painter->drawText(QPoint(20,  40), "   (NM) ");
			painter->drawText(QPoint(20, 100), "       6");
			painter->drawText(QPoint(20, 190), "       5");
			painter->drawText(QPoint(20, 280), "       4");
			painter->drawText(QPoint(20, 370), "       3");
			painter->drawText(QPoint(20, 460), "       2");
			painter->drawText(QPoint(20, 550), "       1");
		}else {
			int size = (int)(maxData / 6);
			QString t1 = QString("%1").arg(QString("%1").arg(size),     -8, ' ');
			QString t2 = QString("%1").arg(QString("%1").arg(size * 2), -8, ' ');
			QString t3 = QString("%1").arg(QString("%1").arg(size * 3), -8, ' ');
			QString t4 = QString("%1").arg(QString("%1").arg(size * 4), -8, ' ');
			QString t5 = QString("%1").arg(QString("%1").arg(size * 5), -8, ' ');
			QString t6 = QString("%1").arg(QString("%1").arg(maxData), -8, ' ');

			painter->drawText(QPoint(20,  20), "   Speed");
			painter->drawText(QPoint(20,  40), "   (NM) ");
			painter->drawText(QPoint(20, 100), t6);
			painter->drawText(QPoint(20, 190), t5);
			painter->drawText(QPoint(20, 280), t4);
			painter->drawText(QPoint(20, 370), t3);
			painter->drawText(QPoint(20, 460), t2);
			painter->drawText(QPoint(20, 550), t1);
		}
		fontRect = metrics.boundingRect("Speed     ");
	}
	// 가로 / 세로 라인
	painter->drawLine(QPoint(fontRect.width()+cap, 20),  QPoint(fontRect.width()+cap, 640));
	painter->drawLine(QPoint(fontRect.width()+cap, 640), QPoint(widthDef+fontRect.width()+cap, 640));

	// 고도 라인
	pen.setStyle(Qt::DotLine);
	painter->setPen(pen);
	painter->drawLine(QPoint(fontRect.width()+cap, 100),QPoint(widthDef+fontRect.width()+cap, 100));
	painter->drawLine(QPoint(fontRect.width()+cap, 190),QPoint(widthDef+fontRect.width()+cap, 190));
	painter->drawLine(QPoint(fontRect.width()+cap, 280),QPoint(widthDef+fontRect.width()+cap, 280));
	painter->drawLine(QPoint(fontRect.width()+cap, 370),QPoint(widthDef+fontRect.width()+cap, 370));
	painter->drawLine(QPoint(fontRect.width()+cap, 460),QPoint(widthDef+fontRect.width()+cap, 460));
	painter->drawLine(QPoint(fontRect.width()+cap, 550),QPoint(widthDef+fontRect.width()+cap, 550));

	// Time 추출 - 타임 라인
	int timeCount = timeList.size();
	int lineWidth = (int)((widthDef-100)/timeCount);		// time pixel per line width
	int secWidth  = (int)(lineWidth/plus);						// 1 second per pixel
	int printWidth = lineWidth;

	//qDebug() << timeCount;
	for (int i=0; i<timeCount; i++) {
		// Time line 출력
		painter->drawLine(QPoint(fontRect.width()+cap+printWidth, 20),  QPoint(fontRect.width()+cap+printWidth, 640));
		painter->drawText(QPoint(fontRect.width()+printWidth, 640+15), timeList[i].toString("hh:mm:ss"));

		printWidth += lineWidth;
	}

	//qDebug() << "secWidth : " << secWidth << ", lineWidth : " << lineWidth;

	// 고도에 따른 트랙 출력
	QTime minTime = timeList.at(0);

	// 데이터 블록은 서로 겹쳐 보일 수 있으로 출력시 +- 80 으로 해서 지그재그로 보일 수 있도록 한다.
	int dataBlock = 80;
	int idx       = 0;

	for (int i=0; i<model.size(); i++) {
		// TrackDataModel
		//qDebug() << "dataModel size : " << model[i].dataModel.size();
		for (int j=0; j<model[i].dataModel.size(); j++) {
			//qDebug() << model[i].dataModel[j].occur_dt;

			if (mode == 0) {		// altitude
				if (model[i].dataModel[j].alt == 0) continue;		   // alt = 0 에 대해서 처리하지 않는다.
			}else if(mode == 1) {	// speed
				if (model[i].dataModel[j].spd == 0) continue;			// spd = 0 에 대해서 처리하지 않는다.
			}
			idx++;

			QString occur_dt = model[i].dataModel[j].occur_dt;		// datetime
			QString tm = occur_dt.right(8);
			QTime t = QTime::fromString(tm, "hh:mm:ss");
			int sec = minTime.secsTo(t);

			int secPixel = sec * secWidth;

			//qDebug() << "sec : " << sec << ", secPixel : " << secPixel;
			QString fullname;
			if (model[i].dataModel[j].psr == "0" && model[i].dataModel[j].ssr == "1") {       // PSR only
				fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg("psr_only.xpm");
			}else if (model[i].dataModel[j].psr == "1" && model[i].dataModel[j].ssr == "0") { // SSR only
				fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg("ssr_only.xpm");
			}else if(model[i].dataModel[j].cst == "1") {									// Coasting
				fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg("coasting_only.xpm");
			}else {
				fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg(model[i].symbol);
			}

			//QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg(model[i].symbol);
			QPixmap icon2;
			icon2.load(fullname);
			QPixmap icon = icon2.scaled(QSize(10, 10));

			QPixmap batang(QSize(icon.width()+1, icon.height()+1));
			batang.fill(QColor(0, 0, 0));

			QPainter pp(&batang);
			pp.drawPixmap(0, 0, icon);

			// 고도
			int alt = 0;

			if (mode == 0) {			// Altitude
				alt = model[i].dataModel[j].alt;				// unit = FL
				alt = alt * 25;	// 1FL = 25 ft
			}else if(mode == 1) {	// Speed
				alt = (int)model[i].dataModel[j].spd;		// unit = NM
			}

			int fixel = 0;

			if (mode == 0) {			// Altitude
				// max 고도에서 640을 나눈 값을 곱한다.
				double s = 544.0 / maxData;
				// 1ft = 0.018 fixel
				fixel = (int)(s * alt);	// 고도 대 픽셀 위치

				qDebug() << "s : " << s << ", fixel : " << fixel;
			}else if(mode == 1) {	// Speed
				double s = 544.0 / maxData;
				fixel = (int)(s * alt);	   // 속도 대 픽셀 위치
			}

			painter->drawPixmap(QPoint(fontRect.width()+18+lineWidth+secPixel, 640 - fixel), batang);

			// Altitude와 Speed가 같다면 계속적으로 데이터 블럭을 표현할 필요가 없다.
			if (model[i].dataModel[j].alt == model[i].dataModel[j].prev_alt
					&& model[i].dataModel[j].spd == model[i].dataModel[j].prev_spd) {
				continue;
			}

			// 데이터 블럭 출력 옵션에 따라서 출력한다.
			if (rptOption->blockCount > 0) {
				if ((j+1) != 1) {		// first data
					//qDebug() << "blockCount : " << rptOption->blockCount;
					//qDebug() << "myNumber   : " << (j+1);
					//qDebug() << "cal        : " << ((j+1) / rptOption->blockCount);
					if ((j+1) % rptOption->blockCount != 0) {
						continue;
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Data block define
			QPen pen(Qt::black);
			QColor textColor = Qt::black;
			painter->setPen(pen);
			if (idx%2) {
				dataBlock = -40;
			}else {
				dataBlock = +80;
			}


			QString msg = "";
			//////////////////////////////////////////////////////////////
			// 경보 상태가 있다면...

			//////////////////////////////////////////////////////////////
			int found = 0;
			int tmpHeight = 15;
			if (rptOption->trackNumber && model[i].dataModel[j].type == 0) {	// track data
				msg += QString("%1").arg(model[i].trackNo);
			}else {
				msg += "     ";
			}
			if (rptOption->ssr && model[i].dataModel[j].type == 0) {		// ReportOption check
				msg += QString("/%1").arg(model[i].ssr)+"\n";
			}else {
				msg += "    \n";
			}
			tmpHeight += 15;

			// 하강, 상승
			QString climb;
			if (model[i].dataModel[j].climb > 0) {		// 상승
				climb = "^";
			}else if(model[i].dataModel[j].climb == 0) {  // 수평비행
				climb = "-";
			}else {
				climb = "V";
			}
			QString cfl;
			if (model[i].dataModel[j].cfl == 0) {
				cfl = "";
			}else {
				cfl = QString("%1").arg(model[i].dataModel[j].cfl);
			}
			// 고도 | 상승,하강 | 배정고도 | 속도
			found = 0;
			QString tmp = "";
			if (rptOption->modec) {
				msg += QString("%1 %2 ").arg(model[i].dataModel[j].alt).arg(climb);
				found = 1;
			}else {
				msg += "    ";
			}
			if (rptOption->assignedFL && model[i].dataModel[j].type == 0) {
				msg += QString( "%1 ").arg(cfl);
				found = 1;
			}else {
				msg += "   ";
			}
			if (rptOption->velocity) {
				msg += QString(" /%1 \n").arg((int)model[i].dataModel[j].spd);
				found = 1;
			}else {
				msg += " /  \n";
			}
			tmpHeight += 15;
			QString callsign = model[i].callsign;
			if (callsign != "" && rptOption->callsing) {
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


			tmpHeight += 5;

			QRectF rect(
							QPointF(fontRect.width()+18+lineWidth+secPixel - 45, 640 - fixel - 50+dataBlock),
							QSizeF(100, tmpHeight));

			painter->drawRect(rect);
			painter->setPen(textColor);
			painter->drawText(rect, Qt::AlignCenter, msg);

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Line
			int dim1 = 5;
			int dim2 = -10;
			painter->setPen(pen);

			if (idx%2) {
				painter->drawLine(QLineF(QPointF(fontRect.width()+18+lineWidth+secPixel+dim1,  640 - fixel - 50+dataBlock + 50),
						QPointF(fontRect.width()+18+lineWidth+secPixel+dim1, 640 - fixel - dim2)));
			}else {
				painter->drawLine(QLineF(QPointF(fontRect.width()+18+lineWidth+secPixel+dim1,  640 - fixel - 50+dataBlock ),
						QPointF(fontRect.width()+18+lineWidth+secPixel+dim1, 640 - fixel - dim2)));
			}
		}
	}

}

QRectF VerticalViewItem::boundingRect() const
{
	QRectF rect = QRectF(0, 0, 1033, 624);

	return rect;
}

int VerticalViewItem::getMaxAlt()
{

	int max = 0;
	for (int i=0; i<model.size(); i++) {
		// TrackDataModel
		//qDebug() << "dataModel size : " << model[i].dataModel.size();
		for (int j=0; j<model[i].dataModel.size(); j++) {
			//qDebug() << model[i].dataModel[j].occur_dt;

			if (mode == 0) {		// altitude
				if (model[i].dataModel[j].alt > max)
				{
					max = model[i].dataModel[j].alt;
				}
			}else if(mode == 1) {	// speed
				if ((int)model[i].dataModel[j].spd > max)
				{
					max = (int)model[i].dataModel[j].spd;
				}
			}
		}
	}
	return max;
}
