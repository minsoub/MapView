/*
 * Cat021.h
 *
 *  Created on: 2012. 5. 11.
 *      Author: JMS
 *  Reference :
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 21
 *              ADS-B Messages
 */

#ifndef CAT021_H_
#define CAT021_H_

#include <QtCore>

#include "../lib/CBuffer.h"
#include "../lib/CTrackTime.h"
#include "../lib/AsterixLib.h"
#include "ADSBCls.h"
#include "TrajectoryIntent.h"

class Cat021 : public AsterixLib {
public:
	Cat021();
	~Cat021();

	void Clear();
	void GetPacket(CBuffer& rBuffer);
	void BufferPrint(CBuffer& rBuffer, int s, int end, QString item);
	QString getAccurDt() {
		return QString("%1").arg(adsb.timeStamp.toString());
	}
	QString getCallsign();
	double  getLatitude();
	double  getLongitude();
	double  getSpeed();
	double  getHeading();
	double  getAltitude();
private:
	ADSBCls adsb;

	BOOL FSPec(CBuffer& rBuffer);
	void I021_010(CBuffer& rBuffer);			// Data Source Identification
	void I021_020(CBuffer& rBuffer);			// Emitter Category
	void I021_030(CBuffer& rBuffer);			// Time of Day
	void I021_032(CBuffer& rBuffer);			// Time of Day Accuracy
	void I021_040(CBuffer& rBuffer);			// Target Report Descriptor
	void I021_080(CBuffer& rBuffer);			// Target Address
	void I021_090(CBuffer& rBuffer);			// Figure of Merit
	void I021_095(CBuffer& rBuffer);			// Velocity Accuracy
	void I021_110(CBuffer& rBuffer);			// Trajectory Intent
	void I021_130(CBuffer& rBuffer);			// Position in WGS-84 co-ordinates
	void I021_140(CBuffer& rBuffer);			// Geometric Altitude
	void I021_145(CBuffer& rBuffer);			// Flight Level
	void I021_146(CBuffer& rBuffer);			// Intermediate State Selected Altitude
	void I021_148(CBuffer& rBuffer);			// Final State Selected Altitude
	void I021_150(CBuffer& rBuffer);			// Air Speed
	void I021_151(CBuffer& rBuffer);			// True Air Speed
	void I021_152(CBuffer& rBuffer);			// Magnetic Heading
	void I021_155(CBuffer& rBuffer);			// Barometric Vertical Rate
	void I021_157(CBuffer& rBuffer);			// Geometric Vertical Rate
	void I021_160(CBuffer& rBuffer);			// Ground Vector
	void I021_165(CBuffer& rBuffer);			// Rate of Turn
	void I021_170(CBuffer& rBuffer);			// Target Identification
	void I021_200(CBuffer& rBuffer);			// Target Status
	void I021_210(CBuffer& rBuffer);			// Link Technology Indicator
	void I021_220(CBuffer& rBuffer);			// Met Report
	void I021_230(CBuffer& rBuffer);			// Roll Angle


};

#endif /* CAT021_H_ */
