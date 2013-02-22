/*
 * CTrackTime.cpp
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 */

#include "CTrackTime.h"

F64 DeltaTimeSec(const CTrackTime& crTime1, const CTrackTime& crTime0)
{
	F64 f64DeltaSeconds = difftime(crTime1.m_tv.tv_sec, crTime0.m_tv.tv_sec);
	S32 s32Usec1 = crTime1.m_tv.tv_usec;
	S32 s32Usec0 = crTime0.m_tv.tv_usec;

	f64DeltaSeconds += 0.000001 * (s32Usec1 - s32Usec0);

	return f64DeltaSeconds;
}

CTrackTime::CTrackTime() {
	// TODO Auto-generated constructor stub
	ZeroTime();
}

CTrackTime::CTrackTime(timeval tv)
{
	m_tv.tv_sec = tv.tv_sec;
	m_tv.tv_usec = tv.tv_usec;
}

CTrackTime::CTrackTime(time_t tt)
{
	m_tv.tv_sec = tt;
	m_tv.tv_usec = 0;
}

CTrackTime::CTrackTime(tm tmIn)
{
	m_tv.tv_sec = mktime(&tmIn);
	m_tv.tv_usec = 0;
}

CTrackTime::CTrackTime(const CTrackTime& crut)
{
	m_tv.tv_sec = crut.m_tv.tv_sec;
	m_tv.tv_usec = crut.m_tv.tv_usec;
}

CTrackTime::~CTrackTime() {
	// TODO Auto-generated destructor stub
}

/**
 * return number of seconds since midnight of Jan 1 1970
 */
S64 CTrackTime::GetAsMS() const
{
	S64 s64Res = m_tv.tv_sec * (S64)1000 + (S64)(m_tv.tv_usec / 1000L);
	return s64Res;
}

time_t CTrackTime::GetTimeT() const
{
	return m_tv.tv_sec;
}

U64 CTrackTime::GetSec() const
{
	return (U64)(m_tv.tv_sec);
}

U64 CTrackTime::GetUSec() const
{
	return (U64)(m_tv.tv_usec);
}

BOOL CTrackTime::IsZero() const
{
	if (m_tv.tv_sec != 0)
	{
		return FALSE;
	}
	if (m_tv.tv_usec != 0)
	{
		return FALSE;
	}
	return TRUE;
}

S64 CTrackTime::GetAsUSec() const
{
	S64 s64Res = m_tv.tv_sec * (S64)1000000 + (S64)m_tv.tv_usec;

	return s64Res;
}

BOOL CTrackTime::SetFromUSec(S64 s64USec)
{
	if (s64USec < 0)
	{
		return FALSE;
	}

	m_tv.tv_sec = (time_t)(s64USec / (S64)1000000);

	return TRUE;
}

BOOL CTrackTime::AddMS(S64 s64MS)
{
	S64 s64USec = GetAsUSec();
	s64USec += s64MS * (S64)1000;
	BOOL bRes = SetFromUSec(s64USec);

	return bRes;
}

BOOL CTrackTime::SubMS(S64 s64MS)
{
	S64 s64USec = GetAsUSec();
	s64USec -= s64MS * (S64)1000;
	BOOL bRes = SetFromUSec(s64USec);

	return bRes;
}
/**
 * ������ �ð��� �����´�.
 */
void CTrackTime::GetSysTime(void)
{
	gettimeofday(&m_tv, NULL);
}

void CTrackTime::ZeroTime(void)
{
	m_tv.tv_sec = 0;
	m_tv.tv_usec = 0;
}

const CTrackTime& CTrackTime::operator =(const CTrackTime& utIn)
{
	m_tv.tv_sec = utIn.m_tv.tv_sec;
	m_tv.tv_usec = utIn.m_tv.tv_usec;

	return utIn;
}

const tm& CTrackTime::operator =(const tm& tmIn)
{
	struct tm tm1 = tmIn;
	m_tv.tv_sec = mktime(&tm1);
	m_tv.tv_usec = 0;

	return tmIn;
}

const S64& CTrackTime::operator =(const S64& s64In)
{
	SetFromUSec(s64In);

	return s64In;
}

BOOL CTrackTime::operator ==(const CTrackTime& utIn)
{
	if ((m_tv.tv_sec == utIn.m_tv.tv_sec) && (m_tv.tv_usec == utIn.m_tv.tv_usec))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CTrackTime::operator !=(const CTrackTime& utIn)
{
	if ((m_tv.tv_sec != utIn.m_tv.tv_sec) || (m_tv.tv_usec != utIn.m_tv.tv_usec))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CTrackTime::operator <(const CTrackTime& utIn)
{
	return timercmp(&m_tv, &utIn.m_tv, <);
}

BOOL CTrackTime::operator >(const CTrackTime& utIn)
{
	return timercmp(&m_tv, &utIn.m_tv, >);
}

BOOL CTrackTime::operator <=(const CTrackTime& utIn)
{
	return timercmp(&m_tv, &utIn.m_tv, >);
}

BOOL CTrackTime::operator >=(const CTrackTime& utIn)
{
	return timercmp(&m_tv, &utIn.m_tv, <);
}

/**
 * Convert time_t value to string
 * Converts the time_t object pointed by timer to a C string containing a human-readable version of the corresponding local time and date.
 * The returned string has the following format:
 * Www Mmm dd hh:mm:ss yyyy
 * Where Www is the weekday, Mmm the month in letters, dd the day of the month, hh:mm:ss the time, and yyyy the year.
 * The string is followed by a new-line character ('\n') and the terminating null-character.
 * This function is equivalent to: asctime(localtime(timer)).
 *
 */
S8* CTrackTime::GetStrTime() const
{
	return (ctime(&m_tv.tv_sec));
}

QString CTrackTime::toString()
{
	S8 tmBuf[64], buf[64];

	time_t nowtime;
	struct tm *nowtm;
	nowtime = m_tv.tv_sec;
	nowtm = localtime(&nowtime);

	strftime(tmBuf, sizeof tmBuf, "%Y-%m-%d %H:%M:%S", nowtm);
	sprintf(buf, "%s", tmBuf);

	//printf("%s", GetStrTime());


	buf[19] = '\0';

	dateTime = QString("%1").arg(buf);

	//qDebug() << "toString : " << dateTime;

	return dateTime;

//	struct timeval tv;
//	time_t nowtime﻿;
//	struct tm *nowtm;
//	char tmbuf[64], buf[64];
//	gettimeofday(&tv, NULL);
//	nowtime = tv.tv_sec;
//	nowtm = localtime(&nowtime);
//
//	strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
//	snprintf(buf, sizeof buf, "%s.%06d", tmbuf, tv.tv_usec);


}
