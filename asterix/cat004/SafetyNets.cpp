/*
 * SafetyNets.cpp
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 *
 *  Description:
 *      SafetyNets Data structure
 */

#include "SafetyNets.h"

SafetyNets::SafetyNets() {
	// TODO Auto-generated constructor stub
	Clear();
}

SafetyNets::~SafetyNets() {
	// TODO Auto-generated destructor stub
}

void SafetyNets::Clear()
{
	messge_type = 0x00;	// Message type
	sac = 0x00;			// System Area code
	sic = 0x00;			// System Identification Code
	sdpsIdentifier.clear();
	u16TrackNum1 = 0;			// I004/040 - Track Number 1
	u16TrackNum2 = 0;			// I004/035 - Track Number 2
	u16AlertIdentifier = 0;		// I004/040 - Alert Identifier
	u8AlertStatus = 0x00;			// I004/045 - Alert Status

	// I004/060 - Safety Net Function & System Status
	u8MRVA = 0x00;
	u8RAMLD = 0x00;
	u8RAMHD = 0x00;
	u8MSAW = 0x00;
	u8APW = 0x00;
	u8CLAM = 0x00;
	u8STCA = 0x00;
	u8AFDA = 0x00;
	u8RIMCA = 0x00;
	u8ACASRA = 0x00;
	u8NTCA = 0x00;
	u8DG = 0x00;
	u8OF = 0x00;
	u8OL = 0x00;

	// I004/070 - Conflict Timing and Separation
	u8TC = 0x00;				// Time to Conflict check field
	u8TCA = 0x00;				// Time to Closet Approach check field
	u8CHS = 0x00;				// Current Horizontal Separation check field
	u8MHS = 0x00;				// Estimated Minimum Horizontal Separation check field
	u8CVS = 0x00;				// Current Vertical Separation check field
	u8MVS = 0x00;				// Estimated Minimum Vertical Separation check field
	f64TimeToConflict = 0.0;	// Time To Conflict
	f64TimeToApproach = 0.0;  // Time to closest Approach
	f64CurHorSep = 0.0;       // Current horizontal separation
	f64EstMinHorSep = 0.0;	// Estimated minimum horizontal separation
	f64CurVerSep = 0.0;		// Current Vertical Separation
	f64EstMinVerSep = 0.0;	// Estimated minimum Vertical separation

	f64LonDeviation = 0.0;	// I004/074 - Longitudinal Deviation
	f64TranDistDev = 0.0;     // I004/075 - Transversal Distance Deviation
	f64VerDeviation = 0.0;    // I004/076 - Vertical Deviation

	// I004/100 - Area Definition
	u8AreaName = 0x00;			// Area Name check field
	u8CrossAreaName = 0x00;		// Crossing Area Name check field
	u8RunTaxiDes1 = 0x00;		// Runway/Taxiway Designator 1 check field
	u8RunTaxiDes2 = 0x00;		// Runway/Taxiway Designator 2 check field
	u8StopBarDes = 0x00;		// Stop Bar Designator check field
	u8GateDes = 0x00;			// Gate Designator check field
	strAreaName = "";	// Name of the area involved in a Safety Net alerm.
	strCrossAreaName = ""; // Name of Crossing Area Involved in a RIMCA.
	strRunTaxDes1 = "";	// Runway/Taxiway Designator 1
	strRunTaxDes2 = "";	// Runway/Taxiway Designator 2
	strStopBarDes = "";  // Stop Bar Designator
	strGateDes = "";		// Gate Designator

	lstFdp_sc_id.clear();	// I004/110 - FDPS Sector Control Identification

	// I004/120 - Conflict Characteristics
	u8ConflictNature = 0x00;			// Subfield #1 : Conflict Nature
	u8ConflictClassification = 0x00;	// Subfield #2 : Conflict Classification
	u8ConflictProbability = 0x00;		// Subfield #3 : Conflict Probability
	u8ConflictDuration = 0x00;			// Subfield #4 : Conflict Duration;

	u8MAS = 0x00;						// Subfield #1 : Conflict location in military airspace
	u8CAS = 0x00;						// Subfield #1 : Conflict location in civil airspace
	u8FLD = 0x00;						// Subfield #1 : Fast lateral divergence
	u8FVD = 0x00;						// Subfield #1 : Fast vertical divergence
	u8TYPE = 0x00;						// Subfield #1 : Type of separation infringement
	u8CROSS = 0x00;						// Subfield #1 : Crossing test
	u8DIV = 0x00;						// Subfield #1 : Divergence test

	u8RPC = 0x00;						// Subfield #2 : Runway/Runway crossing in RIMCAS
	u8RTC = 0x00;						// Subfield #2 : Runway/Taxiway Crossing in RIMCAS
	u8MRVA_2 = 0x00;						// Subfield #2 : Msg type 4 (MSAW) indicates MRVA

	u8TableID = 0x00;					// Subfield #3 : Identification of conflict categories.
									//               0000 => 0, 0001 => 1, 0010 => 2
	u8SeverityCls = 0x00;				// Subfield #3 : Conflict Severity Class
									//    001 (1) : major separation infringement and not (crossed and diverging)
	                                //    010 (2) : minor separation infringement and not (crossed and diverging)
	                                //    011 (3) : major separation infringement and (crossed and diverging)
	                                //    100 (4) : minor separation infringement and (crossed and diverging)
	u8Severity = 0x00;                  // Subfield #3 : Conflict Severity 0:LOW, 1 : HIGHT
	s32ProbComflict = 0;			// Subfield #3 : Probability of the conclict
	f64Duration = 0.0;				// Subfield #4 : Conflicit Duration

	// I004/170 - Aircraft Identification & Characteristics 1
	airId1.Clear();

	// I004/171 - Aircraft Identification & Characteristics 2
	airId2.Clear();
}
