/*
 * AMapconf.cpp
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */
#include <iostream>
#include <QFile>
#include <QDomDocument>
#include "AMapconf.h"

AMapconf::AMapconf() {
	// TODO Auto-generated constructor stub

}

AMapconf::~AMapconf() {
	// TODO Auto-generated destructor stub
	for (int i=listMapConf.count()-1; i>=0; i--) {
		delete listMapConf[i];
	}
	for (int i=listMapDefault.count()-1; i>=0; i--) {
		delete listMapDefault[i];
	}
}

void AMapconf::addMapConf(
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
			)
{
	AMapConf* item = new AMapConf;
	item->line_type = line_type;
	item->line_width = line_width;
	item->line_color = line_color;
	item->fill_pattern = fill_pattern;
	item->fill_color = fill_color;
	item->font = font;
	item->font_size = font_size;
	item->font_color = font_color;
	item->symbol = symbol;
	item->layer_id = layer_id;
	item->scope = scope;
	item->disp = disp;

	listMapConf.append(item);
}

QString AMapconf::findMapConf(const QString& layer_id, const QString& attr) const
{
	for (int i=0; i<listMapConf.count(); i++) {
		AMapConf* item = listMapConf[i];
		if (item->layer_id == layer_id) {
			if (attr == "LINE_TYPE") return item->line_type;
			else if(attr == "LINE_WIDTH") return item->line_width;
			else if(attr == "LINE_COLOR") return item->line_color;
			else if(attr == "FILL_PATTERN") return item->fill_pattern;
			else if(attr == "FILL_COLOR") return item->fill_color;
			else if(attr == "FONT") return item->font;
			else if(attr == "FONT_SIZE") return item->font_size;
			else if(attr == "FONT_COLOR") return item->font_color;
			else if(attr == "SYMBOL") return item->symbol;
			else if(attr == "DISP") return item->disp;
			else if(attr == "SCOPE") return item->scope;
			else return QString("");
		}
	}
	return QString("");
}

QString AMapconf::bg_colorString()
{
	if(listMapDefault.count() > 0) {
		return listMapDefault[0]->bg_color;
	}
	return QString("");
}

QColor AMapconf::bg_color()
{
	qDebug() << "AMapconf::bg_color called.........";
	qDebug() << "listMapDefault count : " << listMapDefault.count();
	if (listMapDefault.count() > 0) {
		QStringList tmpList = listMapDefault[0]->bg_color.split(',');

		qDebug() << "AMapconf::bg_color " << listMapDefault[0]->bg_color;
		qDebug() << "AMapconf::bg_color " << tmpList[0].toInt();
		qDebug() << "AMapconf::bg_color " << tmpList[1].toInt();
		qDebug() << "AMapconf::bg_color " << tmpList[2].toInt();

		QColor color = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt(), TuMyungDo);

		qDebug() << "AMapconf::bg_color => " << color;

		return color;
	}
	return QColor(0, 0, 0);
}

QString AMapconf::range()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->rng;
	}
	return QString("");
}

double AMapconf::mpp()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->mpp.toDouble();
	}
	return 2000;
}

QString AMapconf::mppString()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->mpp;
	}
	return QString("");
}

QColor AMapconf::grid_color()
{
	if (listMapDefault.count() > 0) {
		QStringList tmpList = listMapDefault[0]->grid_color.split(',');
		QColor color = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt(), TuMyungDo);

		qDebug() << "AMapconf::grid_color => " << color;
		return color;
	}
	return QColor(0, 0, 0);
}

QString AMapconf::grid_colorString()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->grid_color;
	}
	return QString("");
}

QColor AMapconf::cps_color()
{
	if (listMapDefault.count() > 0) {
		QStringList tmpList = listMapDefault[0]->cps_color.split(',');
		QColor color = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt(), TuMyungDo);
		return color;
	}
	return QColor(0, 0, 0);
}

QString AMapconf::cps_colorString()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->cps_color;
	}
	return QString("");
}

QString AMapconf::log_ynString()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->log_yn;
	}
	return QString("");
}

