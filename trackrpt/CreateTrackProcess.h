/*
 * CreateTrackProcess.h
 *
 *  Created on: 2012. 4. 26.
 *      Author: JMS
 *  Description : System Track 데이터를 생성해서 데이터베이스에 저장한다.
 */

#ifndef CREATETRACKPROCESS_H_
#define CREATETRACKPROCESS_H_
#include <QtCore>
#include <QtSql>
#include "../asterix/DecodeAsterix.h"
#include "../asterix/lib/CBuffer.h"
#include "../asterix/cat062/Cat062.h"
#include "../lib/DbManager.h"
#include "../lib/Log424.h"
#include "../lib/ConfigParser.h"
#include "TrackThread.h"


#include <sqlcli.h>
#define DRS_DB_IP	"opdrs01"
#define DRS_DB_PORT	20300
#define DRS_DB_USER	"neo"
#define DRS_DB_PASS	"neo1234"
#define NLS				"US7ASCII"
#define BUF_LEN		(1024 * 32)
#define MSG_LEN          (1024)

// If drs db is altibase, set up DB 'ALTIBASE'
#define DB		"ALTIBASE"				// ALTIBASE, ORACLE

class CreateTrackProcess : public QObject {

	Q_OBJECT

public:
	CreateTrackProcess(QObject* parent = 0);
	~CreateTrackProcess();

	void setDate(QString ft, QString tt) { fromDt = ft, toDt = tt; }
	int getCount();
	bool trackProcess();
	void setLog(Log424* log) { this->log = log; }
	bool dbSMSDOpen();
private:
	QString fromDt;
	QString toDt;
	DecodeAsterix asterix;
	DbManager* dbManager;
	Log424* log;
	TrackThread thread;

	int count;
	bool dbOpen();
	bool dbUpdate(Cat062&);
	bool dbDelete();
	bool altibase_connect();
	SQLRETURN alt_connect();
	SQLRETURN alti_alloc_handle();
	void alti_free_handle();
	void execute_err(SQLHDBC aCon, SQLHSTMT aStmt, char* q);

	SQLHENV			env;
	SQLHDBC			dbc;
	SQLRETURN		rc;
	int				conn_flag;
public slots:
	void threadStop();
signals:
	void valueChanged(int changed);
};

#endif /* CREATETRACKPROCESS_H_ */
