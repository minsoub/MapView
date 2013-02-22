/*
 * VerticalViewItem.h
 *
 *  Created on: 2012. 5. 4.
 *      Author: JMS
  *  Description : paint item in Vertical View
 */

#ifndef VERTICALVIEWITEM_H_
#define VERTICALVIEWITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "TrackDataModel.h"
#include "ReportOption.h"

class VerticalViewItem : public QGraphicsItem {
public:
	VerticalViewItem(QVector<TrackDataModel> m);
	~VerticalViewItem();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void setReportOption(ReportOption* opt) { rptOption = opt; }
	void setMode(int m) { mode = m; }
private:
	QVector<TrackDataModel> model;
	QVector<QString> time;
	QVector<QTime>   timeList;
	ReportOption*    rptOption;
	int plus;
	int mode;
	int getMaxAlt();
};

#endif /* VERTICALVIEWITEM_H_ */
