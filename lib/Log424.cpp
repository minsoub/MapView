/*
 * Log424.cpp
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtCore>
#include "Log424.h"

Log424::Log424() {
	// TODO Auto-generated constructor stub
	enable = true;
	logFileName = "arinc424.log";
	deleteLogFile();
}
Log424::Log424(const QString& fileName)
{
	enable = true;
	logFileName = fileName;

	//qDebug() << "c : " << enable;
	//qDebug() << "log : " << logFileName;
	deleteLogFile();
}

Log424::~Log424() {
	// TODO Auto-generated destructor stub
}

void Log424::print(const QString& msg)
{
	//qDebug() << enable;
	//qDebug() << logFileName;

	if (enable == false) return;
	if (logFileName.isNull() || logFileName.isEmpty()) return;

	QFile file(logFileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
	{
		return;
	}
	QTextStream in(&file);
	in << "[" << QDateTime::currentDateTime().toString(Qt::ISODate) << "] " << msg << "\n";
	file.close();
}

void Log424::print(const char* msg)
{
	print(QString(msg));
}

void Log424::print(const QPoint& p)
{
	QString msg = QString("%1,%2").arg(p.x()).arg(p.y());
	print(msg);
}

void Log424::print(const QPointF& p)
{
	QString msg = QString("%1,%2").arg(p.x()).arg(p.y());
	print(msg);
}

void Log424::deleteLogFile()
{
	if (QFile::exists(logFileName)) {
		QFile::remove(logFileName);
	}
}
