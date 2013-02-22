/*
 * LegendItem.h
 *
 *  Created on: 2012. 5. 3.
 *      Author: JMS
 *  Description : Print legend of preview screen.
 */

#ifndef LEGENDITEM_H_
#define LEGENDITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "TrackDataModel.h"

class LegendItem : public QGraphicsItem {
public:
	LegendItem();
	LegendItem(int ims, QRectF size);
	~LegendItem();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	void setSize(int ims, QRectF size) { imgSize = ims, rect = size; }
	void setTrackData(QVector<TrackDataModel> data);
private:
	QRectF rect;
	int imgSize;
	QVector<TrackDataModel> model;

	QString getColorName(QColor color);
};

#endif /* LEGENDITEM_H_ */