bool AMapconf::log_yn()
{
	if (listMapDefault.count() > 0) {
		QString yn = listMapDefault[0]->log_yn;
		if (yn == "Y") {
			return true;
		}
	}
	return false;
}

QString AMapconf::log_file()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->log_file;
	}
	return QString("");
}

QString AMapconf::center()
{
	if (listMapDefault.count() > 0) {
		return QString("%1%2")
				.arg(listMapDefault[0]->center_lat.trimmed())
				.arg(listMapDefault[0]->center_lon.trimmed());
	}
	return QString("");
}

QString AMapconf::vw_cps()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->vw_cps;
	}
	return QString("");
}

QString AMapconf::vw_latlon()
{
	if (listMapDefault.count() > 0) {
		return listMapDefault[0]->vw_latlon;
	}
	return QString("");
}

// debug print
void AMapconf::print()
{
	std::cout << "mapconf : " << std::endl;
	for (int i=0; i<listMapConf.count(); i++) {
		AMapConf* item = listMapConf[i];
		std::cout << item->layer_id.toStdString() << ", ";
		std::cout << item->line_type.toStdString() << ", ";
		std::cout << item->line_width.toStdString() << ", ";
		std::cout << item->line_color.toStdString() << ", ";
		std::cout << item->fill_pattern.toStdString() << ", ";
		std::cout << item->fill_color.toStdString() << ", ";
		std::cout << item->font.toStdString() << ", ";
		std::cout << item->font_size.toStdString() << ", ";
		std::cout << item->font_color.toStdString() << ", ";
		std::cout << item->symbol.toStdString() << ", ";
		std::cout << item->scope.toStdString() << ", ";
		std::cout << item->disp.toStdString() << std::endl;
		std::cout << std::endl;
	}
	std::cout << "mapdefault : " << std::endl;
	for (int i=0; i<listMapDefault.count(); i++) {
		AMapDefault* item = listMapDefault[i];
		std::cout << item->bg_color.toStdString() << ", ";
		std::cout << item->rng.toStdString() << ", ";
		std::cout << item->mpp.toStdString() << ", ";
		std::cout << item->grid_color.toStdString() << ", ";
		std::cout << item->cps_color.toStdString() << ", ";
		std::cout << item->log_yn.toStdString() << ", ";
		std::cout << item->log_file.toStdString() << ", ";
		std::cout << item->center_lat.toStdString() << ", ";
		std::cout << item->center_lon.toStdString() << std::endl;
	}
}

QString AMapconf::dftvalue(const QString& layer_id)
{
	QString lineType    = findMapConf(layer_id, "LINE_TYPE");
	QString lineWidth   = findMapConf(layer_id, "LINE_WIDTH");
	QString lineColor   = findMapConf(layer_id, "LINE_COLOR");
	QString fillPattern = findMapConf(layer_id, "FILL_PATTERN");
	QString fillColor   = findMapConf(layer_id, "FILL_COLOR");
	QString font        = findMapConf(layer_id, "FONT");
	QString fontSize    = findMapConf(layer_id, "FONT_SIZE");
	QString fontColor   = findMapConf(layer_id, "FONT_COLOR");
	QString symbol      = findMapConf(layer_id, "SYMBOL");


	return QString("%1:%2:%3:%4:%5:%6:%7:%8:%9")
			.arg(lineType)
			.arg(lineWidth)
			.arg(lineColor)
			.arg(fillPattern)
			.arg(fillColor)
			.arg(font)
			.arg(fontSize)
			.arg(fontColor)
			.arg(symbol);
}

void AMapconf::addLayerAttr(const QString& layer_id, const ALayerAttr& attr)
{
	QString alayer_id = layer_id;
	QString aline_type = attr.linetype;
	QString aline_width = attr.linewidth;
	QString aline_color = attr.linecolor;
	QString afill_pattern = attr.fillpattern;
	QString afill_color = attr.fillcolor;
	QString afont = attr.fontname;
	QString afont_size = attr.fontsize;
	QString afont_color = attr.fontcolor;
	QString asymbol = attr.symbol;
	QString ascope = QString("");
	QString adisp = QString("");

	addMapConf(
			aline_type,
			aline_width,
			aline_color,
			afill_pattern,
			afill_color,
			afont,
			afont_size,
			afont_color,
			asymbol,
			alayer_id,
			ascope,
			adisp
			);
}

