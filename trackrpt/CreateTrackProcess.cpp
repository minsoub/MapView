/*
 * CreateTrackProcess.cpp
 *
 *  Created on: 2012. 4. 26.
 *      Author: JMS
 *  Description : System Track 데이터를 생성해서 데이터베이스에 저장한다.
 */

#include "CreateTrackProcess.h"

CreateTrackProcess::CreateTrackProcess(QObject* parent):QObject(parent) {
	// TODO Auto-generated constructor stub
	dbManager = NULL;
	count     = 0;
}

CreateTrackProcess::~CreateTrackProcess() {
	// TODO Auto-generated destructor stub
	if (dbManager != NULL) {
		delete dbManager;
	}
}

void CreateTrackProcess::threadStop()
{
	qDebug() << "CreateTrackProcess threadStop called....";
	thread.setStop(true);
	//thread.terminate();
}
/**
 * DRS에 등록된 데이터를 읽어서 Asterix Cat 62 데이터를 파싱해서 데이터베이스에
 * 등록한다.
 *
 */
bool CreateTrackProcess::trackProcess()
{
	if (count == 0) return false;

	QString sql;
	if (DB == "ORACLE" && dbOpen()) {		// DRS DB

		thread.setLog(log);
		thread.setDbManager(dbManager);
		thread.setCondition(fromDt, toDt);
		connect(&thread, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)), Qt::AutoConnection);
		thread.makeProcess(count);
		thread.start();

		thread.wait();

		if (thread.isFinished()) {
			qDebug() << "CreateTrackProcess::trackProcess completed....";
		}
	}else if(DB == "ALTIBASE" && altibase_connect()) {	// DRS DB - altibase
		thread.setDB(dbc, DB);
		thread.setLog(log);
		thread.setDbManager(dbManager);
		thread.setCondition(fromDt, toDt);
		connect(&thread, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)), Qt::AutoConnection);
		thread.makeProcess(count);
		thread.start();

		thread.wait();

		if (thread.isFinished()) {
			qDebug() << "CreateTrackProcess::trackProcess completed....";
		}
	}

	return true;
}


/**
 * DRS에 등록된 from~to 에 대한 데이터의 총개수를 리턴한다.
 */
