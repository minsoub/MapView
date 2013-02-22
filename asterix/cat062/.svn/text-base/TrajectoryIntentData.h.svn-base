/*
 * TrajectoryIntentData.h
 *
 *  Created on: 2012. 4. 16.
 *      Author: JMS
 *
 *  Description :
 *	 Subfield #9 : Trajectory Intent Data
 *	 Format : Repetitive Data Item starting with a one-octet Field Repetition Indicator (REP) followed
 *	          by at least one Trajectory Intent Point comprising fifteen octets.
 *	 NOTES
 *			1. NC is set to one when the aircraft will not fly the path described by the TCP data.
 *			2. TCP numbers start from zero.
 *			3. LT = Lateral Type
 *			4. VT = Vertical Type
 *			5. TOV gives the estimated time before reaching the point. It is defined as the
 *				absolute time from midnight.
 *			6. TOV is meaningfull only if TOA is set to 0.
 *
 */

#ifndef TRAJECTORYINTENTDATA_H_
#define TRAJECTORYINTENTDATA_H_

#include <QString>
#include "../lib/BaseTypes.h"

class TrajectoryIntentData {
public:
	TrajectoryIntentData();
	~TrajectoryIntentData();

	U8 tidTca;					// = 0 TCP number available
								// = 1 TCP number not available
	U8 tidNc;						// = 0 TCP compliance
								// = 1 TCP non-compliance
	int tidTcpNum;				// Trajectory Change Point number
	F64 tidAltitude;			// Altitude in two's complement. LSB = 10ft  -1500ft <= altitude <= 150000 ft
	F64 tidLatitude;			// In WGS.84 in two's complement. -90 <= latitude <= 90 deg.
								// LSB = 180/2^23 deg = approx.2.145767*10^-05 deg.
	F64 tidLongitude;			// In WGS.84 in two's complement. -180 <= latitude <= 180 deg.
								// LSB = 180/2^23 deg = approx.2.145767*10^-05 deg.
	U8  tidPointType;			// = 0 Unknown
								// = 1 Fly by waypoint (LT)
								// = 2 Fly over waypoint (LT)
								// = 3 Hold pattern	(LT)
								// = 4 Procedure hold (LT)
								// = 5 Procedure turn (LT)
								// = 6 RF leg (LT)
								// = 7 Top of climb (VT)
								// = 8 Top of descent (VT)
								// = 9 Start of level (VT)
								// = 10 Cross-over altitude (VT)
								// = 11 Transition altitude (VT)
	U8 tidTd;					// = 00 N/A
								// = 01 Turn right
								// = 10 Turn left
								// = 11 No turn
	U8 tidTra;					// Turn Radius Availability
								// 0 TTR not available
								// 1 TTR available
	U8 tidToa;					// 0 TOV available
								// 1 TOV not available
	F64 tidTov;					// Time Over Point	LSB = 1 second
	F64 tidTtr;					// TCP Turn radius
								// LSB = 0.01 Nm   0 <= TTR <= 655.36 Nm
};

#endif /* TRAJECTORYINTENTDATA_H_ */
