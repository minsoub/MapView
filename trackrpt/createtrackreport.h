/*
 * CreateTrackReport.h
 *
 *  Created on: 2012. 4. 12.
 *      Author: JMS
 *  Description : System Track 데이터를 조회할 날짜를 선택할 수 있는 폼
 */
#ifndef CREATETRACKREPORT_H
#define CREATETRACKREPORT_H

#include <QtGui>
#include "ui_createtrackreport.h"

class CreateTrackReport : public QDialog, public Ui::CreateTrackReportClass
{
    Q_OBJECT

public:
    CreateTrackReport(QWidget *parent = 0);
    ~CreateTrackReport();

private slots:
	void createTrackStart();
signals:
	void setCreateTrackReport(QString&, QString&);
};

#endif // CREATETRACKREPORT_H
