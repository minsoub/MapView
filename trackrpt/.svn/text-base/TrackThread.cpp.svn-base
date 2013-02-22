/*
 * TrackThread.cpp
 *
 *  Created on: 2012. 5. 8.
 *      Author: JMS
 *  Description : Track 데이터 처리하는 Thread
 *                DRS 데이터베이스에 접속해서 Track 데이터를 가져온다.
 *                Thread를 사용하는 이유는 대용량 데이터를 한번에 가져오면 시스템이 늦기 때문에
 *                     여러개의 Thread로 나뉘어서 데이터를 가져온다.
 */

#include "TrackThread.h"
#include <string>

TrackThread::TrackThread() {
	// TODO Auto-generated constructor stub
	totalCount = 0;
	isStop = false;
	isDB = "ALTIBASE";			// DRS DB
}

TrackThread::~TrackThread() {
	// TODO Auto-generated destructor stub

}

void TrackThread::makeProcess(int cnt)
{
	 QDateTime st_dt = QDateTime::fromString(fromDt, "yyyy-MM-dd hh:mm:ss");
	 QDateTime et_dt = QDateTime::fromString(toDt,   "yyyy-MM-dd hh:mm:ss");
	 QDateTime loop_dt = st_dt;
	 int loop_cnt    = 1;

	 loopList.push_back(st_dt);
	 while(true) {
		 loop_dt = loop_dt.addSecs(60);		// 1 minute

		 if (loop_dt >= et_dt) {
			 loop_dt = loop_dt.addSecs(-1);	// 59 second
			 loopList.push_back(loop_dt);
			 loop_cnt++;
			 break;
		 }else {
			 loopList.push_back(loop_dt);
			 loop_cnt++;
		 }
	 }
	 loop_dt = st_dt;

	 dbDelete();
	 totalCount = cnt;
	 qDebug() << "makeProcess totalCount : " << totalCount;
}
/**
 * Thread를 가동한다.
 */
