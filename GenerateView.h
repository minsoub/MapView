/*
 * GenerateView.h
 *
 *  Created on: 2012. 1. 16.
 *      Author: JMS
 *  Description : QGraphicsView를 상속받아 QGraphicsScene 클래스를 제어한다.
 */

#ifndef GENERATEVIEW_H_
#define GENERATEVIEW_H_

#include <QtGui>
#include <QGraphicsView>
#ifndef LATLONCONVERT_H_
#include "lib/LatLonConvert.h"
//#define LATLONCONVERT_H_
#endif
#include "lib/Log424.h"
#include "item/UserDrawItem.h"
#include "item/AirPlaneTextItem.h"
#include "item/AUserLayerItem.h"
#include "item/DirBearing.h"

#define DEBUG_MODE	0

//#include "lib/NorthGreenichPoint.h"
class GenerateView : public QGraphicsView
{
	Q_OBJECT

public:
	GenerateView(QWidget *parent=0);
	void setScreenConvertClass(LatLonConvert *vp) { this->vp = vp; }
	void refreshPixmap();
	void setLog(Log424* log) { this->log = log; }
	void setUserDrawItem(UserDrawItem* item) { userItem = item; }
	void setUserDistBearing(DirBearing* item) { distbear = item; }
	//void setNorthGreenichPoint(NorthGreenichPoint *northGreenich) { this->northGreenich = northGreenich; }
	int  mode;
public slots:
	void changeZoom(double zoom);
	void zoomIn();
	void zoomOut();
private:
	enum ModeType { Normal, DistanceBearing };
	LatLonConvert *vp;
	Log424* log;
	bool drawing;
	bool startDrawing;
	QPoint mouseXY;
	UserDrawItem* userItem;
	DirBearing*   distbear;
	QRect rubberBandRect;
	//bool caseInsensitiveLessThan(const QGraphicsItem* item1, const QGraphicsItem* item2);
protected:
	void wheelEvent(QWheelEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void mousePressEvent(QMouseEvent* event);
signals:
	void setChangeZoom(double zoom);
	void changeMousePos(const QString& msg);
	void changeLatLonPos(const QString& msg);
	void changeStatusMessage(const QString& msg);
	void userFinishedDrawCall();
	void leftPanelWidgetChange();			// MapCanvas에 왼쪽 판넬의 reload를 위해서 발생시키는 시그널
};

#endif /* GENERATEVIEW_H_ */
