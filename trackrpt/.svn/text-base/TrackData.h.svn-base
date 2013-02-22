/*
 * TrackData.h
 *
 *  Created on: 2012. 4. 30.
 *      Author: JMS
 *  Description : TB_TRK 데이터 모델 정의
 */

#ifndef TRACKDATA_H_
#define TRACKDATA_H_

#include <QString>

class TrackData {
public:
	TrackData();
	~TrackData();

	int     type;				// 0 = track data  1 = ADSB
	QString occur_dt;
	double  lat;
	double  lon;
	double  spd;				// Speed
	double  prev_spd;       // Previous Speed
	double  heading;			// Heading
	int     mlt_alt;			// Measured Flight Level
	int     alt;				// Altitude
	int     prev_alt;       // Previous Alt
	QString qnh;
	int     climb;				// Calculated Rate of Climb/Descent
	QString spi;
	QString mrh;
	QString cnf;
	QString sim;
	QString tse;
	QString fpc;
	QString cst;
	QString psr;
	QString ssr;
	QString mds;
	QString ads;
//	QString fl_type;			// GAT/OAT 비행형식
	QString flt_rule;			// FR1/FR2 비행규칙
	QString rvsm;				// RVSM
//	QString hpr;				// Priority Flight Type
	QString actp;		   	// Aircraft Type
	QString wt_type;			// Wake Turbulence Category
	QString dep_ad;			// Departure Airport
	QString arr_ad;			// Destination Airport
	QString rway_no;			// Runway Designation
	int     cfl;				// Current Cleared Flight Level (허가된 배정고도)
	QString center_id;		// Cetre identification
	QString pos;				// Control Position identification
	QString alert;

};

#endif /* TRACKDATA_H_ */
