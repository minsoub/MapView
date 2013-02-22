/*
 * ModeSMBData.h
 *
 *  Created on: 2012. 4. 16.
 *      Author: JMS
 *
 *  Description :
 *  	 Subfield #25 : MODE S MB DATA
 *	     Format : Repetitive starting with an one-octet Field Repetition Indicator (REP)
 *				followed by at least one BDS report comprising one seven octet BDS
 *				register and one octet BDS code.
 */

#ifndef MODESMBDATA_H_
#define MODESMBDATA_H_
#include <QString>
#include "../lib/BaseTypes.h"

class ModeSMBData {
public:
	ModeSMBData();
	~ModeSMBData();

	// NOTES - Only DAPs that can not be encoded into other subfields of this item
	//			should be sent using subfield #25
	QString msgMbData;			// 56 bit message conveying Mode S B message data
	U8 bds1;					// Comm B data Buffer Store 1 Address
	U8 bds2;					// Comm B data Buffer Store 2 Address
};

#endif /* MODESMBDATA_H_ */
