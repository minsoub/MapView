/*
 * MsbBound.h
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */

#ifndef MSBBOUND_H_
#define MSBBOUND_H_

#include <QPointF>
#include "MapDefine.h"

class MsgBound {
private:
	AMsb _msb;
	QPointF _mousePoint;

public:
	MsgBound() { };

	QString toString() const {
		return (QString("_msb:(%1, %2), (%3, %4)")
				.arg(_msb.latlon1.lat).arg(_msb.latlon1.lon)
				.arg(_msb.latlon2.lat).arg(_msb.latlon2.lon));
	}
};
#endif /* MSBBOUND_H_ */
