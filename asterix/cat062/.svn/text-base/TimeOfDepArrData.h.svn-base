/*
 * TimeOfDepArrData.h
 *
 *  Created on: 2012. 4. 16.
 *      Author: JMS
 *  Description:
 *              Structure of Subfield #12 : Time of Departure / Arrival
 *
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 *              - Data Item I062/390, Flight Plan Related Data.
 *              - This class describes Data Item I062/390.
 *              - All flight plan related information, provided by ground-based systems.
 */
#ifndef TIMEOFDEPARRDATA_H_
#define TIMEOFDEPARRDATA_H_

#include <QString>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"

class TimeOfDepArrData {
public:
	TimeOfDepArrData();
	~TimeOfDepArrData();

	// NOTE - Estimated times are derived from flight plan systems. Predicted times
	//		  are derived by the fusion system, based on surveillance data. For
	//		  definitions, see [Ref.4]
	U8 typ;						// = 0 Scheduled off-block time
								// = 1 Estimated off-block time
								// = 2 Estimated take-off time
								// = 3 Actual off-block time
								// = 4 Predicted time at runway hold
								// = 5 Actual time at runway hold
								// = 6 Actual line-up time
								// = 7 Actual take-off time
								// = 8 Estimated time of arrival
								// = 9 Predicted landing time
								// = 10 Actual landing time
								// = 11 Actual time  of runway
								// = 12 Predicted time to gate
								// = 13 Actual on-block time
	U8 day;						// = 00 Today
								// = 01 Yesterday
								// = 10 Tomorrow
								// = 11 Invalid
	U8 hor;						// = Hours, from 0 to 23
	U8 min;						// = Minutes, from 0 to 59
	U8 avs;						// = 0 Seconds available
								// = 1 Seconds not available
	U8 sec;						// = Seconds, from 0 to 59
};

#endif /* TIMEOFDEPARRDATA_H_ */
