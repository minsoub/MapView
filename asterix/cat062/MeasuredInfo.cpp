/*
 * MeasuredInfo.cpp
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

#include "MeasuredInfo.h"

MeasuredInfo::MeasuredInfo() {
	// TODO Auto-generated constructor stub
	Clear();
}

MeasuredInfo::~MeasuredInfo() {
	// TODO Auto-generated destructor stub
}

void MeasuredInfo::Clear()
{
	sidCHK = 0x00;					// Subfield #1 : Sensor Identification
	posCHK = 0x00;					// Subfield #2 : Measured Position
	heiCHK = 0x00;					// Subfield #3 : Measured 3-D Height
	mdcCHK = 0x00;					// Subfield #4 : Last Measured Mode C code
	mdaCHK = 0x00;					// Subfield #5 : Last Measured Mode 3/A code
	typCHK = 0x00;					// Subfield #6 : Report Type

	// Subfield #1 : Sensor Identification
	sac = 0;					// SAC - System Area Code
	sic = 0;					// SIC - System Identification Code

	// Subfield #2 : Measured Position
	// Note - The measured position is :
	//			1. In case of a plot, the measured bias-corrected polar co-ordinates;
	//			2. In case of a sensor local track, the measured bias-corrected
	//			   polar co-ordinates of the plot associated to the track;
	//			3. In case of a local track without detection, the extrapolated bias-
	//			   corrected polar co-ordinates.
	rho = 0.0;					// RHO - Measured distance (LSB 1/256 NM)
	theta = 0.0;					// THETA - Measured azimuth (LSB 360/2^16 = 0.0055)

	// Subfield #3 : Measured 3-D Height
	height = 0.0;					// Height (LSB 25 feet)

	// Subfield #4 : Last Measured Mode C Code
	v = 0x00;						// = 0 Code validated
								// = 1 Code not validated
	g = 0x00;						// = 0 Default
								// = 1 Garbled code
	modeC = 0.0;					// Last Measured Mode C Code (LSB = 1/4 FL)

	// Subfield #5 : Last Measured Mode 3/A Code
	// Note - Smoothed MODE 3/A data (L = 1) will be used in case of absence of
	//		  MODE 3/A code information in the plot or in case of difference
	//		  between plot and sensor local track MODE 3/A code information.
	v2 = 0x00;						// = 0 Code validated
								// = 1 Code not validated
	g2 = 0x00;						// = 0 Default
								// = 1 Garbled code
	l = 0x00;						// = 0 MODE 3/A code as derived from the reply of the transponder
								// = 1 Smoothed MODE 3/A code as provided by a sensor local tracker.
	mode3A = "";				// Mode 3/A reply under the form of 4 digits in octal representation.

	// Subfield #6 : Report Type
	typ = 0x00;						// = 000 No detection
								// = 001(1) Single PSR detection
								// = 010(2) Single SSR detection
								// = 011(3) SSR + PSR detection
								// = 100(4) Single ModeS All-Call
								// = 101(5) Single ModeS Roll-Call
								// = 110(6) ModeS All-Call + PSR
								// = 111(7) ModeS Roll-Call + PSR
	sim = 0x00;						// = 0 Actual target report
								// = 1 Simulated target report
	rab = 0x00;						// = 0 Report from target transponder
								// = 1 Report from field monitor (fixed transponder)
	tst = 0x00;						// = 0 Real target report
								// = 1 Test target report
}
