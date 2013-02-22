/*
 * SystemTrack.h
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 */

#ifndef SYSTEMTRACK_H_
#define SYSTEMTRACK_H_

#include <QString>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"

class SystemTrack {
public:
	SystemTrack();
	~SystemTrack();
	void Clear();

	U8 sac;						// System Area code
	U8 sic;						// System Identification Code

	U8 sid;			 			// I062/015 Service Identification
	U16 TRACK_NUM;   			// I062/040 Track Number
	CTrackTime timeStamp;		// I062/070 Time of track information

	F64 cartesianXpos;			// I062/100 Calculated Track Position(Cartesian)
	F64 cartesianYpos;
	F64 wgsXpos;				// I062/105 Calculated Position in WGS-84 Co-ordinates.
	F64 wgsYpos;

	QString mode2Code;			// I062/120 Track Mode 2 Code
	F64 altGeo;					// I062/130 Calculated Track Geometric Altitude

	// I062/135, Calculated Track Barometric Altitude
	U8 qnhApply;				// 0 = No QNH correction applied
								// 1 = QNH correction applied
	F64 altBar;					// Calculated Track Barometric Altitude.

	F64 measuredFL;				// Data Item I062/136 Measured Flight Level

	// I062/185  Calculated Track Velocity (Cartesian)
	F64 vx;
	F64 vy;
	F64 speed;
	F64 heading;

	// I062/200  Mode of Movement
	U8 u8Trans;					// Transversal Acceleration
								// 00	Constant Course
								// 01	Right Turn
								// 10	Left Turn
								// 11	Undetermined
	U8 u8Long;					// Longitudinal Acceleration
								// 00	Constant Groundspeed
								// 01	Increasing Groundspeed
								// 10	Decreasing Groundspeed
								// 11	Undetermined
	U8 u8Vert;					// Vertical Rate
								// 00	Level
								// 01	Climb
								// 10	Descent
								// 11	Undetermined
	// I062/210  Calculated Acceleration (Cartesian)
	F64 ax;
	F64 ay;
	// I062/220  Calculated Rate of Climb/Descent
	// A positive value indicates a climb, whereas a negative value indicates a descent.
	F64 climb_descent;
	// I062/245  Target Identification
	U8  u8STI;					// 00	Callsign or registeration downlinked from target
								// 01	Callsign not downlinked from target
								// 10	Registration not downlinked from target
								// 11	Invalid
	QString callsign;			// Target Identification
	// I062/270  Target Size & Orientation
	int targetLength;			// LSB = 1m
	F64 orientation;			// 360 /128 = appro. 2.81
	int targetWidth;			// LSB = 1m

	// I062/300  Vehicle Fleet Identification
	U8 vfi;						//  	= 0 Unknown
								//  	= 1 ATC equipment maintenance
								//  	= 2 Airport maintenance
								//  	= 3 Fire
								//  	= 4 Bird scarer
								//  	= 5 Snow plough
								//  	= 6 Runway sweeper
								//  	= 7 Emergency
								//  	= 8 Police
								//  	= 9 Bus
								//  	= 10 Tug (push/tow)
								//  	= 11 Grass cutter
								//  	= 12 Fuel
								//  	= 13 Baggage
								//  	= 14 Catering
								//  	= 15 Aircraft maintenance
								//  	= 16 Flyco (follow me)

	// I062/510  Composed Track Number
	U8 systemUnitId1;
	int trackNum1;
	U8 systemUnitId2;
	int trackNum2;
};

#endif /* SYSTEMTRACK_H_ */
