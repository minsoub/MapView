/*
 * FlightPlanData.h
 *
 *  Created on: 2012. 4. 16.
 *      Author: JMS
 *  Description:
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 *              - Data Item I062/390, Flight Plan Related Data.
 *              - This class describes Data Item I062/390.
 *              - All flight plan related information, provided by ground-based systems.
 */

#ifndef FLIGHTPLANDATA_H_
#define FLIGHTPLANDATA_H_
#include <QString>
#include <QVector>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"
#include "TimeOfDepArrData.h"

class FlightPlanData {
public:
	FlightPlanData();
	~FlightPlanData();

	void Clear();

	U8 tagCHK;					// Subfield #1 : FPPS identification Tag
	U8 csnCHK;					// Subfield #2 : Callsign
	U8 ifiCHK;					// Subfield #3 : IFPS_FLIGHT_ID
	U8 fctCHK;					// Subfield #4 : Flight Category
	U8 tacCHK;					// Subfield #5 : Type of Aircraft
	U8 wtcCHK;					// Subfield #6 : Wake Turbulence Category
	U8 depCHK;					// Subfield #7 : Departure Airport
	U8 dstCHK;					// Subfield #8 : Destination Airport
	U8 rdsCHK;					// Subfield #9 : Runway Designation
	U8 cflCHK;					// Subfield #10 : Current Cleared Flight Level
	U8 ctlCHK;					// Subfield #11 : Current Control Position
	U8 todCHK;					// Subfield #12 : Time of Departure / Arrival
	U8 astCHK;					// Subfield #13 : Aircraft Stand
	U8 stsCHK;					// Subfield #14 : Stand Status
	U8 stdCHK;					// Subfield #15 : Standard Instrument Departure
	U8 staCHK;					// Subfield #16 : Standard Instrument Arrival
	U8 pemCHK;					// Subfield #17 : Pre-emergency Mode 3/A code
	U8 pecCHK;					// Subfield #18 : Pre-emergency Callsign

	// Subfield #1 : FPPS Identification Tag
	int sac;					// System Area Code
	int sic;					// System Identity Code

	// Subfield #2 : Callsign
	// NOTE - Each one of the seven Octets contains an ASCII Character. The Callsign
	//        is always left adjusted. It contains up to seven upper-case alphanumeric
	//		  characters, the remaining character positiions (if any) are padded with
	//        space characters.
	QString callsign;

	// Subfield #3 : IFPS_FLIGHT_ID
	U8 typ;						// = 00 Plan Number
								// = 01 Unit 1 internal flight number
								// = 10 Unit 2 internal flight number
								// = 11 Unit 3 internal flight number
	U32 nbr;					// NBR => Number from 0 to 99 999 999

	// Subfield #4 : Flight Category
	U8 cat;						// CAT/OAT = 00 Unknown
								//         = 01 General Air Traffic
								//         = 10 Operational Air Traffic
								//         = 11 Not applicable
	U8 fr;						// FR1/FR2 = 00 Instrument Flight Rules
								//         = 01 Visual Flight rules
								//		   = 10 Not applicable
								//         = 11 Controlled Visual Flight Rules
	U8 rvsm;					// RVSM    = 00 Unknown
								//         = 01 Approved
								//         = 10 Exempt
								//         = 11 Not Approved
	U8 hpr;						// HPR     = 0 Normal Priority Flight
								//         = 1 High Priority Flight

	// Subfield #5 : Type of Aircraft
	// NOTES
	//		1. Each one of the four Octets composing the type of an aircrfat contains an ASCII
	//			Character (upper-case alphabetic characters with trailling spaces).
	//		2. The types of aircraft are defined in [Ref.4]
	QString typeAircraft;

	// Subfield #6 : Wake Turbulence Category
	QString wtc;				// Wake Turbulence Category is an ASCII character code which
								// should be one of the following values
								// L = Light
								// M = Midium
								// H = Heavy
								// J = "Super"

	// Subfield #7 : Departure Airport
	// NOTES
	//		1. Each one of the four Octets composing the name of an airport contains an ASCII Character (upper case)
	//		2. The Airport Names are indicated in the ICAO Location Indicators book.
	QString depAirport;

	// Subfield #8 : Destination Airport
	QString destAirport;

	// Subfield #9 : Runway Designation
	// NOTES
	//		1. NU1, NU2 and LTR each contain in an ASCII character.
	//		2. For details refer to [5]Section 5
	QString nu1;				// First number
	QString nu2;				// Second number
	QString ltr;				// Letter
	QString rway;				// Runway NO
	// Subfield #10 : Current Cleared Flight Level
	F64 cfl;					// LSB = 1/4 FL

	// Subfield #11 : Current Control Position
	// NOTE - The centre and the control position identification codes have to be
	//		  defined between communication partners.
	U8 centre;					// 8-bit group Identificatioin code
	U8 position;				// 8-bit Control Position identification code.

	// Subfield #12 : Time of Departure / Arrival
	int rep;					// Repetition Factor
	QVector<TimeOfDepArrData> timeOfDepArrList;

	// Subfield #13 : Aircraft Stand
	// NOTE - Each one of the six Octets contains an ASCII Character. The Aircraft
	//        Stand identification is always left adjusted. It contains up to six
	//		  upper-case alphanumeric characters, the remaining character positions
	//		  (if any) are padded with space characters.
	QString aircraftStand;

	// Subfield #14 : Stand Status
	U8 emp;						// = 00 Empty
								// = 01 Occupied
								// = 10 Unknown
								// = 11 Invalid
	U8 avl;						// = 00 Available
								// = 01 Not available
								// = 10 Unknown
								// = 11 Invalid

	// Subfield #15 : Standard Instrument Departure
	QString standardInstrumentDep;

	// Subfield #16 : Standard Instrument Arrival
	QString standardInstrumentArr;

	// Subfield #17 : Pre-Emergency Mode 3/A
	// NOTES
	//		1. This subfield is used only when the aircraft is transmitting an emergency
	//		   Mode 3/A code
	//		2. If VA = 0, the content of bits 12/1 is meaningless.
	U8 va;						// = 0 No valid Mode 3/A available
								// = 1 Valid Mode 3/A available
	QString mode3A;				// Mode-3/A reply in octal

	// Subfield #18 : Pre-Emergency Callsign
	// NOTES
	//		1. Each one of the seven Octets contains an ASCII Character. The Callsign is
	//		   always left adjusted. It contains up to seven upper-case alphanumeric
	//		   characters, the remaining character positions (if any) are padded with
	//		   space characters.
	//		2. This subfield is used only when en emergency Mode 3/A is associated with
	//		   the track (I062/390 Subfield #17)
	QString pre_callsign;

};

#endif /* FLIGHTPLANDATA_H_ */
