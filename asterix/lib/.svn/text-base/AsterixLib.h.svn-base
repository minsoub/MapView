/*
 * AsterixLib.h
 *
 *  Created on: 2012. 4. 20.
 *      Author: JMS
 */

#ifndef ASTERIXLIB_H_
#define ASTERIXLIB_H_

#include <QString>
#include "GlobalConsts.h"
#include "BaseTypes.h"
#include "CBuffer.h"
#include "CTrackTime.h"

class AsterixLib {
public:
	AsterixLib();
	~AsterixLib();

	U8 CharacterValue(U8 bb);
	QString searchItem(int idx);
	QString searchItem004(int idx);
	QString searchItem021(int idx);
	void Clear();
	QString toString();

protected:
	int index;
	U8 DEBUG;
	QString tmpBuf;
	bool m_bFSPEC[MAX_FSPEC];
	CTrackTime m_TimeOfPacket;
};

#endif /* ASTERIXLIB_H_ */
