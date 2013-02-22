/*
 * VerticalViewControl.cpp
 *
 *  Created on: 2012. 5. 7.
 *      Author: JMS
 *  Description : Vertical View의 컨트롤 창을 제어한다.
 */
#include <cmath>
#include <iostream>
#include "VerticalViewControl.h"

VerticalViewControl::VerticalViewControl(QWidget *parent):QGraphicsView(parent) {
	// TODO Auto-generated constructor stub
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setCacheMode(QGraphicsView::CacheBackground);
	setDragMode(QGraphicsView::RubberBandDrag);
	setInteractive(true);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);
}

VerticalViewControl::~VerticalViewControl() {
	// TODO Auto-generated destructor stub
}

/**
 * Mouse Wheel의 ZoomIn, ZoomOut을 처리한다.
 */
void VerticalViewControl::wheelEvent(QWheelEvent *event)
{

	double numDegrees = -event->delta() / 8.0;
	double numSteps   = numDegrees / 15.0;
	double factor     = std::pow(1.125, numSteps);

	scale(factor, factor);

	return;

}

/**
 * Zoom In 버튼을 클릭했을 때
 */
void VerticalViewControl::zoomIn()
{
	double numDegrees = 15;
	double numSteps   = numDegrees / 15.0;
	double factor     = std::pow(1.125, numSteps);

	scale(factor, factor);

	return;
}

/**
 * Zoom Out 버튼을 클릭했을 떄
 */
void VerticalViewControl::zoomOut()
{
	double numDegrees = -15;
	double numSteps   = numDegrees / 15.0;
	double factor     = std::pow(1.125, numSteps);

	scale(factor, factor);

	return;
}
