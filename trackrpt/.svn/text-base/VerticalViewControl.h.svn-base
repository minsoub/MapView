/*
 * VerticalViewControl.h
 *
 *  Created on: 2012. 5. 7.
 *      Author: JMS
 *  Description : Vertical View의 컨트롤 창을 제어한다.
 */

#ifndef VERTICALVIEWCONTROL_H_
#define VERTICALVIEWCONTROL_H_
#include <QtGui>
#include <QGraphicsView>

class VerticalViewControl : public QGraphicsView
{
	Q_OBJECT

public:
	VerticalViewControl(QWidget *parent=0);
	~VerticalViewControl();
	void zoomIn();
	void zoomOut();
protected:
	void wheelEvent(QWheelEvent *event);
};

#endif /* VERTICALVIEWCONTROL_H_ */
