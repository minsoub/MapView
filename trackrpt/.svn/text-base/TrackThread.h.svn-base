/*
 * TrackThread.h
 *
 *  Created on: 2012. 5. 8.
 *      Author: JMS
 *  Description : Track 데이터 처리하는 Thread
 *                DRS 데이터베이스에 접속해서 Track 데이터를 가져온다.
 *                Thread를 사용하는 이유는 대용량 데이터를 한번에 가져오면 시스템이 늦기 때문에
 *                     여러개의 Thread로 나뉘어서 데이터를 가져온다.
 */

#ifndef TRACKTHREAD_H_
#define TRACKTHREAD_H_
#include <QtCore>
#include <QtSql>
#include "../asterix/DecodeAsterix.h"
#include "../asterix/lib/CBuffer.h"
#include "../asterix/cat062/Cat062.h"
#include "../lib/DbManager.h"
#include "../lib/Log424.h"
#include "../lib/ConfigParser.h"
#include "../asterix/lib/Base64.h"
#include <sqlcli.h>
#include "../asterix/lib/Base64.h"
#define BUF_LEN		(1024 * 32)
#define MSG_LEN          (1024)
class TrackThread : public QThread {
	Q_OBJECT
public:
	TrackThread();
	~TrackThread();
	void setLog(Log424* log) { this->log = log; }
	void setCondition(QString from, QString to) { this->fromDt = from, this->toDt = to; }
	void setDbManager(DbManager* db) { this->dbManager = db; }
	void makeProcess(int cnt);
	void run();
	void setStop(bool stop) { isStop = stop; }
	void setDB(SQLHDBC &db, QString set) { dbc = db; isDB = set; }
private:
	QString fromDt;
	QString toDt;
	QList<QDateTime> loopList;
	DecodeAsterix asterix;
	DbManager* dbManager;
	Log424* log;
	int totalCount;
	bool isStop;
	Base64 base64;
	//bool dbOpen();
	bool dbUpdate(Cat062&,   QString);
	bool dbUpdate21(Cat021&, QString);
	bool dbUpdate04(Cat004&, QString);
	bool dbUpdate04(QStringList, QString);
	bool dbDelete();
	SQLHENV			env;
	SQLHDBC			dbc;
	SQLRETURN		rc;
	int				conn_flag;
	QString        isDB;
	void execute_err(SQLHDBC aCon, SQLHSTMT aStmt, char* q);
signals:
	void valueChanged(int changed);
};

#endif /* TRACKTHREAD_H_ */
