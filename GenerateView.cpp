/*
 * GenerateView.cpp
 *
 *  Created on: 2012. 1. 16.
 *      Author: JMS
 *  Description : QGraphicsView를 상속받아 QGraphicsScene 클래스를 제어한다.
 */
#include <cmath>
#include <iostream>
#include "GenerateView.h"
#include "./item/AreaLayerItem.h"

GenerateView::GenerateView(QWidget *parent):QGraphicsView(parent) {
	// TODO Auto-generated constructor stub
	//setDragMode(ScrollHandDrag);		// 이모드는 마우스 이벤트를 잡기 때문에 마우스 포인트를 구할 수가 없다.

	// TODO : 20130108 modify - jms
	//setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	//setRenderHint(QPainter::Antialiasing);
	//setCacheMode(QGraphicsView::CacheBackground);
	setDragMode(QGraphicsView::RubberBandDrag);
	//setInteractive(true);
   //setTransformationAnchor(AnchorUnderMouse);
   //setResizeAnchor(AnchorViewCenter);



	//setRubberBandSelectionMode(Qt::IntersectsItemShape);

	// 정확한 ViewPort의 크기를 구하기 위해서는 ScrollBar를 제거해야 한다.
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setOptimizationFlag(QGraphicsView::DontClipPainter);
	setOptimizationFlag(QGraphicsView::DontSavePainterState);
	setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);

	// bug fix
	//this->rotate(-90);
	drawing = false;
	startDrawing = false;
	//connect(this, SIGNAL(setChangeZoom(double)), this, SLOT(changeZoom(double)));
}

/**
 * Mouse Wheel의 ZoomIn, ZoomOut을 처리한다.
 */
void GenerateView::wheelEvent(QWheelEvent *event)
{

//	double numDegrees = -event->delta() / 8.0;
//	double numSteps   = numDegrees / 15.0;
//	double factor     = std::pow(1.125, numSteps);
//
//	scale(factor, factor);
//
//	return;

	if (drawing == true) return;

	if (event->orientation() == Qt::Horizontal) {
		if (event->delta() > 0) {
			zoomIn();
		}else {
			zoomOut();
		}
	}else {
		if (event->delta() > 0) {
			zoomIn();
		}else {
			zoomOut();
		}
	}
	//refreshPixmap();
}

void GenerateView::zoomIn() {
	double mpp = vp->mpp();
	double percent = 10;
	mpp -= (mpp * percent / 100);
	if (mpp <= 10) { mpp = 10; }
	vp->setMeterPerPixel((int)floor(mpp));

	//refreshPixmap();
	emit setChangeZoom(vp->mpp());
}

void GenerateView::zoomOut() {
	double mpp = vp->mpp();
	double percent = 10;
	mpp += (mpp * percent / 100);
	if (mpp > 46000) { mpp = 46000; }
	vp->setMeterPerPixel((int)floor(mpp));

	//refreshPixmap();
	emit setChangeZoom(vp->mpp());
}

void GenerateView::changeZoom(double zoom)
{
	vp->setMeterPerPixel(zoom);
	refreshPixmap();
}

void GenerateView::mousePressEvent(QMouseEvent* event)
{

	qDebug() << "mousePressEvent called..........";
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
		mouseXY = event->pos();

		if (vp->srcRect().contains(event->pos())) {
			if (userItem->type() == Select) {
				if (mode == DistanceBearing) {
					distbear->mPress(event);
				}else {
					if (event->button() == Qt::LeftButton) {
						rubberBandRect.setTopLeft(event->pos());
						rubberBandRect.setBottomRight(event->pos());
					}

					//log->print("mousePressEvent called...");
					// item selected..
					QList<QGraphicsItem*> itemList = this->scene()->selectedItems();
					//QList<QGraphicsItem*> itemList = items(event->pos());
					if (DEBUG_MODE) {
						qDebug() << "items count : " << itemList.count();
						for (int i=0; i<itemList.count(); i++) {
							qDebug() << "items type : " << itemList[i]->type();
						}
						qDebug() << QString("mousePressEvent SelectedItems count : %1").arg(itemList.count());
					}
					startDrawing = true;

					for (int i=0; i<itemList.size(); i++) {
						if (DEBUG_MODE) {
							qDebug() << "press : " << QString("items[%1] type : %2").arg(i).arg(itemList[i]->type());
						}
						if ( itemList[i]->type() == 1000 || itemList[i]->type() == 998) {
							itemList[i]->setSelected(true);
							if (DEBUG_MODE) {
								qDebug() << QString("press items[%1] type : %2").arg(i).arg(itemList[i]->type());
							}
							if (itemList[i]->type() == 1000) {
								AirPlaneTextItem* item = dynamic_cast<AirPlaneTextItem*>(itemList[i]);
								item->setMoving(true);
								//break;
							}else if(itemList[i]->type() == 998) {
								AUserLayerItem* item = dynamic_cast<AUserLayerItem*>(itemList[i]);
								item->setMoving(true);
								QRectF rect = item->boundingRect();
								//log->print(QString("mousePressEvent prev center : (%1, %2)").arg(rect.center().x()).arg(rect.center().y()));
								//log->print(QString("mousePressEvent prev size : (width, height) = (%1, %2)").arg(rect.width()).arg(rect.height()));
								//break;
							}
						}
					}
				}
			}else {		// user item drawing..
				setCursor(Qt::CrossCursor);
				userItem->mPress(event);
			}
		}
	}
	QGraphicsView::mousePressEvent(event);

	//log->print("mousePressEvent called...end");
}

