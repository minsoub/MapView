/*
 * CreateTrackReport.cpp
 *
 *  Created on: 2012. 4. 12.
 *      Author: JMS
 *  Description : System Track 데이터를 조회할 날짜를 선택할 수 있는 폼
 */
#include "createtrackreport.h"

CreateTrackReport::CreateTrackReport(QWidget *parent)
    : QDialog(parent)
{
	setupUi(this);

	connect(btnOK, SIGNAL(clicked()), this, SLOT(createTrackStart()));
	connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));

	fromDt->setDate(QDate::currentDate());
	toDt->setDate(QDate::currentDate());
}

CreateTrackReport::~CreateTrackReport()
{

}

/**
 * Track Data를 조회할 날짜를 MapCanvas 클래스에 넘겨준다.
 * setCreateTrackReport 시그널을 호출해서 MapCanvas 클래스의 setCreateTrackReport slot을 호출한다.
 */
void CreateTrackReport::createTrackStart()
{
	QDate fromDate = fromDt->date();
	QDate toDate   = toDt->date();
	QTime fromTm   = fromTM->time();
	QTime toTm     = toTM->time();

	QDateTime from;
	QDateTime to;

	from.setDate(fromDate);
	to.setDate(toDate);
	from.setTime(QTime::fromString(fromTm.toString("hh:mm")+":00", "hh:mm:ss"));
	to.setTime(QTime::fromString(toTm.toString("hh:mm")+":59", "hh:mm:ss"));

	if (fromDate == toDate && fromTm == toTm) {
		QMessageBox::warning(this, tr("Date/Time Validation Error"), tr("From Date/Tiem should be before To Date/Time"));
		return;
	}

	if (from >= to) {
		QMessageBox::warning(this, tr("Date/Time Validation Error"), tr("From Date/Tiem should be before To Date/Time"));
		return;
	}

	QString strFrom = from.toString("yyyy-MM-dd hh:mm:ss");
	QString strTo   = to.toString("yyyy-MM-dd hh:mm:ss");

	emit setCreateTrackReport(strFrom, strTo);
	this->accept();
}
