/*
 * AMapconf.h
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */

#ifndef AMAPCONF_H_
#define AMAPCONF_H_

#include <QString>
#include <QVector>
#include <QtSql>
#include "../lib_layer/MapDefine.h"
#include "Log424.h"

class AMapconf {
public:
	AMapconf();
	~AMapconf();

	void addMapConf(
			const QString& line_type,
			const QString& line_width,
			const QString& line_color,
			const QString& fill_pattern,
			const QString& fill_color,
			const QString& font,
			const QString& font_size,
			const QString& font_color,
			const QString& symbol,
			const QString& layer_id,
			const QString& scope,
			const QString& disp
			);
	QString findMapConf(const QString& layer_id, const QString& attr) const;
	QString dftvalue(const QString& layer_id);
	void addLayerAttr(const QString& layer_id, const ALayerAttr& attr);
	void addLayerAttr(const QString& layer_id, const ALayerAttr* attr);
	void addMapDefault(
			const QString& bg_color,
			const QString& rng,
			const QString& mpp,
			const QString& grid_color,
			const QString& cps_color,
			const QString& log_yn,
			const QString& log_file,
			const QString& center_lat,
			const QString& center_lon,
			const QString& vw_cps,
			const QString& vw_latlon
			);
	void setMapConfDisp(const QString& layer_id, const QString& disp);
	bool isLayerDisplay(const QString& layer_id);
	bool isMapFileLayer(const QString& layer_id);
	void setBg_Color(const QString& bg);
	QColor bg_color();
	QString bg_colorString();
	void setRange(const QString& r);
	QString range();

	QString mppString();
	double mpp();
	QColor grid_color();
	QString grid_colorString();
	QColor cps_color();
	QString cps_colorString();

	bool log_yn();
	QString log_ynString();
	QString log_file();
	void setCenter(const QString& c);
	QString center();
	QString vw_cps();
	QString vw_latlon();

	void clear();
	bool writeConfigXml(const QString& fileName);
	bool readConfigXml(const QString& fileName);

	void getFromDb(const QSqlDatabase& db, const Log424& log);
	void getConfigFromDb(const QSqlDatabase& db, const Log424& log);
	void getDefaultFromDb(const QSqlDatabase& db, const Log424& log);
	void print();
private:
	QVector<AMapConf*> listMapConf;		    // TB_MAPCONF table
	QVector<AMapDefault*> listMapDefault;	// TB_MAPDEFAULT table
};

#endif /* AMAPCONF_H_ */