void GenerateView::mouseMoveEvent(QMouseEvent *event)
{
	mouseXY = event->pos();
	if (!vp->srcRect().contains(mouseXY)) {
		//QGraphicsView::mouseMoveEvent(event);
		//log->print(QString("mouseMoveEvent extra called (w, h) = (%1, %2), mouse point (x, y) = (%3, %4)")
		//		.arg(vp->srcRect().width()).arg(vp->srcRect().height())
		//		.arg(mouseXY.x()).arg(mouseXY.y()));
		unsetCursor();
		return;
	}

	if (userItem->type() == Select) {
		if (mode == DistanceBearing) {
			QPoint sp = distbear->startPoint();
			double d = vp->distance(sp, event->pos());
			d = UnitChange::meterToHaeri(d);
			QString dist = QLocale(QLocale::English).toString(d, 'f', 2);
			QString bearing = QString("%1").arg(vp->bearing(sp, event->pos()), 0, 'f', 2);
			distbear->mMove(event, dist, bearing);
		}else {

			QList<QGraphicsItem*> itemList = this->scene()->selectedItems();
			//QList<QGraphicsItem*> itemList = items(event->pos());
			//log->print(QString("mouseMoveEvent SelectedItems count : %1").arg(items.count()));
			for (int i=0; i<itemList.count(); i++) {
				//log->print(QString("item type : %1 ").arg(items[i]->type()));
				if (DEBUG_MODE) {
					qDebug() << QString("move item type : %1 ").arg(itemList[i]->type());
					qDebug() << "startDrawing : " << startDrawing;
				}
				if ( itemList[i]->type() == 1000 && startDrawing) {
					AirPlaneTextItem* item = dynamic_cast<AirPlaneTextItem*>(itemList[i]);

					setCursor(Qt::OpenHandCursor);
					if (DEBUG_MODE) {
						qDebug() << QString("AirPlaneTextItem mouseMoveEvent in called  mouse point (x, y) = (%1, %2)")
									.arg(mouseXY.x()).arg(mouseXY.y());
					}
					item->setCurrentPosition(event->posF());
					// line을 다시 그려야 한다.
					refreshPixmap();
					//break;
				}else if(itemList[i]->type() == 998 && startDrawing){
					AUserLayerItem* item = dynamic_cast<AUserLayerItem*>(itemList[i]);
					if (!item->layerVisible()) continue;
					setCursor(Qt::OpenHandCursor);

					item->updateMove(event->pos());
					refreshPixmap();
				}
			}
		}
	}else {
		userItem->mMove(event);
		refreshPixmap();
	}

	//log->print("mouseMoveEvent called...3");
	// 마우스의 위치가 변경되었음을 알려준다.
	//std::cout << "GenerateView mouseMoveEvent called...........\n";
	emit changeMousePos(QString("%1,%2").arg(mouseXY.x()).arg(mouseXY.y()));
	QPointF p = vp->screenToDecimal(mouseXY);
	emit changeLatLonPos(QString("%1").arg(vp->toDMSHuman(p)));
	//log->print("mouseMoveEvent called...4");

	//QGraphicsView::mouseMoveEvent(event);		// 에러가 발생함..

	//log->print("mouseMoveEvent called...end ");
}