void AMapconf::addLayerAttr(const QString& layer_id, const ALayerAttr* attr)
{
	QString alayer_id = layer_id;
	QString aline_type = attr->linetype;
	QString aline_width = attr->linewidth;
	QString aline_color = attr->linecolor;
	QString afill_pattern = attr->fillpattern;
	QString afill_color = attr->fillcolor;
	QString afont = attr->fontname;
	QString afont_size = attr->fontsize;
	QString afont_color = attr->fontcolor;
	QString asymbol = attr->symbol;
	QString ascope = QString("");
	QString adisp = QString("");

	addMapConf(
			aline_type,
			aline_width,
			aline_color,
			afill_pattern,
			afill_color,
			afont,
			afont_size,
			afont_color,
			asymbol,
			alayer_id,
			ascope,
			adisp
			);
}

void AMapconf::setMapConfDisp(const QString& layer_id, const QString& disp)
{
	for (int i=0; i<listMapConf.count(); i++) {
		AMapConf* item = new AMapConf;
		if (item->layer_id == layer_id) {
			item->disp = disp;
			return;
		}
	}
	// 등록된 Layer Id가 없으면 신규로 등록한다.
	AMapConf* item = new AMapConf;
	item->layer_id = layer_id;
	item->disp = disp;
	listMapConf.append(item);
}

bool AMapconf::isLayerDisplay(const QString& layer_id)
{
	for (int i=0; i<listMapConf.count(); i++) {
		AMapConf* item = listMapConf[i];
		if (item->layer_id.toUpper() == layer_id.toUpper()) {
			return item->disp == "Y";
		}
	}
	return false;
}

bool AMapconf::isMapFileLayer(const QString& layer_id)
{
	for (int i=0; i<listMapConf.count(); i++) {
		AMapConf* item = listMapConf[i];
		if (item->layer_id.toUpper() == layer_id.toUpper()) {
			return true;
		}
	}
	return false;
}

void AMapconf::addMapDefault(
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
			)
{
	AMapDefault* item = NULL;
	if (listMapDefault.count() == 0) {
		item = new AMapDefault;
		item->bg_color = bg_color;
		item->rng = rng;
		item->mpp = mpp;
		item->grid_color = grid_color;
		item->cps_color = cps_color;
		item->log_yn = log_yn;
		item->log_file = log_file;
		item->center_lat = center_lat;
		item->center_lon = center_lon;
		item->vw_cps = vw_cps;
		item->vw_latlon = vw_latlon;
		listMapDefault.append(item);
	}else {
		item = listMapDefault[0];
		item->bg_color = bg_color;
		item->rng = rng;
		item->mpp = mpp;
		item->grid_color = grid_color;
		item->cps_color = cps_color;
		item->log_yn = log_yn;
		item->log_file = log_file;
		item->center_lat = center_lat;
		item->center_lon = center_lon;
		item->vw_cps = vw_cps;
		item->vw_latlon = vw_latlon;
	}
}

void AMapconf::clear()
{
	listMapConf.clear();
	listMapDefault.clear();

	AMapConf* item = new AMapConf;
	listMapConf.append(item);

	AMapDefault* mapdefault = new AMapDefault;
	listMapDefault.append(mapdefault);
}

