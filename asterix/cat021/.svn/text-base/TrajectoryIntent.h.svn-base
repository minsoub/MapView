/*
 * TrajectoryIntent.h
 *
 *  Created on: 2012. 5. 14.
 *      Author: JMS
 *  Description : Trajectory Intent Data
 *                Data Item I021/110, Trajectory Intent
 *                Structure of Subfield #2
 */

#ifndef TRAJECTORYINTENT_H_
#define TRAJECTORYINTENT_H_

#include "../lib/BaseTypes.h"

class TrajectoryIntent {
public:
	TrajectoryIntent();
	~TrajectoryIntent();

	U8 tca;						// = 0 TCP number available
									// = 1 TCP number not available
	U8 nc;						// = 0 TCP compliance
									// = 1 TCP non-compliance
	int tcpNum;					// Trajectory Change Point number
	F64 altitude;				// Altitude in two's complement form
									// LSB = 10ft
									// -1500ft <= altitude <= 150000 ft
	F64 lat;						// In WGS.84 in two's complement.
									// -90 <= latitude <= 90 deg.
									// LSB = 180 / 2^23 deg
	F64 lon;						// In WGS.84 in two's complement.
									// -180 <= longitude < 180
									// LSB = 180/2^23 deg
	int pointType;				// = 0 Unknown
									// = 1 Fly by waypoint (LT)
									// = 2 Fly over waypoint (LT)
									// = 3 Hold pattern (LT)
									// = 4 Procedure hold (LT)
									// = 5 Procedure turn (LT)
									// = 6 RF leg (LT)
									// = 7 Top of climb (VT)
									// = 8 Top of descent (VT)
									// = 9 Start of level (VT)
									// = 10 Cross-over altitude (VT)
									// = 11 Transition altitude (VT)
	U8 td;						// = 00 N/A
									// = 01 Turn right
									// = 10 Turn left
									// = 11 No turn
	U8 tra;						// Turn Radius Availability
									// = 0 TTR not available
									// = 1 TTR available
	U8 toa;						// = 0 TOV available
									// = 1 TOV not available
	F64 tov;						// Time Over point
									// LSB = 1 second
	F64 ttr;						// TCP Turn radius
									// LSB = 0.01 Nm
									// 0 <= TTR <= 655.35 NM
};

#endif /* TRAJECTORYINTENT_H_ */
