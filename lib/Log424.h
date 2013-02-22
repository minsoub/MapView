/*
 * Log424.h
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */

#ifndef LOG424_H_
#define LOG424_H_

#include <QString>
#include <QPoint>
#include <QPointF>

class Log424 {
public:
	Log424();
	Log424(const QString& fileName);
	~Log424();
	void setEnable(bool b) { enable = b; }
	void off() { logFileName = QString(); }
	void print(const QString& msg);
	void print(const char* msg);
	void print(const QPoint& p);
	void print(const QPointF& p);
private:
	QString logFileName;
	void deleteLogFile();
	bool enable;
};

#endif /* LOG424_H_ */
