/*
 * AircraftIdentification.cpp
 *
 *  Created on: 2012. 3. 29.
 *      Author: JMS
 */

#include "AircraftIdentification.h"

AircraftIdentification::AircraftIdentification() {
	// TODO Auto-generated constructor stub

	Clear();
}

AircraftIdentification::~AircraftIdentification() {
	// TODO Auto-generated destructor stub
}

/**
 * Clear data
 */
void AircraftIdentification::Clear()
{
	u8AI1 = 0x00;		// Subfield #1 : Aircraft Identifier 1
	u8M31 = 0x00;		// Subfield #2 : Mode 3/A Code Aircraft 1
	u8CPW = 0x00;		// Subfield #3 : Predicted Conflict Position 1 (WGS84)
	u8CPC = 0x00;		// Subfield #4 : Predicted Conflict Position 1 (Cartesian Coordinates)
	u8TT1 = 0x00;		// Subfield #5 : Time to Threshold Aircraft 1
	u8DT1 = 0x00;		// Subfield #6 : Distance to Threshold Aircraft 1
	u8AC1 = 0x00;		// Subfield #7 : Aircraft Characteristics Aircraft 1
	u8MS1 = 0x00;		// Subfield #8 : Mode S Identifier Aircraft 1
	u8FP1 = 0x00;		// Subfield #9 : Flight Plan Number Aircraft 1
	u8CF1 = 0x00;		// Subfield #10 : Cleared Flight Level Aircraft 1

	strAircraftID = "";	// Subfield #1 : Aircraft Identifier 1
	// Subfield #2 : Mode 3/A Code Aircraft 1 (0 or 1)
	u8A4 = 0x00, u8A2 = 0x00, u8A1 = 0x00;
	u8B4 = 0x00, u8B2 = 0x00, u8B1 = 0x00;
	u8C4 = 0x00, u8C2 = 0x00, u8C1 = 0x00;
	u8D4 = 0x00, u8D2 = 0x00, u8D1 = 0x00;
	strMode3ACode = "";
	// Subfield #3
	f64Lat = 0.0;
	f64Lon = 0.0;
	s32Alt = 0;
	// Subfield #4 : Predicted conflict Position Aircraft 1 in Cartesian Coordinates
	f64XPOS = 0.0;	// Starting X-Position of Conflict
	f64YPOS = 0.0;	// Starting Y-Position of Conflict
	s32ZPOS = 0;	// Starting Z-Position of Conflict
	// Subfield #5 : Time to Threshold Aircraft 1
	f64TimeToThreshold = 0.0;
	// Subfield #6 : Distance to Threshold Aircraft 1
	f64DistToThreshold = 0.0;
	// Subfield #7 : Aircraft Characteristics Aircraft 1
	u8GATOAT = 0x00;		// GAT/OAT = 00 Unknown
	                    //         = 01 General Air Traffic
	                    //         = 10 Operational Air Traffic
	                    //         = 11 Not applicable
	u8FR1FR2 = 0x00;        // FR1/FR2 = 00 Instrument Flight Rules
	                    //         = 01 Visual Flight rules
	                    //         = 10 Not Applicable
	                    //         = 11 Controlled Visual Flight Rules
	u8RVSM = 0x00;			// RVSM    = 00 Unknown
	                    //         = 01 Approved
	                    //         = 10 Exempt
	                    //         = 11 Not Approved
	u8HRP = 0x00;           // HPR     =  0 Normal Priority Flight
	                    //         =  1 High Priority Flight
	u8CDM = 0x00;           // CDM     Climbing / Descending mode
	                    //         = 00 Maintaining
	                    //         = 01 Climbing
	                    //         = 10 Descending
	                    //         = 11 Invalid
	u8PRI = 0x00;           // PRI     =  0 Non primary target
	                    //         =  1 Primary target
	u8GV = 0x00;            // GV      =  0 Default
	                    //         =  1 Ground Vehicle

	// Subfield #8 : Mode-S Identifier Aircraft 1
	strModesID = "";

	u32NBR = 0;		// Subfield #9 : Flight Plan Number Aircraft 1
	f64CFL = 0.0;		// Subfield #10: Cleared Flight Level Aircraft 1
}
