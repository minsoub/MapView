#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QtSql>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include "mapview.h"
#include "./lib/ConfigParser.h"
#include "./lib/DbManager.h"
#include "./lib/Log424.h"
#include "AMap.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString map_dir = QString(getenv("MAP_DIR"));
    QString adapt_dir = QString(getenv("ADAPT_DIR"));

    if (map_dir.isEmpty() || adapt_dir.isEmpty()) {
    	QMessageBox::critical(NULL, "Error", "$MAP_DIR or $ADAPT_DIR is not setted.");
    	return -1;
    }
    QDir mapdir(map_dir);
    QDir adaptdir(adapt_dir);

    if (!mapdir.exists() || !adaptdir.exists()) {
    	QMessageBox::critical(NULL, "Error", "$MAP_DIR or $ADAPT_DIR does not exits.");
    	return -2;
    }

    QString mapconfigxml = QString("%1/%2").arg(adapt_dir).arg("map_config.xml");

    if (!QFile::exists(mapconfigxml)) {
    	QString msg = QString("%1 file is not exists.").arg(mapconfigxml);
    	QMessageBox::critical(NULL, "Error", msg);
    	return -3;
    }

#ifndef QT_NO_DEBUG
    std::cout << "mapconfig : " << mapconfigxml.toStdString() << "\n";
#endif

    if (argc != 2) {			// default map editor execute
    	// 환경변수 2개를 세팅
    	ConfigParser::getInstance().setEnvMapDir(map_dir);
    	ConfigParser::getInstance().setEnvAdaptDir(adapt_dir);

    	ConfigParser::getInstance().readConfigXml(mapconfigxml);

    	QString fileName = QFileDialog::getOpenFileName(NULL,
    	     "Open Map File", map_dir, "Map Files (*.map);;All Files(*)", 0, 0);

    	if (!fileName.isEmpty()) {
    		ConfigParser::getInstance().setMapfile(fileName);
    	}else {
    		QMessageBox::critical(NULL, "User Cancel", "User Canceled");
    		return -3;
    	}

    	MapView w;
    	w.showMaximized();

    	//w.showFullScreen();

    	return a.exec();
    }else {			// db2map execute
    	Log424 *log = new Log424(QString("db2map.log")); //log 객체
    	DbManager *dbmanager = new DbManager(log);
    	QString mapFileName = "ams.map";

      bool b = dbmanager->setDb(ConfigParser::getInstance().driver(),
               ConfigParser::getInstance().host(),
               ConfigParser::getInstance().db(),
               ConfigParser::getInstance().user(),
               ConfigParser::getInstance().password(),
               ConfigParser::getInstance().port());

      if(b == false){
            QString errmsg = dbmanager->error();
            QMessageBox::critical(NULL,"Db Connection Error", errmsg);
				exit(-1);
        }

      AMap* map = new AMap(*log);

      map->getDataFromDb(QSqlDatabase::database("amsdb"));

      map->write(mapFileName);
      std::cout << "done. plz,check " << mapFileName.toStdString() <<  std::endl;

    	return 0;
    }
}
