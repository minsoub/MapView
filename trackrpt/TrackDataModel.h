/*
 * TrackDataModel.h
 *
 *  Created on: 2012. 4. 30.
 *      Author: JMS
 *   맵 에디터에 출력된 트랙 데이터 모델을 정의한다.
 */

#ifndef TRACKDATAMODEL_H_
#define TRACKDATAMODEL_H_

#include <QString>
#include <QVector>

#include "../lib/DbManager.h"
#include "../lib/ConfigParser.h"
#include "../lib/Log424.h"
#include "../lib/AirPlaneModel.h"
#include "TrackData.h"


class TrackDataModel {
public:
	TrackDataModel();
	~TrackDataModel();

	QString ssr;
	QString callsign;
	QString trackNo;
	QString alert;
	QString symbol;
	QColor  selectedColor;
	QString colorName;
	QString disTrack;
	QVector<TrackData> dataModel;
	QVector<AirPlaneModel*> trackModel;
	DbManager* dbmanager;

	bool trackDataSearch();
	void setLog(Log424 *l) { log = l; }
	QVector<TrackData> getTrackData() { return dataModel; }
private:
	Log424 *log;
};

#endif /* TRACKDATAMODEL_H_ */
