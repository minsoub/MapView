/*
 * AUserDefinedMapList.cpp
 *
 *  Created on: 2012. 2. 24.
 *      Author: HIST002
 */

#include "AUserDefinedMapList.h"

AUserDefinedMapList::AUserDefinedMapList(Log424* log) {
	// TODO Auto-generated constructor stub
	_log = log;
	mapList = QVector<AUserDefinedMap*>();
}

AUserDefinedMapList::AUserDefinedMapList() {
	// TODO Auto-generated destructor stub
	_log = NULL;
	mapList = QVector<AUserDefinedMap*>();
}

bool AUserDefinedMapList::query(QSqlQuery* q)
{
	_lasterror = QString("");
	int count = 0;
#ifndef QT_NO_DEBUG
	logprint(QString("%1 query start").arg("User Defined Map"));
#endif

	QString prevMap = QString("");
	QString prevLayer = QString("");
	QSqlError sqlerror;
	QString sql = QString (
			"SELECT                                              "
			"       USER_LAYER_ID, LAYER_ID, ELEMENT_ID          "
			"  FROM TB_USERLAYERCONF                             "
			" ORDER BY USER_LAYER_ID, LAYER_ID, ELEMENT_ID       "
			);
	q->exec(sql);
	if (q->lastError().type() != QSqlError::NoError) {
		_lasterror = q->lastError().text();
		logprint(QString("AUserDefinedMapList query error : %1 (%2)").arg(q->lastError().text()).arg(sql));
		return false;
	}
	mapList.clear();
	AUserDefinedMap* nowmap;
	while(q->next()) {
		QString mapid = q->value(0).toString();
		QString layerid = q->value(1).toString();
		QString id = q->value(2).toString();

		QString keyMap = mapid;
		QString keyLayer = layerid;

		if (keyMap != prevMap) {
			AUserDefinedMap* newmap = new AUserDefinedMap(mapid);
			mapList.append(newmap);
			newmap->addLayer(layerid);
			newmap->addId(layerid, id);
			nowmap = newmap;
		}else {		// map이 같으면
			if (keyLayer != prevLayer) {
				nowmap->addLayer(layerid);
				nowmap->addId(layerid, id);
			}else {
				nowmap->addId(layerid, id);
			}
		}
		prevLayer = keyLayer;
		prevMap = keyMap;
		count++;
	}
	return true;
}

void AUserDefinedMapList::print(QTextStream& out)
{
	if (mapList.count() < 1) {
		return;
	}

	for (int i=0; i<mapList.count(); i++) {
		AUserDefinedMap* map = mapList[i];
		out << QString("USER_LAYER:%1").arg(map->ID()) << "\n";

		for (int j=0; j<map->LayerCount(); j++) {
			AUserDefinedLayer* layer = map->layer(j);

			if (layer != NULL) {
				out << QString("LAYER:%1").arg(layer->Id()) << "\n";
				if (layer->isAll) {
					out << QString("ID:ALL") << "\n";
				}else {
					for (int k=0; k<layer->IdCount(); k++) {
						out << QString("ID:%1").arg(layer->idName(k)) << "\n";
					}
				}
				out << QString("ENDLAYER") << "\n";
			}
		}
		out << QString("ENDUSER_LAYER") << "\n";
	}
}

void AUserDefinedMapList::addMap(const QString& mapid)
{
	AUserDefinedMap* newmap = new AUserDefinedMap(mapid);
	mapList.append(newmap);
}

/**
 * 사용자 맵 정의 레이어를 파일에서 읽어서 데이터를 구성한다.
 */
void AUserDefinedMapList::read(QTextStream& in, int& lineNo, const QString& mapid)
{
	QStringList list;
	QString line;
	AUserDefinedMap* newmap = new AUserDefinedMap(mapid);

	while(true) {
		line = in.readLine();
		lineNo++;
		if (line == "ENDUSER_LAYER") {
			mapList.append(newmap);
			break;
		}
		list = line.split(":");
		if (list[0] == "LAYER") {
			AUserDefinedLayer* newlayer = new AUserDefinedLayer(list[1]);
			newmap->addLayer(newlayer);
			while(true) {
				line = in.readLine();
				lineNo++;
				if (line == "ENDLAYER") break;
				list = line.split(":");
				newlayer->addId(list[1]);
			}
		}
	}
}

void AUserDefinedMapList::draw(QPainter* painter, AirDraw* ad)
{
	for (int i=0; i<mapList.count(); i++)
	{
		mapList[i]->draw(painter, ad);
	}
}
