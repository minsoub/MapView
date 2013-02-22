/*
 * ConfigParser.cpp
 *
 *  Created on: 2012. 2. 20.
 *      Author: HIST002
 */
#include <QUrl>
#include <QFile>
#include "../lib_layer/MapDefine.h"
#include "ConfigParser.h"

ConfigParser* ConfigParser::pinstance = NULL;

ConfigParser::ConfigParser() {
	// TODO Auto-generated constructor stub
	_errorMessage = QString("");
	_driver = QString("QOCI");
	_host   = QString("165.246.34.221");
	_db     = QString("SMSD");
	_user   = QString("adapt");
	_password = QString("adapt");
	_port     = 1521;
	_layervisible = QString(MaxLayerCount, QChar('0'));		// visible true

	_wonjum = QPointF(37.0, 127.0);
	_mpp    = 2000;
	_bgcolor = QColor::fromRgb(0, 0, 0, TuMyungDo);
	_cpscolor = QColor::fromRgb(255, 255, 255, TuMyungDo);
	_gridcolor = QColor::fromRgb(255, 255, 255, TuMyungDo);
	_compassshow = false;
	_latlonshow  = false;
	_logenable   = false;
	_logfilename = "smeu.log";
}

ConfigParser::~ConfigParser() {
	// TODO Auto-generated destructor stub
	if (pinstance != NULL) delete pinstance;
}

bool ConfigParser::ParseUrl(const QString url)
{
	QUrl dburl(url, QUrl::TolerantMode);
	if (!dburl.isValid()) return false;

	_driver = dburl.scheme();
	_host   = dburl.host();
	_db     = dburl.path().mid(1);
	_user   = dburl.userName();
	_password = dburl.password();
	_port   = dburl.port(1521);

	return true;
}

bool ConfigParser::ParseFile(const QString fileName)
{
	if (!QFile::exists(fileName)) {
		_errorMessage = QString("%1 not exits").arg(fileName);
		return false;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		_errorMessage = QString(QObject::tr("Cannot read file %1:\n%2")
					.arg(file.fileName()).arg(file.errorString()));
		return false;
	}
	QTextStream in(&file);
	while(!in.atEnd()) {
		QString line = in.readLine().simplified();
		if (line.startsWith("//")) continue;
		if (line.length() < 1) continue;
		QStringList fields = line.split(':');
		if (fields.count() == 2) {
			QString key = fields.at(0).toLower().trimmed();
			QString value = fields.at(1).trimmed();

			if (key == "driver") _driver = value;
			if (key == "host")   _host = value;
			if (key == "database") _db = value;
			if (key == "userid") _user = value;
			if (key == "password") _password = value;
			if (key == "port") _port = value.toInt();
			if (key == "wonjum") {
				_wonjum.setX(35);
				_wonjum.setY(127);
				QStringList tmpList = value.split(',');
				if (tmpList.length() == 2) {
					_wonjum.setX(tmpList[0].toDouble());
					_wonjum.setY(tmpList[1].toDouble());
				}
			}
			if (key == "mpp") _mpp = value.toDouble();
			if (key == "bgcolor") {
				_bgcolor = QColor(Qt::black);
				QStringList tmpList = value.split(',');
				if (tmpList.length() == 3) {
					_bgcolor = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt());
				}
			}

			if (key == "coast") { if(value == "1") _layervisible[Layer_Coast] = QChar('1'); }
			if (key == "fir")   { if(value == "1") _layervisible[Layer_Fir]   = QChar('1'); }
			if (key == "kadiz") { if(value == "1") _layervisible[Layer_Kadiz] = QChar('1'); }
			if (key == "sector") { if(value == "1") _layervisible[Layer_Sector] = QChar('1'); }
			if (key == "tca") { if(value == "1") _layervisible[Layer_Tca] = QChar('1'); }
			if (key == "ra") { if(value == "1") _layervisible[Layer_Ra] = QChar('1'); }
			if (key == "da") { if(value == "1") _layervisible[Layer_Da] = QChar('1'); }
			if (key == "pa") { if(value == "1") _layervisible[Layer_Pa] = QChar('1'); }
			if (key == "aa") { if(value == "1") _layervisible[Layer_Aa] = QChar('1'); }
			if (key == "moa") { if(value == "1") _layervisible[Layer_Moa] = QChar('1'); }
			if (key == "msaw") { if(value == "1") _layervisible[Layer_Msaw] = QChar('1'); }
			if (key == "cata") { if(value == "1") _layervisible[Layer_Cata] = QChar('1'); }
			if (key == "ad_civil") { if(value == "1") _layervisible[Layer_Ad_Civil] = QChar('1'); }
			if (key == "ad_mil") { if(value == "1") _layervisible[Layer_Ad_Mil] = QChar('1'); }
			if (key == "ad_joint") { if(value == "1") _layervisible[Layer_Ad_Joint] = QChar('1'); }
			if (key == "runway") { if(value == "1") _layervisible[Layer_Runway] = QChar('1'); }
			if (key == "rep_fix") { if(value == "1") _layervisible[Layer_Rep_Fix] = QChar('1'); }
			if (key == "fix") { if(value == "1") _layervisible[Layer_Fix] = QChar('1'); }
			if (key == "t_fix") { if(value == "1") _layervisible[Layer_T_Fix] = QChar('1'); }
			if (key == "vortac") { if(value == "1") _layervisible[Layer_Vortac] = QChar('1'); }
			if (key == "vordme") { if(value == "1") _layervisible[Layer_Vordme] = QChar('1'); }
			if (key == "ndb") { if(value == "1") _layervisible[Layer_Ndb] = QChar('1'); }
			if (key == "route") { if(value == "1") _layervisible[Layer_Route] = QChar('1'); }
			if (key == "hold") { if(value == "1") _layervisible[Layer_Hold] = QChar('1'); }
			if (key == "sensor") { if(value == "1") _layervisible[Layer_Sensor] = QChar('1'); }
			if (key == "sid") { if(value == "1") _layervisible[Layer_Sid] = QChar('1'); }
			if (key == "star") { if(value == "1") _layervisible[Layer_Star] = QChar('1'); }
			if (key == "apch") { if(value == "1") _layervisible[Layer_Apch] = QChar('1'); }
			if (key == "user") { if(value == "1") _layervisible[Layer_User] = QChar('1'); }
			if (key == "logfilename") _logfilename = value;
			if (key == "logenable") {
				_logenable = false;
				if (value == "1") _logenable = true;
			}
		}
	}
	file.close();
	if (file.error() != QFile::NoError) {
		_errorMessage = QString(QObject::tr("Error When reading from %1:\n%2")
					.arg(file.fileName())
					.arg(file.errorString()));
		return false;
	}
	return true;
}

