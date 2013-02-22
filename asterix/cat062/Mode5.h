/*
 * Mode5.h
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 *  Description : Data Item I062/110, Mode 5 Data reports & Extended Mode 1 Code
 */

#ifndef MODE5_H_
#define MODE5_H_

#include <QString>
#include "../lib/BaseTypes.h"

class Mode5 {
public:
	Mode5();
	~Mode5();
	void Clear();

	// Structure of Primary Subfield
	U8 sum;			// Subfield #1 : Mode 5 Summary
					// = 0 Absence of Subfield #1
					// = 1 Presence of Subfield #1
	U8 pmn;			// Subfield #2 : Mode 5 PIN/National Origin/Mission Code
					// = 0 Absence of Subfield #2
					// = 1 Presence of Subfield #2
	U8 pos;			// Subfield #3 : Mode 5 Reported Position
					// = 0 Absence of Subfield #3
					// = 1 Presence of Subfield #3
	U8 ga;			// Subfield #4 : Mode 5 GNSS-derived Altitude
					// = 0 Absence of Subfield #4
					// = 1 Presence of Subfield #4
	U8 em1;			// Subfield #5 : Extended Mode 1 Code in Octal Representation
					// = 0 Absence of Subfield #5
					// = 1 Presence of Subfield #5
	U8 tosCHK;			// Subfield #6 : Time Offset for POS and GA
					// = 0 Absence of Subfield #6
					// = 1 Presence of Subfield #6
	U8 xp;			// Subfield #7 : X Pulse Presence
					// = 0 Absence of Subfield #7
					// = 1 Presence of Subfield #7

	// Structure of Subfield #1 : Mode 5 Summary
	// NOTES.
	//	1. The flags M2, M3, MC refer to the contents of data items I062/120, I062/060 and I062/135
	//	   respectively. The flag M1 refer to the contents of the Subfield #5 (Extended Mode 1 Code in
	//     Octal REpresentation).
	//  2. If an authenticated Mode 5 reply is recieved with the Emergency bit set,
	//     then the Military Emergency bit(ME) in Data Item I062/080, Track Status, shall be set.
	//  3. If an authenticated Mode 5 reply is received with the Identification of Postion bit set,
	//     then the Special Postion Identification bit (SPI) in Data Item I062/080, Track Status,
	//     shall be set.
	U8 m5;			// = 0 No Mode 5 interrogation
					// = 1 Mode 5 interrogation
	U8 id;			// = 0 No authenticated Mode 5 ID reply
					// = 1 Authenticated Mode 5 ID reply
	U8 da;			// = 0 No authenticated Mode 5 Data reply or Report
					// = 1 Authenticated Mode 5 Data reply or Report (i.e any valid Mode 5 reply type other than ID)
	U8 m1;			// = 0 Mode 1 code not present or not from Mode 5 reply
					// = 1 Mode 1 code from Mode 5 reply
	U8 m2;			// = 0 Mode 2 code not present or not from Mode 5 reply
					// = 1 Mode 2 code from Mode 5 reply
	U8 m3;			// = 0 Mode 3 code not present or not from Mode 5 reply
					// = 1 Mode 3 code from Mode 5 reply
	U8 mc;			// = 0 Mode C altitude not present or not from Mode 5 reply
					// = 1 Mode C altitude from Mode 5 reply
	U8 x;			// X-pulse from Mode 5 Data reply or Report
					// = 0 X-pulse set to zero or no authenticated Data reply or Report received.
					// = 1 X-pulse set to one.

	// Structure of Subfield #2 : Mode 5 PIN/National Origin/Mission Code
	S16 pin;		// PIN Code
	U8  nat;		// National Origin
	U8  mis;		// Mission Code

	// Structure of Subfield #3 : Mode 5 Reported Position
	F64 lat;		// In WGS.84 in two's complement - Latitude
					// Range -90 <= latitude <= 90 deg
					// LSB = 180/2^23 degrees
	F64 lon;		// In WGS.84 in two's complement - Longitude
					// Range -180 <= Longitude < 180 deg
					// LSB = 180/2^23 degrees

	// Structure of Subfield #4 : Mode 5 GNSS-derived Altitude
	// NOTES
	//  1. GA is coded as a 14-bit two's complement binary number with an LSB of 25 ft.
	//     irrespective of the setting of RES.
	//  2. The minimum value of GA that can be reported is -1000 ft.
	U8 res;			// Resolution with which the GNSS-derived Altitude (GA) is reported.
					// = 0 GA reported in 100 ft increments,
					// = 1 GA reported in 25 ft increments.
	S16 s16Ga;		// GNSS-derived Altitude of target, expressed as height above WGS 84 ellipsoid.

	// Structure of Subfield #5 : Extended Mode 1 Code in Octal Representation.
	// NOTE
	//  If Subfield #1 is present, the M1 bit in Subfield #1 indeicates whether the Extended Mode 1
	//  Code is from a Mode 5 reply or a Mode 1 reply. If Subfield #1 is not present, the Extended
	//  Mode 1 Code is from a Mode 1 reply.
	QString mode1Code;	// 4�ڸ� (9999)

	// Structure of Subfield #6 : Time Offset for POS and GA
	// NOTE
	//  TOS shall be assumed to be zero if Subfield #6 is not present.
	F64 tos;		// Time Offset coded as a twos complement number with an LSB of 1/128 s.
					// The time at which the Mode 5 Reported Position (Subfield #3) and Mode 5
					// GNSS-derived Altitude (Subfield #4) are valid is given by Time of Day (I048/140)
					// plus Time Offset.

	// Structure of Subfield #7 : X Pulse Presence
	U8 x5;			// X-pulse from Mode 5 Data reply or Report
					// = 0 X-pulse set to zero or no authenticated Data reply or Report received.
					// = 1 X-pulse set to one (present).
	U8 xc;			// X-pulse from Mode C reply
					// = 0 X-pulse set to zero or no Mode C reply
					// = 1 X-pulse set to one (present)
	U8 x3;			// X-pulse from Mode 3/A reply
					// = 0 X-pulse set to zero or no Mode 3/A reply
					// = 1 X-pulse set to one (present)
	U8 x2;			// X-pulse from Mode 2 reply
					// = 0 X-pulse set to zero or no Mode 2 reply
					// = 1 X-pulse set to one (present)
	U8 x1;			// X-pulse from Mode 1 reply
					// = 0 X-pulse set to zero or no Mode 1 reply
					// = 1 X-pulse set to one (present)
};

#endif /* MODE5_H_ */
