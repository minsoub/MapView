/*
 * TrackDataAge.h
 *
 *  Created on: 2012. 4. 13.
 *      Author: JMS
 *  Description:
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 *              - Data Item I062/295, Track Data Ages.
 *              - This class describes Data Item I062/295.
 */

#ifndef TRACKDATAAGE_H_
#define TRACKDATAAGE_H_
#include <QString>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"

class TrackDataAge {
public:
	TrackDataAge();
	~TrackDataAge();

	void Clear();

	U8 mflCHK;			// Subfield #1 : Measured Flight Level age
	U8 md1CHK;			// Subfield #2 : Mode 1 age
	U8 md2CHK;			// Subfield #3 : Mode 2 age
	U8 mdaCHK;			// Subfield #4 : Mode 3/A age
	U8 md4CHK;			// Subfield #5 : Mode 4 age
	U8 md5CHK;			// Subfield #6 : Mode 5 age
	U8 mhgCHK;			// Subfield #7 : Magnetic Heading age
	U8 iasCHK;			// Subfield #8 : Indicated Airspeed/Mach Nb age
	U8 tasCHK;			// Subfield #9 : True Airspeed age
	U8 salCHK;			// Subfield #10 : Selected Altitude age
	U8 fssCHK;			// Subfield #11 : Final State Selected Altitude age
	U8 tidCHK;			// Subfield #12 : Trajectory Intent Data age
	U8 comCHK;			// Subfield #13 : Communications / ACAS Capability and Flight Status age
	U8 sabCHK;			// Subfield #14 : Status Reported by ADS-B age
	U8 acsCHK;			// Subfield #15 : ACAS Resolutioin Advisory Report age
	U8 bvrCHK;			// Subfield #16 : Barometric Vertical Rate age
	U8 gvrCHK;			// Subfield #17 : Geometric Vertical Rate age
	U8 ranCHK;			// Subfield #18 : Roll Angle age
	U8 tarCHK;			// Subfield #19 : Track Angle Rate age
	U8 tanCHK;			// Subfield #20 : Track Angle age
	U8 gspCHK;			// Subfield #21 : Ground Speed age
	U8 vunCHK;			// Subfield #22 : Velocity Uncertainty age
	U8 metCHK;			// Subfield #23 : Meteorological Data age
	U8 emcCHK;			// Subfield #24 : Emitter Category age
	U8 posCHK;			// Subfield #25 : Position Data age
	U8 galCHK;			// Subfield #26 : Geometric Altitude Data age
	U8 punCHK;			// Subfield #27 : Position Uncertainty Data age
	U8 mbCHK;			// Subfield #28 : Mode S MB Data age
	U8 iarCHK;			// Subfield #29 : Indicated Airspeed Data age
	U8 macCHK;			// Subfield #30 : Mach Number Data age
	U8 bpsCHK;			// Subfield #31 : Barometric Pressure Setting Data age

	F64 mfl;			// Age of the last valid and credible Mode C code or barometric altitude
						// from ADS-B used to update the track (I062/136)
	F64 md1;			// Age of the last valid and credible Mode 1 code used to update the track (I062/110)
	F64 md2;			// Age of the last valid and credible Mode 2 code used to update the track (I062/120)
	F64 mda;			// Age of the last valid and credible Mode 3/A code used to update the track (I062/060)
	F64 md4;			// Age of the last valid and credible Mode 4 code used to update the track
	F64 md5;			// Age of the last valid and credible Mode 5 code used to update the track (I062/110)
	F64 mhg;			// Age of the DAP "Magnetic Heading" in item 062/380 (Subfield #3)
	F64 ias;			// Age of the DAP "Indicated Airspeed / Mach Number" in item 062/380 (Subfield #4)
	F64 tas;			// Age of the DAP "True Airspeed" in item 062/380 (Subfield #5)
	F64 sal;			// Age of the DAP "Selected Altitude" in item 062/380 (Subfield #6)
	F64 fss;			// Age of the DAP "Final State Selected Altitude" in item 062/380 (Subfield #7)
	F64 tid;			// Age of the DAP "Trajectory Intent" in item 062/380 (Subfield #8)
	F64 com;			// Age of the DAP "Communication/ACAS Capability and Flight Status" in item 062/380 (Subfield #10)
	F64 sab;			// Age of the DAP "Status Reproted by ADS-B" in item 062/380 (Subfield #11)
	F64 acs;			// Age of the DAP "ACAS Resolution Advisory Report" in item 062/380 (Subfield #12)
	F64 bvr;			// Age of the DAP "Barometric Vertical Rate" in item 062/380 (Subfield #13)
	F64 gvr;			// Age of the DAP "Geometrical Vertical Rate" in item 062/380 (Subfield #14)
	F64 ran;			// Age of the DAP "Roll Angle" in item 062/380 (Subfield #15)
	F64 tar;			// Age of the DAP "Track Angle Rate" in item 062/380 (Subfield #16)
	F64 tan;			// Age of the DAP "Track Angle" in item 062/380 (Subfield #17)
	F64 gsp;			// Age of the DAP "Ground Speed" in item 062/380 (Subfield #18)
	F64 vun;			// Age of the DAP "Velocity Uncertainty" in item 062/380 (Subfield #19)
	F64 met;			// Age of the DAP "Meteorological Data" in item 062/380 (Subfield #20)
	F64 emc;			// Age of the DAP "Emitter Category" in item 062/380 (Subfield #21)
	F64 pos;			// Age of the DAP "Position" in item 062/380 (Subfield #23)
	F64 gal;			// Age of the DAP "Geometric Altitude" in item 062/380 (Subfield #24)
	F64 pun;			// Age of the DAP "Position Uncertainty" in item 062/380 (Subfield #25)
	F64 mb;				// Age of the DAP "Mode S MB Data" in item 062/380 (Subfield #22)
	F64 iar;			// Age of the DAP "Indicated Airspeed" in item 062/380 (Subfield #26)
	F64 mac;			// Age of the DAP "Mach Number" in item 062/380 (Subfield #27)
	F64 bps;			// Age of the DAP "Barometric Pressure Setting" in item 062/380 (Subfield #28)

};

#endif /* TRACKDATAAGE_H_ */