QString ConfigParser::toString()
{
	int r, g, b;
	_bgcolor.getRgb(&r, &g, &b);

	return QString(""
			"wonjum:%1,%2\n"
			"mpp:%3\n"
			"bgcolor:%4,%5,%6\n"
			"mapfilename:%7\n"
			).arg(_wonjum.x()).arg(_wonjum.y())
			.arg(_mpp)
			.arg(r).arg(g).arg(b)
			.arg(_mapfilename);
}

void ConfigParser::readConfigXml(const QString& xmlFile)
{
	mapconf.readConfigXml(xmlFile);
	_mpp = mapconf.mpp();
	_cpscolor = mapconf.cps_color();
	_gridcolor = mapconf.grid_color();
	_logenable = mapconf.log_yn();
	_logfilename = mapconf.log_file();

	if (mapconf.isLayerDisplay("coast")) { _layervisible[Layer_Coast] = QChar('1'); }
	if (mapconf.isLayerDisplay("fir")) { _layervisible[Layer_Fir] = QChar('1'); }
	if (mapconf.isLayerDisplay("kadiz")) { _layervisible[Layer_Kadiz] = QChar('1'); }
	if (mapconf.isLayerDisplay("sector")) { _layervisible[Layer_Sector] = QChar('1'); }
	if (mapconf.isLayerDisplay("tca")) { _layervisible[Layer_Tca] = QChar('1'); }
	if (mapconf.isLayerDisplay("ra")) { _layervisible[Layer_Ra] = QChar('1'); }
	if (mapconf.isLayerDisplay("da")) { _layervisible[Layer_Da] = QChar('1'); }
	if (mapconf.isLayerDisplay("pa")) { _layervisible[Layer_Pa] = QChar('1'); }
	if (mapconf.isLayerDisplay("aa")) { _layervisible[Layer_Aa] = QChar('1'); }
	if (mapconf.isLayerDisplay("moa")) { _layervisible[Layer_Moa] = QChar('1'); }
	if (mapconf.isLayerDisplay("msaw")) { _layervisible[Layer_Msaw] = QChar('1'); }
	if (mapconf.isLayerDisplay("cata")) { _layervisible[Layer_Cata] = QChar('1'); }

	if (mapconf.isLayerDisplay("ad_civil")) { _layervisible[Layer_Ad_Civil] = QChar('1'); }
	if (mapconf.isLayerDisplay("ad_mil")) { _layervisible[Layer_Ad_Mil] = QChar('1'); }
	if (mapconf.isLayerDisplay("ad_joint")) { _layervisible[Layer_Ad_Joint] = QChar('1'); }

	if (mapconf.isLayerDisplay("runway")) { _layervisible[Layer_Runway] = QChar('1'); }

	if (mapconf.isLayerDisplay("rep_fix")) { _layervisible[Layer_Rep_Fix] = QChar('1'); }
	if (mapconf.isLayerDisplay("fix")) { _layervisible[Layer_Fix] = QChar('1'); }
	if (mapconf.isLayerDisplay("t_fix")) { _layervisible[Layer_T_Fix] = QChar('1'); }

	if (mapconf.isLayerDisplay("vortac")) { _layervisible[Layer_Vortac] = QChar('1'); }
	if (mapconf.isLayerDisplay("vordme")) { _layervisible[Layer_Vordme] = QChar('1'); }
	if (mapconf.isLayerDisplay("ndb")) { _layervisible[Layer_Ndb] = QChar('1'); }
	if (mapconf.isLayerDisplay("route")) { _layervisible[Layer_Route] = QChar('1'); }
	if (mapconf.isLayerDisplay("hold")) { _layervisible[Layer_Hold] = QChar('1'); }
	if (mapconf.isLayerDisplay("sensor")) { _layervisible[Layer_Sensor] = QChar('1'); }
	if (mapconf.isLayerDisplay("sid")) { _layervisible[Layer_Sid] = QChar('1'); }
	if (mapconf.isLayerDisplay("star")) { _layervisible[Layer_Star] = QChar('1'); }
	if (mapconf.isLayerDisplay("apch")) { _layervisible[Layer_Apch] = QChar('1'); }
	if (mapconf.isLayerDisplay("user")) { _layervisible[Layer_User] = QChar('1'); }

}
