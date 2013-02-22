/*
 * SystemTrackUpdateAge.h
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

#ifndef SYSTEMTRACKUPDATEAGE_H_
#define SYSTEMTRACKUPDATEAGE_H_

#include <QString>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"

class SystemTrackUpdateAge {
public:
	SystemTrackUpdateAge();
	~SystemTrackUpdateAge();

	void Clear();

	U8 trkCHK;				// Subfield #1 : Track age
							// = 0 Absence of Subfield #1
							// = 1 Presence of Subfield #1
	U8 psrCHK;				// Subfield #2 : PSR age
							// = 0 Absence of Subfield #2
							// = 1 Presence of Subfield #2
	U8 ssrCHK;				// Subfield #3 : SSR age
							// = 0 Absence of Subfield #3
							// = 1 Presence of Subfield #3
	U8 mdsCHK;				// Subfield #4 : Mode S age
							// = 0 Absence of Subfield #4
							// = 1 Presence of Subfield #4
	U8 adsCHK;				// Subfield #5 : ADS-C age
							// = 0 Absence of Subfield #5
							// = 1 Presence of Subfield #5
	U8 esCHK;				// Subfield #6 : ADS-B Extended Squitter age
							// = 0 Absence of Subfield #6
							// = 1 Presence of Subfiled #6
	U8 vdlCHK;				// Subfield #7 : ADS-B VDL Mode 4 age
							// = 0 Absence of Subfield #7
							// = 1 Presence of Subfield #7
	U8 uatCHK;				// Subfield #8 : ADS-B UAT age
							// = 0 Absence of Subfield #8
							// = 1 Presence of Subfield #8
	U8 lopCHK;				// Subfield #9 : Loop age
							// = 0 Absence of Subfield #9
							// = 1 Presence of Subfield #9
	U8 mltCHK;				// Subfield #10 : Multilateration age
							// = 0 Absence of Subfield #10
							// = 1 Presence of Subfield #10

	F64 trk;				// Actual track age since first occurence (LSB = 1/4 s)
	F64 psr;				// Age of the last primary detection used to update the track (LSB = 1/4 s)
	F64 ssr;				// Age of the last secondary detection used to update the track (LSB = 1/4 s)
	F64 mds;				// Age of the last Mode S detection used to update the track (LSB = 1/4 s)
	F64 ads;				// Age of the last ADS-C report used to update the track (LSB = 1/4 s)
	F64 es;					// Age of the last 1090 Extended Squitter ADS-B report used to update the track (LSB = 1/4 s)
	F64 vdl;				// Age of the last VDL Mode 4 ADS-B report used to update the track (LSB = 1/4 s)
	F64 uat;				// Age of the last UAT ADS-B report to udpate the track (LSB = 1/4 s)
	F64 lop;				// Age of the last magnetic loop detectiion (LSB = 1/4 s)
	F64 mlt;				// Age of the last MLT detection (LSB = 1/4 s)


};

#endif /* SYSTEMTRACKUPDATEAGE_H_ */
