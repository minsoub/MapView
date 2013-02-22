/*
 * ConfigParser.h
 *
 *  Created on: 2012. 2. 20.
 *      Author: HIST002
 */

#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include <QtCore>
#include <QPointF>
#include <QColor>
#include "../lib/AMapconf.h"

class ConfigParser {
public:
	static ConfigParser& getInstance()
	{
		if (pinstance == NULL) {
			pinstance = new ConfigParser;
		}
		return *pinstance;
	}
	ConfigParser();
	~ConfigParser();
	bool ParseUrl(const QString url);
	bool ParseFile(const QString fileName);
	QString errorMessage() {return _errorMessage; };
	QString driver() const { return _driver; };
	QString host() const { return _host; };
	QString db() const { return _db; };
	QString user() const { return _user; };
	QString password() const { return _password; };
	int port() const { return _port; };
	QPointF wonjum() const { return _wonjum; };
	double lat() const { return _wonjum.x(); };
	double lon() const { return _wonjum.y(); };
	double mpp() const { return _mpp; };
	QColor bgcolor() const { return _bgcolor; };
	QColor gridcolor() const { return _gridcolor; };
	QColor cpscolor() const { return _cpscolor; };
	bool compassshow() const { return _compassshow; };
	bool latlonshow() const { return _latlonshow; };

	QString mapFile() const { return _mapfilename; };
	void setMapfile(const QString& mapfilename) { _mapfilename = mapfilename; };
	QString layerVisible() { return _layervisible; };
	// log
	QString logFileName() { return _logfilename; };
	bool logEnable() { return _logenable; };

	void readConfigXml(const QString& xmlFile);

	void setWonJum(QPointF p) { _wonjum = p; };
	const QString envMapDir() { return _envmapdir; };
	const QString envAdaptDir() { return _envadaptdir; };
	void setEnvMapDir(const QString& d) { _envmapdir = d; };
	void setEnvAdaptDir(const QString& d) { _envadaptdir = d; };
	void setBgcolor(const QColor& color) { _bgcolor = color; };

	QString toString();

private:
	static ConfigParser* pinstance;
	QString _errorMessage;
	QString _driver;
	QString _host;
	QString _db;
	QString _user;
	QString _password;
	int _port;
	// map
	QString _mapfilename;
	QString _layervisible;

	QPointF _wonjum;
	double _mpp;
	QColor _bgcolor;
	QColor _cpscolor;
	QColor _gridcolor;
	bool _compassshow;
	bool _latlonshow;
	bool _logenable;
	QString _logfilename;

	QString _envmapdir;		// 환경변수 Map dir
	QString _envadaptdir;	// 환경변수 Adapt dir

	AMapconf mapconf;
};

#endif /* CONFIGPARSER_H_ */
