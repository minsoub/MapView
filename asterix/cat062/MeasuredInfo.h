/*
 * MeasuredInfo.h
 *
 *  Created on: 2012. 4. 13.
 *      Author: JMS
 *  Description:
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 *              - Data Item I062/340, Measured Information.
 *              - This class describes Data Item I062/340.
 *
 *              All measured data related to the last report used to update the track.
 */

#ifndef MEASUREDINFO_H_
#define MEASUREDINFO_H_
#include <QString>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"

class MeasuredInfo {
public:
	MeasuredInfo();
	~MeasuredInfo();

	void Clear();

	U8 sidCHK;					// Subfield #1 : Sensor Identification
	U8 posCHK;					// Subfield #2 : Measured Position
	U8 heiCHK;					// Subfield #3 : Measured 3-D Height
	U8 mdcCHK;					// Subfield #4 : Last Measured Mode C code
	U8 mdaCHK;					// Subfield #5 : Last Measured Mode 3/A code
	U8 typCHK;					// Subfield #6 : Report Type

	// Subfield #1 : Sensor Identification
	int sac;					// SAC - System Area Code
	int sic;					// SIC - System Identification Code

	// Subfield #2 : Measured Position
	// Note - The measured position is :
	//			1. In case of a plot, the measured bias-corrected polar co-ordinates;
	//			2. In case of a sensor local track, the measured bias-corrected
	//			   polar co-ordinates of the plot associated to the track;
	//			3. In case of a local track without detection, the extrapolated bias-
	//			   corrected polar co-ordinates.
	F64 rho;					// RHO - Measured distance (LSB 1/256 NM)
	F64 theta;					// THETA - Measured azimuth (LSB 360/2^16 = 0.0055)

	// Subfield #3 : Measured 3-D Height
	F64 height;					// Height (LSB 25 feet)

	// Subfield #4 : Last Measured Mode C Code
	U8 v;						// = 0 Code validated
								// = 1 Code not validated
	U8 g;						// = 0 Default
								// = 1 Garbled code
	F64 modeC;					// Last Measured Mode C Code (LSB = 1/4 FL)

	// Subfield #5 : Last Measured Mode 3/A Code
	// Note - Smoothed MODE 3/A data (L = 1) will be used in case of absence of
	//		  MODE 3/A code information in the plot or in case of difference
	//		  between plot and sensor local track MODE 3/A code information.
	U8 v2;						// = 0 Code validated
								// = 1 Code not validated
	U8 g2;						// = 0 Default
								// = 1 Garbled code
	U8 l;						// = 0 MODE 3/A code as derived from the reply of the transponder
								// = 1 Smoothed MODE 3/A code as provided by a sensor local tracker.
	QString mode3A;				// Mode 3/A reply under the form of 4 digits in octal representation.

	// Subfield #6 : Report Type
	U8 typ;						// = 000 No detection
								// = 001(1) Single PSR detection
								// = 010(2) Single SSR detection
								// = 011(3) SSR + PSR detection
								// = 100(4) Single ModeS All-Call
								// = 101(5) Single ModeS Roll-Call
								// = 110(6) ModeS All-Call + PSR
								// = 111(7) ModeS Roll-Call + PSR
	U8 sim;						// = 0 Actual target report
								// = 1 Simulated target report
	U8 rab;						// = 0 Report from target transponder
								// = 1 Report from field monitor (fixed transponder)
	U8 tst;						// = 0 Real target report
								// = 1 Test target report
};

#endif /* MEASUREDINFO_H_ */
