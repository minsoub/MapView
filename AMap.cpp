/*
 * AMap.cpp
 *
 *  Created on: 2012. 2. 24.
 *      Author: HIST002
 */
#include <QFile>
#include <iostream>
#include "AMap.h"
#include "lib/MapUtil.h"
#include "lib/CalcAir.h"
#include "lib/UnitChange.h"

using namespace std;

AMap::AMap(Log424& log424, AirDraw* ad):log(log424) {
	// TODO Auto-generated constructor stub
	air = ad;
	udmList = NULL;

	textvisible = false;

	initMap(log424);

	// User Layer Item List
	userlayerList = new AUserLayerItemMng;
	userlayerList->setLog(log424);
	userlayerList->setAirdraw(air);

	// 사용자 정의 layer = map이다.
	udmList = new AUserDefinedMapList();
}

AMap::AMap(Log424& log424):log(log424) {
	udmList = NULL;

	textvisible = false;

	initMap(log424);

	// User Layer Item List
	userlayerList = new AUserLayerItemMng;
	userlayerList->setLog(log424);
	//userlayerList->setAirdraw(air);

	// 사용자 정의 layer = map이다.
	udmList = new AUserDefinedMapList();
}

AMap::~AMap() {
	// TODO Auto-generated destructor stub
	layerList.clear();
}

QString AMap::magicString()
{
	return QString("ATAP-MAP-%1").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmm"));
}

ALayer* AMap::findLayer(LayerType t)
{
	if (t == Layer_Unknown) return NULL;
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		if (layer->layerType() == t) { return layer; }
	}
	return NULL;
}

ALayer* AMap::findLayer(const QString& name)
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		if (layer->shortName().toUpper() == name.toUpper()) { return layer; }
	}
	return NULL;
}

void AMap::getUserDataFromDb(const QSqlDatabase& db)
{
	QSqlQuery *query = new QSqlQuery(db);
	userlayerList->query(query);
	delete query;
}

/**
 * DB로 부터 map의 내용을 조회해서 메모리에 넣는다.
 */