bool AMapconf::readConfigXml(const QString& fileName)
{
	clear();
	AMapDefault* mapdefault = listMapDefault[0];

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		std::cerr << "Error : cannot read file " << qPrintable(fileName)
				<< " : " << qPrintable(file.errorString())
				<< std::endl;
		return false;
	}
	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument doc;
	if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
		std::cerr << "Error : Parse error at line  " << errorLine << ", "
				<< "column " << errorColumn << " : "
				<< qPrintable(errorStr) << std::endl;
	}
	QDomElement root = doc.documentElement();
	if (root.tagName() != "MapConfig") {
		std::cerr << "Error : not a map_config.xml file " << std::endl;
		return false;
	}
	QDomNode child = root.firstChild();
	while(!child.isNull()) {
		if (child.toElement().tagName() == "MPP") {
			mapdefault->mpp = child.toElement().text();
		}
		else if(child.toElement().tagName() == "GridColor") {
			mapdefault->grid_color = child.toElement().text();
		}
		else if(child.toElement().tagName() == "CPSColor") {
			mapdefault->cps_color = child.toElement().text();
		}
		else if(child.toElement().tagName() == "Layers") {
			QDomNode child2 = child.firstChild();
			while(!child2.isNull()) {
				if (child2.toElement().tagName() == "Layer") {
					QString layer_id = child2.toElement().attribute("name");
					QString disp = child2.toElement().attribute("display");
					setMapConfDisp(layer_id, disp);
				}
				child2 = child2.nextSibling();
			}
		}
		else if(child.toElement().tagName() == "ToggleView") {
			QDomNode child2 = child.firstChild();
			while(!child2.isNull()) {
				if (child2.toElement().tagName() == "Compass") {
					QString compass = child2.toElement().text();
					mapdefault->vw_cps = compass;
				}
				else if(child2.toElement().tagName() == "LatLon") {
					QString latlon = child2.toElement().text();
					mapdefault->vw_latlon = latlon;
				}
				child2 = child2.nextSibling();
			}
		}
		else if(child.toElement().tagName() == "Log") {
			QDomNode child2 = child.firstChild();
			while(!child2.isNull()) {
				if (child2.toElement().tagName() == "Enabled") {
					QString logenabled = child2.toElement().text();
					mapdefault->log_yn = logenabled;
				}
				else if(child2.toElement().tagName() == "FileName") {
					QString fileName = child2.toElement().text();
					mapdefault->log_file = fileName;
				}
				child2 = child2.nextSibling();
			}
		}else {
			;
		}
		child = child.nextSibling();
	}
	file.close();

	return true;
}

bool AMapconf::writeConfigXml(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		return false;
	}
	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement("MapConfig");

	xmlWriter.writeTextElement("MPP", mppString());
	xmlWriter.writeTextElement("GridColor", grid_colorString());
	xmlWriter.writeTextElement("CPSColor", cps_colorString());

	xmlWriter.writeStartElement("Layers");
	for (int i=0; i<listMapConf.count(); i++) {
		AMapConf* item = listMapConf[i];
		xmlWriter.writeStartElement("Layer");
		xmlWriter.writeAttribute("name", item->layer_id);
		xmlWriter.writeAttribute("display", item->disp);
		xmlWriter.writeEndElement();
	}
	xmlWriter.writeEndElement();

	xmlWriter.writeStartElement("ToggleView");
	xmlWriter.writeTextElement("Compass", vw_cps());
	xmlWriter.writeTextElement("LatLon", vw_latlon());
	xmlWriter.writeEndElement();

	xmlWriter.writeStartElement("Log");
	xmlWriter.writeTextElement("Enabled", log_ynString());
	xmlWriter.writeTextElement("FileName", log_file());
	xmlWriter.writeEndElement();

	xmlWriter.writeEndDocument();

	file.close();

	if (file.error()) {
		return false;
	}
	return true;
}