void TrackThread::run()
{
	QString sql;

	if (isDB == "ORACLE") {
		QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("minsoub"));
		int num = 0;
		for (int i=0; i<loopList.size()-1; i++) {
			if (isStop) {
				break;
			}
			QDateTime st = loopList[i];
			QDateTime et = loopList[i+1];

			sql  = "SELECT                                                                  \n";
			sql += "        SEQNO,   RECV_DAY,   SUBSYSTEM_CODE,                            \n";
			sql += "        TO_CHAR(RECV_TIME, 'yyyy-MM-dd HH24:MI:SS'),                    \n";
			sql += "        TO_CHAR(ARCH_TIME, 'yyyy-MM-dd HH24:MI:SS'),                    \n";
			sql += "        TO_CHAR(REMOVE_SCHEDULED_DATE, 'yyyy-MM-dd HH24:MI:SS'),        \n";
			sql += "        PACKETCOUNT,                                                    \n";
			sql += "        TO_CHAR(TIMESTAMP, 'yyyy-MM-dd HH24:MI:SS'),                    \n";
			sql += "        DESTINATION,                                                    \n";
			sql += "        DESTINATION_SUB,   DESTINATION_SECTOR,                          \n";
			sql += "        SOURCE,  PROCESSID,  DATATYPE,  SEVERITY,                       \n";
			sql += "        LOGCATEGORY1,  LOGCATEGORY2,                                    \n";
			sql += "        LOGBODYLENGTH, LOGBODY                                          \n";
			sql += "  FROM DRS_ARCHIVELOGDATA                                               \n";
			sql += " WHERE SUBSYSTEM_CODE IN ('1', '2', '3')                                \n";
			sql += "   AND (                                                                \n";
			sql += "         (LOGCATEGORY1 = '1101' AND LOGCATEGORY2 = '0405') OR           \n";		// ADSB
			sql += "         (LOGCATEGORY1 = '1A01' AND LOGCATEGORY2 = '0201') OR           \n";		// System Track
			sql += "         (LOGCATEGORY1 = '0401' AND LOGCATEGORY2 = '0D01') OR           \n";      // System Track - Mini Plan
			sql += "         (                                                              \n";
			sql += "               (LOGCATEGORY1 = '1A08' AND LOGCATEGORY2 IN ('0801', '0802', '0804', '0808'))   \n";  // Safety Net Message - SDP
			sql += "            OR (LOGCATEGORY1 = '0405' AND LOGCATEGORY2 IN ('0E01', '0E02', '0E03', '0E04'))   \n";  // Safety Net Message - FDP
			sql += "         )                                                              \n";
			sql += "       )                                                                \n";
			sql += "   AND TIMESTAMP BETWEEN TO_DATE('"+st.toString("yyyy-MM-dd hh:mm:ss")+"', 'yyyy-MM-dd HH24:MI:SS') \n";
			sql += "                     AND TO_DATE('"+et.toString("yyyy-MM-dd hh:mm:ss")+"', 'yyyy-MM-dd HH24:MI:SS')   \n";
			sql += " ORDER BY SEQNO                                                         \n";

			//qDebug() << sql;

			query->prepare(sql);

			query->exec();

			while (query->next()) {
				if (isStop) {
					break;
				}
				int length = query->value(17).toInt();
				QByteArray bb = query->value(18).toByteArray();

				CBuffer buffer;
				buffer.Clear();
				char * buf = bb.data();

				buffer.CopyBuffer(reinterpret_cast<unsigned char *>(buf), length);

				asterix.GetPacket(buffer);

				if (asterix.getCategory() == 62) {		// Cat 62
					//qDebug() << "category 62 db update...";
					Cat062 cat = asterix.getCat62();
					if (!dbUpdate(cat, query->value(3).toString())) {		// smsd db open
						delete query;
						return;
					}
				}else if(asterix.getCategory() == 21) {  // Cat 21
					Cat021 cat = asterix.getCat21();
					if (!dbUpdate21(cat, query->value(3).toString())) {
						delete query;
						return;
					}
				}
				num++;
				emit valueChanged(num);
				//qApp->processEvents();
			}
			query->finish();
		}
		delete query;
	}else if(isDB == "ALTIBASE") {
		int num = 0;
		SQL_TIMESTAMP_STRUCT	recv_time;
		SQLINTEGER		logbodylength;
		QByteArray		logBodyArray;
		SQLHSTMT		   stmt = SQL_NULL_HSTMT;
		char logbody[32000];
		char logcategory1[2];
		char logcategory2[2];

		for (int i=0; i<loopList.size()-1; i++) {
			if (isStop) {
				break;
			}
			QDateTime st = loopList[i];
			QDateTime et = loopList[i+1];

			char c_sql[1024];
			char ch_from_dt[14];
			char ch_to_dt[14];

			sprintf(c_sql, "SELECT TIMESTAMP, LOGBODYLENGTH, LOGBODY,                           \n"
				            "       LOGCATEGORY1, LOGCATEGORY2                                   \n"
					         "  FROM DRS_LOGDATA                                                  \n"
					         " WHERE SUBSYSTEM_CODE IN (1, 2, 3)                                  \n"
					         "   AND (                                                            \n"
					"       (LOGCATEGORY1 = '0101' AND LOGCATEGORY2 = '0301') OR       \n"                        // ADS-B
					//"       (LOGCATEGORY1 = '0301' AND LOGCATEGORY2 = '0201') OR       \n"       // system Track - New
					"       (LOGCATEGORY1 = '1A01' AND LOGCATEGORY2 = '0201') OR       \n"       // system Track - Old
					"       (LOGCATEGORY1 = '0401' AND LOGCATEGORY2 = '0D01') OR       \n"       // System Track - Mini Plan
					"       (                                                          \n"
					"          (LOGCATEGORY1 = '0305' AND LOGCATEGORY2 IN ('0801', '0802', '0804', '0808'))    \n"                        // Safety Net Message - SDP
					//"       OR (LOGCATEGORY1 = '0405' AND LOGCATEGORY2 IN ('0E01', '0E02', '0E03', '0E04'))    \n"       // Safety Net Message - FDP
					"       )                                                          \n"
					"     )                                                            \n"
			               "   AND TIMESTAMP >= TO_DATE(?, 'yyyyMMddHH24MISS')                  \n"
					         "   AND TIMESTAMP <  TO_DATE(?, 'yyyyMMddHH24MISS')                  \n"
					         "   ORDER BY SEQNO                                                   \n"
					);
			sprintf(ch_from_dt, st.toString("yyyyMMddhhmmss").toStdString().c_str());
			sprintf(ch_to_dt,   et.toString("yyyyMMddhhmmss").toStdString().c_str());

//			qDebug() << st.toString("yyyy-MM-dd hh:mm:ss");
//			qDebug() << c_sql;
//			qDebug() << ch_from_dt;
//			qDebug() << ch_to_dt;

			qDebug() << c_sql;
			qDebug() << "Search condition From dt : " << st.toString("yyyyMMddhhmmss");
			qDebug() << "Search condition To   dt : " << et.toString("yyyyMMddhhmmss");
			/* allocate Statement handle */
			if (SQL_ERROR == SQLAllocStmt(dbc, &stmt)) {
				qDebug() << "SQLAllocStmt error!!";
				break;
			}
			//char *sql_chr = (char *)sql.toStdString().c_str();
			//printf("SQL : %s\n", sql_chr);
			if (SQLPrepare(stmt, (SQLCHAR *)c_sql, SQL_NTS) != SQL_SUCCESS)
			{
				execute_err(dbc, stmt, c_sql);
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}

			if (SQLBindParameter(stmt,
										1,
										SQL_PARAM_INPUT,
										SQL_C_CHAR,
										SQL_CHAR,
										14,
										0,
										ch_from_dt,
										sizeof(ch_from_dt),
										NULL) != SQL_SUCCESS)
			{
				execute_err(dbc, stmt, c_sql);
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}
			if (SQLBindParameter(stmt,
										2,
										SQL_PARAM_INPUT,
										SQL_C_CHAR,
										SQL_CHAR,
										14,
										0,
										ch_to_dt,
										sizeof(ch_to_dt),
										NULL) != SQL_SUCCESS)
			{
				execute_err(dbc, stmt, c_sql);
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}

			if (SQLBindCol(stmt, 1, SQL_C_TYPE_TIMESTAMP, &recv_time, 0, NULL) != SQL_SUCCESS) {
				qDebug() << "SQLBindCol error ........................1";
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}
			if (SQLBindCol(stmt, 2, SQL_C_SLONG, &logbodylength, 0, NULL) != SQL_SUCCESS) {
				qDebug() << "SQLBindCol error ........................2";
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}
			if (SQLBindCol(stmt, 3, SQL_C_BINARY, &logbody, sizeof(logbody), NULL) != SQL_SUCCESS) {
				qDebug() << "SQLBindCol error ........................3";
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}
			if (SQLBindCol(stmt, 4, SQL_C_BINARY, &logcategory1, sizeof(logcategory1), NULL) != SQL_SUCCESS) {
				qDebug() << "SQLBindCol error ........................4";
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}
			if (SQLBindCol(stmt, 5, SQL_C_BINARY, &logcategory2, sizeof(logcategory2), NULL) != SQL_SUCCESS) {
				qDebug() << "SQLBindCol error ........................5";
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}

			if (SQLExecute(stmt) != SQL_SUCCESS)
			{
				execute_err(dbc, stmt, "SQLExecute : ");
				SQLFreeStmt(stmt, SQL_DROP);
				break;
			}

			while((rc = SQLFetch(stmt)) != SQL_NO_DATA)
			{
				if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
					qDebug() << "SQLFetch error " << rc;
					break;
				}
				if (isStop) {
					break;
				}
				//qDebug() << "SQLFetch result : " << logbodylength;

				int length = logbodylength;
				QByteArray bb(logbody);   //  = query->value(18).toByteArray();
				QByteArray text = QByteArray::fromBase64(bb);
				char *decoded_char = text.data();

				QString timestamp;
				timestamp.sprintf("%d-%.2d-%.2d %.2d:%.2d:%.2d",
									recv_time.year, recv_time.month, recv_time.day,
									recv_time.hour, recv_time.minute, recv_time.second);

				//qDebug() << "timestamp : " << timestamp;
				// FDP에서 보내는 Safety Nets 관련해서는 Asterix format이 아니고 Text format이다.
				// 0405, 0E01~04
				char log1[4];
				char log2[4];
				sprintf(log1, "%.2d%.2d", logcategory1[0], logcategory1[1]);
				sprintf(log2, "%.2d%.2d", logcategory2[0], logcategory2[1]);

				QString strLog1 = QString("%1").arg(log1);
				QString strLog2 = QString("%1").arg(log2);


				// FDP에서 보내는 Safety Nets 관련한 Text format : CLAM, RAM, ETO, Fuel Prediction
				if (strLog1 == "0405" && (strLog2 == "1401" || strLog2 == "1402" || strLog2 == "1403" || strLog2 == "1404"))
				{
					qDebug() << "====================================================================================";
					qDebug() << "LogCategory1 : " << strLog1 << ", LogCategory2 : " << strLog2;

					// Debug Start
					QString tmp;
					QString str;
					QString tmp1;
					QString str1;
					unsigned char m_u8Buf[length];
					memcpy(m_u8Buf, reinterpret_cast<unsigned char *>(decoded_char), length);
					for (int i=0; i<length; i++) {
						tmp.sprintf("%.2X ", m_u8Buf[i]);
						str.append(tmp);

						tmp1.sprintf("%c", m_u8Buf[i]);
						str1.append(tmp1);
					}
					qDebug() << str;
					qDebug() << str1;
					qDebug() << timestamp;
					// Debug End

					QString logData = str1;	    // format : "67634-TWB706-5007--Y-CLAM-0300-S"
					QStringList listData = logData.split("-");

					if (!dbUpdate04(listData, timestamp)) {
						SQLFreeStmt(stmt, SQL_DROP);
						return;
					}
					qDebug() << "====================================================================================";
				}else {

					CBuffer buffer;
					buffer.Clear();
					buffer.CopyBuffer(reinterpret_cast<unsigned char *>(decoded_char), length);

					asterix.GetPacket(buffer);

					if (asterix.getCategory() == 62) {		// Cat 62
						//qDebug() << "category 62 db update...";
						Cat062 cat = asterix.getCat62();

						//qDebug() << cat.toString();
						// timestamp 조절
						if (!dbUpdate(cat, timestamp)) {		// smsd db open
							SQLFreeStmt(stmt, SQL_DROP);
							return;
						}
					}else if(asterix.getCategory() == 21) {  // Cat 21
						// debug start
						QString tmp;
						QString str;
						unsigned char m_u8Buf[length];
						memcpy(m_u8Buf, reinterpret_cast<unsigned char *>(decoded_char), length);
						for (int i=0; i<length; i++) {
							tmp.sprintf("%.2X ", m_u8Buf[i]);
							str.append(tmp);
						}
						qDebug() << str;
						// debug end

						Cat021 cat = asterix.getCat21();
						if (!dbUpdate21(cat, timestamp)) {
							SQLFreeStmt(stmt, SQL_DROP);
							return;
						}

					}else if(asterix.getCategory() == 4) {		// Cat 004
						// debug start
						QString tmp;
						QString str;
						unsigned char m_u8Buf[length];
						memcpy(m_u8Buf, reinterpret_cast<unsigned char *>(decoded_char), length);
						for (int i=0; i<length; i++) {
							tmp.sprintf("%.2X ", m_u8Buf[i]);
							str.append(tmp);
						}
						qDebug() << str;
						// debug end

						Cat004 cat = asterix.getCat04();
						if (!dbUpdate04(cat, timestamp)) {
							SQLFreeStmt(stmt, SQL_DROP);
							return;
						}
					}
				}

				num++;
				emit valueChanged(num);

			} /* while end */
			SQLFreeStmt(stmt, SQL_DROP);
		}
	}
	// this->exit(1);		// debug
}