void AMap::getDataFromDb(const QSqlDatabase& db)
{
	ALayer* layer;
	QSqlQuery* query = new QSqlQuery(db);
	QString sql;

	log.print(QString("Start retrieve data from DB (%1)").arg(db.hostName()));
	log.print(QString("TB_MAPCONF, TB_MAPDEFAULT, TB_MAPLAYER data query.."));

	mapconf.clear();
	mapconf.getFromDb(db, log);

	// 각 layer를 가져와서 데이터를 생성한다.
	// select 순서(9개) : id -> idx -> via -> lat -> lon -> center_lat -> center_lon ->bearing -> dist

	// Coast
	sql = QString(
			"SELECT                                                       "
			"       A.COAST_ID,      b.BNDRY_IDX,      'G',               "
			"       B.LAT,           B.LON,            B.LAT,     B.LON,  "
			"         0.0,                   0.0,                    ''                        "
			"  FROM TB_COAST A, TB_COASTBNDRY B                           "
			" WHERE A.COAST_ID = B.COAST_ID                               "
			" ORDER BY A.COAST_ID, B.BNDRY_IDX                            "
			);
	layer = findLayer(Layer_Coast);			// 생성자에서 생성한 레이어에서 Coast 레이어를 찾아서 리턴한다.
	if (layer)
		layer->query(query, sql);

	// FIR
	sql = QString(
			"SELECT                                                        "
			"       FIR_ID,   BNDRY_IDX,      BNDRY_VIA,      LAT,         "
			"       LON,      ARC_CENTER_LAT, ARC_CENTER_LON, ARC_BEARING, "
			"       ARC_DIST                                               "
			"  FROM TB_FIRBNDRY                                            "
			" WHERE FIR_ID IN ( 'RKRR', 'RJJJ', 'RCAA', 'RPHI', 'ZKKP', 'ZSHA' )                           "
			" ORDER BY FIR_ID, BNDRY_IDX                                   "
			);
	layer = findLayer(Layer_Fir);
	if (layer)
		layer->query(query, sql);

	// RA
	sql = QString(
			" SELECT                                                                     "
			"        A.RA_ID,        B.BNDRY_IDX,       B.BNDRY_VIA,      B.LAT,         "
			"        B.LON,          B.ARC_CENTER_LAT,  B.ARC_CENTER_LON, B.ARC_BEARING, "
			"        B.ARC_DIST*2,   B.MULTI_CD                                          "
			"   FROM TB_RA A, TB_RABNDRY B                                               "
			"  WHERE A.RA_ID = B.RA_ID                                                   "
			"    AND A.RA_TP = B.RA_TP                                                   "
			"    AND A.ICAO_CD = B.ICAO_CD                                               "
			"    AND A.MULTI_CD = B.MULTI_CD                                             "
			"    AND A.ICAO_CD  = 'RK'                                                   "
			"    AND A.RA_TP    = 'R'                                                    "
			"  ORDER BY A.RA_ID, B.BNDRY_IDX                                             "
			);
	layer = findLayer(Layer_Ra);
	if (layer)
		layer->query(query, sql);

	// DA
	sql = QString(
			" SELECT                                                                     "
			"        A.RA_ID,        B.BNDRY_IDX,       B.BNDRY_VIA,      B.LAT,         "
			"        B.LON,          B.ARC_CENTER_LAT,  B.ARC_CENTER_LON, B.ARC_BEARING, "
			"        B.ARC_DIST*2,   A.MULTI_CD                                          "
			"   FROM TB_RA A, TB_RABNDRY B                                               "
			"  WHERE A.RA_ID = B.RA_ID                                                   "
			"    AND A.RA_TP = B.RA_TP                                                   "
			"    AND A.ICAO_CD = B.ICAO_CD                                               "
			"    AND A.MULTI_CD = B.MULTI_CD                                             "
			"    AND A.ICAO_CD = 'RK'                                                    "
			"    AND A.RA_TP   = 'D'                                                     "
			"  ORDER BY A.RA_ID, B.BNDRY_IDX                                             "
			);
	layer = findLayer(Layer_Da);
	if (layer)
		layer->query(query, sql);

	// PA
	sql = QString(
			" SELECT                                                                     "
			"        A.RA_ID,        B.BNDRY_IDX,       B.BNDRY_VIA,      B.LAT,         "
			"        B.LON,          B.ARC_CENTER_LAT,  B.ARC_CENTER_LON, B.ARC_BEARING, "
			"        B.ARC_DIST*2,   A.MULTI_CD                                          "
			"   FROM TB_RA A, TB_RABNDRY B                                               "
			"  WHERE A.RA_ID = B.RA_ID                                                   "
			"    AND A.RA_TP = B.RA_TP                                                   "
			"    AND A.ICAO_CD = B.ICAO_CD                                               "
			"    AND A.MULTI_CD = B.MULTI_CD                                             "
			"    AND A.ICAO_CD = 'RK'                                                    "
			"    AND A.RA_TP   = 'P'                                                     "
			"  ORDER BY A.RA_ID, B.BNDRY_IDX                                             "
			);
	layer = findLayer(Layer_Pa);
	if (layer)
		layer->query(query, sql);

	// AA
	sql = QString(
			" SELECT                                                                     "
			"        A.RA_ID,        B.BNDRY_IDX,       B.BNDRY_VIA,      B.LAT,         "
			"        B.LON,          B.ARC_CENTER_LAT,  B.ARC_CENTER_LON, B.ARC_BEARING, "
			"        B.ARC_DIST,     A.MULTI_CD                                          "
			"   FROM TB_RA A, TB_RABNDRY B                                               "
			"  WHERE A.RA_ID = B.RA_ID                                                   "
			"    AND A.RA_TP = B.RA_TP                                                   "
			"    AND A.ICAO_CD = B.ICAO_CD                                               "
			"    AND A.MULTI_CD = B.MULTI_CD                                             "
			"    AND A.ICAO_CD = 'RK'                                                    "
			"    AND A.RA_TP   = 'A'                                                     "
			"  ORDER BY A.RA_ID, B.BNDRY_IDX                                             "
			);
	layer = findLayer(Layer_Aa);
	if (layer)
		layer->query(query, sql);

	// MOA
	sql = QString(
			" SELECT                                                                     "
			"        A.MOA_ID,       B.BNDRY_IDX,       B.BNDRY_VIA,                     "
			"        B.LAT,          B.LON,             B.ARC_CENTER_LAT,             B.ARC_CENTER_LON,        "
			"        B.ARC_BEARING,  B.ARC_DIST,        ''                               "
			"   FROM TB_MOA A, TB_MOABNDRY B                                             "
			"  WHERE A.MOA_ID = B.MOA_ID                                                 "
			"  ORDER BY A.MOA_ID, B.BNDRY_IDX                                            "
			);
	layer = findLayer(Layer_Moa);
	if (layer)
		layer->query(query, sql);

	// Ad_Civil
	sql = QString(
			" SELECT                                                                     "
			"        AD_ID,         1,         'S',      LAT,            LON,            "
			"        LAT,           LON,        0.0,      0.0,           ''              "
			"   FROM TB_AD                                                               "
			"  WHERE ICAO_CD = 'RK'                                                      "
			"    AND PUB_YN  = 'C'                                                       "
			);
	layer = findLayer(Layer_Ad_Civil);
	if (layer)
		layer->query(query, sql);

	// Ad_Mil
	sql = QString(
			" SELECT                                                                     "
			"        AD_ID,         1,         'S',      LAT,            LON,            "
			"        LAT,           LON,        0.0,     0.0,            ''              "
			"   FROM TB_AD                                                               "
			"  WHERE ICAO_CD = 'RK'                                                      "
			"    AND PUB_YN  = 'M'                                                       "
			);
	layer = findLayer(Layer_Ad_Mil);
	if (layer)
		layer->query(query, sql);

	// Ad_Joint
	sql = QString(
			" SELECT                                                                     "
			"        AD_ID,         1,         'S',      LAT,            LON,            "
			"        LAT,           LON,        0.0,     0.0,    			 ''        "
			"   FROM TB_AD                                                               "
			"  WHERE ICAO_CD = 'RK'                                                      "
			"    AND PUB_YN  = 'J'                                                       "
			);
	layer = findLayer(Layer_Ad_Joint);
	if (layer)
		layer->query(query, sql);

	// Runway
	sql = QString(
			" SELECT                                                                     "
			"        A.AD_ID,                                                            "
			"        A.HEAD1 || A.HEAD2 || DECODE(A.HEAD3, 'X', '', 'Y', '', A.HEAD3) || "
			"        B.HEAD2 || DECODE(B.HEAD3, 'X', '', 'Y', '', B.HEAD3) AS RWAY_NO,   "
			"        A.LEN,    A.WIDTH,    A.BEARING AS ABEARING, B.BEARING AS BBEARING, "
			"        A.LAT AS ALAT,  A.LON AS ALON,  B.LAT AS BLAT,  B.LON AS BLON       "
			"   FROM (                                                                   "
			"          SELECT                                                            "
			"                 AD_ID,  RWAY_NO,   SUBSTR(RWAY_NO, 1, 2) AS HEAD1,         "
			"                 SUBSTR(RWAY_NO, 3, 2) AS HEAD2,                            "
			"                 DECODE(LENGTH(RWAY_NO),5,SUBSTR(RWAY_NO,5,1),'Y') AS HEAD3,"
			"                 LEN, WIDTH, BEARING, TO_NUMBER(BEARING) AS BEARING1,       "
			"                 MOD(TO_NUMBER(BEARING)+1800, 3600) AS BEARING2,            "
			"                 LAT, LON                                                   "
			"            FROM TB_RWAY                                                    "
			"           WHERE ICAO_CD = 'RK' AND SUBSTR(RWAY_NO, 3, 2) <= '18'           "
			"         ) A,  (                                                            "
			"          SELECT                                                            "
			"                 AD_ID,  RWAY_NO,   SUBSTR(RWAY_NO, 1, 2) AS HEAD1,         "
			"                 SUBSTR(RWAY_NO, 3, 2) AS HEAD2,                            "
			"                 DECODE(LENGTH(RWAY_NO),5,SUBSTR(RWAY_NO,5,1),'X') AS HEAD3,"
			"                 LEN, WIDTH, BEARING, TO_NUMBER(BEARING) AS BEARING1,       "
			"                 MOD(TO_NUMBER(BEARING)+1800, 3600) AS BEARING2,            "
			"                 LAT, LON                                                   "
			"            FROM TB_RWAY                                                    "
			"           WHERE ICAO_CD = 'RK' AND SUBSTR(RWAY_NO, 3, 2) > '18'            "
			"         ) B                                                                "
			"  WHERE A.AD_ID = B.AD_ID                                                   "
			"    AND A.LEN   = B.LEN                                                     "
			"    AND A.WIDTH = B.WIDTH                                                   "
			"    AND A.BEARING1 = B.BEARING2                                             "
			"    AND A.HEAD3 <> B.HEAD3                                                  "
			);
	layer = findLayer(Layer_Runway);
	if (layer)
		layer->query(query, sql);

	// Rep_Fix
	sql = QString(
			" SELECT                                                                     "
			"        A.RT_CONF_FIX_ID,    1,   'S',    A.LAT, A.LON, A.LAT, A.LON,       "
			"        0.0,    0.0,    ''                                                  "
			"   FROM (                                                                   "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,  ICAO_CD,  LAT,    LON                     "
			"            FROM TB_WAYPOINT                                                "
			"           WHERE ICAO_CD = 'RK'                                             "
			"              OR RT_CONF_FIX_ID IN (                                        "
			"                   SELECT                                                   "
			"                          RT_CONF_FIX_ID                                    "
			"                     FROM TB_RTCONFFIX                                      "
			"                    WHERE ICAO_CD <> 'RK' AND MAP_DISP = 'Y'                "
			"              )                                                             "
			"  ) A, TB_RTCONFFIX B                                                       "
			"  WHERE A.RT_CONF_FIX_ID = B.RT_CONF_FIX_ID                                 "
			"    AND B.WP_DESCR_CD3   = 'C'                                              "
			"  GROUP BY A.RT_CONF_FIX_ID, A.ICAO_CD, A.LAT, A.LON                        "
			"  ORDER BY A.RT_CONF_FIX_ID                                                 "
			);
	layer = findLayer(Layer_Rep_Fix);
	if (layer)
		layer->query(query, sql);

	// Fix
	sql = QString(
			" SELECT                                                                     "
			"        A.RT_CONF_FIX_ID,   1,  'S',   A.LAT, A.LON, A.LAT, A.LON,          "
			"        0.0,    0.0,     ''                                                 "
			"   FROM (                                                                   "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,  ICAO_CD,   LAT,   LON                     "
			"            FROM TB_WAYPOINT                                                "
			"           WHERE                                                            "
			"                 ICAO_CD = 'RK'                                             "
			"              OR RT_CONF_FIX_ID IN (                                        "
			"                      SELECT                                                "
			"                             RT_CONF_FIX_ID                                 "
			"                        FROM TB_RTCONFFIX WHERE ICAO_CD <> 'RK' AND MAP_DISP='Y' "
			"                 )                                                          "
			"  ) A                                                                       "
			" WHERE A.RT_CONF_FIX_ID NOT IN (                                            "
			"          SELECT A.RT_CONF_FIX_ID                                           "
			"            FROM (                                                          "
			"                   SELECT RT_CONF_FIX_ID, ICAO_CD, LAT, LON                 "
			"                     FROM TB_WAYPOINT                                       "
			"                    WHERE ICAO_CD = 'RK'                                    "
			"                       OR RT_CONF_FIX_ID IN (                               "
			"                              SELECT RT_CONF_FIX_ID                         "
			"                                FROM TB_RTCONFFIX                           "
			"                               WHERE ICAO_CD <> 'RK'                        "
			"                                 AND MAP_DISP = 'Y'                         "
			"                          )                                                 "
			"            ) A, TB_RTCONFFIX B                                             "
			"           WHERE A.RT_CONF_FIX_ID = B.RT_CONF_FIX_ID                        "
			"             AND B.WP_DESCR_CD3 = 'C'                                       "
			"           GROUP BY A.RT_CONF_FIX_ID, A.ICAO_CD, A.LAT, A.LON               "
			"          )                                                                 "
			" GROUP BY A.RT_CONF_FIX_ID, A.ICAO_CD, A.LAT, A.LON                         "
			" ORDER BY A.RT_CONF_FIX_ID                                                  "
			);
	layer = findLayer(Layer_Fix);
	if (layer)
		layer->query(query, sql);

	// T_Fix
	sql = QString(
			" SELECT *                                                                   "
			"   FROM (                                                                   "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,   1,  'S',   LAT,   LON,   LAT AS LAT1,    "
			"                 LON AS LON1,     0.0 as P1,   0.0 AS P2,   '' AS MULTI_CD  "
			"            FROM TB_TWAYPOINT                                               "
			"           WHERE ICAO_CD = 'RK'                                             "
			"          UNION                                                             "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,   1,  'S',   LAT,   LON,   LAT AS LAT1,    "
			"                 LON AS LON1,     0.0 AS P1,   0.0 AS P2,   '' AS MULTI_CD  "
			"            FROM TB_TNDB                                                    "
			"           WHERE ICAO_CD = 'RK'                                             "
			"   ) A                                                                      "
			" ORDER BY RT_CONF_FIX_ID                                                    "
			);
	layer = findLayer(Layer_T_Fix);
	if (layer)
		layer->query(query, sql);

	// Vortac
	sql = QString(
			" SELECT                                                                     "
			"        RT_CONF_FIX_ID,   1,   'S',   LAT,   LON,   LAT,  LON,              "
			"        0.0,   0.0,    ''                                                   "
			"   FROM TB_VHF                                                              "
			"  WHERE ICAO_CD = 'RK'                                                      "
			"    AND AD_ID IS NULL                                                       "
			"    AND LAT IS NOT NULL                                                     "
			"    AND LON IS NOT NULL                                                     "
			"    AND CLS_TP1 = 'V'                                                       "
			"    AND CLS_TP2 = 'T'                                                       "
			" ORDER BY RT_CONF_FIX_ID                                                    "
			);
	layer = findLayer(Layer_Vortac);
	if (layer)
		layer->query(query, sql);

	// Vordme
	sql = QString(
			" SELECT                                                                     "
			"        RT_CONF_FIX_ID,   1,   'S',   LAT,   LON,   LAT,  LON,              "
			"        0.0,   0.0,    ''                                                   "
			"   FROM TB_VHF                                                              "
			"  WHERE ICAO_CD = 'RK'                                                      "
			"    AND AD_ID IS NULL                                                       "
			"    AND LAT IS NOT NULL                                                     "
			"    AND LON IS NOT NULL                                                     "
			"    AND CLS_TP1 = 'V'                                                       "
			"    AND CLS_TP2 = 'D'                                                       "
			" ORDER BY RT_CONF_FIX_ID                                                    "
			);
	layer = findLayer(Layer_Vordme);
	if (layer)
		layer->query(query, sql);

	// Ndb
	sql = QString(
			" SELECT                                                                     "
			"        RT_CONF_FIX_ID,   1,   'S',   LAT,   LON,   LAT,  LON,              "
			"        0.0,   0.0,    ''                                                                             "
			"   FROM (                                                                   "
			"       SELECT RT_CONF_FIX_ID, LAT, LON FROM TB_NDB WHERE ICAO_CD='RK'       "
			"        UNION                                                               "
			"       SELECT RT_CONF_FIX_ID, LAT, LON FROM TB_TNDB WHERE ICAO_CD='RK'      "
			"    )                                                                                                 "
			" ORDER BY RT_CONF_FIX_ID                                                    "
			);
	layer = findLayer(Layer_Ndb);
	if (layer)
		layer->query(query, sql);

	// Route
	sql = QString(
			" SELECT                                                                     "
			"        A.RT_ID,    1,    'G',     B.LAT,   B.LON,    B.LAT,   B.LON,       "
			"        0.0,   0.0,    ''                                                   "
			"   FROM (                                                                   "
			"          SELECT                                                            "
			"                 RT_ID,   ICAO_CD,   RT_CONF_FIX_ID,  FIX_IDX               "
			"            FROM TB_RTCONFFIX                                               "
			"           WHERE ICAO_CD = 'RK'                                             "
			"              OR (ICAO_CD <> 'RK' AND MAP_DISP = 'Y')                       "
			"        ) A,                                                                "
			"        (                                                                   "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,   LAT,   LON,   ICAO_CD                    "
			"            FROM TB_WAYPOINT                                                "
			"           WHERE LAT IS NOT NULL AND LON IS NOT NULL                        "
			"          UNION                                                             "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,   LAT,   LON,   ICAO_CD                    "
			"            FROM TB_VHF                                                     "
			"           WHERE LAT IS NOT NULL AND LON IS NOT NULL                        "
			"          UNION                                                             "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,   LAT,   LON,   ICAO_CD                    "
			"            FROM TB_NDB                                                     "
			"           WHERE LAT IS NOT NULL AND LON IS NOT NULL                        "
			"         ) B                                                                "
			" WHERE A.RT_CONF_FIX_ID = B.RT_CONF_FIX_ID                                  "
			"   AND A.ICAO_CD = B.ICAO_CD                                                "
			" ORDER BY A.RT_ID, A.FIX_IDX                                                "
			);
	layer = findLayer(Layer_Route);
	if (layer)
		layer->query(query, sql);

	// Hold
	sql = QString(
			" SELECT                                                                     "
			"        A.RT_CONF_FIX_ID,     A.DUP_ID,    A.INB_HLD_CRS/10 AS INB_HLD_CRS, "
			"        A.DIRECTION,   DECODE(A.LEG_LEN, NULL, A.LEG_TM*5, A.LEG_LEN) AS LEN, "
			"        B.LAT,    B.LON                                                     "
			"   FROM TB_HLDPATTERN A,                                                    "
			"        (                                                                   "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,  LAT,  LON                                 "
			"            FROM TB_NDB                                                     "
			"           WHERE ICAO_CD = 'RK'                                             "
			"          UNION                                                             "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,  LAT,  LON                                 "
			"            FROM TB_WAYPOINT                                                "
			"           WHERE ICAO_CD = 'RK'                                             "
			"        ) B                                                                 "
			" WHERE A.ICAO_CD = 'RK'                                                     "
			"   AND A.RT_CONF_FIX_ID = B.RT_CONF_FIX_ID                                  "
			" UNION                                                                      "
			" SELECT                                                                     "
			"        A.RT_CONF_FIX_ID,    A.DUP_ID,  A.INB_HLD_CRS/10 AS INB_HLD_CRS,    "
			"        a.DIRECTION,  DECODE(A.LEG_LEN, NULL, A.LEG_TM*5, A.LEG_LEN) AS LEN, "
			"        B.LAT,       B.LON                                                  "
			"   FROM TB_HLDPATTERN A,                                                    "
			"        (                                                                   "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,  LAT,  LON,  AD_ID                         "
			"            FROM TB_VHF                                                     "
			"           WHERE ICAO_CD = 'RK'                                             "
			"           UNION                                                            "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,  LAT,  LON,  AD_ID                         "
			"            FROM TB_TNDB                                                    "
			"           WHERE ICAO_CD = 'RK'                                             "
			"           UNION                                                            "
			"          SELECT                                                            "
			"                 RT_CONF_FIX_ID,  LAT,  LON,  AD_ID                         "
			"            FROM TB_TWAYPOINT                                               "
			"           WHERE ICAO_CD = 'RK'                                             "
			"        ) B                                                                 "
			" WHERE A.ICAO_CD = 'RK'                                                     "
			"   AND A.RT_CONF_FIX_ID = B.RT_CONF_FIX_ID                                  "
			"   AND A.AD_ID = B.AD_ID                                                    "

			);
	layer = findLayer(Layer_Hold);
	if (layer)
		layer->query(query, sql);

    //Sensor
    sql = QString( "select sensor_id,1,'S',lat,lon,lat,lon,0.0,0.0,''  "
                         "from tb_sensor  "
                         "order by sensor_id ");
    layer = findLayer(Layer_Sensor);
    if(layer)layer->query(query,sql);

    //Cata
    sql = QString(
            "select "
            "        'CATA ' || cata_id, bndry_idx,bndry_via, lat, lon, arc_center_lat, arc_center_lon,arc_bearing,arc_dist,'' "
            "from tb_catabndry "
            "order by cata_id, bndry_idx " );
    layer = findLayer(Layer_Cata);
    if(layer)layer->query(query,sql);

	// Sector
	sql = QString(
			" SELECT                                                                     "
			"        A.SECTOR_ID,    B.BNDRY_IDX,    B.BNDRY_VIA,   B.LAT,   B.LON,      "
			"        B.ARC_CENTER_LAT,   B.ARC_CENTER_LON,  B.ARC_BEARING, B.ARC_DIST, ''       "
			"   FROM TB_SECTOR A, TB_SECTORBNDRY B                                       "
			"  WHERE A.SECTOR_ID = B.SECTOR_ID                                           "
			"  ORDER BY A.SECTOR_ID, B.BNDRY_IDX                                         "
			);
	layer = findLayer(Layer_Sector);
	if (layer)
		layer->query(query, sql);

    //Msaw
    sql = QString(
            "select "
            "         safety_nm, idx, bndry_via, lat, lon, AZ0, AZ1, RMIN, RMAX, multi_cd "
            "from ( select "
            "                safety_nm, idx,'G' as bndry_via, lat, lon, 0 as AZ0, 0 as AZ1, 0.0 as RMIN,0.0 as RMAX,'P' as multi_cd "
            "         from tb_safetypolygon "
            "         where cat = 'M' "
            "         union all "
            "         select "
            "                safety_nm, 1 as idx,'G' as bndry_via, center_lat as lat, center_lon as lon, AZ0, AZ1,RMIN,RMAX,'S' as multi_cd "
            "         from tb_safetysector "
            "         where cat = 'M' ) "
            "order by safety_nm, idx " );
    layer = findLayer(Layer_Msaw);
    if(layer)layer->query(query,sql);

	// Tca
	sql = QString(
			" SELECT                                                                     "
			"        A.TMA_ID,   B.BNDRY_IDX,    B.BNDRY_VIA,    B.LAT,   B.LON,         "
			"        B.ARC_CENTER_LAT,  B.ARC_CENTER_LON,   B.ARC_BEARING,  B.ARC_DIST, ''   "
			"   FROM TB_TCA A, TB_TCABNDRY B                                             "
			"  WHERE A.TMA_ID = B.TMA_ID                                                 "
			"  ORDER BY A.TMA_ID, B.BNDRY_IDX                                            "
			);
	layer = findLayer(Layer_Tca);
	if (layer)
		layer->query(query, sql);

	// Kadiz
	sql = QString(
			" SELECT                                                                     "
			"        A.KADIZ_ID,    B.BNDRY_IDX,   'G',   B.LAT,   B.LON,                "
			"        B.LAT,   B.LON,  0.0, 0.0 , ''                                      "
			"   FROM TB_KADIZ A, TB_KADIZBNDRY B                                         "
			"  WHERE A.KADIZ_ID = B.KADIZ_ID                                             "
			"  ORDER BY A.KADIZ_ID, B.BNDRY_IDX                                          "
			);
	layer = findLayer(Layer_Kadiz);
	if (layer)
		layer->query(query, sql);

    //-- Sid
    sql = QString(" SELECT "
                       " 	      TRIM(A.AD_ID) || '_' || TRIM(A.SID_ID) || DECODE(A.SUBTRANS_ID, 'AAAAA', '(' || TRIM(A.TRANS_ID) || ')' ,'(' || TRIM(A.TRANS_ID) || ')' || '_' || A.SUBTRANS_ID ) AS ID "
                       "         ,B.idx,B.bndry_via,B.lat,B.lon,B.arc_center_lat,B.arc_center_lon,B.arc_bearing,B.arc_dist,'' "
                       " FROM TB_SID A "
					   "     ,TB_ARTSAD Z "
                       "         ,TB_SIDSTARMAP B "
                       " WHERE A.RT_TP IN ('2' , '5' , 'M' ) "
					   " AND   A.AD_ID = Z.AD_ID "
                       " AND     A.SIDSTAR_KEY = B.SIDSTAR_KEY "
                       " AND     B.SIDSTARAPCH = 'S' "
                       " UNION ALL "
                       " SELECT "
                       " 	      TRIM(A.AD_ID) || '_' || TRIM(A.SID_ID) || DECODE(A.SUBTRANS_ID, 'AAAAA', '(' || TRIM(A.TRANS_ID) || ')' ,'(' || TRIM(A.TRANS_ID) || ')' || '_' || A.SUBTRANS_ID ) AS ID "
                       "        , C.FIX_IDX,'G', D.lat, D.lon, D.lat, D.lon "
                       "        , DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', C.THETA, 0.0), DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', C.RHO, 0.0), DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', 'D', '') "
                       " FROM TB_SID A "
					   "     ,TB_ARTSAD Z "
                       "         ,TB_SIDCONFFIX C "
                       "         ,V_FIX D "
                       " WHERE A.RT_TP IN ('2' , '5' , 'M' ) "
					   " AND   A.AD_ID = Z.AD_ID "
                       " AND NOT EXISTS (SELECT *  FROM TB_SID X, TB_ARTSAD Z, TB_SIDSTARMAP Y "
                       "                         WHERE X.SIDSTAR_KEY = A.SIDSTAR_KEY AND X.RT_TP IN ('2' , '5' , 'M' ) "
					   "                         AND   X.AD_ID = Z.AD_ID "
                       "                         AND   X.SIDSTAR_KEY = Y.SIDSTAR_KEY "
                       "                         AND   Y.SIDSTARAPCH = 'S' ) "
                       " AND   A.SIDSTAR_KEY = C.SIDSTAR_KEY "
                       " AND   SUBSTR(C.PATH_TERM,2,1) IN ('F', 'D') "
                       " AND   DECODE (SUBSTR(C.PATH_TERM,2,1), 'F', C.RT_CONF_FIX_ID, C.RECM_NAVAID) = D.FIX_ID "
					   " AND   C.ICAO_CD = D.ICAO_CD "
                       " ORDER BY 1, 2 ");
    layer = findLayer(Layer_Sid);
    if(layer)layer->query(query,sql);

    //-- Star
    sql = QString(" SELECT "
                            " 	  TRIM(A.AD_ID) || '_' || TRIM(A.STAR_ID) || '(' || TRIM(A.TRANS_ID) || ')' AS ID "
                            " 	 ,B.idx,B.bndry_via,B.lat,B.lon,B.arc_center_lat,B.arc_center_lon,B.arc_bearing,B.arc_dist,'' "
                            " FROM  TB_STAR A "
							"      ,TB_ARTSAD Z "
                            " 	   ,TB_SIDSTARMAP B "
                            " WHERE A.AD_ID = Z.AD_ID AND A.SIDSTAR_KEY = B.SIDSTAR_KEY "
                            " AND     B.SIDSTARAPCH = 'T' "
                            " UNION ALL "
                            " SELECT "
                            "           TRIM(A.AD_ID) || '_' || TRIM(A.STAR_ID) || '(' || TRIM(A.TRANS_ID) || ')' AS ID "
                            " 	   , C.FIX_IDX,'G', D.lat, D.lon, D.lat, D.lon "
                            " 	   , DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', C.THETA, 0.0), DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', C.RHO, 0.0), DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', 'D', '') "
                            " FROM TB_STAR A "
							"     ,TB_ARTSAD Z "
                            " 	  ,TB_STARCONFFIX C "
                            "        ,V_FIX D "
                            " WHERE A.AD_ID = Z.AD_ID "
							" AND   NOT EXISTS (SELECT *  FROM TB_STAR X, TB_ARTSAD Z, TB_SIDSTARMAP Y "
                            " 			       WHERE X.AD_ID = Z.AD_ID AND X.SIDSTAR_KEY = A.SIDSTAR_KEY "
                            " 			       AND     X.SIDSTAR_KEY = Y.SIDSTAR_KEY "
                            " 	   		       AND     Y.SIDSTARAPCH = 'T' ) "
                            " AND   A.SIDSTAR_KEY = C.SIDSTAR_KEY "
                            " AND   SUBSTR(C.PATH_TERM,2,1) IN ('F', 'D') "
                            " AND   DECODE (SUBSTR(C.PATH_TERM,2,1), 'F', C.RT_CONF_FIX_ID, C.RECM_NAVAID) = D.FIX_ID "
							" AND   C.ICAO_CD = D.ICAO_CD "
                            " ORDER BY 1, 2 ");
    layer = findLayer(Layer_Star);
    if(layer)layer->query(query,sql);

    //-- Apch
    sql = QString(" SELECT "
                    " 	  TRIM(A.AD_ID) || '_' || TRIM(A.APCH_ID) || '(' || TRIM(A.TRANS_ID) || ')' AS ID "
                    " 	 ,B.idx,B.bndry_via,B.lat,B.lon,B.arc_center_lat,B.arc_center_lon,B.arc_bearing,B.arc_dist,'' "
                    " FROM  TB_APCH A "
					"      ,TB_ARTSAD Z "
                    " 	   ,TB_SIDSTARMAP B "
                    " WHERE A.AD_ID = Z.AD_ID AND A.SIDSTAR_KEY = B.SIDSTAR_KEY "
                    " AND     B.SIDSTARAPCH = 'A' "
                    " UNION ALL "
                    " SELECT "
                    " 	     TRIM(A.AD_ID) || '_' || TRIM(A.APCH_ID) || '(' || TRIM(A.TRANS_ID) || ')' AS ID "
                    " 	   , C.FIX_IDX,'G', D.lat, D.lon, D.lat, D.lon "
                    " 	   , DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', C.THETA, 0.0), DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', C.RHO, 0.0), DECODE(SUBSTR(C.PATH_TERM,2,1), 'D', 'D', '') "
                    " FROM TB_APCH A "
					"      ,TB_ARTSAD Z "
                    " 	  ,TB_APCHCONFFIX C "
                    "    	  ,V_FIX D "
                    " WHERE A.AD_ID = Z.AD_ID "
					" AND   NOT EXISTS (SELECT *  FROM TB_APCH X, TB_ARTSAD Z, TB_SIDSTARMAP Y "
                    " 	   	               WHERE X.AD_ID = Z.AD_ID AND X.SIDSTAR_KEY = A.SIDSTAR_KEY "
                    " 			       AND     X.SIDSTAR_KEY = Y.SIDSTAR_KEY "
                    " 			       AND     Y.SIDSTARAPCH = 'A' ) "
                    " AND   A.SIDSTAR_KEY = C.SIDSTAR_KEY "
                    " AND   SUBSTR(C.PATH_TERM,2,1) IN ('F', 'D') "
                    " AND   DECODE (SUBSTR(C.PATH_TERM,2,1), 'F', C.RT_CONF_FIX_ID, C.RECM_NAVAID) = D.FIX_ID "
					" AND   C.ICAO_CD = D.ICAO_CD "
                    " ORDER BY 1, 2 ");
        layer = findLayer(Layer_Apch);
        if(layer)layer->query(query,sql);

    //Airspace
    sql = QString(" SELECT "
                    "          A.AD_ID || '_' || A.RNG AS ID, A.bndry_idx,A.bndry_via, A.lat, A.lon, A.arc_center_lat, A.arc_center_lon, A.arc_bearing, A.arc_dist, '' "
                    " FROM TB_CLSBNDRY A "
                    " WHERE NOT EXISTS (SELECT B.AREA_ID FROM TB_CLSMAPBNDRY B "
                    "                             WHERE  B.AREA_ID LIKE '%' || A.AD_ID || '%' ) "
                    " UNION ALL "
                    " SELECT "
                    "          A.AREA_ID || '_' || A.RNG AS ID, A.bndry_idx,A.bndry_via, A.lat, A.lon, A.arc_center_lat, A.arc_center_lon, A.arc_bearing, A.arc_dist, '' "
                    " FROM TB_CLSMAPBNDRY A "
                    " WHERE EXISTS (SELECT B.AD_ID FROM TB_CLSBNDRY B "
                    "                       WHERE  A.AREA_ID LIKE '%' || B.AD_ID || '%' ) "
                    " ORDER BY 1, 2 ");
    layer = findLayer(Layer_Airspace);
    if(layer)layer->query(query,sql);

    //Vfr_Rp
    sql = QString( " SELECT TRIM(AD_ID) || ' ' || TRIM(RP_CD) ,1,'S',lat,lon,lat,lon,0.0,0.0,''  "
                       " FROM TB_ADVFRRP  "
                       " ORDER BY 1 " );
    layer = findLayer(Layer_Vfr_Rp);
    if(layer)layer->query(query,sql);

    //Obstacles
    sql = QString( " SELECT TRIM(AD_ID) || ' ' || TRIM(OBS_NM) ,1,'S',lat,lon,lat,lon,0.0,0.0,''  "
                       " FROM TB_ADOBS  "
                       " ORDER BY 1 " );
    layer = findLayer(Layer_Obstacles);
    if(layer)layer->query(query,sql);

    //Vfr_Cp
    sql = QString( " SELECT VFR_RT_CD || ' ' || CP_IDX ,1,'S',lat,lon,lat,lon,0.0,0.0,''  "
                       " FROM TB_VFRRTCP  "
                       " ORDER BY VFR_RT_CD || ' ' || CP_IDX " );
    layer = findLayer(Layer_Vfr_Cp);
    if(layer)layer->query(query,sql);

    //Vfr_Route
    sql = QString( " SELECT VFR_RT_CD, CP_IDX,'G', lat, lon,lat,lon,0.0,0.0,''  "
                       " FROM TB_VFRRTCP  "
                       " ORDER BY VFR_RT_CD, CP_IDX " );
    layer = findLayer(Layer_Vfr_Route);
    if(layer)layer->query(query,sql);

    //Mva
    sql = QString(" SELECT "
                    "      A.AD_ID || '_' || B.MVA_ID AS ID, 1 as idx, 'G' as bndry_via, A.center_lat as lat, A.center_lon as lon, B.AZ0, B.AZ1, B.RMIN, B.RMAX,'S' as multi_cd "
                    " FROM TB_MVA A "
                    "     ,TB_MVASECTOR B "
                    " WHERE A.AD_ID = B.AD_ID ");
    layer = findLayer(Layer_Mva);
    if(layer)layer->query(query,sql);

	// User Layer
	userlayerList->query(query);

	// User defined map List
	udmList->query(query);

	delete query;
}

