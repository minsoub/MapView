/*
 * TrackViewSelection.h
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : 생성된 트렉 데이터를 현시할 수 있는 옵션창을 보여준다.
 *                     데이터베이스에서 트렉 데이터를 그룹화해서 그리드 화면에 뿌려준다.
 */

#ifndef TRACKVIEWSELECTION_H
#define TRACKVIEWSELECTION_H

#include <QtGui>
#include "ui_TrackViewSelection.h"
#include "../lib/DbManager.h"
#include "../lib/Log424.h"
#include "../lib/ConfigParser.h"
#include "../lib/CustomItemDelegate.h"
#include "../lib/TrackViewQueryModel.h"
#include "TrackDataModel.h"
#include "TrackData.h"
#include "VerticalView.h"
#include "ReportOption.h"

class TrackViewSelection : public QWidget, public Ui::TrackViewSelectionClass
{
    Q_OBJECT

public:
    TrackViewSelection(QWidget *parent = 0);
    ~TrackViewSelection();
    void setLog(Log424* log) { this->log = log; }
    void trackDataSearch();
    void trackXmlRead(QXmlStreamReader* xml);
    void setReportOption(ReportOption* opt) { reportOption = opt; }
private:
	 DbManager* dbManager;
	 Log424* log;
	 VerticalView* view;
	 CustomItemDelegate* delegate;
	 QVector<TrackDataModel> model;
	 QVector<TrackDataModel> xmlModel;
	 ReportOption *reportOption;
	 int dataBlockCheck;
	 int xmlCheck;
	 QVector<TrackData> getTrackDetailInfo(QString ssr, QString callsign, QString trackNum);
	 QVector<TrackData> getADSBDetailInfo(QString ssr, QString callsign, QString trackNum);
	 int getColorIndex(QString colorName);
	 void makeGridView();
	 void removeAll();
protected:
	 void closeEvent(QCloseEvent *event);
private slots:
	void selectAll();
	void unSelectAll();
	void trackReport();
	void verticalView();
	void viewADSB();
	void viewDataBlock();
	void closeTrackData();
	void reportExcel();
signals:
	void trackReport(QVector<TrackDataModel>);
	void dataBlockPrint(int);
	void clearTrackData();
};

#endif // TRACKVIEWSELECTION_H
