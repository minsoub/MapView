/*
 * ADSBCls.h
 *
 *  Created on: 2012. 5. 11.
 *      Author: JMS
 *  Description : ADS-B data structure
 */

#ifndef ADSBCLS_H_
#define ADSBCLS_H_

#include <QVector>
#include "../lib/CTrackTime.h"
#include "TrajectoryIntent.h"

class ADSBCls {
public:
	ADSBCls();
	~ADSBCls();
	void Clear();

	U8 sac;				// System Area Code
	U8 sic;				// System Identification Code

	int ecat;			// Data Item I021/020, Emitter Category
							//   ECAT : Emitter Category
							// 		1 = light aircraft <= 7000 kg
							// 		2 = reserved
							// 		3 = 7000 kg < medium aircraft < 136000 kg
							// 		4 = reserved
							// 		5 = 136000 kg <= heavy aircraft
							// 		6 = highly manoeuvrable (5g acceleration capability) and high speed(>400 knots cruise)
							// 		7 to 9 = reserved
							// 		10 = rotocraft
							// 		11 = glider / sailplane
							// 		12 = lighter-than-air
							// 		13 = unmannned aerial vehicle
							// 		14 = space / transatmospheric vehicle
							// 		15 = ultralight / handglider / paraglider
							// 		16 = parachutist / skydiver
							// 		17 to 19 = reserved
							// 		20 = surface emegency vehicle
							// 		21 = surface service vehicle
							// 		22 = fixed ground or tethered obstruction
							// 		23 to 24 = reserved

	CTrackTime timeStamp;		// Data Item I021/030, Time of Day
	F64 timeofdayAccuracy;		// Data Item I021/032, Time of Day Accuracy

	// Data Item I021/040 Target Report Descriptor
	U8 u8DCR;			// = 0 No differential correction (ADS-B)
							// = 1 Differential correction (ADS-B)
	U8 u8GBS;			// = 0 Ground Bit not set
							// = 1 Ground Bit set
	U8 u8SIM;			// = 0 Actual target report
							// = 1 Simulated target report
	U8 u8TST;			// = 0 Default
							// = 1 Test Target
	U8 u8RAB;			// = 0 Report from target transponder
							// = 1 Report from field monitor (fixed transponder)
	U8 u8SAA;			// = 0 Equipement not capable to provide Selected Altitude
							// = 1 Equipement capable to provide Selected Altitude
	U8 u8SPI;			// = 0 Absence of SPI
							// = 1 Special Position Identification
	U8 u8ATP;			// = 0 Non unique address
							// = 1 24-Bit ICAO address
							// = 2 Surface vehicle address
							// = 3 Anonymous address
							// = 4-7 Reserved for future use
	U8 u8ARC;			// Altitude Reporting Capability
							// = 0 Unknown
							// = 1 25 ft
							// = 2 100 ft
	int targetAddr;			// Data Item I021/080 Target Address

	// Data Item I021/090 Figure of Merit
	U8 u8AC;				// 00 = unknown
							// 01 = ACAS not operatinal
							// 10 = ACAS operational
							// 11 = invalid
	U8 u8MN;				// 00 = unknown
							// 01 = Multiple navigational aids not operating
							// 10 = Multiple navigatinal aids operating
							// 11 = invalid
	U8 u8DC;				// 00 = unknown
							// 01 = Differential correction
							// 10 = No differential correction
							// 11 = invalid
	U8 u8PA;				// Position Accuracy

	U8 u8VelocityAccur;			// Data Item I021/095 Velocity Accuracy

	// Data Item I021/110 Trajectory Intent
	U8 tisCHK;			// Trajectory Intent Status check
	U8 tidCHK;			// Trajectory Intent Data check
	U8 nav;				// = 0 Trajectory Intent Data is available for this aircraft
							// = 1 Trajectory Intent Data is not available for this aircraft
	U8 nvb;				// = 0 Trajectory Intent Data is valid
							// = 1 Trajectory Intent Data is not valid

	int trajectorRep;	// Repetition number
	QVector<TrajectoryIntent> trajectoryList;		// Structure of Subfield #2

	// Data Item I021/130 Position in WGS-84 Co-ordinates
	F64 lat;				// In WGS-84 in two's complement.
							// Range -90 <= latitude <= 90 deg.
							// LSB = 180/2^23 degrees
	F64 lon;				// In WGS-84 in two's complement.
							// Range -180 <= latitude < 180 deg.
							// LSB = 180/2^23 degrees

