/*
 * TrackStatus.cpp
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 *  Description :
 *                Data Item I062/080	Track Status
 */

#include "TrackStatus.h"

TrackStatus::TrackStatus() {
	// TODO Auto-generated constructor stub
	Clear();
}

TrackStatus::~TrackStatus() {
	// TODO Auto-generated destructor stub
}

void TrackStatus::Clear()
{
	mon = 0x00;			// = 0 Multisensor track
					// = 1 Monosensor track
	spi = 0x00;			// = 0 default value
					// = 1 SPI present in the last report received from a sensor capable of
	                //     decoding this data
	mrh = 0x00;			// Most Reliable Height
					// = 0 Barometric altitude (Mode C) more reliable
					// = 1 Geometric altitude more reliable
	src = 0x00;			// Source of calculated track altitude for I062/130
					// = 000 no source
					// = 001 GNSS
					// = 010 3D radar
					// = 011 triangulation
					// = 100 height from coverage
					// = 101 speed look-up table
					// = 110 default height
					// = 111 multilateration
	cnf = 0x00;			// = 0 Confirmed track
					// = 1 Tentative track
	sim = 0x00;			// = 0 Actual track
					// = 1 Simulated track
	tse = 0x00;			// = 0 default value
					// = 1 last message transmitted to the user for the track
	tsb = 0x00;			// = 0 default value
					// = 1 first message transmitted to the user for the track
	fpc = 0x00;			// = 0 Not flight-plan correlated
					// = 1 Flight plan correlated
	aff = 0x00;			// = 0 default value
					// = 1 ADS-B data inconsistent with other surveillance information
	stp = 0x00;			// = 0 default value
					// = 1 Slave track promotion
	kos = 0x00;			// = 0 Complementary service used
					// = 1 Background service used
	ama = 0x00;			// = 0 track not resulting from amalgamation process
					// = 1 track resulting from amalgamation process
	md4 = 0x00;			// = 00 No Mode 4 interrogation
					// = 01 Friendly target
					// = 10 Unknown target
					// = 11 No reply
	me = 0x00;			// = 0 default value
					// = 1 Military Emergency present in the last report receved from a sensor
					//     capable of decoding this data
	mi = 0x00;			// = 0 default value
					// = 1 Military Identification present in the last report received from a sensor
					//     capable of decoding this data
	md5 = 0x00;			// = 00 No Mode 5 interrogation
					// = 01 Friendly target
					// = 10 Unknown target
					// = 11 No reply
	cst = 0x00;			// = 0 Default value
					// = 1 Age of the last received track update is higher than system dependent threshold(coasting)
	psr = 0x00;			// = 0 Default value
					// = 1 Age of the last received PSR track update is higher than system dependent threshold
	ssr = 0x00;			// = 0 Default value
					// = 1 Age of the last received SSR track update is higher than system dependent threshold
	mds = 0x00;			// = 0 Default value
					// = 1 Age of the last received Mode S track update is higher than system dependent threshold
	ads = 0x00;			// = 0 Default value
					// = 1 Age of the last received ADS-B track update is higher than system dependent threshold
	suc = 0x00;			// = 0 default value
					// = 1 Spcial Used Code (Mode A codes to be defined in the system to mark a track
					//     with special interest)
	aac = 0x00;			// = 0 Default value
					// = 1 Assigned Mode A Code Conflict (same discrete Mode A Code assigned to another track)


	sds = 0x00;			// Surveillance Data Status
					// 00 Combined
					// 01 Co-operative only
					// 10 Non-Cooperative only
					// 11 Not defined
	// Note - Bits 6/4 (EM) : other than sufield #11 of data item I062/380, these bits allow the SDPS
	//        to set the emergency indication as derived from other sources than ADS-B(e.g. based on
	//        the Mode 3/A code).
	ems = 0x00;			// Emergency Status Indication
					// = 0 No emergency
					// = 1 General emergency
					// = 2 Lifeguard / medical
					// = 3 Minimum fuel
					// = 4 No communications
					// = 5 Unlawful interference
					// = 6 "Downed" Aircraft
					// = 7 Undefined
}
