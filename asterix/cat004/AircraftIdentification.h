/*
 * AircraftIdentification.h
 *
 *  Created on: 2012. 3. 29.
 *      Author: JMS
 */

#ifndef AIRCRAFTIDENTIFICATION_H_
#define AIRCRAFTIDENTIFICATION_H_

#include <QString>
#include "../lib/BaseTypes.h"

class AircraftIdentification {
public:
	AircraftIdentification();
	~AircraftIdentification();
	void Clear();

	U8 u8AI1;		// Subfield #1 : Aircraft Identifier 1
	U8 u8M31;		// Subfield #2 : Mode 3/A Code Aircraft 1
	U8 u8CPW;		// Subfield #3 : Predicted Conflict Position 1 (WGS84)
	U8 u8CPC;		// Subfield #4 : Predicted Conflict Position 1 (Cartesian Coordinates)
	U8 u8TT1;		// Subfield #5 : Time to Threshold Aircraft 1
	U8 u8DT1;		// Subfield #6 : Distance to Threshold Aircraft 1
	U8 u8AC1;		// Subfield #7 : Aircraft Characteristics Aircraft 1
	U8 u8MS1;		// Subfield #8 : Mode S Identifier Aircraft 1
	U8 u8FP1;		// Subfield #9 : Flight Plan Number Aircraft 1
	U8 u8CF1;		// Subfield #10 : Cleared Flight Level Aircraft 1

	QString strAircraftID;	// Subfield #1 : Aircraft Identifier 1
	// Subfield #2 : Mode 3/A Code Aircraft 1 (0 or 1)
	U8 u8A4, u8A2, u8A1, u8B4, u8B2, u8B1, u8C4, u8C2, u8C1, u8D4, u8D2, u8D1;
	QString strMode3ACode;
	// Subfield #3
	F64 f64Lat;
	F64 f64Lon;
	S32 s32Alt;
	// Subfield #4 : Predicted conflict Position Aircraft 1 in Cartesian Coordinates
	F64 f64XPOS;	// Starting X-Position of Conflict
	F64 f64YPOS;	// Starting Y-Position of Conflict
	S32 s32ZPOS;	// Starting Z-Position of Conflict
	// Subfield #5 : Time to Threshold Aircraft 1
	F64 f64TimeToThreshold;
	// Subfield #6 : Distance to Threshold Aircraft 1
	F64 f64DistToThreshold;
	// Subfield #7 : Aircraft Characteristics Aircraft 1
	U8 u8GATOAT;		// GAT/OAT = 00 Unknown
	                    //         = 01 General Air Traffic
	                    //         = 10 Operational Air Traffic
	                    //         = 11 Not applicable
	U8 u8FR1FR2;        // FR1/FR2 = 00 Instrument Flight Rules
	                    //         = 01 Visual Flight rules
	                    //         = 10 Not Applicable
	                    //         = 11 Controlled Visual Flight Rules
	U8 u8RVSM;			// RVSM    = 00 Unknown
	                    //         = 01 Approved
	                    //         = 10 Exempt
	                    //         = 11 Not Approved
	U8 u8HRP;           // HPR     =  0 Normal Priority Flight
	                    //         =  1 High Priority Flight
	U8 u8CDM;           // CDM     Climbing / Descending mode
	                    //         = 00 Maintaining
	                    //         = 01 Climbing
	                    //         = 10 Descending
	                    //         = 11 Invalid
	U8 u8PRI;           // PRI     =  0 Non primary target
	                    //         =  1 Primary target
	U8 u8GV;            // GV      =  0 Default
	                    //         =  1 Ground Vehicle

	// Subfield #8 : Mode-S Identifier Aircraft 1
	QString strModesID;

	U32 u32NBR;		// Subfield #9 : Flight Plan Number Aircraft 1
	F64 f64CFL;		// Subfield #10: Cleared Flight Level Aircraft 1
};

#endif /* AIRCRAFTIDENTIFICATION_H_ */
