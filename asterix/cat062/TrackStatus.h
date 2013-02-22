/*
 * TrackStatus.h
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 *  Description :
 *                Data Item I062/080	Track Status
 */

#ifndef TRACKSTATUS_H_
#define TRACKSTATUS_H_

#include <QString>
#include "../lib/BaseTypes.h"

class TrackStatus {
public:
	TrackStatus();
	~TrackStatus();

	void Clear();

	U8 mon;			// = 0 Multisensor track
					// = 1 Monosensor track
	U8 spi;			// = 0 default value
					// = 1 SPI present in the last report received from a sensor capable of
	                //     decoding this data
	U8 mrh;			// Most Reliable Height
					// = 0 Barometric altitude (Mode C) more reliable
					// = 1 Geometric altitude more reliable
	U8 src;			// Source of calculated track altitude for I062/130
					// = 000 no source
					// = 001 GNSS
					// = 010 3D radar
					// = 011 triangulation
					// = 100 height from coverage
					// = 101 speed look-up table
					// = 110 default height
					// = 111 multilateration
	U8 cnf;			// = 0 Confirmed track
					// = 1 Tentative track
	U8 sim;			// = 0 Actual track
					// = 1 Simulated track
	U8 tse;			// = 0 default value
					// = 1 last message transmitted to the user for the track
	U8 tsb;			// = 0 default value
					// = 1 first message transmitted to the user for the track
	U8 fpc;			// = 0 Not flight-plan correlated
					// = 1 Flight plan correlated
	U8 aff;			// = 0 default value
					// = 1 ADS-B data inconsistent with other surveillance information
	U8 stp;			// = 0 default value
					// = 1 Slave track promotion
	U8 kos;			// = 0 Complementary service used
					// = 1 Background service used
	U8 ama;			// = 0 track not resulting from amalgamation process
					// = 1 track resulting from amalgamation process
	U8 md4;			// = 00 No Mode 4 interrogation
					// = 01 Friendly target
					// = 10 Unknown target
					// = 11 No reply
	U8 me;			// = 0 default value
					// = 1 Military Emergency present in the last report receved from a sensor
					//     capable of decoding this data
	U8 mi;			// = 0 default value
					// = 1 Military Identification present in the last report received from a sensor
					//     capable of decoding this data
	U8 md5;			// = 00 No Mode 5 interrogation
					// = 01 Friendly target
					// = 10 Unknown target
					// = 11 No reply
	U8 cst;			// = 0 Default value
					// = 1 Age of the last received track update is higher than system dependent threshold(coasting)
	U8 psr;			// = 0 Default value
					// = 1 Age of the last received PSR track update is higher than system dependent threshold
	U8 ssr;			// = 0 Default value
					// = 1 Age of the last received SSR track update is higher than system dependent threshold
	U8 mds;			// = 0 Default value
					// = 1 Age of the last received Mode S track update is higher than system dependent threshold
	U8 ads;			// = 0 Default value
					// = 1 Age of the last received ADS-B track update is higher than system dependent threshold
	U8 suc;			// = 0 default value
					// = 1 Spcial Used Code (Mode A codes to be defined in the system to mark a track
					//     with special interest)
	U8 aac;			// = 0 Default value
					// = 1 Assigned Mode A Code Conflict (same discrete Mode A Code assigned to another track)


	U8 sds;			// Surveillance Data Status
					// 00 Combined
					// 01 Co-operative only
					// 10 Non-Cooperative only
					// 11 Not defined
	// Note - Bits 6/4 (EM) : other than sufield #11 of data item I062/380, these bits allow the SDPS
	//        to set the emergency indication as derived from other sources than ADS-B(e.g. based on
	//        the Mode 3/A code).
	U8 ems;			// Emergency Status Indication
					// = 0 No emergency
					// = 1 General emergency
					// = 2 Lifeguard / medical
					// = 3 Minimum fuel
					// = 4 No communications
					// = 5 Unlawful interference
					// = 6 "Downed" Aircraft
					// = 7 Undefined

};

#endif /* TRACKSTATUS_H_ */
