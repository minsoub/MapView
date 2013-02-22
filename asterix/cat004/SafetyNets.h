/*
 * SafetyNets.h
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 *
 *  Description:
 *      SafetyNets Data structure
 */

#ifndef SAFETYNETS_H_
#define SAFETYNETS_H_

#include <QVector>

#include "../lib/CTrackTime.h"
#include "AircraftIdentification.h"

typedef struct _Tag {
	U8 sac;
	U8 sic;
} Tag;

typedef struct _FDPS_Sector_Control_Identification {
	U8 centre;
	U8 position;
} FDP_SC_ID;

class SafetyNets {
public:
	SafetyNets();
	~SafetyNets();
	void Clear();

	U8 messge_type;	// Message type
	U8 sac;			// System Area code
	U8 sic;			// System Identification Code
	QVector<Tag> sdpsIdentifier;
	CTrackTime timeStamp;
	U16 u16TrackNum1;			   // I004/040 - Track Number 1
	U16 u16TrackNum2;			   // I004/035 - Track Number 2
	U16 u16AlertIdentifier;		// I004/040 - Alert Identifier
	U8  u8AlertStatus;			// I004/045 - Alert Status

	// I004/060 - Safety Net Function & System Status
	U8  u8MRVA;
	U8  u8RAMLD;
	U8  u8RAMHD;
	U8  u8MSAW;
	U8  u8APW;
	U8  u8CLAM;
	U8  u8STCA;
	U8  u8AFDA;
	U8  u8RIMCA;
	U8  u8ACASRA;
	U8  u8NTCA;
	U8  u8DG;
	U8  u8OF;
	U8  u8OL;

	// I004/070 - Conflict Timing and Separation
	U8 u8TC;				// Time to Conflict check field
	U8 u8TCA;				// Time to Closet Approach check field
	U8 u8CHS;				// Current Horizontal Separation check field
	U8 u8MHS;				// Estimated Minimum Horizontal Separation check field
	U8 u8CVS;				// Current Vertical Separation check field
	U8 u8MVS;				// Estimated Minimum Vertical Separation check field
	F64 f64TimeToConflict;	// Time To Conflict
	F64 f64TimeToApproach;  // Time to closest Approach
	F64 f64CurHorSep;       // Current horizontal separation
	F64 f64EstMinHorSep;	// Estimated minimum horizontal separation
	F64 f64CurVerSep;		// Current Vertical Separation
	F64 f64EstMinVerSep;	// Estimated minimum Vertical separation

	F64 f64LonDeviation;	// I004/074 - Longitudinal Deviation
	F64 f64TranDistDev;     // I004/075 - Transversal Distance Deviation
	F64 f64VerDeviation;    // I004/076 - Vertical Deviation

	// I004/100 - Area Definition
	U8 u8AreaName;			// Area Name check field
	U8 u8CrossAreaName;		// Crossing Area Name check field
	U8 u8RunTaxiDes1;		// Runway/Taxiway Designator 1 check field
	U8 u8RunTaxiDes2;		// Runway/Taxiway Designator 2 check field
	U8 u8StopBarDes;		// Stop Bar Designator check field
	U8 u8GateDes;			// Gate Designator check field
	QString strAreaName;	// Name of the area involved in a Safety Net alerm.
	QString strCrossAreaName; // Name of Crossing Area Involved in a RIMCA.
	QString strRunTaxDes1;	// Runway/Taxiway Designator 1
	QString strRunTaxDes2;	// Runway/Taxiway Designator 2
	QString strStopBarDes;  // Stop Bar Designator
	QString strGateDes;		// Gate Designator

	QVector<FDP_SC_ID> lstFdp_sc_id;	// I004/110 - FDPS Sector Control Identification

	// I004/120 - Conflict Characteristics
	U8 u8ConflictNature;			// Subfield #1 : Conflict Nature
	U8 u8ConflictClassification;	// Subfield #2 : Conflict Classification
	U8 u8ConflictProbability;		// Subfield #3 : Conflict Probability
	U8 u8ConflictDuration;			// Subfield #4 : Conflict Duration;

	U8 u8MAS;						// Subfield #1 : Conflict location in military airspace
	U8 u8CAS;						// Subfield #1 : Conflict location in civil airspace
	U8 u8FLD;						// Subfield #1 : Fast lateral divergence
	U8 u8FVD;						// Subfield #1 : Fast vertical divergence
	U8 u8TYPE;						// Subfield #1 : Type of separation infringement
	U8 u8CROSS;						// Subfield #1 : Crossing test
	U8 u8DIV;						// Subfield #1 : Divergence test

	U8 u8RPC;						// Subfield #2 : Runway/Runway crossing in RIMCAS
	U8 u8RTC;						// Subfield #2 : Runway/Taxiway Crossing in RIMCAS
	U8 u8MRVA_2;						// Subfield #2 : Msg type 4 (MSAW) indicates MRVA

	U8 u8TableID;					// Subfield #3 : Identification of conflict categories.
									//               0000 => 0, 0001 => 1, 0010 => 2
	U8 u8SeverityCls;				// Subfield #3 : Conflict Severity Class
									//    001 (1) : major separation infringement and not (crossed and diverging)
	                                //    010 (2) : minor separation infringement and not (crossed and diverging)
	                                //    011 (3) : major separation infringement and (crossed and diverging)
	                                //    100 (4) : minor separation infringement and (crossed and diverging)
	U8 u8Severity;                  // Subfield #3 : Conflict Severity 0:LOW, 1 : HIGHT
	S32 s32ProbComflict;			// Subfield #3 : Probability of the conclict
	F64 f64Duration;				// Subfield #4 : Conflicit Duration

	// I004/170 - Aircraft Identification & Characteristics 1
	AircraftIdentification airId1;

	// I004/171 - Aircraft Identification & Characteristics 2
	AircraftIdentification airId2;


};

#endif /* SAFETYNETS_H_ */
