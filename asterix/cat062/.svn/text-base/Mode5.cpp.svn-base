/*
 * Mode5.cpp
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 *  Description : Data Item I062/110, Mode 5 Data reports & Extended Mode 1 Code
 */

#include "Mode5.h"

Mode5::Mode5() {
	// TODO Auto-generated constructor stub
	Clear();
}

Mode5::~Mode5() {
	// TODO Auto-generated destructor stub
}

void Mode5::Clear()
{
	// Structure of Primary Subfield
	sum = 0x00;			// Subfield #1 : Mode 5 Summary
					// = 0 Absence of Subfield #1
					// = 1 Presence of Subfield #1
	pmn = 0x00;			// Subfield #2 : Mode 5 PIN/National Origin/Mission Code
					// = 0 Absence of Subfield #2
					// = 1 Presence of Subfield #2
	pos = 0x00;			// Subfield #3 : Mode 5 Reported Position
					// = 0 Absence of Subfield #3
					// = 1 Presence of Subfield #3
	ga = 0x00;			// Subfield #4 : Mode 5 GNSS-derived Altitude
					// = 0 Absence of Subfield #4
					// = 1 Presence of Subfield #4
	em1 = 0x00;			// Subfield #5 : Extended Mode 1 Code in Octal Representation
					// = 0 Absence of Subfield #5
					// = 1 Presence of Subfield #5
	tosCHK = 0x00;			// Subfield #6 : Time Offset for POS and GA
					// = 0 Absence of Subfield #6
					// = 1 Presence of Subfield #6
	xp = 0x00;			// Subfield #7 : X Pulse Presence
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
	m5 = 0x00;			// = 0 No Mode 5 interrogation
					// = 1 Mode 5 interrogation
	id = 0x00;			// = 0 No authenticated Mode 5 ID reply
					// = 1 Authenticated Mode 5 ID reply
	da = 0x00;			// = 0 No authenticated Mode 5 Data reply or Report
					// = 1 Authenticated Mode 5 Data reply or Report (i.e any valid Mode 5 reply type other than ID)
	m1 = 0x00;			// = 0 Mode 1 code not present or not from Mode 5 reply
					// = 1 Mode 1 code from Mode 5 reply
	m2 = 0x00;			// = 0 Mode 2 code not present or not from Mode 5 reply
					// = 1 Mode 2 code from Mode 5 reply
	m3 = 0x00;			// = 0 Mode 3 code not present or not from Mode 5 reply
					// = 1 Mode 3 code from Mode 5 reply
	mc = 0x00;			// = 0 Mode C altitude not present or not from Mode 5 reply
					// = 1 Mode C altitude from Mode 5 reply
	x = 0x00;			// X-pulse from Mode 5 Data reply or Report
					// = 0 X-pulse set to zero or no authenticated Data reply or Report received.
					// = 1 X-pulse set to one.

	// Structure of Subfield #2 : Mode 5 PIN/National Origin/Mission Code
	pin = 0;		// PIN Code
	nat = 0x00;		// National Origin
	mis = 0x00;		// Mission Code

	// Structure of Subfield #3 : Mode 5 Reported Position
	lat = 0.0;		// In WGS.84 in two's complement - Latitude
					// Range -90 <= latitude <= 90 deg
					// LSB = 180/2^23 degrees
	lon = 0.0;		// In WGS.84 in two's complement - Longitude
					// Range -180 <= Longitude < 180 deg
					// LSB = 180/2^23 degrees

	// Structure of Subfield #4 : Mode 5 GNSS-derived Altitude
	// NOTES
	//  1. GA is coded as a 14-bit two's complement binary number with an LSB of 25 ft.
	//     irrespective of the setting of RES.
	//  2. The minimum value of GA that can be reported is -1000 ft.
	res = 0x00;			// Resolution with which the GNSS-derived Altitude (GA) is reported.
					// = 0 GA reported in 100 ft increments,
					// = 1 GA reported in 25 ft increments.
	s16Ga = 0;		// GNSS-derived Altitude of target, expressed as height above WGS 84 ellipsoid.

	// Structure of Subfield #5 : Extended Mode 1 Code in Octal Representation.
	// NOTE
	//  If Subfield #1 is present, the M1 bit in Subfield #1 indeicates whether the Extended Mode 1
	//  Code is from a Mode 5 reply or a Mode 1 reply. If Subfield #1 is not present, the Extended
	//  Mode 1 Code is from a Mode 1 reply.
	mode1Code = "";	// 4�ڸ� (9999)

	// Structure of Subfield #6 : Time Offset for POS and GA
	// NOTE
	//  TOS shall be assumed to be zero if Subfield #6 is not present.
	tos = 0.0;		// Time Offset coded as a twos complement number with an LSB of 1/128 s.
					// The time at which the Mode 5 Reported Position (Subfield #3) and Mode 5
					// GNSS-derived Altitude (Subfield #4) are valid is given by Time of Day (I048/140)
					// plus Time Offset.

	// Structure of Subfield #7 : X Pulse Presence
	x5 = 0x00;			// X-pulse from Mode 5 Data reply or Report
					// = 0 X-pulse set to zero or no authenticated Data reply or Report received.
					// = 1 X-pulse set to one (present).
	xc = 0x00;			// X-pulse from Mode C reply
					// = 0 X-pulse set to zero or no Mode C reply
					// = 1 X-pulse set to one (present)
	x3 = 0x00;			// X-pulse from Mode 3/A reply
					// = 0 X-pulse set to zero or no Mode 3/A reply
					// = 1 X-pulse set to one (present)
	x2 = 0x00;			// X-pulse from Mode 2 reply
					// = 0 X-pulse set to zero or no Mode 2 reply
					// = 1 X-pulse set to one (present)
	x1 = 0x00;			// X-pulse from Mode 1 reply
					// = 0 X-pulse set to zero or no Mode 1 reply
					// = 1 X-pulse set to one (present)
}
