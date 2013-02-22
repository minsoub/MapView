/*
 * Cat062.h
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 *  Reference :
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 */

#ifndef CAT062_H_
#define CAT062_H_

#include <QtCore>
#include <QString>

#include "../lib/CBuffer.h"
#include "../lib/AsterixLib.h"
#include "SystemTrack.h"
#include "Mode3A.h"
#include "TrackStatus.h"
#include "Mode5.h"
#include "SystemTrackUpdateAge.h"
#include "TrackDataAge.h"
#include "MeasuredInfo.h"
#include "AircraftDerivedData.h"
#include "TrajectoryIntentData.h"
#include "ModeSMBData.h"
#include "FlightPlanData.h"
#include "TimeOfDepArrData.h"
#include "EstimatedAccuracy.h"

class Cat062 : public AsterixLib {
public:
	Cat062();
	~Cat062();
	void GetPacket(CBuffer& rBuffer);
	void Clear();
	void BufferPrint(CBuffer& rBuffer, int s, int end, QString item);
	int fileMode;

	QString getSSRCode();
	int     getTrackNum();
	QString getCallsign();
	QString getAccurDt();
	double  getLatitude();
	double  getLongitude();
	double  getSpeed();
	double  getHeading();
	int     getMltAltitude();
	int     getAltitude();
	S8      getQNH();
	int     getClimbDescent();
	S8      getSPI();
	S8      getMRH();
	S8      getCNF();
	S8      getSIM();
	S8      getTSE();
	S8      getFPC();
	S8      getCST();
	S8      getPSR();
	S8      getSSR();
	S8      getMDS();
	S8      getADS();

	S8      getFlType();
	S8      getFlRule();
	S8      getRVSM();
	S8      getHPR();
	QString getAirType();
	QString getWtType();
	QString getDepAd();
	QString getDesAd();
	QString getRwayNo();
	int     getCFL();
	S8      getCetre();
	S8      getPos();

	bool miniPlanCheck();
private:
	SystemTrack systemTrack;
	Mode3A      mode3A;
	Mode5		mode5;
	TrackStatus trackStatus;
	SystemTrackUpdateAge stuAges;
	TrackDataAge trackAges;
	MeasuredInfo measuredInfo;
	AircraftDerivedData derivedData;
	FlightPlanData flightPlanData;
	EstimatedAccuracy estAccuracyData;

	BOOL FSPec(CBuffer& rBuffer);

	void I062_010(CBuffer& rBuffer);	// Data Source Identifier
	void I062_015(CBuffer& rBuffer);	// Service Identification
	void I062_040(CBuffer& rBuffer);	// Track Number
	void I062_060(CBuffer& rBuffer);	// Track Mode 3/A Code
	void I062_070(CBuffer& rBuffer);	// Time Of Track Information
	void I062_080(CBuffer& rBuffer);	// Track Status
	void I062_100(CBuffer& rBuffer);	// Calculated Track Position (Cartesian)
	void I062_105(CBuffer& rBuffer);	// Calculated Track Position (WGS-84)
	void I062_110(CBuffer& rBuffer);	// Mode 5 Data reports & Extended Mode 1 Code
	void I062_120(CBuffer& rBuffer);	// Track Mode 2 Code
	void I062_130(CBuffer& rBuffer);	// Calculated Track Geometric Altitude
	void I062_135(CBuffer& rBuffer);	// Calculated Track Barometric Altitude
	void I062_136(CBuffer& rBuffer);	// Measured Flight Level
	void I062_185(CBuffer& rBuffer);    // Calculated Track Velocity(Cartesian)
	void I062_200(CBuffer& rBuffer);	// Mode of Movement
	void I062_210(CBuffer& rBuffer);	// Calculated Track Velocity(Cartesian)
	void I062_220(CBuffer& rBuffer);	// Calculated Rate Of Climb/Descent
	void I062_245(CBuffer& rBuffer);	// Target Identification
	void I062_270(CBuffer& rBuffer);	// Target Size & Orientation
	void I062_290(CBuffer& rBuffer);	// System Track Update Ages
	void I062_295(CBuffer& rBuffer);	// Track Data Ages
	void I062_300(CBuffer& rBuffer);	// Vehicle Fleet Identification
	void I062_340(CBuffer& rBuffer);	// Measured Information
	void I062_380(CBuffer& rBuffer);	// Aircraft Derived Data
	void I062_390(CBuffer& rBuffer);	// Flight Plan Related Data
	void I062_500(CBuffer& rBuffer);	// Estimated Accuracies
	void I062_510(CBuffer& rBuffer);	// Composed Track Number

	void fileWrite();
};

#endif /* CAT062_H_ */