/**
 * 가지고 있는 데이터를 파일에 출력해서 저장한다.
 */
void AMap::print(QTextStream& out)
{
	ALayer* layer;

	// magic string
	out << magicString() << "\n";

	// range->center
	out << mapconf.center() << "\n";
	out << mapconf.bg_colorString() << "\n";
	out << mapconf.range() << "\n";

	// layer의 내용을 출력한다.
	for (int i=0; i<layerList.count(); i++) {
		layer = layerList[i];
		layer->print(out, mapconf);
	}

	// User Layer의 내용을 출력한다.
	userlayerList->print(out);
	udmList->print(out);
}

void AMap::write(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		log.print(QString("file %1 open error").arg(fileName));
		return;
	}

	QTextStream out(&file);
	print(out);
	file.close();
}

void AMap::read(const QString& fileName)
{
	qDebug() << "called....?";
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		log.print(QString("file %1 open error").arg(fileName));
		return;
	}

	int lineNo = 0;
	QTextStream in(&file);
	while(!in.atEnd()){
		QString line = in.readLine();
		QStringList list = line.split(":");

		if (line.length() < 1) continue;
		lineNo++;

		if (lineNo == 1) {
			if (line.left(8) != "ATAP-MAP") {	// Magic string check
				log.print(QString("This file is nont ATAP-MAP"));
				break;
			}else {
				log.print(QString("Start read a mapfile which is created at %1").arg(line.right(12)));
			}
		}else if(lineNo == 2) {
			msb.latlon1.lat = LLU::lat(line.mid(0,9));
			msb.latlon1.lon = LLU::lon(line.mid(9,10));
			msb.latlon2.lat = LLU::lat(line.mid(0,9));
			msb.latlon2.lon = LLU::lon(line.mid(9,10));
			mapconf.setCenter(line);
			log.print(QString("msb:(%1,%2),(%3,%4)").arg(msb.latlon1.lat).arg(msb.latlon1.lon)
					.arg(msb.latlon2.lat).arg(msb.latlon2.lon));
		}else if(lineNo == 3) {
			qDebug() << line;
			mapconf.setBg_Color(line);
		}else if(lineNo == 4) {
			mapconf.setRange(line);
		}else if(list.count() >= 2 && list[0] == "LAYER") {
			QString layername = list[1].trimmed().toUpper();
			if (list[0] == "LAYER" && layername != "USERMAP") {	// default layer
				log.print(QString("find layer : %1").arg(layername));
				ALayer* layer = findLayer(layername);
				if (layer != NULL) {
					layer->setLayerproperty(list);
					mapconf.addLayerAttr(layername, layer->layerAttr());
					layer->read(in, lineNo);
				}else {
					log.print(QString("%1 is not found in layer list").arg(layername));
				}
			}else if(list[0] == "LAYER" && layername == "USERMAP") {
				// User Layer define
				userlayerList->read(in, lineNo);
			}
		}else if(list.count() >= 2 && (list[0] == "USER_LAYER")) {
			udmList->read(in, lineNo, list[1]);		// 맵파일에 있는 문자열로만 사용자정의맵을 구성
		}
	}

	file.close();

	CopyMapToUserDefinedMap();
}