/**
 * TB_TRK, TB_MINIPLN 테이블 데이터를 삭제한다.
 */
bool TrackThread::dbDelete()
{
	QSqlQuery *query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));
	QString sql;

	// all delete
	sql = " DELETE FROM TB_TRK";
	query->prepare(sql);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		qDebug() << query->lastError().text();
		query->finish();
		delete query;

		return false;
	}
	query->finish();

	sql = " DELETE FROM TB_MINIPLN";
	query->prepare(sql);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		qDebug() << query->lastError().text();
		query->finish();
		delete query;

		return false;
	}
	query->finish();

	sql = " DELETE FROM TB_ADSB";
	query->prepare(sql);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		qDebug() << query->lastError().text();
		query->finish();
		delete query;

		return false;
	}
	query->finish();


	delete query;

	return true;
}

/**
 * TB_ADSB 테이블에 데이터를 등록한다.
 */
bool TrackThread::dbUpdate21(Cat021& cat, QString timestamp)
{
	QString sql;
	QSqlQuery *query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));


	sql = "INSERT INTO TB_ADSB ";
	sql += " ( NO,     CALLSIGN,   OCCUR_DT,    LAT,    LON,     ";
	sql += "   SPD,    HEADING,    ALT                           ";
	sql += " ) VALUES (                                          ";
	sql += "   ADSB_NUM.nextval,     ?,  ?,  ?,  ?,               ";
	sql += "   ?,      ?,      ?                                 ";
	sql += " ) ";
	query->prepare(sql);

	query->addBindValue(cat.getCallsign());
	QDateTime dt1 = QDateTime::fromString(cat.getAccurDt(), "yyyy-MM-dd hh:mm:ss");
	QDateTime dt2 = QDateTime::fromString(timestamp,        "yyyy-MM-dd hh:mm:ss");
	QTime time = dt1.time();
	dt2.setTime(time);

	query->addBindValue(dt2);
	query->addBindValue(cat.getLatitude());
	query->addBindValue(cat.getLongitude());
	query->addBindValue(cat.getSpeed());
	query->addBindValue(cat.getHeading());
	query->addBindValue(cat.getAltitude());

	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		qDebug() << query->lastError().text();
		qDebug() << cat.toString();
		query->finish();
		delete query;

		return false;
	}
	query->finish();

	delete query;

	return true;
}

