/*
 * CTrackTime.h
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 */

#ifndef CTRACKTIME_H_
#define CTRACKTIME_H_

#include <sys/time.h>
#include <time.h>
#include <QString>
#include <QtCore>
#include "../lib/BaseTypes.h"

class CTrackTime {
public:
	CTrackTime();
	CTrackTime(timeval tv);
	CTrackTime(time_t tt);
	CTrackTime(tm tmIn);
	CTrackTime(const CTrackTime& crut);
	~CTrackTime();

	friend F64 DeltaTimeSec(const CTrackTime& crTime1, const CTrackTime& crTime0);

protected:
	timeval m_tv;
public:
	S64 GetAsMS() const;
	time_t GetTimeT() const;
	S64 GetAsUSec() const;
	BOOL SetFromUSec(S64 s64USec);
	U64 GetSec() const;
	U64 GetUSec() const;
	BOOL IsZero() const;
	BOOL AddMS(S64 s64MS);
	BOOL SubMS(S64 s64MS);
	void GetSysTime();
	void ZeroTime();

	const CTrackTime& operator =(const CTrackTime& utIn);
	const tm& operator =(const tm& tmIn);
	const S64& operator =(const S64& s64In);
	BOOL operator ==(const CTrackTime& utIn);
	BOOL operator !=(const CTrackTime& utIn);
	BOOL operator <(const CTrackTime& utIn);
	BOOL operator >(const CTrackTime& utIn);
	BOOL operator <=(const CTrackTime& utIn);
	BOOL operator >=(const CTrackTime& utIn);

	S8* GetStrTime() const;
	QString toString();
private:
	QString dateTime;
};

#endif /* CTRACKTIME_H_ */