/**
 * Map Layer 기본구성을 설정한다.
 * Map file 오픈시 이 메소드를 반드시 호출되어야 한다.
 */
void AMap::initMap(Log424& log)
{

	layerList.clear();

	layerList.append(new ALinesLayerItem(Layer_Coast));		// Coast Layer
	layerList.append(new ALinesLayerItem(Layer_Fir));		// Fir Layer
	layerList.append(new AreaLayerItem(Layer_Kadiz));       // Kadiz Layer
	layerList.append(new AreaLayerItem(Layer_Sector));      // Sector Layer
	layerList.append(new AreaLayerItem(Layer_Tca));         // TCA Layer
	layerList.append(new AreaLayerItem(Layer_Ra));          // RA Layer
	layerList.append(new AreaLayerItem(Layer_Da));          // DA Layer
	layerList.append(new AreaLayerItem(Layer_Pa));          // PA Layer
	layerList.append(new AreaLayerItem(Layer_Aa));          // AA Layer
	layerList.append(new AreaLayerItem(Layer_Moa));         // MOA Layer
	layerList.append(new ASymbolLayerItem(Layer_Ad_Civil)); // Ad Civil Layer
	layerList.append(new ASymbolLayerItem(Layer_Ad_Mil));   // Ad Mil Layer
	layerList.append(new ASymbolLayerItem(Layer_Ad_Joint)); // Ad Joint Layer
	layerList.append(new ALinesLayerItem(Layer_Runway));    // Runway Layer
	layerList.append(new ASymbolLayerItem(Layer_Rep_Fix));  // Rep Fix Layer
	layerList.append(new ASymbolLayerItem(Layer_Fix));      // Fix Layer
	layerList.append(new ASymbolLayerItem(Layer_T_Fix));    // Terminal Fix Layer
	layerList.append(new ASymbolLayerItem(Layer_Vortac));   // Vortac Layer
	layerList.append(new ASymbolLayerItem(Layer_Vordme));   // Vordme Layer
	layerList.append(new ASymbolLayerItem(Layer_Ndb));      // NDB Layer
	layerList.append(new ALinesLayerItem(Layer_Route));     // Route Layer

	/// add layer
	layerList.append(new ALinesLayerItem(Layer_Sid));			// SID Layer
	layerList.append(new ALinesLayerItem(Layer_Star));			// STAR Layer
	layerList.append(new ALinesLayerItem(Layer_Apch));			// APCH Layer
	layerList.append(new AreaLayerItem(Layer_Airspace));		// Airspace Layer

	layerList.append(new AHoldLayerItem(Layer_Hold));           // Hold Layer
	layerList.append(new ASymbolLayerItem(Layer_Sensor));       // Sensor Layer
	layerList.append(new AreaLayerItem(Layer_Cata));           // Cata Layer
	layerList.append(new AreaLayerItem(Layer_Msaw));           // MSAW Layer

	// add layer
	layerList.append(new ASymbolLayerItem(Layer_Vfr_Rp));			// VFR RP Layer
	layerList.append(new ASymbolLayerItem(Layer_Obstacles));		// Obstacles Layer
	layerList.append(new ASymbolLayerItem(Layer_Vfr_Cp));			// VFR CP Layer
	layerList.append(new ALinesLayerItem(Layer_Vfr_Route));		// VFR Route Layer
	layerList.append(new AreaLayerItem(Layer_Mva));					// MVA Layer


	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		layer->setLog(log);
		layer->setAirdraw(air);
	}
}
/**
 * 실제적으로 사용자 정의맵의 내용을 채운다.
 */
