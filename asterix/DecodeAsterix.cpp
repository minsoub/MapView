/*
 * DecodeAsterix.cpp
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 */
#include <QFile>
#include "DecodeAsterix.h"

DecodeAsterix::DecodeAsterix() {
	// TODO Auto-generated constructor stub

}

DecodeAsterix::~DecodeAsterix() {
	// TODO Auto-generated destructor stub
}

void DecodeAsterix::GetPacket(CBuffer& rBuffer)
{
	index = rBuffer.GetIndex();

	rBuffer.ReadU8(&cat);


	qDebug () << QString("CAT : %1").arg(cat);

	if (cat == 4) {	// Category - 004
		cat004.Clear();
		cat004.BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
		cat004.GetPacket(rBuffer);
	}else if(cat == 62) {   // Category - 062 System track
		cat062.Clear();
		cat062.BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
		cat062.GetPacket(rBuffer);
		//qDebug() << cat062.toString();
	}else if(cat == 21) {   // Category - 021 ADSB
		cat021.Clear();
		cat021.BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
		cat021.GetPacket(rBuffer);
		//qDebug() << cat021.toString();
	}else {
		qDebug() << "Not found category...";
	}
}

QString DecodeAsterix::toString() {
	if (cat == 4) {
		return cat004.toString();
	}else if(cat == 62) {
		return cat062.toString();
	}else if(cat == 21) {
		return cat021.toString();
	}
}