int CreateTrackProcess::getCount()
{
	QString sql;
	SQLHSTMT stmt = SQL_NULL_HSTMT;

	if (DB == "ORACLE" && dbOpen()) {
		sql  = "SELECT COUNT(*)                                                         \n";
		sql += "  FROM STORE_ARCHIVE_P                                                  \n";
		sql += " WHERE SUBSYSTEM_CODE IN ('1', '2', '3')                                \n";
		sql += "   AND (                                                                \n";
      sql += "         (LOGCATEGORY1 = '1101' AND LOGCATEGORY2 = '0405') OR           \n";      // ADSB
      sql += "         (LOGCATEGORY1 = '1A01' AND LOGCATEGORY2 = '0201') OR           \n";    // System Track - New
      //sql += "         (LOGCATEGORY1 = '1A01' AND LOGCATEGORY2 = '0201') OR           \n";      // System Track - Old
      sql += "         (LOGCATEGORY1 = '0401' AND LOGCATEGORY2 = '0D01') OR           \n";      // System Track - Mini Plan
      sql += "         (                                                              \n";
      sql += "               (LOGCATEGORY1 = '1A08' AND LOGCATEGORY2 IN ('0801', '0802', '0804', '0808'))   \n";  // Safety Net Message - SDP
      //sql += "            OR (LOGCATEGORY1 = '0405' AND LOGCATEGORY2 IN ('0E01', '0E02', '0E03', '0E04'))   \n";  // Safety Net Message - FDP
      sql += "         )                                                              \n";
      sql += "       )                                                                \n";
		sql += "   AND TIMESTAMP BETWEEN TO_DATE('"+fromDt+"', 'yyyy-MM-dd HH24:MI:SS') \n";
		sql += "                     AND TO_DATE('"+toDt+"',   'yyyy-MM-dd HH24:MI:SS') \n";

		qDebug() << sql;
		QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("minsoub"));

		query->prepare(sql);

		query->exec();
		if (query->next()) {
			count = query->value(0).toInt();
		}
		query->finish();
		delete query;
	}else if(DB == "ALTIBASE" && altibase_connect()) {
		char query[1024];
		char ch_from_dt[19];
		char ch_to_dt[19];

		sprintf(query, " SELECT COUNT(*) FROM DRS_LOGDATA                                  \n"
				          " WHERE SUBSYSTEM_CODE IN ('1', '2', '3')                          \n"
							 " AND (                                                            \n"
							"       (LOGCATEGORY1 = '0101' AND LOGCATEGORY2 = '0301') OR       \n"                        // ADS-B
							"       (LOGCATEGORY1 = '0301' AND LOGCATEGORY2 = '0201') OR       \n"       // system Track
							"       (LOGCATEGORY1 = '0401' AND LOGCATEGORY2 = '0D01') OR       \n"       // System Track - Mini Plan
							"       (                                                          \n"
							"          (LOGCATEGORY1 = '0305' AND LOGCATEGORY2 IN ('0801', '0802', '0804', '0808'))    \n"                        // Safety Net Message - SDP
							//"       OR (LOGCATEGORY1 = '0405' AND LOGCATEGORY2 IN ('0E01', '0E02', '0E03', '0E04'))    \n"       // Safety Net Message - FDP
							"       )                                                          \n"
							"     )                                                            \n"
	                   "  AND TIMESTAMP >= TO_DATE(?, 'yyyyMMddHH24MISS')                 \n"
			             "  AND TIMESTAMP <  TO_DATE(?, 'yyyyMMddHH24MISS')                 \n"
				);
		QString fdt = fromDt;
		QString tdt = toDt;
		fdt = fdt.replace("-","").replace(":","").replace(" ","");
		tdt = tdt.replace("-","").replace(":","").replace(" ","");
		sprintf(ch_from_dt, (char *)fdt.toStdString().c_str());
		sprintf(ch_to_dt, (char *)tdt.toStdString().c_str());

		/* allocate Statement handle */
		if (SQL_ERROR == SQLAllocStmt(dbc, &stmt)) {
			qDebug() << "SQLAllocStmt error!!";
			return 0;
		}
		//char *sql_chr = (char *)sql.toStdString().c_str();

		qDebug() << query;
		if (SQLPrepare(stmt, (SQLCHAR *)query, SQL_NTS) != SQL_SUCCESS)
		{
			execute_err(dbc, stmt, "SQLPrepare error : ");
			SQLFreeStmt(stmt, SQL_DROP);
			return 0;
		}

		if (SQLBindParameter(stmt,
									1,
									SQL_PARAM_INPUT,
									SQL_C_CHAR,
									SQL_CHAR,
									19,
									0,
									ch_from_dt,
									sizeof(ch_from_dt),
									NULL) != SQL_SUCCESS)
		{
			execute_err(dbc, stmt, query);
			SQLFreeStmt(stmt, SQL_DROP);
			return 0;
		}
		if (SQLBindParameter(stmt,
									2,
									SQL_PARAM_INPUT,
									SQL_C_CHAR,
									SQL_CHAR,
									19,
									0,
									ch_to_dt,
									sizeof(ch_to_dt),
									NULL) != SQL_SUCCESS)
		{
			execute_err(dbc, stmt, query);
			SQLFreeStmt(stmt, SQL_DROP);
			return 0;
		}

		if (SQLBindCol(stmt,
							1,
							SQL_C_SLONG,
							&count,
							0,
							NULL) != SQL_SUCCESS)
		{
			qDebug() << "SQLBindCol error !!!!";
			execute_err(dbc, stmt, "SQLBindCol error !!!!");
			SQLFreeStmt(stmt, SQL_DROP);
			return 0;
		}

		if (SQLExecute(stmt) != SQL_SUCCESS)
		{
			execute_err(dbc, stmt, "SQLExecute : ");
			SQLFreeStmt(stmt, SQL_DROP);
			return 0;
		}

		if ((rc = SQLFetch(stmt)) != SQL_NO_DATA)
		{
			if (rc != SQL_SUCCESS)
			{
				execute_err(dbc, stmt, "SQLFetch error");
			}
		}
		SQLFreeStmt(stmt, SQL_DROP);
	}

	return count;
}

/**
 * DRS Db Open - Oracle (Test)
 */
bool CreateTrackProcess::dbOpen()
{
	if (QSqlDatabase::database("minsoub").isOpen()) return true;

	QSqlError err;
	QString host = "165.246.34.66";
	QString dbName = "ORCL";
	int port = 1521;
	QString user = "minsoub";
	QString password = "minsoub";
	QString driver = "QOCI";

	QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("minsoub"));
	db.setHostName(host);
	db.setDatabaseName(dbName);
	db.setPort(port);

	if (!db.open(user, password)) {
		qDebug() << "DB open error : " << db.lastError().text();
		return false;
	}
	return true;
}

/**
 * SMSD 데이터베이스를 연결한다.
 */