void AMap::CopyMapToUserDefinedMap()
{
	for (int i=0; i<udmList->count(); i++) {
		AUserDefinedMap* udm = udmList->getMap(i);
		if (udm != NULL) {
			for (int j=0; j<udm->LayerCount(); j++) {
				AUserDefinedLayer* udlayer = udm->layer(j);
				QString layername = udlayer->getId();
				ALayer* realLayer = findLayer(layername);
				if (realLayer != NULL) {
					if (udlayer->isAll) {
						//TODO: ALayer에서 clone 메소드 구현 필요
						//qDebug() << realLayer->toString();
						udlayer->assignRealLayer(realLayer->clone());
					}else {
						//TODO: ALayer에서 clone 메소드 구현 필요
						udlayer->assignRealLayer(realLayer->clone());
						udlayer->removeIds();
					}
				}
			}
		}
	}
}

/**
 * User Layer를 포함한 모든 레이어를 지운다.
 */
void AMap::clear()
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		layer->clear();
	}
	userlayerList->clear();
	udmList->clear();
}

void AMap::idList(int t, QStringList& list)
{
	if (t == Layer_User) {
		userlayerList->fillId(list);
	}else if(t == GroupLayer_Airport) {
		LayerType child[3] = { Layer_Ad_Civil, Layer_Ad_Mil, Layer_Ad_Joint };
		for (int j=0; j<3; j++) {
			ALayer* layer = findLayer(child[j]);
			if (layer != NULL) layer->fillId(list);
		}
	}else if(t == GroupLayer_Waypoint) {
		LayerType child[3] = { Layer_Rep_Fix, Layer_Fix, Layer_T_Fix };
		for (int j=0; j<3; j++) {
			ALayer* layer = findLayer(child[j]);
			if (layer != NULL) layer->fillId(list);
		}
	}else if(t == GroupLayer_Navaids) {
		LayerType child[3] = { Layer_Vortac, Layer_Vordme, Layer_Ndb };
		for (int j=0; j<3; j++) {
			ALayer* layer = findLayer(child[j]);
			if (layer != NULL) layer->fillId(list);
		}
	}else if(t < MaxLayerCount) {
		ALayer* layer = findLayer((LayerType) t);
		if (layer != NULL) layer->fillId(list);
	}
}

