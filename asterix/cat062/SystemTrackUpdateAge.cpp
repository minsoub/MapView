/*
 * SystemTrackUpdateAge.cpp
 *
 *  Created on: 2012. 4. 13.
 *      Author: JMS
 *  Description:
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 *              - Data Item I062/290, System Track Update Ages.
 *              - This class describes Data Item I062/290.
 */
#include "SystemTrackUpdateAge.h"

SystemTrackUpdateAge::SystemTrackUpdateAge() {
	// TODO Auto-generated constructor stub
	Clear();
}

SystemTrackUpdateAge::~SystemTrackUpdateAge() {
	// TODO Auto-generated destructor stub
}

void SystemTrackUpdateAge::Clear()
{
	trkCHK = 0x00;				// Subfield #1 : Track age
							// = 0 Absence of Subfield #1
							// = 1 Presence of Subfield #1
	psrCHK = 0x00;				// Subfield #2 : PSR age
							// = 0 Absence of Subfield #2
							// = 1 Presence of Subfield #2
	ssrCHK = 0x00;				// Subfield #3 : SSR age
							// = 0 Absence of Subfield #3
							// = 1 Presence of Subfield #3
	mdsCHK = 0x00;				// Subfield #4 : Mode S age
							// = 0 Absence of Subfield #4
							// = 1 Presence of Subfield #4
	adsCHK = 0x00;				// Subfield #5 : ADS-C age
							// = 0 Absence of Subfield #5
							// = 1 Presence of Subfield #5
	esCHK = 0x00;				// Subfield #6 : ADS-B Extended Squitter age
							// = 0 Absence of Subfield #6
							// = 1 Presence of Subfiled #6
	vdlCHK = 0x00;				// Subfield #7 : ADS-B VDL Mode 4 age
							// = 0 Absence of Subfield #7
							// = 1 Presence of Subfield #7
	uatCHK = 0x00;				// Subfield #8 : ADS-B UAT age
							// = 0 Absence of Subfield #8
							// = 1 Presence of Subfield #8
	lopCHK = 0x00;				// Subfield #9 : Loop age
							// = 0 Absence of Subfield #9
							// = 1 Presence of Subfield #9
	mltCHK = 0x00;				// Subfield #10 : Multilateration age
							// = 0 Absence of Subfield #10
							// = 1 Presence of Subfield #10

	trk = 0.0;				// Actual track age since first occurence (LSB = 1/4 s)
	psr = 0.0;				// Age of the last primary detection used to update the track (LSB = 1/4 s)
	ssr = 0.0;				// Age of the last secondary detection used to update the track (LSB = 1/4 s)
	mds = 0.0;				// Age of the last Mode S detection used to update the track (LSB = 1/4 s)
	ads = 0.0;				// Age of the last ADS-C report used to update the track (LSB = 1/4 s)
	es = 0.0;					// Age of the last 1090 Extended Squitter ADS-B report used to update the track (LSB = 1/4 s)
	vdl = 0.0;				// Age of the last VDL Mode 4 ADS-B report used to update the track (LSB = 1/4 s)
	uat = 0.0;				// Age of the last UAT ADS-B report to udpate the track (LSB = 1/4 s)
	lop = 0.0;				// Age of the last magnetic loop detectiion (LSB = 1/4 s)
	mlt = 0.0;				// Age of the last MLT detection (LSB = 1/4 s)
}
