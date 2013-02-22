/*
 * DbManager.cpp
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 */

#include "DbManager.h"

DbManager::DbManager() {
	// TODO Auto-generated constructor stub
	log = NULL;
	errorMessage = QString("");
}
DbManager::DbManager(Log424* log) {
	// TODO Auto-generated constructor stub
	this->log = log;
	errorMessage = QString("");
}
/**
 * 데이터베이스 연결을 생성한다.
 */
bool DbManager::createDatabase(const QString &driver, const QString& host, const QString &dbName,
							const QString &user, const QString &password, int port)
{
	log->print("DbManager::createDatabase start");
	QSqlError error;
	if (QSqlDatabase::database("amsdb").isOpen()) return true;

	QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("amsdb"));
	db.setHostName(host);
	db.setDatabaseName(dbName);
	db.setPort(port);

	if (!db.open(user, password)) {
		log->print("open db start");
		errorMessage = QString("Error: cannot open database\n"
					"driver:%1\n"
					"hostname:%2\n"
					"port:%3\n"
					"user:%4\n"
					"password:%5\n")
					.arg(driver).arg(host).arg(port).arg(user).arg(password);
		return false;
	}else {
		return true;
	}
}

/**
 * 데이터베이스 연결을 설정한다.
 */
bool DbManager::setDb(const QString &driver, const QString &host, const QString &dbname,
				const QString &user, const QString &password, int port)
{
	bool b = createDatabase(driver, host, dbname, user, password, port);
	if (!b) {
		log->print(QString("db open failed. check config file"));
		databaseName = QString("");
		return false;
	}
	databaseName = "amsdb";
	return true;
}