/**
 * 모든 레이어의 visible을 세팅한다.
 */
void AMap::setAllLayerVisible(bool b)
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		layer->setLayerVisible(b);
		layer->setAllIdVisible(b);
	}
	userlayerList->setLayerVisible(b);
	userlayerList->setAllIdVisible(b);
}

void AMap::setLayerVisible(int t, LayerVisible visible)
{
	ALayer* layer = findLayer((LayerType) t);
	if (layer != NULL) {
		if (visible == Unvisible) {		// 모두 unvisible이 아니면 layer는 visible
			layer->setLayerVisible(false);
		}
		layer->setLayerVisible(true);
		return;
	}
	if ((LayerType)t == Layer_User) {
		if (visible == Unvisible) {		// 모두 unvisible이 아니면 layer는 visible
			userlayerList->setLayerVisible(false);
		}
		userlayerList->setLayerVisible(true);
	}
}

void AMap::setAllIdVisible(int t, bool b)
{
	if(t == Layer_User){
		userlayerList->setAllIdVisible(b);
	}else if(t == GroupLayer_Airport){
		LayerType child[3] = {Layer_Ad_Civil,Layer_Ad_Mil,Layer_Ad_Joint};
		for(int j=0;j<3;j++){
			ALayer* layer = findLayer(child[j]);
			if(layer != NULL){
				layer->setAllIdVisible(b);
			}
		}
	}else if(t == GroupLayer_Waypoint){
		LayerType child[3] = {Layer_Rep_Fix,Layer_Fix,Layer_T_Fix};
		for(int j=0;j<3;j++){
			ALayer* layer = findLayer(child[j]);
			if(layer != NULL){
				layer->setAllIdVisible(b);
			}
		}
	}else if(t == GroupLayer_Navaids){
		LayerType child[3] = {Layer_Vortac,Layer_Vordme,Layer_Ndb};
		for(int j=0;j<3;j++){
			ALayer* layer = findLayer(child[j]);
			if(layer != NULL){
				layer->setAllIdVisible(b);
			}
		}
	}else if(t < MaxLayerCount ){
			ALayer* layer = findLayer((LayerType)t);
			if(layer != NULL) layer->setAllIdVisible(b);
	}
}

