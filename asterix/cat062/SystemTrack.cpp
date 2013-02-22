/*
 * SystemTrack.cpp
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 */

#include "SystemTrack.h"

SystemTrack::SystemTrack() {
	// TODO Auto-generated constructor stub
	Clear();
}

SystemTrack::~SystemTrack() {
	// TODO Auto-generated destructor stub
}

void SystemTrack::Clear()
{
	sac = 0x00;						// System Area code
	sic = 0x00;						// System Identification Code
	sid = 0x00;			 			// I062/015 Service Identification
	TRACK_NUM = 0;   			// I062/040 Track Number
	timeStamp = NULL;		// I062/070 Time of track information

	cartesianXpos = 0.0;			// I062/100 Calculated Track Position(Cartesian)
	cartesianYpos = 0.0;
	wgsXpos = 0.0;				// I062/105 Calculated Position in WGS-84 Co-ordinates.
	wgsYpos = 0.0;

	mode2Code = "";			// I062/120 Track Mode 2 Code
	altGeo = 0.0;					// I062/130 Calculated Track Geometric Altitude

	// I062/135, Calculated Track Barometric Altitude
	qnhApply = 0x00;				// 0 = No QNH correction applied
								      // 1 = QNH correction applied
	altBar = 0.0;					// Calculated Track Barometric Altitude.
	measuredFL = 0.0;				// Data Item I062/136 Measured Flight Level

	// I062/185  Calculated Track Velocity (Cartesian)
	vx = 0.0;
	vy = 0.0;
	speed = 0.0;
	heading = 0.0;

	// I062/200  Mode of Movement
	u8Trans = 0x00;					// Transversal Acceleration
								// 00	Constant Course
								// 01	Right Turn
								// 10	Left Turn
								// 11	Undetermined
	u8Long = 0x00;					// Longitudinal Acceleration
								// 00	Constant Groundspeed
								// 01	Increasing Groundspeed
								// 10	Decreasing Groundspeed
								// 11	Undetermined
	u8Vert = 0x00;					// Vertical Rate
								// 00	Level
								// 01	Climb
								// 10	Descent
								// 11	Undetermined
	// I062/210  Calculated Acceleration (Cartesian)
	ax = 0.0;
	ay = 0.0;
	// I062/220  Calculated Rate of Climb/Descent
	// A positive value indicates a climb, whereas a negative value indicates a descent.
	climb_descent = 0.0;
	// I062/245  Target Identification
	u8STI = 0x00;					// 00	Callsign or registeration downlinked from target
								// 01	Callsign not downlinked from target
								// 10	Registration not downlinked from target
								// 11	Invalid
	callsign = "";			// Target Identification
	// I062/270  Target Size & Orientation
	targetLength = 0;			// LSB = 1m
	orientation  = 0.0;			// 360 /128 = appro. 2.81
	targetWidth  = 0;			// LSB = 1m

	// I062/300  Vehicle Fleet Identification
	vfi = 0x00;						//  	= 0 Unknown
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
	systemUnitId1 = 0x00;
	trackNum1 = 0;
	systemUnitId2 = 0x00;
	trackNum2 = 0;
}
