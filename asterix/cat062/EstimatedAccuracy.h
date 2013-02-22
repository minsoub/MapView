/*
 * EstimatedAccuracy.h
 *
 *  Created on: 2012. 4. 16.
 *      Author: JMS
 *  Description:
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 *              - Data Item I062/500, Estimated Accuracies.
 *              - This class describes Data Item I062/500.
 *              - Overview of all important accuracies
 */

#ifndef ESTIMATEDACCURACY_H_
#define ESTIMATEDACCURACY_H_

#include <QString>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"

class EstimatedAccuracy {
public:
	EstimatedAccuracy();
	~EstimatedAccuracy();

	void Clear();

	U8 apcCHK;					// Subfield #1 : Estimated Acccuracy Of Track Position (Cartesian)
	U8 covCHK;					// Subfield #2 : XY Covariance
	U8 apwCHK;					// Subfield #3 : Estimated Accuracy Of Track Position (WGS-84)
	U8 agaCHK;					// Subfield #4 : Estimated Accuracy Of Calculated Track Geometric Altitude
	U8 abaCHK;					// Subfield #5 : Estimated Accuracy of Calculated Track Barometric Altitude
	U8 atvCHK;					// Subfield #6 : Estimated Accuracy of Track Velocity (Cartesian)
	U8 aaCHK;					// Subfield #7 : Estimated Accuracy of Acceleration (Cartesian)
	U8 arcCHK;					// Subfield #8 : Estimated Accuracy of Rate of Climb/Descent

	// Subfield #1 : Estimated Accuracy of Track Position (Cartesian)
	F64 apc_x;					// Estimated accuracy of the calculated position of a target expressed
	F64 apc_y;					// in Cartesian co-ordinates.	LSB = 0.5m

	// Subfield #2 : XY covariance component
	// NOTES
	//		1. XY covariance component = sign { Cov(X, Y)} * sqrt{abs[Cov(X, Y)]}
	//		2. The maximum value for the (unsigned) XY covariance component is 16.383 km.
	F64 cov;					// XY Covariance Component in two's complement form.
								// LSB = 0.5 m

	// Subfield #3 : Estimated Accuracy Of Track Position (WGS-84)
	F64 apw_lat;				// APW - Estimated accuracy (i.e. standard deviation) of the calculated
								// position of a target expressed in WGS-84.
	F64 apw_lon;				// LSB = 180 / 2^25 degrees

	// Subfield #4 : Estimated Accuracy of Calculated Track Geometric Altitude.
	F64 aga;					// LSB = 6.25ft

	// Subfield #5 : Estimated Accuracy of Calculated Track Barometric Altitude.
	F64 aba;					// LSB = 1/4 FL

	// Subfield #6 : Estimated Accuracy of Track Velocity (Cartesian)
	F64 atv_x;					// LSB = 0.25 m/s
	F64 atv_y;

	// Subfield #7 : Estimated Accuracy of Acceleration (Cartesian)
	F64 aa_x;					// LSB = 0.25 m/s^2
	F64 aa_y;

	// Subfield #8 : Estimated Accuracy of Rate of Clibm/Descent
	F64 arc;					// LSB = 6.25 feet/minute

};

#endif /* ESTIMATEDACCURACY_H_ */