void AMapconf::getConfigFromDb(const QSqlDatabase& db, const Log424& loger)
{
	Log424 log = loger;

	QSqlError sqlerror;
	QSqlQuery *query = new QSqlQuery(db);
	QString sql;
	int count = 0;
	log.print(QString("retrieve data from db (%1)").arg(db.hostName()));

	// mapconf
	sql  = " SELECT                                                      \n";
	sql += "        LINE_TYPE,  LINE_WIDTH,  LINE_COLOR, FILL_PATTERN,   \n";
	sql += "        FILL_COLOR, FONT,        FONT_SIZE,  FONT_COLOR,     \n";
	sql += "        SYMBOL,     LAYER_ID,    SCOPE,      DISP            \n";
	sql += "   FROM TB_MAPCONF ";

	query->exec(sql);

	sqlerror = query->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		log.print(QString("DB Error : %1").arg(sqlerror.text()));
		delete query;
		return;
	}
	count = 0;
	while(query->next()) {
		QString line_type = query->value(0).toString();
		QString line_width = query->value(1).toString();
		QString line_color = query->value(2).toString();
		QString fill_pattern = query->value(3).toString();
		QString fill_color = query->value(4).toString();
		QString font = query->value(5).toString();
		QString font_size = query->value(6).toString();
		QString font_color = query->value(7).toString();
		QString symbol = query->value(8).toString();
		QString layer_id = query->value(9).toString();
		QString scope = query->value(10).toString();
		QString disp = query->value(11).toString();

		addMapConf(
				line_type,
				line_width,
				line_color,
				fill_pattern,
				fill_color,
				font,
				font_size,
				font_color,
				symbol,
				layer_id,
				scope,
				disp
				);
		count++;
	}
	log.print(QString("mapconf %1 read done").arg(count));
}

void AMapconf::getDefaultFromDb(const QSqlDatabase& db, const Log424& logger)
{
	Log424 log = logger;
	QSqlError sqlerror;
	QSqlQuery *query = new QSqlQuery(db);
	QString sql;
	int count = 0;

	// mapdefault
	sql  = " SELECT                                                     \n";
	sql += "        BG_COLOR,       RNG,       MPP,       GRID_COLOR,   \n";
	sql += "        CPS_COLOR,      LOG_YN,    LOG_FILE,  CENTER_LAT,   \n";
	sql += "        CENTER_LON,     VW_CPS,    VW_LATLON                \n";
	sql += "   FROM TB_MAPDEFAULT ";

	query->exec(sql);

	sqlerror = query->lastError();
	if (sqlerror.type() != QSqlError::NoError) {
		log.print(QString("DB Error : %1").arg(sqlerror.text()));
		delete query;
		return;
	}
	count = 0;
	while(query->next()) {
		QString bg_color = query->value(0).toString();
		QString rng = query->value(1).toString();
		QString mpp = query->value(2).toString();
		QString grid_color = query->value(3).toString();
		QString cps_color = query->value(4).toString();
		QString log_yn = query->value(5).toString();
		QString log_file = query->value(6).toString();
		QString center_lat = query->value(7).toString();
		QString center_lon = query->value(8).toString();
		QString vw_cps = query->value(9).toString();
		QString vw_latlon = query->value(10).toString();

		addMapDefault(
				bg_color,
				rng,
				mpp,
				grid_color,
				cps_color,
				log_yn,
				log_file,
				center_lat,
				center_lon,
				vw_cps,
				vw_latlon
				);
		count++;
	}
	log.print(QString("mapdefault %1 read done").arg(count));
}

void AMapconf::getFromDb(const QSqlDatabase& db, const Log424& logger)
{
	getConfigFromDb(db, logger);
	getDefaultFromDb(db, logger);
}

void AMapconf::setCenter(const QString& c)
{
	AMapDefault* item = NULL;
	if (listMapDefault.count() < 1) {
		item = new AMapDefault;
		item->center_lat = c.mid(0, 9);
		item->center_lon = c.mid(9, 10);
		listMapDefault.append(item);
	}else {
		item = listMapDefault[0];
		item->center_lat = c.mid(0, 9);
		item->center_lon = c.mid(9, 10);
	}
}

void AMapconf::setRange(const QString& r)
{
	AMapDefault* item = NULL;
	if (listMapDefault.count() < 1) {
		item = new AMapDefault;
		item->rng = r;
		listMapDefault.append(item);
	}else {
		item = listMapDefault[0];
		item->rng = r;
	}
}

void AMapconf::setBg_Color(const QString& bg)
{
	AMapDefault* item = NULL;
	if (listMapDefault.count() < 1) {
		item = new AMapDefault;
		item->bg_color = bg;
		listMapDefault.append(item);
	}else {
		item = listMapDefault[0];
		item->bg_color = bg;
	}
}

