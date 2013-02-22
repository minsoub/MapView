/*
 * Cat004.h
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 *  Reference :
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 4
 *              Safety Net Messages
 */

#ifndef CAT004_H_
#define CAT004_H_

#include <QtCore>

#include "../lib/CBuffer.h"
#include "../lib/CTrackTime.h"
#include "../lib/AsterixLib.h"
#include "SafetyNets.h"

class Cat004 : public AsterixLib {
public:
	Cat004();
	~Cat004();
	void Clear();
	void GetPacket(CBuffer& rBuffer);
	void BufferPrint(CBuffer& rBuffer, int s, int end, QString item);
	SafetyNets getSafetyNets() { return safetyNets; }
private:
	SafetyNets safetyNets;

	BOOL FSPec(CBuffer& rBuffer);

	void I004_000(CBuffer& rBuffer);		// Message Type
	void I004_010(CBuffer& rBuffer);		// Data Source Identifier
	void I004_015(CBuffer& rBuffer);		// SDPS Identifier
	void I004_020(CBuffer& rBuffer);		// Time of Message
	void I004_030(CBuffer& rBuffer);		// Track Number 1
	void I004_035(CBuffer& rBuffer);		// Track Number 2
	void I004_040(CBuffer& rBuffer);		// Alert Identifer
	void I004_045(CBuffer& rBuffer);		// Alert Status
	void I004_060(CBuffer& rBuffer);		// Safety Net Function & System Status
	void I004_070(CBuffer& rBuffer);		// Conflict Timing and Separation
	void I004_074(CBuffer& rBuffer);		// Longitudinal Deviation
	void I004_075(CBuffer& rBuffer);		// Transversal Distance Deviation
	void I004_076(CBuffer& rBuffer);		// Vertical Deviation
	void I004_100(CBuffer& rBuffer);		// Area Definitions
	void I004_110(CBuffer& rBuffer);		// FDPS Sector Control Positions
	void I004_120(CBuffer& rBuffer);		// Conflict Characteristics
	void I004_170(CBuffer& rBuffer);		// Aircraft Identification & Characteristics 1
	void I004_171(CBuffer& rBuffer);		// Aircraft Identification & Characteristics 2

};

#endif /* CAT004_H_ */