/**
 * TB_TRK 테이블에 데이터를 업데이트 한다.
 * 업데이트 조건 : TRK_NO, SSR, CALLSIGN, OCCUR_DT가 같을 때
 * 업데이트 필드 : SAFETY_TYPE
 * FORMAT : "67634-TWB706-5007--Y-CLAM-0300-S"
 *           TRK_NO-CALLSIGN-SSR
 * 발생메시지 : CLAM, RAM, ETO, Fuel Prediction
 * NOTICE : 메시지 포멧에 발생시각이 존재하는데 이 시각을 사용할 것인지 아니면 TimeStamp를 사용할 것인지에 대한
 *             정의가 필요하다.
 */
bool TrackThread::dbUpdate04(QStringList list, QString timestamp)
{
	QString sql;
	QSqlQuery *query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));
	QString trk_no;
	QString callsign;
	QString ssr;
	QString strMsgType;

	int no;
	trk_no     = list.at(4);
	callsign   = list.at(1);
	ssr        = list.at(2);
	strMsgType = list.at(5);

	// TODO: 후에 Track ID 추출은 변경될 수 있음.
//	QString binaryTrack_no = list.at(4);
//	QChar *data = binaryTrack_no.data();
//
//	char s3 = data[0].toAscii();
//	char s4 = data[1].toAscii();
//
//	int ss1 = 0;
//	ss1 = ss1 + s3;
//	ss1 = (ss1 << 8);
//	ss1 = ss1 + s4;
//	trk_no = QString("%1").arg(ss1);


	qDebug() << "TRK NO : " << trk_no << ", CallSign : " << callsign << ", SSR : " << ssr << ", MsgType : " << strMsgType;

	sql  = " SELECT NO                                     ";
	sql += "   FROM TB_TRK                                 ";
	sql += "  WHERE TRK_NO = ? AND CALLSIGN = ?            ";
	sql += "    AND SSR    = ? AND OCCUR_DT = ?            ";  // TO_DATE(?, 'yyyy-MM-dd HH24:MI:SS') ";

	query->prepare(sql);

	query->addBindValue(trk_no);
	query->addBindValue(callsign);
	query->addBindValue(ssr);
	QDateTime dt1 = QDateTime::fromString(timestamp, "yyyy-MM-dd hh:mm:ss");
	query->addBindValue(dt1);
	query->exec();

	no = -1;
	if (query->next()) {
		no = query->value(0).toInt();
	}
	query->finish();

	if (no != -1) {
		int msgType;
		if (strMsgType == "CLAM") {
			msgType = 6;
		}else if(strMsgType == "RAM") {
			msgType = 20;
		}else if(strMsgType == "ETO") {
			msgType = 21;
		}
		sql = "UPDATE TB_TRK SET SAFETY_MSG_TP=? WHERE NO = ? ";
		query->prepare(sql);
		query->addBindValue(msgType);
		query->addBindValue(no);
		query->exec();
		query->finish();
		no = -1;
		qDebug() << "Found data ......................";
	}else {
		qDebug() << "NOT Found data...................";
	}

	delete query;

	return true;
}
/**
 * TB_TRK 테이블에 데이터를 업데이트 한다.
 * 업데이트 조건 : TRK_NO와 OCCUR_DT가 같을 때
 * 업데이트 필드 : SAFETY_TYPE
 */