bool CreateTrackProcess::dbSMSDOpen()
{
	if (dbManager == NULL) {
		dbManager = new DbManager();
		dbManager->setLog(log);
	}

	bool b = dbManager->setDb(ConfigParser::getInstance().driver(),
			ConfigParser::getInstance().host(),
			ConfigParser::getInstance().db(),
			ConfigParser::getInstance().user(),
			ConfigParser::getInstance().password(),
			ConfigParser::getInstance().port());
	if (!b) {
		QString errmsg = dbManager->error();
		//QMessageBox::critical(this, "DB Connection Error", errmsg);
		qDebug() << errmsg;
		return false;
	}
	return true;
}

bool CreateTrackProcess::altibase_connect()
{
	qDebug() << "altibase_connect() : Altibase connect start................";

	env = SQL_NULL_HENV;
	dbc = SQL_NULL_HDBC;

	rc = alti_alloc_handle();
	conn_flag = 0;
	if (rc != SQL_SUCCESS)
	{
		alti_free_handle();
		qDebug() << "can't connect altibase............";
		return false;
	}

	rc = alt_connect();
	if (rc != SQL_SUCCESS)
	{
		alti_free_handle();
		qDebug() << "error while connect altibase.............";
		return false;
	}
	conn_flag = 1;
	qDebug() << "altibase connect success............";

	return true;
}

void CreateTrackProcess::alti_free_handle()
{
	if (conn_flag == 1)
	{
		SQLDisconnect(dbc);
	}
	if (dbc != NULL)
	{
		SQLFreeConnect(dbc);
	}
	if (env != NULL)
	{
		SQLFreeEnv(env);
	}
}

SQLRETURN CreateTrackProcess::alt_connect()
{
	SQLHSTMT	stmt = SQL_NULL_HSTMT;
	char conn_str[1024];
   SQLINTEGER  sErrNo;
   SQLSMALLINT sMsgLength;
   SQLCHAR     sErrMsg[MSG_LEN];

	sprintf(conn_str, "DSN=%s;PORT_NO=%d;UID=%s;PWD=%s;CONNTYPE=%d;NLS_USE=%s",
				DRS_DB_IP, DRS_DB_PORT, DRS_DB_USER, DRS_DB_PASS, 1, NLS);

	if (SQLDriverConnect(dbc, NULL, (SQLCHAR*)conn_str, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT) != SQL_SUCCESS)
	{
		qDebug() << "alt_connect() : SQLDriver connect error.........";
		return SQL_ERROR;
	}
    if (SQLSetConnectAttr(dbc, SQL_ATTR_AUTOCOMMIT,
                          (void*)SQL_AUTOCOMMIT_OFF, 0) != SQL_SUCCESS)
    {
        //execute_err(dbc, SQL_NULL_HSTMT, "Autocommit OFF");
        printf("Error : SQLSetConnectAttr\n");
        if (SQLError ( SQL_NULL_HENV, dbc, SQL_NULL_HSTMT,
                   NULL, &sErrNo,
                   sErrMsg, MSG_LEN, &sMsgLength ) == SQL_SUCCESS)
        {
            printf(" Error : # %ld, %s\n", sErrNo, sErrMsg);
        }
        return SQL_ERROR;
    }

	if (SQL_ERROR == SQLAllocStmt(dbc, &stmt))
	{
		qDebug() << "SQLAllocStmt error.........";
		return SQL_ERROR;
	}

	return SQL_SUCCESS;
}

SQLRETURN CreateTrackProcess::alti_alloc_handle()
{
	if (SQLAllocEnv(&env) != SQL_SUCCESS)
	{
		qDebug() << "SQLAllocEnv error..........";
		return SQL_ERROR;
	}
	if (SQLAllocConnect(env, &dbc) != SQL_SUCCESS)
	{
		qDebug() << "SQLAllocConnect error...........";
		return SQL_ERROR;
	}
	qDebug() << "alti_alloc_handle success...........";

	return SQL_SUCCESS;
}
void CreateTrackProcess::execute_err(SQLHDBC aCon, SQLHSTMT aStmt, char* q)
{
    printf("Error : %s\n",q);

    SQLINTEGER errNo;
    SQLSMALLINT msgLength;
    SQLCHAR errMsg[MSG_LEN];

    if (SQLError ( SQL_NULL_HENV, aCon, aStmt,
                   NULL, &errNo,
                   errMsg, MSG_LEN, &msgLength ) == SQL_SUCCESS)
    {
        printf(" Error : # %d, %s\n", errNo, errMsg);
    }
}
