/*
 * TrackDataModel.cpp
 *
 *  Created on: 2012. 4. 30.
 *      Author: JMS
 *   맵 에디터에 출력된 트랙 데이터 모델을 정의한다.
 */

#include "TrackDataModel.h"

TrackDataModel::TrackDataModel() {
	// TODO Auto-generated constructor stub
	ssr			= "";
	callsign		= "";
	trackNo		= "";
	alert			= "";
	symbol    	= "";
	dbmanager   = NULL;
	dataModel.clear();
	trackModel.clear();
}

TrackDataModel::~TrackDataModel() {
	// TODO Auto-generated destructor stub
	if (dbmanager != NULL) delete dbmanager;
}

/**
 * TB_TRK 테이블에서 데이터를 가져와서 비행데이터를 구성한다.
 */
bool TrackDataModel::trackDataSearch()
{
	QString sql;
	QSqlQuery *query;

	if (dbmanager == NULL) {
		dbmanager = new DbManager;
		dbmanager->setLog(log);
		bool b = dbmanager->setDb(ConfigParser::getInstance().driver(),
				ConfigParser::getInstance().host(),
				ConfigParser::getInstance().db(),
				ConfigParser::getInstance().user(),
				ConfigParser::getInstance().password(),
				ConfigParser::getInstance().port());
		if (b == false) {
			return false;
		}
	}

	query = new QSqlQuery(QSqlDatabase::database(dbmanager->dbName()));

	sql  = "SELECT TO_CHAR(OCCUR_DT, 'yyyy-MM-dd HH24:MI:SS') occur_dt,      ";
	sql += "       LAT, LON, SPD, HEADING, MLT_ALT, ALT, QNH, CLIMB_DESCENT, ";
	sql += "       SPI_CHK, MRH_CHK, CNF_CHK, SIM_CHK, TSE_CHK, FPC_CHK,     ";
	sql += "       CST_CHK, PSR_CHK, SSR_CHK, MDS_CHK, ADS_CHK               ";
	sql += "  FROM TB_TRK                                                    ";
	sql += " WHERE                                                           ";
	sql += "       SSR = ?                                                   ";
	sql += "   AND TRK_NO = ?                                                ";
	//sql += "   AND CALLSIGN = ?                                              ";
	sql += " ORDER BY OCCUR_DT                                               ";
	query->prepare(sql);
	query->addBindValue(ssr);
	query->addBindValue(trackNo);
	//query->addBindValue(callsign);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		qDebug() << query->lastError().text();
		query->finish();
		delete query;
		return false;
	}
	while(query->next()) {
		TrackData data;

		data.occur_dt = query->value(0).toString();
		data.lat      = query->value(1).toDouble();
		data.lon      = query->value(2).toDouble();
		data.spd      = query->value(3).toDouble();
		data.heading  = query->value(4).toDouble();
		data.mlt_alt  = query->value(5).toInt();
		data.alt      = query->value(6).toInt();
		data.qnh      = query->value(7).toString();
		data.climb    = query->value(8).toInt();
		data.spi      = query->value(9).toString();
		data.mrh      = query->value(10).toString();
		data.cnf      = query->value(11).toString();
		data.sim      = query->value(12).toString();
		data.tse      = query->value(13).toString();
		data.fpc      = query->value(14).toString();
		data.cst      = query->value(15).toString();
		data.psr      = query->value(16).toString();
		data.ssr      = query->value(17).toString();
		data.mds      = query->value(18).toString();
		data.ads      = query->value(19).toString();

		dataModel.push_back(data);
	}
	query->finish();
	delete query;
	return true;
}