bool TrackThread::dbUpdate04(Cat004& cat, QString timestamp)
{
	QString sql;
	QSqlQuery *query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));

	int trk_num1 = -1;
	int trk_num2 = -1;
	int no = -1;
	trk_num1 = cat.getSafetyNets().u16TrackNum1;
	trk_num2 = cat.getSafetyNets().u16TrackNum2;

	QDateTime dt1 = QDateTime::fromString(cat.getSafetyNets().timeStamp.toString(), "yyyy-MM-dd hh:mm:ss");
	QDateTime dt2 = QDateTime::fromString(timestamp,        "yyyy-MM-dd hh:mm:ss");
	QTime time = dt1.time();
	dt2.setTime(time);

	sql = "SELECT NO FROM TB_TRK WHERE TRK_NO = ? AND OCCUR_DT = ?  ";  // TO_DATE(?, 'yyyy-MM-dd HH24:MI:SS') ";

	query->prepare(sql);
	query->addBindValue(trk_num1);
	query->addBindValue(dt2);

	query->exec();

	if (query->next()) {
		no = query->value(0).toInt();
	}
	query->finish();

	if (no != -1) {
		sql = "UPDATE TB_TRK SET SAFETY_MSG_TP=? WHERE NO = ? ";
		query->prepare(sql);
		query->addBindValue(cat.getSafetyNets().messge_type);
		query->addBindValue(no);
		query->exec();
		query->finish();
		no = -1;
	}

	if (cat.getSafetyNets().messge_type == 7) {			// STCA
		sql = "SELECT NO FROM TB_TRK WHERE TRK_NO = ? AND OCCUR_DT = ?  ";  // TO_DATE(?, 'yyyy-MM-dd HH24:MI:SS') ";

		query->prepare(sql);

		query->addBindValue(trk_num2);
		query->addBindValue(dt2);

		query->exec();

		if (query->next()) {
			no = query->value(0).toInt();
		}
		query->finish();

		if (no != -1) {
			sql = "UPDATE TB_TRK SET SAFETY_MSG_TP=? WHERE NO = ? ";
			query->prepare(sql);
			query->addBindValue(cat.getSafetyNets().messge_type);
			query->addBindValue(no);
			query->exec();
			query->finish();
			no = -1;
		}
	}
	delete query;

	return true;
}


