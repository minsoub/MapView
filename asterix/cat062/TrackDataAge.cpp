/*
 * TrackDataAge.cpp
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

#include "TrackDataAge.h"

TrackDataAge::TrackDataAge() {
	// TODO Auto-generated constructor stub

}

TrackDataAge::~TrackDataAge() {
	// TODO Auto-generated destructor stub
}

void TrackDataAge::Clear()
{
	mflCHK = 0x00;			// Subfield #1 : Measured Flight Level age
	md1CHK = 0x00;			// Subfield #2 : Mode 1 age
	md2CHK = 0x00;			// Subfield #3 : Mode 2 age
	mdaCHK = 0x00;			// Subfield #4 : Mode 3/A age
	md4CHK = 0x00;			// Subfield #5 : Mode 4 age
	md5CHK = 0x00;			// Subfield #6 : Mode 5 age
	mhgCHK = 0x00;			// Subfield #7 : Magnetic Heading age
	iasCHK = 0x00;			// Subfield #8 : Indicated Airspeed/Mach Nb age
	tasCHK = 0x00;			// Subfield #9 : True Airspeed age
	salCHK = 0x00;			// Subfield #10 : Selected Altitude age
	fssCHK = 0x00;			// Subfield #11 : Final State Selected Altitude age
	tidCHK = 0x00;			// Subfield #12 : Trajectory Intent Data age
	comCHK = 0x00;			// Subfield #13 : Communications / ACAS Capability and Flight Status age
	sabCHK = 0x00;			// Subfield #14 : Status Reported by ADS-B age
	acsCHK = 0x00;			// Subfield #15 : ACAS Resolutioin Advisory Report age
	bvrCHK = 0x00;			// Subfield #16 : Barometric Vertical Rate age
	gvrCHK = 0x00;			// Subfield #17 : Geometric Vertical Rate age
	ranCHK = 0x00;			// Subfield #18 : Roll Angle age
	tarCHK = 0x00;			// Subfield #19 : Track Angle Rate age
	tanCHK = 0x00;			// Subfield #20 : Track Angle age
	gspCHK = 0x00;			// Subfield #21 : Ground Speed age
	vunCHK = 0x00;			// Subfield #22 : Velocity Uncertainty age
	metCHK = 0x00;			// Subfield #23 : Meteorological Data age
	emcCHK = 0x00;			// Subfield #24 : Emitter Category age
	posCHK = 0x00;			// Subfield #25 : Position Data age
	galCHK = 0x00;			// Subfield #26 : Geometric Altitude Data age
	punCHK = 0x00;			// Subfield #27 : Position Uncertainty Data age
	mbCHK = 0x00;			// Subfield #28 : Mode S MB Data age
	iarCHK = 0x00;			// Subfield #29 : Indicated Airspeed Data age
	macCHK = 0x00;			// Subfield #30 : Mach Number Data age
	bpsCHK = 0x00;			// Subfield #31 : Barometric Pressure Setting Data age

	mfl= 0.0;			// Age of the last valid and credible Mode C code or barometric altitude
						// from ADS-B used to update the track (I062/136)
	md1= 0.0;			// Age of the last valid and credible Mode 1 code used to update the track (I062/110)
	md2= 0.0;			// Age of the last valid and credible Mode 2 code used to update the track (I062/120)
	mda= 0.0;			// Age of the last valid and credible Mode 3/A code used to update the track (I062/060)
	md4= 0.0;			// Age of the last valid and credible Mode 4 code used to update the track
	md5= 0.0;			// Age of the last valid and credible Mode 5 code used to update the track (I062/110)
	mhg= 0.0;			// Age of the DAP "Magnetic Heading" in item 062/380 (Subfield #3)
	ias= 0.0;			// Age of the DAP "Indicated Airspeed / Mach Number" in item 062/380 (Subfield #4)
	tas= 0.0;			// Age of the DAP "True Airspeed" in item 062/380 (Subfield #5)
	sal= 0.0;			// Age of the DAP "Selected Altitude" in item 062/380 (Subfield #6)
	fss= 0.0;			// Age of the DAP "Final State Selected Altitude" in item 062/380 (Subfield #7)
	tid= 0.0;			// Age of the DAP "Trajectory Intent" in item 062/380 (Subfield #8)
	com= 0.0;			// Age of the DAP "Communication/ACAS Capability and Flight Status" in item 062/380 (Subfield #10)
	sab= 0.0;			// Age of the DAP "Status Reproted by ADS-B" in item 062/380 (Subfield #11)
	acs= 0.0;			// Age of the DAP "ACAS Resolution Advisory Report" in item 062/380 (Subfield #12)
	bvr= 0.0;			// Age of the DAP "Barometric Vertical Rate" in item 062/380 (Subfield #13)
	gvr= 0.0;			// Age of the DAP "Geometrical Vertical Rate" in item 062/380 (Subfield #14)
	ran= 0.0;			// Age of the DAP "Roll Angle" in item 062/380 (Subfield #15)
	tar= 0.0;			// Age of the DAP "Track Angle Rate" in item 062/380 (Subfield #16)
	tan= 0.0;			// Age of the DAP "Track Angle" in item 062/380 (Subfield #17)
	gsp= 0.0;			// Age of the DAP "Ground Speed" in item 062/380 (Subfield #18)
	vun= 0.0;			// Age of the DAP "Velocity Uncertainty" in item 062/380 (Subfield #19)
	met= 0.0;			// Age of the DAP "Meteorological Data" in item 062/380 (Subfield #20)
	emc= 0.0;			// Age of the DAP "Emitter Category" in item 062/380 (Subfield #21)
	pos= 0.0;			// Age of the DAP "Position" in item 062/380 (Subfield #23)
	gal= 0.0;			// Age of the DAP "Geometric Altitude" in item 062/380 (Subfield #24)
	pun= 0.0;			// Age of the DAP "Position Uncertainty" in item 062/380 (Subfield #25)
	mb= 0.0;				// Age of the DAP "Mode S MB Data" in item 062/380 (Subfield #22)
	iar= 0.0;			// Age of the DAP "Indicated Airspeed" in item 062/380 (Subfield #26)
	mac= 0.0;			// Age of the DAP "Mach Number" in item 062/380 (Subfield #27)
	bps= 0.0;			// Age of the DAP "Barometric Pressure Setting" in item 062/380 (Subfield #28)
}
