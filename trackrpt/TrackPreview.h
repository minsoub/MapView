/*
 * TrackPreview.h
 *
 *  Created on: 2012. 5. 03.
 *      Author: JMS
 *  Description : Preview Track Data report
 */
#ifndef TRACKPREVIEW_H
#define TRACKPREVIEW_H

#include <QtGui>
#include "ui_TrackPreview.h"
#include "LegendItem.h"
#include "../lib/AirPlaneModel.h"

class TrackPreview : public QWidget, public Ui::TrackPreviewClass
{
    Q_OBJECT

public:
    TrackPreview(QWidget *parent = 0);
    ~TrackPreview();

    void setSceneSize(QRectF rect);
    void setScene(QVector<TrackDataModel> data, QPixmap *image);
private:
    QGraphicsScene *scene;
    LegendItem *item;
private slots:
	void trackPrint();
	void previewClose();
};

#endif // TRACKPREVIEW_H
