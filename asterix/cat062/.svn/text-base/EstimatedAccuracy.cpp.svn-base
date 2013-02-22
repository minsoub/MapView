/*
 * EstimatedAccuracy.cpp
 *
 *  Created on: 2012. 4. 16.
 *      Author: JMS
 */

#include "EstimatedAccuracy.h"

EstimatedAccuracy::EstimatedAccuracy() {
	// TODO Auto-generated constructor stub
	Clear();

}

EstimatedAccuracy::~EstimatedAccuracy() {
	// TODO Auto-generated destructor stub
}

void EstimatedAccuracy::Clear()
{
	apcCHK = 0x00;					// Subfield #1 : Estimated Acccuracy Of Track Position (Cartesian)
	covCHK = 0x00;					// Subfield #2 : XY Covariance
	apwCHK = 0x00;					// Subfield #3 : Estimated Accuracy Of Track Position (WGS-84)
	agaCHK = 0x00;					// Subfield #4 : Estimated Accuracy Of Calculated Track Geometric Altitude
	abaCHK = 0x00;					// Subfield #5 : Estimated Accuracy of Calculated Track Barometric Altitude
	atvCHK = 0x00;					// Subfield #6 : Estimated Accuracy of Track Velocity (Cartesian)
	aaCHK = 0x00;					// Subfield #7 : Estimated Accuracy of Acceleration (Cartesian)
	arcCHK = 0x00;					// Subfield #8 : Estimated Accuracy of Rate of Climb/Descent

	// Subfield #1 : Estimated Accuracy of Track Position (Cartesian)
	apc_x = 0.0;					// Estimated accuracy of the calculated position of a target expressed
	apc_y = 0.0;					// in Cartesian co-ordinates.	LSB = 0.5m

	// Subfield #2 : XY covariance component
	// NOTES
	//		1. XY covariance component = sign { Cov(X, Y)} * sqrt{abs[Cov(X, Y)]}
	//		2. The maximum value for the (unsigned) XY covariance component is 16.383 km.
	cov = 0.0;					// XY Covariance Component in two's complement form.
								// LSB = 0.5 m

	// Subfield #3 : Estimated Accuracy Of Track Position (WGS-84)
	apw_lat = 0.0;				// APW - Estimated accuracy (i.e. standard deviation) of the calculated
								// position of a target expressed in WGS-84.
	apw_lon = 0.0;				// LSB = 180 / 2^25 degrees

	// Subfield #4 : Estimated Accuracy of Calculated Track Geometric Altitude.
	aga = 0.0;					// LSB = 6.25ft

	// Subfield #5 : Estimated Accuracy of Calculated Track Barometric Altitude.
	aba = 0.0;					// LSB = 1/4 FL

	// Subfield #6 : Estimated Accuracy of Track Velocity (Cartesian)
	atv_x = 0.0;					// LSB = 0.25 m/s
	atv_y = 0.0;

	// Subfield #7 : Estimated Accuracy of Acceleration (Cartesian)
	aa_x = 0.0;					// LSB = 0.25 m/s^2
	aa_y = 0.0;

	// Subfield #8 : Estimated Accuracy of Rate of Clibm/Descent
	arc = 0.0;					// LSB = 6.25 feet/minute
}