/**
 * layer의 특정 id만의 visible을 설정한다
 */
void AMap::setIdVisible(int t, const QString& id, bool b)
{
	if(t == Layer_User){
		userlayerList->setIdVisible(id,b);
	}else if(t == GroupLayer_Airport){
		bool found = false;
		ALayer* layer = findLayer(Layer_Ad_Civil);
		if(layer != NULL){
			found = layer->setIdVisible(id,b);
		}
		layer = findLayer(Layer_Ad_Mil);
		if(!found){
			found = layer->setIdVisible(id,b);
		}
		layer = findLayer(Layer_Ad_Joint);
		if(!found){
			found = layer->setIdVisible(id,b);
		}
	}else if(t == GroupLayer_Waypoint){
		bool found = false;
		ALayer* layer = findLayer(Layer_Rep_Fix);
		if(layer != NULL){
			found = layer->setIdVisible(id,b);
		}
		layer = findLayer(Layer_Fix);
		if(!found){
			found = layer->setIdVisible(id,b);
		}
		layer = findLayer(Layer_T_Fix);
		if(!found){
			found = layer->setIdVisible(id,b);
		}
	}else if(t == GroupLayer_Navaids){
		bool found = false;
		ALayer* layer = findLayer(Layer_Vortac);
		if(layer != NULL){
			found = layer->setIdVisible(id,b);
		}
		layer = findLayer(Layer_Vordme);
		if(!found){
			found = layer->setIdVisible(id,b);
		}
		layer = findLayer(Layer_Ndb);
		if(!found){
			found = layer->setIdVisible(id,b);
		}
	}else if(t < MaxLayerCount ){
		ALayer* layer = findLayer((LayerType)t);
		if(layer != NULL){
			layer->setIdVisible(id,b);
		}
	}
}

