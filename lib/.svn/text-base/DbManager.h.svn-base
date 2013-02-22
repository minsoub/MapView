/*
 * DbManager.h
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 */
#include <QtSql>
#include <QString>
#include "Log424.h"

#ifndef DBMANAGER_H_
#define DBMANAGER_H_

class DbManager {
public:
	DbManager();
	DbManager(Log424* log);
	bool setDb(const QString &driver, const QString &host, const QString &dbName,
					const QString &user, const QString &password, int port);
	void setLog(Log424* log) { this->log = log; }
	QString error() { return errorMessage; }
	QString dbName() { return databaseName; }
private:
	Log424* log;
	QString databaseName;
	QString errorMessage;
	bool createDatabase(const QString &driver, const QString& host, const QString &dbName,
							const QString &user, const QString &password, int port);
};

#endif /* DBMANAGER_H_ */
