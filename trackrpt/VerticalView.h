/*
 * VerticalView.h
 *
 *  Created on: 2012. 5. 04.
 *      Author: JMS
 *  Description : Vertical View display.
 */
#ifndef VERTICALVIEW_H
#define VERTICALVIEW_H

#include <QtGui>
#include "TrackDataModel.h"
#include "VerticalViewItem.h"
#include "VerticalViewControl.h"
#include "ReportOption.h"

//#include "ui_VerticalView.h"

class VerticalView : public QWidget  //, public Ui::VerticalViewClass
{
    Q_OBJECT

public:
    VerticalView(QWidget *parent = 0);
    ~VerticalView();

    void setTrackModel(QVector<TrackDataModel> m);
    void makeDisplay();
    void setReportOption(ReportOption* opt) { option = opt; }
private:
    QGraphicsScene *scene;
    QVector<TrackDataModel> model;
    VerticalViewItem* item;
    ReportOption* option;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line;
    VerticalViewControl *graphicsView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnZoomIn;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnZoomOut;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer_4;
    QComboBox   *cboSelect;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    void setupUi(QWidget *VerticalViewClass);
private slots:
	void ZoomIn();
	void ZoomOut();
	void selectedChange();
};

#endif // VERTICALVIEW_H
