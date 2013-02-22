/*
 * TrackReportOption.h
 *
 *  Created on: 2012. 5. 09.
 *      Author: JMS
 *  Description : 데이터 블록에 현시할 수 있는 리스트를 보여준다.
 *                     사용자가 데이터 블록에 현시 할 리스트를 선택하면 맵을 다시 그려야 한다..
 */
#ifndef TRACKREPORTOPTION_H
#define TRACKREPORTOPTION_H

#include <QtGui/QWidget>
#include "ui_TrackReportOption.h"
#include "ReportOption.h"

class TrackReportOption : public QWidget, public Ui::TrackReportOptionClass
{
    Q_OBJECT

public:
    TrackReportOption(QWidget *parent = 0);
    ~TrackReportOption();

    void refreshList(ReportOption *opt);
private:
    ReportOption *option;
    void setFlag(QString data);
private slots:
	 void listLeft();
	 void listRight();
	 void optionSave();
signals:
	 void setReportOption();
};

#endif // TRACKREPORTOPTION_H