void AMap::changeUidName(const QString& oldid, const QString& newid)
{
	userlayerList->changeName(oldid, newid);
}

void AMap::setSymboldir(const QString& symboldir)
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		if (layer->classType() == ClassSymbol) {
			ASymbolLayerItem* symbollayer = (ASymbolLayerItem*)layer;
			symbollayer->setSymbolDir(symboldir);
		}
	}
	userlayerList->setSymbolDir(symboldir);
}

void AMap::setTextVisible(bool b)
{
	textvisible = b;

	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		if (layer->classType() == ClassArea) {
			layer->setTextVisible(b);
		}
	}
	// User Layer Text Visible
	userlayerList->setTextVisible(b);
}

/**
 * Default wonjum map파일에 기록된 것을 보낸다.
 * 이것은 mapconf에서 가지고 있다.
 */
QPointF AMap::defaultWonjum()
{
	QString latlon = mapconf.center();
	CalcAir ca;
	return ca.toDD(latlon);
}

void AMap::draw(QPainter* painter, AirDraw* ad)
{
	for (int i=0; i<layerList.count(); i++) {
		ALayer* layer = layerList[i];
		//TODO: Layer에서 AirDraw 객체를 사용할 방법이 필요한다.
		// layer->draw(painter, ad);
		layer->update();
	}
	// userlayer->draw(painter, ad);

	userlayerList->update();
	udmList->draw(painter, ad);
}