/**
 * Cat-62 데이터 처리
 * TB_TRK, TB_MINIPLN 테이블에 데이터를 등록한다.
 */
bool TrackThread::dbUpdate(Cat062& cat, QString timestamp)
{
	//qDebug() << "dbUpdate called...";
	QString sql;
	QSqlQuery *query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));

	// data insert and update
	if (cat.miniPlanCheck()) {		// Mini Plan data
		qDebug() << "Mini Plan data found...............";
		sql = " SELECT COUNT(*) FROM TB_TRK WHERE SSR = ? AND TRK_NO = ? ";
		query->prepare(sql);
		query->addBindValue(cat.getSSRCode());
		query->addBindValue(cat.getTrackNum());
		query->exec();
		int cnt = 0;
		if (query->next()) {
			cnt = query->value(0).toInt();
		}
		query->finish();
		qDebug() << "found count : " << cnt;

		if (cnt > 0) {
			sql = "UPDATE TB_TRK  SET  ";

			sql += "   SPI_CHK = ?,  MRH_CHK = ?,  CNF_CHK = ?,   SIM_CHK = ?,   TSE_CHK = ?,    FPC_CHK = ?,         ";
			sql += "   CST_CHK = ?,  PSR_CHK = ?,  SSR_CHK = ?,   MDS_CHK = ?,   ADS_CHK = ?,                     ";

			sql += "    FLT_RULE = ?,  RVSM = ?,    ACTP = ?,               ";
			sql += "    WT = ?,  DEP_AD = ?,   ARR_AD = ?,     RWAY_NO = ?,      CFL = ?,                    ";
			sql += "    CENTER_ID = ?,    POS = ?,      CALLSIGN = ?                                          ";

			sql += " WHERE            ";
			sql += "       SSR    = ? ";
			sql += "   AND TRK_NO = ? ";
			sql += "   AND NO     = (SELECT MAX(NO) FROM TB_TRK WHERE SSR = ? AND TRK_NO = ? ) ";

			query->prepare(sql);

			query->addBindValue(cat.getSPI());
			query->addBindValue(cat.getMRH());
			query->addBindValue(cat.getCNF());
			query->addBindValue(cat.getSIM());
			query->addBindValue(cat.getTSE());
			query->addBindValue(cat.getFPC());
			query->addBindValue(cat.getCST());
			query->addBindValue(cat.getPSR());
			query->addBindValue(cat.getSSR());
			query->addBindValue(cat.getMDS());
			query->addBindValue(cat.getADS());

			query->addBindValue(cat.getFlRule());
			query->addBindValue(cat.getRVSM());
			query->addBindValue(cat.getAirType());

			query->addBindValue(cat.getWtType());
			query->addBindValue(cat.getDepAd());
			query->addBindValue(cat.getDesAd());
			query->addBindValue(cat.getRwayNo());
			query->addBindValue(cat.getCFL());
			query->addBindValue(cat.getCetre());
			query->addBindValue(cat.getPos());
			query->addBindValue(cat.getCallsign());

			query->addBindValue(cat.getSSRCode());
			query->addBindValue(cat.getTrackNum());
			query->addBindValue(cat.getSSRCode());
			query->addBindValue(cat.getTrackNum());

			query->exec();

			if (query->lastError().type() != QSqlError::NoError) {
				qDebug() << "Update error : " << query->lastError().text();
				qDebug() << cat.toString();
				query->finish();
				delete query;
				return false;
			}
			query->finish();

		}else {
			qDebug() << "first miniplan data - not lat, lon";
			qDebug() << cat.getLatitude() << cat.getLongitude();

			sql  = " INSERT INTO TB_TRK                                                       ";
			sql += "  ( NO,       SSR,      TRK_NO,     CALLSIGN,     OCCUR_DT,               ";
			sql += "   SPI_CHK,  MRH_CHK,  CNF_CHK,   SIM_CHK,   TSE_CHK,    FPC_CHK,         ";
			sql += "   CST_CHK,  PSR_CHK,  SSR_CHK,   MDS_CHK,   ADS_CHK,                     ";

			sql += "    FLT_RULE,  RVSM,           ACTP,               ";
			sql += "    WT,  DEP_AD,   ARR_AD,     RWAY_NO,      CFL,                    ";
			sql += "    CENTER_ID,    POS                                                         ";
			sql += "  ) VALUES (                                                              ";
			sql += "    TRK_NUM.nextval,         ?,       ?,          ?,            ?,        ";
			sql += "   ?,      ?,      ?,           ?,          ?,           ?,               ";
			sql += "   ?,      ?,      ?,           ?,          ?,                            ";

			sql += "    ?,         ?,       ?,                       ";
			sql += "    ?,         ?,       ?,          ?,            ?,                      ";
			sql += "    ?,         ?                                                          ";
			sql += "  )                                                                       ";

			query->prepare(sql);
			query->addBindValue(cat.getSSRCode());
			query->addBindValue(cat.getTrackNum());
			query->addBindValue(cat.getCallsign());
			//qDebug() << cat.getAccurDt();

			QDateTime dt1 = QDateTime::fromString(cat.getAccurDt(), "yyyy-MM-dd hh:mm:ss");
			QDateTime dt2 = QDateTime::fromString(timestamp,        "yyyy-MM-dd hh:mm:ss");
			QTime time = dt1.time();
			dt2.setTime(time);

			//qDebug() << "1 dt2 : " << dt2.toString() << " dt1 : " << dt1.toString() << "timestamp : " << timestamp;

			query->addBindValue(dt2);
			query->addBindValue(cat.getSPI());
			query->addBindValue(cat.getMRH());
			query->addBindValue(cat.getCNF());
			query->addBindValue(cat.getSIM());
			query->addBindValue(cat.getTSE());
			query->addBindValue(cat.getFPC());
			query->addBindValue(cat.getCST());
			query->addBindValue(cat.getPSR());
			query->addBindValue(cat.getSSR());
			query->addBindValue(cat.getMDS());
			query->addBindValue(cat.getADS());

			query->addBindValue(cat.getFlRule());
			query->addBindValue(cat.getRVSM());
			query->addBindValue(cat.getAirType());
			query->addBindValue(cat.getWtType());
			query->addBindValue(cat.getDepAd());
			query->addBindValue(cat.getDesAd());
			query->addBindValue(cat.getRwayNo());
			query->addBindValue(cat.getCFL());
			query->addBindValue(cat.getCetre());
			query->addBindValue(cat.getPos());

			//qDebug() << cat.getWtType();

			query->exec();

			if (query->lastError().type() != QSqlError::NoError) {

				//QMessageBox::warning(this, tr("DataBase Error"), query->lastError().text());
				qDebug() << "insert Error : " << query->lastError().text();
				qDebug() << cat.toString();
				query->finish();
				delete query;

				return false;
			}
			query->finish();
		}

	}else {
		//qDebug() << "track data found.........";
		QString ssr;
		QString callsign;
		int     trackNo;
		trackNo = cat.getTrackNum();
		if (cat.getPSR() == 0 && cat.getSSR() == 1 && cat.getSSRCode().trimmed().isEmpty()) {		// PSR only
			sql = "SELECT SSR, CALLSIGN FROM TB_TRK WHERE TRK_NO = ? AND ROWNUM = 1";
			query->prepare(sql);
			query->addBindValue(trackNo);
			query->exec();

			if (query->next()) {
				ssr = query->value(0).toString();
				callsign = query->value(1).toString();
			}
			query->finish();
		}else if(!cat.getSSRCode().trimmed().isEmpty()) {
			ssr = cat.getSSRCode();

			sql = "SELECT CALLSIGN FROM TB_TRK WHERE TRK_NO = ? AND CALLSIGN = ? AND ROWNUM = 1";
			query->prepare(sql);
			query->addBindValue(trackNo);
			query->addBindValue(ssr);
			query->exec();

			if (query->next()) {
				callsign = query->value(0).toString();
			}
			query->finish();
		}else {
			ssr = cat.getSSRCode();
			callsign = cat.getCallsign();
		}
		qDebug() << "Track insert....";
		sql = "INSERT INTO TB_TRK ";
		sql += " ( NO,     SSR,    TRK_NO,      CALLSIGN,   OCCUR_DT,    LAT,    LON,     ";
		sql += "   SPD,    HEADING,    MLT_ALT,   ALT,      QNH,         CLIMB_DESCENT,   ";
		sql += "   SPI_CHK,  MRH_CHK,  CNF_CHK,   SIM_CHK,   TSE_CHK,    FPC_CHK,         ";
		sql += "   CST_CHK,  PSR_CHK,  SSR_CHK,   MDS_CHK,   ADS_CHK                      ";
		sql += " ) VALUES (                                                               ";
		sql += "   TRK_NUM.nextval,      ?,      ?,           ?,          ?,           ?,      ?,       ";
		sql += "   ?,      ?,      ?,           ?,          ?,           ?,               ";
		sql += "   ?,      ?,      ?,           ?,          ?,           ?,               ";
		sql += "   ?,      ?,      ?,           ?,          ?                             ";
		sql += " ) ";
		query->prepare(sql);

		query->addBindValue(ssr);
		query->addBindValue(trackNo);
		query->addBindValue(callsign);
		//qDebug() << cat.getAccurDt();
		QDateTime dt1 = QDateTime::fromString(cat.getAccurDt(), "yyyy-MM-dd hh:mm:ss");
		QDateTime dt2 = QDateTime::fromString(timestamp,        "yyyy-MM-dd hh:mm:ss");
		QTime time = dt1.time();
		dt2.setTime(time);
		//qDebug() << "2 dt2 : " << dt2.toString()<< " dt1 : " << dt1.toString() << "timestamp : " << timestamp;
		query->addBindValue(dt2);
		query->addBindValue(cat.getLatitude());
		query->addBindValue(cat.getLongitude());
		query->addBindValue(cat.getSpeed());
		query->addBindValue(cat.getHeading());
		query->addBindValue(cat.getMltAltitude());
		query->addBindValue(cat.getAltitude());
		query->addBindValue(cat.getQNH());
		query->addBindValue(cat.getClimbDescent());
		query->addBindValue(cat.getSPI());
		query->addBindValue(cat.getMRH());
		query->addBindValue(cat.getCNF());
		query->addBindValue(cat.getSIM());
		query->addBindValue(cat.getTSE());
		query->addBindValue(cat.getFPC());
		query->addBindValue(cat.getCST());
		query->addBindValue(cat.getPSR());
		query->addBindValue(cat.getSSR());
		query->addBindValue(cat.getMDS());
		query->addBindValue(cat.getADS());

		query->exec();

		if (query->lastError().type() != QSqlError::NoError) {

			//QMessageBox::warning(this, tr("DataBase Error"), query->lastError().text());
			qDebug() << "TB_TRK Insert error : " << query->lastError().text();
			qDebug() << cat.toString();
			query->finish();
			delete query;

			return false;
		}
		query->finish();
	}

	delete query;

	return true;
}


void TrackThread::execute_err(SQLHDBC aCon, SQLHSTMT aStmt, char* q)
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
