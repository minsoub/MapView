/*
 * FlightPlanData.cpp
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

#include "FlightPlanData.h"

FlightPlanData::FlightPlanData() {
	// TODO Auto-generated constructor stub
	Clear();

}

FlightPlanData::~FlightPlanData() {
	// TODO Auto-generated destructor stub
}

void FlightPlanData::Clear()
{
	tagCHK = 0x00;					// Subfield #1 : FPPS identification Tag
	csnCHK = 0x00;					// Subfield #2 : Callsign
	ifiCHK = 0x00;					// Subfield #3 : IFPS_FLIGHT_ID
	fctCHK = 0x00;					// Subfield #4 : Flight Category
	tacCHK = 0x00;					// Subfield #5 : Type of Aircraft
	wtcCHK = 0x00;					// Subfield #6 : Wake Turbulence Category
	depCHK = 0x00;					// Subfield #7 : Departure Airport
	dstCHK = 0x00;					// Subfield #8 : Destination Airport
	rdsCHK = 0x00;					// Subfield #9 : Runway Designation
	cflCHK = 0x00;					// Subfield #10 : Current Cleared Flight Level
	ctlCHK = 0x00;					// Subfield #11 : Current Control Position
	todCHK = 0x00;					// Subfield #12 : Time of Departure / Arrival
	astCHK = 0x00;					// Subfield #13 : Aircraft Stand
	stsCHK = 0x00;					// Subfield #14 : Stand Status
	stdCHK = 0x00;					// Subfield #15 : Standard Instrument Departure
	staCHK = 0x00;					// Subfield #16 : Standard Instrument Arrival
	pemCHK = 0x00;					// Subfield #17 : Pre-emergency Mode 3/A code
	pecCHK = 0x00;					// Subfield #18 : Pre-emergency Callsign

	// Subfield #1 : FPPS Identification Tag
	sac = 0;					// System Area Code
	sic = 0;					// System Identity Code

	// Subfield #2 : Callsign
	// NOTE - Each one of the seven Octets contains an ASCII Character. The Callsign
	//        is always left adjusted. It contains up to seven upper-case alphanumeric
	//		  characters, the remaining character positiions (if any) are padded with
	//        space characters.
	callsign = "";

	// Subfield #3 : IFPS_FLIGHT_ID
	typ = 0x00;						// = 00 Plan Number
								// = 01 Unit 1 internal flight number
								// = 10 Unit 2 internal flight number
								// = 11 Unit 3 internal flight number
	nbr = 0;					// NBR => Number from 0 to 99 999 999

	// Subfield #4 : Flight Category
	cat = 0x00;						// CAT/OAT = 00 Unknown
								//         = 01 General Air Traffic
								//         = 10 Operational Air Traffic
								//         = 11 Not applicable
	fr = 0x00;						// FR1/FR2 = 00 Instrument Flight Rules
								//         = 01 Visual Flight rules
								//		   = 10 Not applicable
								//         = 11 Controlled Visual Flight Rules
	rvsm = 0x00;					// RVSM    = 00 Unknown
								//         = 01 Approved
								//         = 10 Exempt
								//         = 11 Not Approved
	hpr = 0x00;						// HPR     = 0 Normal Priority Flight
								//         = 1 High Priority Flight

	// Subfield #5 : Type of Aircraft
	// NOTES
	//		1. Each one of the four Octets composing the type of an aircrfat contains an ASCII
	//			Character (upper-case alphabetic characters with trailling spaces).
	//		2. The types of aircraft are defined in [Ref.4]
	typeAircraft = "";

	// Subfield #6 : Wake Turbulence Category
	wtc = "";				// Wake Turbulence Category is an ASCII character code which
								// should be one of the following values
								// L = Light
								// M = Midium
								// H = Heavy
								// J = "Super"

	// Subfield #7 : Departure Airport
	// NOTES
	//		1. Each one of the four Octets composing the name of an airport contains an ASCII Character (upper case)
	//		2. The Airport Names are indicated in the ICAO Location Indicators book.
	depAirport = "";

	// Subfield #8 : Destination Airport
	destAirport = "";

	// Subfield #9 : Runway Designation
	// NOTES
	//		1. NU1, NU2 and LTR each contain in an ASCII character.
	//		2. For details refer to [5]Section 5
	nu1 = "";				// First number
	nu2 = "";				// Second number
	ltr = "";				// Letter
	rway = "";				// Runway No
	// Subfield #10 : Current Cleared Flight Level
	cfl = 0.0;					// LSB = 1/4 FL

	// Subfield #11 : Current Control Position
	// NOTE - The centre and the control position identification codes have to be
	//		  defined between communication partners.
	centre = 0x00;					// 8-bit group Identificatioin code
	position = 0x00;				// 8-bit Control Position identification code.

	// Subfield #12 : Time of Departure / Arrival
	rep = 0;					// Repetition Factor
	timeOfDepArrList.clear();

	// Subfield #13 : Aircraft Stand
	// NOTE - Each one of the six Octets contains an ASCII Character. The Aircraft
	//        Stand identification is always left adjusted. It contains up to six
	//		  upper-case alphanumeric characters, the remaining character positions
	//		  (if any) are padded with space characters.
	aircraftStand = "";

	// Subfield #14 : Stand Status
	emp = 0x00;						// = 00 Empty
								// = 01 Occupied
								// = 10 Unknown
								// = 11 Invalid
	avl = 0x00;						// = 00 Available
								// = 01 Not available
								// = 10 Unknown
								// = 11 Invalid

	// Subfield #15 : Standard Instrument Departure
	standardInstrumentDep = "";

	// Subfield #16 : Standard Instrument Arrival
	standardInstrumentArr = "";

	// Subfield #17 : Pre-Emergency Mode 3/A
	// NOTES
	//		1. This subfield is used only when the aircraft is transmitting an emergency
	//		   Mode 3/A code
	//		2. If VA = 0, the content of bits 12/1 is meaningless.
	va = 0x00;						// = 0 No valid Mode 3/A available
								// = 1 Valid Mode 3/A available
	mode3A = "";				// Mode-3/A reply in octal

	// Subfield #18 : Pre-Emergency Callsign
	// NOTES
	//		1. Each one of the seven Octets contains an ASCII Character. The Callsign is
	//		   always left adjusted. It contains up to seven upper-case alphanumeric
	//		   characters, the remaining character positions (if any) are padded with
	//		   space characters.
	//		2. This subfield is used only when en emergency Mode 3/A is associated with
	//		   the track (I062/390 Subfield #17)
	pre_callsign = "";
}