	F64 alt;				// Data Item I021/140 Geometric Altitude
							// LSB = 6.25 ft
							// -1500 ft <= altitude <= 150000 ft
	F64 fl;				// Data Item I021/145 Flight Level
							// LSB = 1/4 FL
							// -15FL <= Flight Level <= 1500 FL

	// Data Item I021/146 Intermediate State Selected Altitude
	U8 sas;				// = 0 No source information provided
							// = 1 Source Information provided
	U8 source;			// = 00 Unknown
							// = 01 Aircraft Altitude
							// = 10 FCU/MSP Selected Altitude
							// = 11 FMS Selected Altitude
	F64 intermediateAlt;		// LSB 25ft
									// -1300ft <= altitude <= 100000 ft

	// Data Item I021/148 Final State Selected Altitude
	U8 mv;				// Manage Vertical Mode
							// = 0 Not active
							// = 1 Active
	U8 ah;				// Altitude Hold Mode
							// = 0 Not active
							// = 1 Active
	U8 am;				// Approach Mode
							// = 0 Not active
							// = 1 Active
	F64 finalStateAlt;	// LSB 25ft
								// -1300ft <= altitude <= 100000 ft

	// Data Item I021/150 Air Speed
	U8 im;				// = 0 Air Speed = IAS
							// = 1 Air Speed = Mach
	F64 airSpeed;		// Air Speed (IAS or Mach)

	// Data Item I021/151 True Airspeed
	F64 trueAirSpeed;	// LSB = 1 knot

	// Data Item I021/152 Magnetic Heading
	F64 magHeading;			// LSB = 0.0055;

	// Data Item I021/155 Barometric Vertical Rate
	F64 barVerticalRate;		// LSB = 6.25 feet/minute

	// Data Item I021/157 Geometric Vertical Rate
	F64 geoVerticalRate;		// LSB = 6.25 feet/minute

	// Data Item I021/160 Ground Vector
	F64 groundSpeed;			// LSB = 2^-14;
	F64 trackAngle;			// LSB = 360 / 2^16

	// Data Item I021/165 Rate Of Turn
	U8 ti;						// Turn Indicator
									// 00 = Not available
									// 01 = Left
									// 10 = Right
									// 11 = Straight
	F64 rateOfTurn;			// Rate of Turn
									// LSB = 2^-2 o/s = 1/4 o/s
									// Maximum value = 15 o/s

	// Data Item I021/170 Target Identification
	QString targetId;

	// Data Item I021/200 Target Status
	U8 targetStatus;			// 0 = No emergency / not reported
									// 1 = General emergency
									// 2 = Lifeguard / medical
									// 3 = Minimum fuel
									// 4 = No communications
									// 5 = Unlawful interference

	// Data Item I021/210 Link Technology Indicator
	U8 dti;						// Cockpit Display of Traffic Information
									// 0 = Unknown
									// 1 = Aircraft equiped whth CDTI
	U8 mds;						// Mode-S Extended Squitter
									// 0 = Not used
									// 1 = Used
	U8 uat;						// UAT
									// 0 = Not used
									// 1 = Used
	U8 vdl;						// VDL Mode 4
									// 0 = Not used
									// 1 = Used
	U8 otr;						// Other Technology
									// 0 = Not used
									// 1 = Used

	// Data Item I021/220 Met Information
	U8 wsCHK;					// 0 = Absence of Subfield #1
									// 1 = Presence of Subfield #1
	U8 wdCHK;					// 0 = Absence of Subfield #1
									// 1 = Presence of Subfield #1
	U8 tmpCHK;					// 0 = Absence of Subfield #1
									// 1 = Presence of Subfield #1
	U8 trbCHK;					// 0 = Absence of Subfield #1
									// 1 = Presence of Subfield #1
	S16 windSpeed;				// Wind Speed
									// LSB = 1 knot
									// 0 <= Wind Speed <= 300
	S16 windDirection;		// Wind Direction
									// LSB = 1 degree
									// 1 <= Wind Direction <= 360
	F64 temperature;			// LSB = 0.25 oC
									// -100 oC <= Temperature <= 100 oC
	S16 turbulence;			// Integer between 0 and 15 inclusive

	// Data Item I021/230 Roll Angle
	F64 rollAngle;				// LSB = 0.01 degree
									// -180 <= Roll Angle <= 180
};

#endif /* ADSBCLS_H_ */