void GenerateView::mouseReleaseEvent(QMouseEvent *event)
{

//	mouseXY = event->pos();
//	if (!vp->srcRect().contains(mouseXY)) {
//		//QGraphicsView::mouseMoveEvent(event);
//		log->print(QString("mouseReleaseEvent extra called (w, h) = (%1, %2), mouse point (x, y) = (%3, %4)")
//				.arg(vp->srcRect().width()).arg(vp->srcRect().height())
//				.arg(mouseXY.x()).arg(mouseXY.y()));
//		unsetCursor();
//		refreshPixmap();
//		return;
//	}

	//log->print("mouseReleaseEvent called...");

	// 오른쪽 버튼일 때 마우스 포인트를 원점으로
	if (userItem->type() == Select && event->button() == Qt::RightButton) {
		QPointF p = vp->screenToDecimal(event->pos());
		vp->moveNorthPoint(p.x());
		vp->moveGreenichPoint(p.y());
		refreshPixmap();
		return;
	}

	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
		// event->pos()에 따라서 동작을 기술한다.
		if (userItem->type() == Select) {
			if (mode == DistanceBearing) {
				distbear->mRelease();
			}else {
				// RubberBandRect
				if (event->button() == Qt::LeftButton) {
//					rubberBandRect.setBottomRight(event->pos());
//
//					double mpp_sum = ( vp->srcWidth() * vp->srcHeight()) / (rubberBandRect.width() * rubberBandRect.height());
//					double mpp = vp->mpp()/mpp_sum;  // - (vp->mpp() * mpp_sum / 100);
//
//					//log->print(QString("mpp_sum : %1").arg(mpp_sum));
//					//log->print(QString("mpp : %1").arg(mpp));
//					if (mpp_sum > 30) {
//						QGraphicsView::mouseReleaseEvent(event);
//						return;
//					}
//					QPointF p = vp->screenToDecimal(rubberBandRect.center());
//					vp->moveNorthPoint(p.x());
//					vp->moveGreenichPoint(p.y());
//
//					if (mpp < 60) { mpp = 60; }
//					vp->setMeterPerPixel((int)floor(mpp));
//					emit setChangeZoom(vp->mpp());

					if ( mouseXY.x() == event->pos().x() && mouseXY.y() == event->pos().y() )
					{
						unsetCursor();
						refreshPixmap();
						startDrawing = false;
					}else {
						QList<QGraphicsItem*> itemList = this->scene()->selectedItems();
						//QList<QGraphicsItem*> itemList = items(event->pos());
						//log->print(QString("mouseReleaseEvent SelectedItems count : %1").arg(items.count()));
						for (int i=0; i<itemList.count(); i++) {
							//log->print(QString("item type : %1").arg(items[i]->type()));
							if (itemList[i]->type() == 1000 ) {
								AirPlaneTextItem* item = dynamic_cast<AirPlaneTextItem*>(itemList[i]);
								if (vp->srcRect().contains(mouseXY)) {
									item->setCurrentPosition(event->posF());
									// items[i]->setPos(event->posF());
									item->update();
								}
								itemList[i]->setSelected(false);
								item->setMoving(false);

							}else if(itemList[i]->type() == 998) {
								itemList[i]->setSelected(false);
								AUserLayerItem* item = dynamic_cast<AUserLayerItem*>(itemList[i]);
								item->setMoving(false);
								//log->print("GenerateView mouseReleaseEvent item moveable complete");

							}
							unsetCursor();
							refreshPixmap();
							startDrawing = false;
						}
					}
				}
			}
		}else {
			userItem->mRelease(event);
			unsetCursor();
			//log->print("userItem mRelease called..... job type convert...");
			if (userItem->isFinish()) {
				emit userFinishedDrawCall();	// MapCanvas의 finishedDraw 메소드 호출하기 위한 시그널
			}

			// left panel call..
			emit leftPanelWidgetChange();		// MapCanvas에서 LeftPanel 위젯을 reload 한다
		}
	}
	QGraphicsView::mouseReleaseEvent(event);
}

inline static bool caseInsensitiveLessThan(const QGraphicsItem* item1, const QGraphicsItem* item2)
{
	if (item1->type() < item2->type()) {
		return true;
	}else {
		return false;
	}
}

/**
 * Scene에 등록된 QGraphicsItem 클래스를 모두 repaint 한다.
 */
void GenerateView::refreshPixmap()
{
	drawing = true;
	QList<QGraphicsItem *> items = this->items();

	// type이 적은 순서로 해서 정렬한다.
	//qSort(items.begin(), items.end(), caseInsensitiveLessThan);

	for (int i=0; i<items.size(); i++) {
		//if (items[i]->type() == 999) {
		//	items[i]->show();
		//}
		if (items[i]->type() == 4) {  // area
			AreaLayerItem* item = (AreaLayerItem*)items[i];
			item->updateInfo();
		}else {
			items[i]->update();
		}
	}


	drawing = false;
}
