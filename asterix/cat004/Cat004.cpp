/*
 * Cat004.cpp
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 *  Reference :
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 4
 *              Safety Net Messages
 */

#include "Cat004.h"

Cat004::Cat004() {
	// TODO Auto-generated constructor stub
}

Cat004::~Cat004() {
	// TODO Auto-generated destructor stub
}

void Cat004::Clear()
{
	tmpBuf = "";

	for (int i=0; i<MAX_FSPEC; i++) {
		m_bFSPEC[i] = FALSE;
	}

	// SafetyNets data clear..
	safetyNets.Clear();
	index = 0;
}

void Cat004::BufferPrint(CBuffer& rBuffer, int s, int end, QString item)
{
	QString tmp, str;

	if (s == 0)
		str.append("Cat No : ");
	else if(s == 1)
		str.append("Length : ");
	else if(s == 3)
		str.append("FSPEC : ");
	else
		str.append("Item " + QString("%1").arg(item) + ":");

	if (s != 1) {
		for (; s < end; s++) {
			tmp.sprintf("%.2X ", rBuffer.GetPBuffer()[s]);
			str.append(tmp);
		}
	}else {
		for (; s < end; s++) {
			tmp.sprintf("%.2X ", rBuffer.GetPBuffer()[s]);
			str.append(tmp);
		}
	}

	qDebug() << str;
}

void Cat004::GetPacket(CBuffer& rBuffer)
{
	index = rBuffer.GetIndex();

	// Len - 2
	U16 u16Length = 0;
	rBuffer.ReadU16(&u16Length);

	S32 s32MaxIndex = rBuffer.GetIndex() + u16Length - 3;
	this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
	index = rBuffer.GetIndex();

	m_TimeOfPacket.GetSysTime();	// set current time

	Clear();		// Decoding category 004

	while (rBuffer.GetIndex() < s32MaxIndex)
	{
		if (!FSPec(rBuffer))
		{
			qDebug() << "SafetyNets FSPec Error is occured.............";
		}else {
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
			index = rBuffer.GetIndex();

			tmpBuf += "FSPec ................................\n";
			for (int i=1; i<48; i++) {
				if (i % 8 == 0) tmpBuf += "\n";
				tmpBuf += QString ("%1 = %2, ").arg(searchItem004(i)).arg(m_bFSPEC[i]);
			}
			tmpBuf += "\n";

			//qDebug() << tmpBuf;
		}

		/* I004/010 Data Source Identifer */
		if (m_bFSPEC[1]) {
			I004_010(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "010");
			index = rBuffer.GetIndex();
		}

		/* I004/000 Message Type  */
		if (m_bFSPEC[2]) {
			I004_000(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
			index = rBuffer.GetIndex();
		}

		/* I004/015 SDPS Identifier */
		if (m_bFSPEC[3]) {
			I004_015(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "015");
			index = rBuffer.GetIndex();
		}

		/* I004/020 Time of Message */
		if (m_bFSPEC[4]) {
			I004_020(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "020");
			index = rBuffer.GetIndex();
		}

		/* I004/040 Alert Identifier */
		if (m_bFSPEC[5]) {
			I004_040(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "040");
			index = rBuffer.GetIndex();
		}

		/* I004/045 Alert Status */
		if (m_bFSPEC[6]) {
			I004_045(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "045");
			index = rBuffer.GetIndex();
		}

		/* I004/060 Safety Net Function & System Status */
		if (m_bFSPEC[7]) {
			I004_060(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "060");
			index = rBuffer.GetIndex();
		}

		/* I004/030 Track Number 1 */
		if (m_bFSPEC[8]) {
			I004_030(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "030");
			index = rBuffer.GetIndex();
		}

		/* I004/170 Aircraft Identification & Characteristics 1 */
		if (m_bFSPEC[9]) {
			I004_170(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "170");
			index = rBuffer.GetIndex();
		}

		/* I004/120 Conflict Characteristics */
		if (m_bFSPEC[10]) {
			I004_120(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "120");
			index = rBuffer.GetIndex();
		}

		/* I004/070 Conflict Timing and Separation */
		if (m_bFSPEC[11]) {
			I004_070(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "070");
			index = rBuffer.GetIndex();
		}

		/* I004/076 Vertical Deviation */
		if (m_bFSPEC[12]) {
			I004_076(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "076");
			index = rBuffer.GetIndex();
		}

		/* I004/074 Longitudinal Deviation */
		if (m_bFSPEC[13]) {
			I004_074(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "074");
			index = rBuffer.GetIndex();
		}

		/* I004/075 Transversal Distance Deviation */
		if (m_bFSPEC[14]) {
			I004_075(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "075");
			index = rBuffer.GetIndex();
		}

		/* I004/100 Area Definitions */
		if (m_bFSPEC[15]) {
			I004_100(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "100");
			index = rBuffer.GetIndex();
		}

		/* I004/035 Track Number 2 */
		if (m_bFSPEC[16]) {
			I004_035(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "035");
			index = rBuffer.GetIndex();
		}

		/* I004/171 Aircraft Identification & Characteristics 2 */
		if (m_bFSPEC[17]) {
			I004_171(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "171");
			index = rBuffer.GetIndex();
		}

		/* I004/110 FDPS Sector Control Positions */
		if (m_bFSPEC[18]) {
			I004_110(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "110");
			index = rBuffer.GetIndex();
		}
	}
}

/**
 * Data Item I004/000, Message Type
 * Definition : This Data Item allows for a more convenient handling of the
 *              messages at the receiver side by further defining the tpe of
 *              transaction.
 * Format : One-octet fixed length Data Item
 * Message Type
 * 		001	Alive Message
 * 		002	Route Adherence Monitor Longitudinal Deviation
 * 		003	Route Adherence Monitor Heading Deviation
 * 		004 Minimum Safe Altitude Warning
 * 		005 Area Proximity Warning
 * 		006 Clearance Level Adherence Monitor
 * 		007 Short Term Conflict Alert
 * 		008 Approach Funnel Deviation Alert
 * 		009 RIMCAS Arrival / Landing Monitor (ALM)
 * 		010 RIMCAS Arrival / Departure Wrong Runway Alert(WRA)
 * 		011	RIMCAS Arrival / Departure Opposite Traffic Alert(OTA)
 * 		012 RIMCAS Departure Monitor (RDM)
 * 		013 RIMCAS Runway / Taxiway Crossing Monitor (RCM)
 * 		014 RIMCAS Taxiway Separation Monitor (TSM)
 * 		015 RIMCAS Unauthorized Taxiway Movement Monitor (UTMM)
 * 		016 RIMCAS Stop Bar Overrun Alert(SBOA)
 * 		017 End Of Conflict(EOC)
 * 		018	ACAS Resolution Advisory(ACASRA)
 * 		019 Near Term Conflict Alert(NTCA)
 */
void Cat004::I004_000(CBuffer& rBuffer)
{
	U8 u8m_type = 0x00;

	rBuffer.ReadU8(&u8m_type);

	safetyNets.messge_type = u8m_type;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/000 messge_type : %1 \n").arg(u8m_type);
	}
}

/**
 * Data Item I004/010	Data Source Identifier
 * Definition : Identification of the Safety Nets server sending the message.
 * Format : Two-octet fixed length Data Item.
 */
void Cat004::I004_010(CBuffer& rBuffer)
{
	U8 u8SAC = 0x00;
	U8 u8SIC = 0x00;

	rBuffer.ReadU8(&u8SAC);
	rBuffer.ReadU8(&u8SIC);

	safetyNets.sac = u8SAC;
	safetyNets.sic = u8SIC;

	// debug
	if (DEBUG)
	{
		//qDebug() << QString("SAC : %1, SIC : %2\n").arg(u8SAC).arg(u8SIC);
		tmpBuf += QString("Data Item I004/010 SAC : %1, SIC : %2\n").arg(u8SAC).arg(u8SIC);
	}
}

/**
 * Data Item I004/015	SDPS Identifier
 * Definition : Identification of the SDPS providing data to the safety nets
 *              server.
 * Format :     Repetitive Data item starting with one-octet Field Repetition
 *              Indicator (REP) followed by at least one SDPS Identifier.
 */
void Cat004::I004_015(CBuffer& rBuffer)
{
	U8 u8REP = 0;
	U8 u8SAC = 0;
	U8 u8SIC = 0;

	rBuffer.ReadU8(&u8REP);

	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/015 \n");
		tmpBuf += QString("      Rep cnt : %1 \n").arg(u8REP);
	}
	for (int i=0; i<u8REP; i++) {
		rBuffer.ReadU8(&u8SAC);
		rBuffer.ReadU8(&u8SIC);

		Tag sacsic;
		sacsic.sac = u8SAC;
		sacsic.sic = u8SIC;

		if (DEBUG)
		{
			tmpBuf += QString("        SAC : %1, SIC : %2 \n").arg(u8SAC).arg(u8SIC);
		}

		safetyNets.sdpsIdentifier.append(sacsic);
	}
}

/**
 * Data Item I004/020 Time of Message
 * Definition : Absolute time stamping of the message in the form of elapsed time
 *              since last midnight
 * Format     : Three-octet fixed length Data Item
 */
void Cat004::I004_020(CBuffer& rBuffer)
{
	U32 u32TimeOfDay = 0x00000000;
	rBuffer.ReadU24(&u32TimeOfDay);	// 3 byte read
	F64 f64TimeOfDay = (1.0 / 128) * u32TimeOfDay;

	S32 s32TimeOfDay = static_cast<S32>( f64TimeOfDay );		// Int part of time
	f64TimeOfDay -= s32TimeOfDay;								      // Frac part of time

	S32 s32H = 0x00000000;
	S32 s32M = 0x00000000;
	S32 s32S = 0x00000000;

	s32H = s32TimeOfDay / 3600;
	s32TimeOfDay -= s32H * 3600;

	s32M = s32TimeOfDay / 60;
	s32TimeOfDay -= s32M * 60;

	s32S = s32TimeOfDay;

	CTrackTime CurrentTime = m_TimeOfPacket;

	time_t t = CurrentTime.GetTimeT();
	struct tm tmCur = *gmtime(&t);	// Convert time_t to tm as UTC time
	struct tm tmTimeStamp = tmCur;
	tmTimeStamp.tm_hour = s32H;
	tmTimeStamp.tm_min  = s32M;
	tmTimeStamp.tm_sec  = s32S;

	CTrackTime TimeStamp(tmTimeStamp);
	TimeStamp.AddMS( static_cast<S64>( f64TimeOfDay * 1000 ) );

	S64 s64Delta = CurrentTime.GetAsMS() - TimeStamp.GetAsMS();

	if (s64Delta > 12 * 3600 * 1000)
	{
		TimeStamp.AddMS(24 * 3600 * 1000);
	}

	if (s64Delta < -12 * 3600 * 1000)
	{
		TimeStamp.SubMS(24 * 3600 * 1000);
	}

	safetyNets.timeStamp = TimeStamp;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/020 Time of Message : %1 \n").arg(safetyNets.timeStamp.toString());
	}
}

/**
 * Data Item I004/030	Track Number 1
 * Definition : Identification of a track number related to conflict
 * Format     : Two-octet fixed length Data Item.
 *
 * bits 16/1 (TRACK NUMBER) : 0 to 65535
 */
void Cat004::I004_030(CBuffer& rBuffer)
{
	U16 u16TrackNum = 0;

	rBuffer.ReadU16(&u16TrackNum);

	safetyNets.u16TrackNum1 = u16TrackNum;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/030 Track Number 1 : %1 \n").arg(safetyNets.u16TrackNum1);
	}
}

/**
 * Data Item I004/035	Track Number 2
 * Definition : Identification of a track number related to conflict
 * Format     : Two-octet fixed length Data Item.
 *
 * bits 16/1 (TRACK NUMBER) : 0 to 65535
 */
void Cat004::I004_035(CBuffer& rBuffer)
{
	U16 u16TrackNum = 0;

	rBuffer.ReadU16(&u16TrackNum);

	safetyNets.u16TrackNum2 = u16TrackNum;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/035 Track Number 2 : %1 \n").arg(safetyNets.u16TrackNum2);
	}
}

/**
 * Data Item I004/040	Alert Identifier
 * Definition : Identification of an alert (Alert number)
 * Format     : Two-octet fixed length Data Item
 *
 * bits 16/1 ( Alert Identifier ) : 0 to 65535
 */
void Cat004::I004_040(CBuffer& rBuffer)
{
	U16 u16AlertIdx = 0;

	rBuffer.ReadU16(&u16AlertIdx);

	safetyNets.u16AlertIdentifier = u16AlertIdx;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/040 Alert Identifier : %1 \n").arg(safetyNets.u16AlertIdentifier);
	}
}

/**
 * Data Item I004/045	Alert Status
 * Definition : Information concerning status of the alert
 * Format     : One-octet fixed length Data Item.
 *
 * bits-4/2 (STAT) Status of the alert
 */
void Cat004::I004_045(CBuffer& rBuffer)
{
	U8 u8AlertStatus = 0;

	//TODO: ���� �ʿ� - bits-4/2 ??
	rBuffer.ReadU8(&u8AlertStatus);

	safetyNets.u8AlertStatus = u8AlertStatus;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/045 Alert Status : %1 \n").arg(safetyNets.u8AlertStatus);
	}
}

/**
 * Data Item I004/060	Safety Net Function & System Status
 * Definition : Status of the Safety Nets functions handled by the system.
 * Format     : Variable length Data Item comprising a first part of one octet,
 *              followed by one-octet extends as necessary.
 */
void Cat004::I004_060(CBuffer& rBuffer)
{
	U8 u8Buf   = 0x00;
	U8 u8FX    = 0x00;
	U8 u8MRVA  = 0x00;
	U8 u8RAMLD = 0x00;
	U8 u8RAMHD = 0x00;
	U8 u8MSAW  = 0x00;
	U8 u8APW   = 0x00;
	U8 u8CLAM  = 0x00;
	U8 u8STCA  = 0x00;
	U8 u8AFDA  = 0x00;
	U8 u8RIMCA = 0x00;
	U8 u8ACASRA = 0x00;
	U8 u8NTCA   = 0x00;
	U8 u8DG     = 0x00;
	U8 u8OF     = 0x00;
	U8 u8OL     = 0x00;

	rBuffer.ReadU8(&u8Buf);

	u8MRVA  = ( u8Buf & 0x80 ) >> 7;
	u8RAMLD = ( u8Buf & 0x40 ) >> 6;
	u8RAMHD = ( u8Buf & 0x20 ) >> 5;
	u8MSAW  = ( u8Buf & 0x10 ) >> 4;
	u8APW   = ( u8Buf & 0x08 ) >> 3;
	u8CLAM  = ( u8Buf & 0x04 ) >> 2;
	u8STCA  = ( u8Buf & 0x02 ) >> 1;
	u8FX    =  u8Buf & 0x01;		// FX Field

	safetyNets.u8MRVA  = u8MRVA;
	safetyNets.u8RAMLD = u8RAMLD;
	safetyNets.u8RAMHD = u8RAMHD;
	safetyNets.u8MSAW  = u8MSAW;
	safetyNets.u8APW   = u8APW;
	safetyNets.u8CLAM  = u8CLAM;
	safetyNets.u8STCA  = u8STCA;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/060 Safety Net Function & System Status : \n");
	}

	if (DEBUG) {
		tmpBuf += QString("  MRVA : %1, RAMLD : %2, RAMHD : %3, MSAW : %4, APW : %5, CLAM : %6, STCA : %7 \n").
				arg(u8MRVA).arg(u8RAMLD).arg(u8RAMHD).arg(u8MSAW).arg(u8APW).arg(u8CLAM).arg(u8STCA);
	}

	if (u8FX) {
		rBuffer.ReadU8(&u8Buf);

		u8AFDA   = ( u8Buf & 0x80 ) >> 7;
		u8RIMCA  = ( u8Buf & 0x40 ) >> 6;
		u8ACASRA = ( u8Buf & 0x20 ) >> 5;
		u8NTCA   = ( u8Buf & 0x10 ) >> 4;
		u8DG     = ( u8Buf & 0x08 ) >> 3;
		u8OF     = ( u8Buf & 0x04 ) >> 2;
		u8OL     = ( u8Buf & 0x02 ) >> 1;

		safetyNets.u8AFDA   = u8AFDA;
		safetyNets.u8RIMCA  = u8RIMCA;
		safetyNets.u8ACASRA = u8ACASRA;
		safetyNets.u8NTCA   = u8NTCA;
		safetyNets.u8DG     = u8DG;
		safetyNets.u8OF     = u8OF;
		safetyNets.u8OL     = u8OL;

		if (DEBUG) {
			tmpBuf += QString("  AFDA : %1, RIMCA : %2, ACASRA : %3, NTCA : %4, DG : %5, OF : %6, OL : %7 \n").
					arg(u8AFDA).arg(u8RIMCA).arg(u8ACASRA).arg(u8NTCA).arg(u8DG).arg(u8OF).arg(u8OL);
		}
	}
}

/**
 * Data Item I004/070	Conflict Timing and Separation
 * Definition : Information on Timing and Aircraft Separation
 * Format     : Compound Data Item, comprising a primary subfield of one octet,
 *              followed by the indicated subfileds.
 */
void Cat004::I004_070(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8FX  = 0x00;
	U8 u8TC  = 0x00;
	U8 u8TCA = 0x00;
	U8 u8CHS = 0x00;
	U8 u8MHS = 0x00;
	U8 u8CVS = 0x00;
	U8 u8MVS = 0x00;

	U32 u32TimeToConflict = 0;
	F64 f64TimeToConflict = 0;
	U32 u32TimeToApproach = 0;
	F64 f64TimeToApproach = 0;
	U32 u32CurHorSep = 0;
	F64 f64CurHorSep = 0;
	S16 s16EstMinHorSep = 0;
	F64 f64EstMinHorSep = 0;
	S16 s16CurVerSep = 0;
	F64 f64CurVerSep = 0;
	S16 s16EstMinVerSep = 0;
	F64 f64EstMinVerSep = 0;


	rBuffer.ReadU8(&u8Buf);

	u8TC   = ( u8Buf & 0x80 ) >> 7;
	u8TCA  = ( u8Buf & 0x40 ) >> 6;
	u8CHS  = ( u8Buf & 0x20 ) >> 5;
	u8MHS  = ( u8Buf & 0x10 ) >> 4;
	u8CVS  = ( u8Buf & 0x08 ) >> 3;
	u8MVS  = ( u8Buf & 0x04 ) >> 2;
	u8FX   = ( u8Buf & 0x01 );

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/070 Conflict Timing and Separation : \n");
	}

	safetyNets.u8TC    = u8TC;		   // Subfield #1 : Time to Conflict
	safetyNets.u8TCA   = u8TCA;		// Subfield #2 : Time to Closest Approach
	safetyNets.u8CHS   = u8CHS;		// Subfield #3 : Current Horizontal Separation
	safetyNets.u8MHS   = u8MHS;		// Subfield #4 : Estimated Minimum Horizontal Separation
	safetyNets.u8CVS   = u8CVS;		// Subfield #5 : Current Vertical Separation
	safetyNets.u8MVS   = u8MVS;		// Subfield #6 : Estimated Minimum Vertical Separation

	if (DEBUG) {
		tmpBuf += QString("  Subfield #1 : Time to Conflict : %1\n Subfield #2 : Time to Closest Approach : %2\n"
				" Subfield #3 : Current Horizontal Separation : %3\n Subfield #4 : Estimated Minimum Horizontal Separation : %4\n"
				" Subfield #5 : Current Vertical Separation : %5\n Subfield #6 : Estimated Minimum Vertical Separation : %6 \n").
				arg(u8TC).arg(u8TCA).arg(u8CHS).arg(u8MHS).arg(u8CVS).arg(u8MVS);
	}

	if (u8TC) {
		// Sufeild #1 : Time to Conflict
		// Defintion  : Time remaining to actual conflict situation
		// Format     : Three-octet fixed length Data Item
		// LSB        : 1/128 sec
		rBuffer.ReadU24(&u32TimeToConflict);
		f64TimeToConflict = (1.0 / 128) * u32TimeToConflict;
		safetyNets.f64TimeToConflict = f64TimeToConflict;
		if (DEBUG) {
			tmpBuf += QString(" Time to Conflict : %1\n").arg(safetyNets.f64TimeToConflict);
		}
	}
	if(u8TCA) {
		// Sufield #2 : Time to Closest Approach
		// Definition : Time to closest proximity between entities in conclict
		// Format     : Three-octet fixed length Data Item
		// LSB        : 1/128 sec
		rBuffer.ReadU24(&u32TimeToApproach);
		f64TimeToApproach = (1.0 / 128) * u32TimeToApproach;
		safetyNets.f64TimeToApproach = f64TimeToApproach;
		if (DEBUG) {
			tmpBuf += QString(" Time to Closest Approach : %1\n").arg(safetyNets.f64TimeToApproach);
		}
	}
	if(u8CHS) {
		// Sufield #3 : Current Horizontal Separation
		// Definition : Current horizontal separation
		// Format     : Three-octet fixed length Data Item.
		// LSB        : 0.5m
		rBuffer.ReadU24(&u32CurHorSep);
		f64CurHorSep = (0.5) * u32CurHorSep;
		safetyNets.f64CurHorSep = f64CurHorSep;
		if (DEBUG) {
			tmpBuf += QString(" Current Horizontal Separation : %1\n").arg(safetyNets.f64CurHorSep);
		}
	}
	if(u8MHS) {
		// Sufield #4 : Estimated Minimum Horizontal Separation
		// Definition : Estimated minimum horizontal separation
		// Format     : Two-octet fixed length Data Item
		// LSB        : 0.5m
		rBuffer.ReadS16(&s16EstMinHorSep);
		f64EstMinHorSep = static_cast<F64>(s16EstMinHorSep);
		f64EstMinHorSep = (0.5) * f64EstMinHorSep;
		safetyNets.f64EstMinHorSep = f64EstMinHorSep;
		safetyNets.f64CurHorSep = f64CurHorSep;
		if (DEBUG) {
			tmpBuf += QString(" Estimated Minimum Horizontal Separation : %1, %2\n").arg(safetyNets.f64EstMinHorSep).arg(safetyNets.f64CurHorSep);
		}
	}
	if(u8CVS) {
		// Sufield #5 : Current Vertical Separation
		// Definition : current vertical separation
		// Format     : Two-octet fixed length Data Item.
		// LSB        : 25ft
		rBuffer.ReadS16(&s16CurVerSep);
		f64CurVerSep = static_cast<F64>(s16CurVerSep);
		f64CurVerSep = 25.0 * f64CurVerSep;
		safetyNets.f64CurVerSep = f64CurVerSep;
		if (DEBUG) {
			tmpBuf += QString(" Current Vertical Separation : %1\n").arg(safetyNets.f64CurVerSep);
		}
	}
	if(u8MVS) {
		// Sufield #6 : Estimated Minimum Vertical Separatiion
		// Definition : Estimated minimum vertical separation
		// Format     : Two-octet fixed length Data Item
		// LSB        : 25ft
		rBuffer.ReadS16(&s16EstMinVerSep);
		f64EstMinVerSep = static_cast<F64>(s16EstMinVerSep);
		f64EstMinVerSep = 25.0 * f64EstMinVerSep;
		safetyNets.f64EstMinVerSep = f64EstMinVerSep;
		if (DEBUG) {
			tmpBuf += QString(" Estimated Minimum Vertical Separatiion : %1\n").arg(safetyNets.f64EstMinVerSep);
		}
	}
}

/**
 * Data Item I004/074	Longitudinal Deviation
 * Definition : Longitudinal deviation for Route Adherence Monitoring, in two's
 *              complement form.
 * Format     : Two-octet fixed length Data Item
 * LSB        : 32m
 * NOTE       : Longitudinal deviation will be positive if the aircraft is ahead of its
 *              planned position.
 *              Longitudinal deviation will be negative if the aircraft is behind its
 *              planned position.
 */
void Cat004::I004_074(CBuffer& rBuffer)
{
	S16 s16LonDeviation = 0;
	F64 f64LonDeviation = 0;

	rBuffer.ReadS16(&s16LonDeviation);
	f64LonDeviation = static_cast<F64>(s16LonDeviation);
	f64LonDeviation = 32 * f64LonDeviation;
	safetyNets.f64LonDeviation = f64LonDeviation;
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/074 Longitudinal Deviation : %1 \n").arg(safetyNets.f64LonDeviation);
	}
}

/**
 * Data Item I004/075	Transversal Distance Deviation
 * Definition : Transversal distance deviation for Route Adherence Monitoring,
 * 				in two's complement form.
 * Format     : Three-octet fixed length Data Item.
 * LSB        : 0.5m
 * NOTE       : Clockwise deviation will be coded as a positive value.
 *              Anticlockwise deviation will be coded as a negative value.
 */
void Cat004::I004_075(CBuffer& rBuffer)
{
	S32 s32TranDistDev = 0;
	F64 f64TranDistDev = 0;

	rBuffer.ReadS24(&s32TranDistDev);
	f64TranDistDev = static_cast<F64>(s32TranDistDev);
	f64TranDistDev = (0.5) * f64TranDistDev;
	safetyNets.f64TranDistDev = f64TranDistDev;
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/075 Transversal Distance Deviation : %1 \n").arg(safetyNets.f64TranDistDev);
	}
}

/**
 * Data Item I004/076	Vertical Deviation
 * Definition : Vertical Deviation from planned altitude, in two's complement
 *              form.
 * Format     : Two-octet fixed length Data Item
 * LSB        : 25ft
 * NOTE       : Positive value if aircraft is above planned altitude.
 *              Negative value if aircraft is below planned latitude.
 */
void Cat004::I004_076(CBuffer& rBuffer)
{
	S16 s16VerDeviation = 0;
	F64 f64VerDeviation = 0;

	rBuffer.ReadS16(&s16VerDeviation);
	f64VerDeviation = static_cast<F64>(s16VerDeviation);
	f64VerDeviation = 25 * f64VerDeviation;
	safetyNets.f64VerDeviation = f64VerDeviation;
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/076 Vertical Deviation : %1 \n").arg(safetyNets.f64VerDeviation);
	}
}

/**
 * Data Item I004/070	Area Definition
 * Defintion : Definition of Areas involved in a Safety Net Alert
 * Format    : Compound Data Item, comprising a primary subfield of one
 *             octet, followed by the indicated subfields.
 */
void Cat004::I004_100(CBuffer& rBuffer)
{
	U8 u8Buf			= 0x00;
	U8 u8AreaName		= 0x00;
	U8 u8CrossAreaName	= 0x00;
	U8 u8RunTaxiDes1	= 0x00;
	U8 u8RunTaxiDes2	= 0x00;
	U8 u8StopBarDes		= 0x00;
	U8 u8GateDes		= 0x00;
	U8 u8FX				= 0x00;
	U8 u8Tmp = 0;
	rBuffer.ReadU8(&u8Buf);

	u8AreaName      = (u8Buf & 0x80) >> 7;
	u8CrossAreaName = (u8Buf & 0x40) >> 6;
	u8RunTaxiDes1   = (u8Buf & 0x20) >> 5;
	u8RunTaxiDes2   = (u8Buf & 0x10) >> 4;
	u8StopBarDes    = (u8Buf & 0x08) >> 3;
	u8GateDes       = (u8Buf & 0x04) >> 2;
	u8FX            = (u8Buf & 0x01);

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/100 Area Definition : \n");
	}


	safetyNets.u8AreaName = u8AreaName;
	safetyNets.u8CrossAreaName = u8CrossAreaName;
	safetyNets.u8RunTaxiDes1 = u8RunTaxiDes1;
	safetyNets.u8RunTaxiDes2 = u8RunTaxiDes2;
	safetyNets.u8StopBarDes  = u8StopBarDes;
	safetyNets.u8GateDes = u8GateDes;

	if (DEBUG) {
		tmpBuf += QString("  Subfield #1 : Area Name : %1\n Subfield #2 : Crossing Area Name : %2\n"
				" Subfield #3 : Runway/Taxiway Designator 1 : %3\n Subfield #4 : Runway/Taxiway Designator 2 : %4\n"
				" Subfield #5 : Stop Bar Designator : %5\n Subfield #6 : Gate Designator : %6 \n").
				arg(u8AreaName).arg(u8CrossAreaName).arg(u8RunTaxiDes1).arg(u8RunTaxiDes2).arg(u8StopBarDes).arg(u8GateDes);
	}

	if (u8AreaName) {
		// Subfield #1 : Area Name
		// Definition  : Name of the area involved in a Safety Net alarm
		// Format      : Six-octet fixed length Data Item.
		// bits-48/1   : Characters 1-8 (coded on 6 Bits each) defining the name of the area
		//               Coding rules are provided in [4] Section 3.1.2.9
		// NOTE        : The area name is always left adjusted. If needed, the remaining
		//               characters are filled with space character.
		U64 u64Buf = 0;
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		U8  u8Ch5  = 0x00;
		U8  u8Ch6  = 0x00;
		U8  u8Ch7  = 0x00;
		U8  u8Ch8  = 0x00;
		rBuffer.ReadU48(&u64Buf);

		u8Ch1 = (u64Buf & 0x0000FC0000000000) >> 42;
		u8Ch2 = (u64Buf & 0x000003F000000000) >> 36;
		u8Ch3 = (u64Buf & 0x0000000FC0000000) >> 30;
		u8Ch4 = (u64Buf & 0x000000003F000000) >> 24;
		u8Ch5 = (u64Buf & 0x0000000000FC0000) >> 18;
		u8Ch6 = (u64Buf & 0x000000000003F000) >> 12;
		u8Ch7 = (u64Buf & 0x0000000000000FC0) >> 6;
		u8Ch8 = (u64Buf & 0x000000000000003F);


		char ch[8];

		sprintf(ch, "%c%c%c%c%c%c%c%c", CharacterValue(u8Ch1), CharacterValue(u8Ch2), CharacterValue(u8Ch3),
				CharacterValue(u8Ch4), CharacterValue(u8Ch5), CharacterValue(u8Ch6), CharacterValue(u8Ch7), CharacterValue(u8Ch8));
//		QString strAreaName;
//		U8 u8Tmp1, u8Tmp2, u8Tmp3, u8Tmp4, u8Tmp5, u8Tmp6, u8Tmp7, u8Tmp8;
//
//		u8Tmp1 = static_cast<U8>( (u64Buf & 0x03FFFFFFFFFF) >> 42 );		// Character 1
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		u8Tmp2 = static_cast<U8>( (u64Buf & 0xFCEFFFFFFFFF) >> 36 );		// Character 2
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		u8Tmp3 = static_cast<U8>( (u64Buf & 0xFFF0CFFFFFFF) >> 30);		// Character 3
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		u8Tmp4 = static_cast<U8>( (u64Buf & 0xFFFFC0FFFFFF) >> 24);		// Character 4
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		u8Tmp5 = static_cast<U8>( (u64Buf & 0xFFFFFF03FFFF) >> 18);		// Character 5
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		u8Tmp6 = static_cast<U8>( (u64Buf & 0xFFFFFFFC0FFF) >> 12);		// Character 6
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		u8Tmp7 = static_cast<U8>( (u64Buf & 0xFFFFFFFFF0CF) >> 6);		// Character 7
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		u8Tmp8 = static_cast<U8>( (u64Buf & 0xFFFFFFFFFF30));			  // Character 8
//		//strAreaName.append(QChar::fromAscii(u8Tmp));
//
//		char ch[8];
//
//		sprintf(ch, "%c%c%c%c%c%c%c%c", CharacterValue(u8Tmp1), CharacterValue(u8Tmp2), CharacterValue(u8Tmp3),
//				CharacterValue(u8Tmp4), CharacterValue(u8Tmp5), CharacterValue(u8Tmp6), CharacterValue(u8Tmp7), CharacterValue(u8Tmp8));

		safetyNets.strAreaName = QString(ch);  // strAreaName;
		if (DEBUG) {
			tmpBuf += QString(" Area Name : %1\n").arg(safetyNets.strAreaName);
		}
	}
	if (u8CrossAreaName) {
		// Subfield #2 : Crossing Area Name
		// Definition  : Name of Crossing Area Involved in a RIMCA
		// Format      : Seven-octet fixed length Data Item.
		// bits-56/1   : Each octet is an ASCII character defining the name of the crossing
		//               area involved in a runway/taxiway crossing alert (message type 013)
		// NOTE        : The name of the crossing area is always left adjusted. If needed,
		//               the remaining characters are filled with space characters.
		QString strCrossAreaName;
		for (int i=0; i<7; i++) {
			rBuffer.ReadU8(&u8Tmp);
			strCrossAreaName.append(QChar::fromAscii(u8Tmp));
		}
		safetyNets.strCrossAreaName = strCrossAreaName;
		if (DEBUG) {
			tmpBuf += QString(" Crossing Area Name : %1\n").arg(safetyNets.strCrossAreaName);
		}
	}
	if (u8RunTaxiDes1) {
		// Subfield #3 : Runway/Taxiway Designator 1
		// Definition  : Designator of Runway/Taxiway 1 Involved in a RIMCA
		// Format      : Seven-octet fixed length Data Item
		// bits-56/1   : Each octet is an ASCII character defining the runway designator
		// NOTE        : The runway designator is always left adjusted. If needed, the
		//               remaining characters are filled with space characters.
		//               The runway is encoded as follows: Location indicator, runway direction,
		//               left or right.
		//               Example: EGLL09L means London Heathrow (EGLL), Runway 09 (direction 090 degrees)
		//               left runway
		QString strRunTaxDes1;
		for (int i=0; i<7; i++) {
			rBuffer.ReadU8(&u8Tmp);
			strRunTaxDes1.append(QChar::fromAscii(u8Tmp));
		}
		safetyNets.strRunTaxDes1 = strRunTaxDes1;
		if (DEBUG) {
			tmpBuf += QString(" Runway/Taxiway Designator 1 : %1\n").arg(safetyNets.strRunTaxDes1);
		}
	}
	if (u8RunTaxiDes2) {
		// Subfield #4 : Runway/Taxiway Designator 2
		// Definition  : Designator of Runway/Taxiway 2 Involved in a RIMCA
		// Format      : Seven-octet fixed length Data Item
		// bits-56/1   : Each octet is an ASCII character defining the runway designator
		// NOTE        : The runway designator is always left adjusted. If needed, the
		//               remaining characters are filled with space characters.
		//               The runway is encoded as follows: Location indicator, runway direction,
		//               left or right.
		//               Example: EGLL09L means London Heathrow (EGLL), Runway 09 (direction 090 degrees)
		//               left runway
		QString strRunTaxDes2;
		for (int i=0; i<7; i++) {
			rBuffer.ReadU8(&u8Tmp);
			strRunTaxDes2.append(QChar::fromAscii(u8Tmp));
		}
		safetyNets.strRunTaxDes2 = strRunTaxDes2;
		if (DEBUG) {
			tmpBuf += QString(" Runway/Taxiway Designator 2 : %1\n").arg(safetyNets.strRunTaxDes2);
		}
	}
	if (u8StopBarDes) {
		// Subfield #5 : Stop Bar Designator
		// Definition  : Designator of Stop-Bar Involved in a RIMCA
		// Format      : Seven-octet fixed length Data Item
		// bits-56/1   : Each octet is an ASCII character defining the stop-bar involved in a stop-bar
		//               crossed alert (message type 016)
		// NOTE        : The stop-bar designator is always left adjusted. If needed, the remaining
		//               characters are filled with space characters.
		QString strStopBarDes;
		for (int i=0; i<7; i++) {
			rBuffer.ReadU8(&u8Tmp);
			strStopBarDes.append(QChar::fromAscii(u8Tmp));
		}
		safetyNets.strStopBarDes = strStopBarDes;
		if (DEBUG) {
			tmpBuf += QString(" Stop Bar Designator : %1\n").arg(safetyNets.strStopBarDes);
		}
	}
	if (u8GateDes) {
		// Subfield #6 : Gate Designator
		// Definition  : Gate Designator (in 7 characters) of the approaching aircraft in a RIMCA
		// Format      : Seven-octet fixed length Data Item.
		// bits-56/1   : Each octet is an ASCII character defining the gate for the approaching aircraft
		// NOTE        : The gate designator is always left adjusted. If needed, the remaining characters
		//               are filled with space character.
		QString strGateDes;
		for (int i=0; i<7; i++) {
			rBuffer.ReadU8(&u8Tmp);
			strGateDes.append(QChar::fromAscii(u8Tmp));
		}
		safetyNets.strGateDes = strGateDes;
		if (DEBUG) {
			tmpBuf += QString(" Gate Designator : %1\n").arg(safetyNets.strGateDes);
		}
	}
}
/**
 * Data Item I004/110	FDPS Sector Control Identification
 * Definition : Identification of a list of FDPS Sector Control Positions in charge of the involved targets,
 *              as provided by the FDPS
 * Format     : Repetitive Data Item starting with one-octet Field Repetition Indicator (REP) followed by
 *              at least one FDPS Sector Control Position
 * NOTE       : The Centre identification code and the Control position identification code must be defined
 *              between the communication partners.
 */
void Cat004::I004_110(CBuffer& rBuffer)
{
	U8 u8Rep = 0;
	U8 u8Centre = 0;
	U8 u8Position = 0;

	rBuffer.ReadU8(&u8Rep);

	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/110 FDPS Sector Control Identification : \n");
	}

	for (int i=0; i<u8Rep; i++) {
		FDP_SC_ID fdp_sc_id;
		rBuffer.ReadU8(&u8Centre);
		rBuffer.ReadU8(&u8Position);

		fdp_sc_id.centre = u8Centre;
		fdp_sc_id.position = u8Position;

		safetyNets.lstFdp_sc_id.append(fdp_sc_id);
	}
}

/**
 * Data Item I004/120	Conflict Characteristics
 * Definition : Description of the Conflict Properties
 * Format     : Compound Data Item, comprising a primary subfield of one octet,
 *              followed by the indicated subfields.
 *
 */
void Cat004::I004_120(CBuffer& rBuffer)
{
	U8 u8Buf = 0;
	U8 u8CN  = 0;		// Conflict Nature
	U8 u8CC  = 0;		// Conflict Classification
	U8 u8CP  = 0;		// Conflict Probability
	U8 u8CD  = 0;		// Conflict Duration
	U8 u8FX  = 0;

	rBuffer.ReadU8(&u8Buf);

	u8CN = (u8Buf & 0x80) >> 7;
	u8CC = (u8Buf & 0x40) >> 6;
	u8CP = (u8Buf & 0x20) >> 5;
	u8CD = (u8Buf & 0x10) >> 4;
	u8FX = (u8Buf & 0x01);

	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/120 Conflict Characteristics : \n");
	}

	safetyNets.u8ConflictNature         = u8CN;
	safetyNets.u8ConflictClassification = u8CC;
	safetyNets.u8ConflictProbability    = u8CP;
	safetyNets.u8ConflictDuration       = u8CD;

	if (DEBUG) {
		tmpBuf += QString("  Subfield #1 : Conflict Nature : %1\n Subfield #2 : Conflict Classification : %2\n"
				" Subfield #3 : Conflict Probability : %3\n Subfield #4 : Conflict Duration : %4\n").
				arg(u8CN).arg(u8CC).arg(u8CP).arg(u8CD);
	}

	if (u8CN) {
		// Subfield #1 : Conflict Nature
		// Definition  : Nature of the conflict expressed by a set of properties
		// Format      : Variable length Data Item comprising a first part of one octet,
		//               followed by one-octet extents as necessary.
		U8 u8MAS   = 0;		// Conflict location in military airspace
		U8 u8CAS   = 0;		// Conflict location in civil airspace
		U8 u8FLD   = 0;		// Fast lateral divergence
		U8 u8FVD   = 0;		// Fast vertical divergence
		U8 u8TYPE  = 0;		// Type of separation infringement
		U8 u8CROSS = 0;		// Crossing test
		U8 u8DIV   = 0;		// Divergence test
		U8 u8FX2   = 0;

		rBuffer.ReadU8(&u8Buf);
		u8MAS   = (u8Buf & 0x80) >> 7;
		u8CAS   = (u8Buf & 0x40) >> 6;
		u8FLD   = (u8Buf & 0x20) >> 5;
		u8FVD   = (u8Buf & 0x10) >> 4;
		u8TYPE  = (u8Buf & 0x08) >> 3;
		u8CROSS = (u8Buf & 0x04) >> 2;
		u8DIV   = (u8Buf & 0x02) >> 1;
		u8FX2    = (u8Buf & 0x01);

		safetyNets.u8MAS   = u8MAS;
		safetyNets.u8CAS   = u8CAS;
		safetyNets.u8FLD   = u8FLD;
		safetyNets.u8FVD   = u8FVD;
		safetyNets.u8TYPE  = u8TYPE;
		safetyNets.u8CROSS = u8CROSS;
		safetyNets.u8DIV   = u8DIV;

		if (DEBUG) {
			tmpBuf += QString(" Conflict Nature \n");
			tmpBuf += QString(" - Conflict location in military airspace : %1\n").arg(u8MAS);
			tmpBuf += QString(" - Conflict location in civil airspace : %1\n").arg(u8CAS);
			tmpBuf += QString(" - Fast lateral divergence : %1\n").arg(u8FLD);
			tmpBuf += QString(" - Fast vertical divergence : %1\n").arg(u8FVD);
			tmpBuf += QString(" - Type of separation infringement : %1\n").arg(u8TYPE);
			tmpBuf += QString(" - Crossing test : %1\n").arg(u8CROSS);
			tmpBuf += QString(" - Divergence test : %1\n").arg(u8DIV);
		}

		if (u8MAS) {
			// First Extent
			// NOTE - The spare bits and extended octets may be used to define additional properties
			//        of a conflict.
			U8 u8RPC  = 0;			// Runway/Runway crossing in RIMCAS
			U8 u8RTC  = 0;			// Runway/Taxiway Crossing in RIMCAS
			U8 u8MRVA = 0;			// Msg type 4 (MSAW) indicates MRVA

			rBuffer.ReadU8(&u8Buf);
			u8RPC  = (u8Buf & 0x80) >> 7;
			u8RTC  = (u8Buf & 0x40) >> 6;
			u8MRVA = (u8Buf & 0x20) >> 5;
			u8FX2  = (u8Buf & 0x01);

			safetyNets.u8RPC  = u8RPC;
			safetyNets.u8RTC  = u8RTC;
			safetyNets.u8MRVA = u8MRVA;
			if (DEBUG) {
				tmpBuf += QString(" - Runway/Runway crossing in RIMCAS : %1\n").arg(u8RPC);
				tmpBuf += QString(" - Runway/Taxiway Crossing in RIMCAS : %1\n").arg(u8RTC);
				tmpBuf += QString(" - Msg type 4 (MSAW) indicates MRVA : %1\n").arg(u8MRVA);
			}
		}
	}
	if (u8CC) {
		// Subfield #2 : Conflict Classification
		// Definition  : Severity classification of the conflict
		// Format      : One-octet fixed length Data Item
		U8 u8TableID = 0x00;
		U8 u8SerCls  = 0x00;
		U8 u8CS      = 0x00;

		rBuffer.ReadU8(&u8Buf);

		u8TableID = (u8Buf & 0xF0) >> 4;
		u8SerCls  = (u8Buf & 0x0E) >> 1;
		u8CS      = (u8Buf * 0x01);

		// TableID�� ��� �з�..
		safetyNets.u8TableID = u8TableID;
		safetyNets.u8SeverityCls = u8SerCls;
		safetyNets.u8Severity = u8CS;
		if (DEBUG) {
			tmpBuf += QString(" Conflict Classification \n");
			tmpBuf += QString(" - TableID : %1\n").arg(u8TableID);
			tmpBuf += QString(" - SeverityCls : %1\n").arg(u8SerCls);
			tmpBuf += QString(" - Severity : %1\n").arg(u8CS);
		}
	}
	if(u8CP) {
		// Subfield #3 : Conflict Probability
		// Definition  : Probability of the conflict
		// Format      : One-octet fixed length Data Item
		// LSB         : 0.5%
		rBuffer.ReadU8(&u8Buf);
		S32 s32ConPro = (0.5) * (double)u8Buf;

		safetyNets.s32ProbComflict = s32ConPro;
		if (DEBUG) {
			tmpBuf += QString(" Conflict Probability : %1\n").arg(safetyNets.s32ProbComflict);
		}

	}
	if(u8CD) {
		// Subfield #4 : Conflict Duration
		// Definition  : The duration of the conflict is the elapsed time since the declaration
		//               of the conflict
		// Format      : Three-octet fixed length Data Item
		// LSB         : 1/128 sec
		U32 u32Duration = 0;
		F64 f64Duration = 0;
		rBuffer.ReadU24(&u32Duration);
		f64Duration = (1.0 / 128) * u32Duration;
		safetyNets.f64Duration = f64Duration;
		if (DEBUG) {
			tmpBuf += QString(" Conflict Duration : %1\n").arg(safetyNets.f64Duration);
		}
	}
}

/**
 * Data Item I004/170	Aircraft Identification & Characteristics 1
 * Definition : Identification & Characteristics of Aircraft 1 Involved in the Conflict
 * Format     : Compound Data Item, comprising a primary subfield of up to two octets,
 *              followed by the indicated subfields.
 */
void Cat004::I004_170(CBuffer& rBuffer)
{
	U8 u8AI1 = 0;		// Subfield #1 : Aircraft Identifier 1
	U8 u8M31 = 0;		// Subfield #2 : Mode 3/A Code Aircraft 1
	U8 u8CPW = 0;		// Subfield #3 : Predicted Conflict Position 1 (WGS84)
	U8 u8CPC = 0;		// Subfield #4 : Predicted Conflict Position 1 (Cartesian Coordinates)
	U8 u8TT1 = 0;		// Subfield #5 : Time to Threshold Aircraft 1
	U8 u8DT1 = 0;		// Subfield #6 : Distance to Threshold Aircraft 1
	U8 u8AC1 = 0;		// Subfield #7 : Aircraft Characteristics Aircraft 1
	U8 u8FX1 = 0;
	U8 u8MS1 = 0;		// Subfield #8 : Mode S Identifier Aircraft 1
	U8 u8FP1 = 0;		// Subfield #9 : Flight Plan Number Aircraft 1
	U8 u8CF1 = 0;		// Subfield #10 : Cleared Flight Level Aircraft 1
	U8 u8FX2 = 0;
	U8 u8Buf = 0;
	U8 u8EFX = 0;

	rBuffer.ReadU8(&u8Buf);
	u8AI1 = (u8Buf & 0x80) >> 7;
	u8M31 = (u8Buf & 0x40) >> 6;
	u8CPW = (u8Buf & 0x20) >> 5;
	u8CPC = (u8Buf & 0x10) >> 4;
	u8TT1 = (u8Buf & 0x08) >> 3;
	u8DT1 = (u8Buf & 0x04) >> 2;
	u8AC1 = (u8Buf & 0x02) >> 1;
	u8FX1 = (u8Buf & 0x01);

	rBuffer.ReadU8(&u8Buf);
	u8MS1 = (u8Buf & 0x80) >> 7;
	u8FP1 = (u8Buf & 0x40) >> 6;
	u8CF1 = (u8Buf & 0x20) >> 5;
	u8FX2 = (u8Buf & 0x01);

	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/170 Aircraft Identification & Characteristics 1 : \n");

		tmpBuf += QString("  Subfield #1 : Aircraft Identifier 1 : %1\n Subfield #2 : Mode 3/A Code Aircraft 1 : %2\n"
					" Subfield #3 : Predicted Conflict Position 1 (WGS84) : %3\n Subfield #4 : Predicted Conflict Position 1 (Cartesian Coordinates) : %4\n"
				   " Subfield #5 : Time to Threshold Aircraft 1 : %5\n Subfield #6 : Distance to Threshold Aircraft 1 : %6\n"
				   " Subfield #7 : Aircraft Characteristics Aircraft 1 : %7\n Subfield #8 : Mode S Identifier Aircraft 1 : %8\n"
				   " Subfield #9 : Flight Plan Number Aircraft 1 : %9\n  Subfield #10 : Cleared Flight Level Aircraft 1 : %10\n").
					arg(u8AI1).arg(u8M31).arg(u8CPW).arg(u8CPC).arg(u8TT1).arg(u8DT1).arg(u8AC1).arg(u8MS1).arg(u8FP1).arg(u8CF1);

	}

	if (u8AI1) {
		// Subfield #1 : Aircraft Identifier 1
		// Defintion   : Aircraft Identifier (in 7 characters) of Aircraft 1 Involved in the Conflict
		// Format      : Seven-octet fixed length Data Item
		// bits-56/1   : Each octet is an ASCII character defining the first aircraft
		// NOTE        : The aircraft identifier is always left adjusted. If needed, the remaining
		//               characters are filled with space character.
		QString strAircraftID;
		for (int i=0; i<7; i++) {
			rBuffer.ReadU8(&u8Buf);
			strAircraftID.append(QChar::fromAscii(u8Buf));
		}
		safetyNets.airId1.strAircraftID = strAircraftID;
		if (DEBUG) {
			tmpBuf += QString(" Aircraft Identifier 1 : %1\n").arg(safetyNets.airId1.strAircraftID);
		}
	}

	if (u8M31) {
		// Subfield #2 : Mode 3/A Code Aircraft 1
		// Definition  : Mode 3/A code (converted into octal representation) of Aircraft 1 Involved
		//               in the Conflict
		// Format      : Two-octet fixed length Data Item.
		//                     16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1
		//                0   0   0   0  A4  A2  A1  B4  B2  B1  C4  C2  C1  D4  D2  D1
		U8 u8A4 =0, u8A2 =0, u8A1 =0, u8B4 =0, u8B2 =0;
		U8 u8B1 =0, u8C4 =0, u8C2 =0, u8C1 =0, u8D4 =0;
		U8 u8D2 =0, u8D1 =0;

		rBuffer.ReadU8(&u8Buf);
		u8A4 = (u8Buf & 0x08) >> 3;
		u8A2 = (u8Buf & 0x04) >> 2;
		u8A1 = (u8Buf & 0x02) >> 1;
		u8B4 = (u8Buf & 0x01);

		rBuffer.ReadU8(&u8Buf);
		u8B2 = (u8Buf & 0x80) >> 7;
		u8B1 = (u8Buf & 0x40) >> 6;
		u8C4 = (u8Buf & 0x20) >> 5;
		u8C2 = (u8Buf & 0x10) >> 4;
		u8C1 = (u8Buf & 0x08) >> 3;
		u8D4 = (u8Buf & 0x04) >> 2;
		u8D2 = (u8Buf & 0x02) >> 1;
		u8D1 = (u8Buf & 0x01);

		safetyNets.airId1.u8A4 = u8A4;
		safetyNets.airId1.u8A2 = u8A2;
		safetyNets.airId1.u8A1 = u8A1;
		safetyNets.airId1.u8B4 = u8B4;
		safetyNets.airId1.u8B2 = u8B2;
		safetyNets.airId1.u8B1 = u8B1;
		safetyNets.airId1.u8C4 = u8C4;
		safetyNets.airId1.u8C2 = u8C2;
		safetyNets.airId1.u8C1 = u8C1;
		safetyNets.airId1.u8D4 = u8D4;
		safetyNets.airId1.u8D2 = u8D2;
		safetyNets.airId1.u8D1 = u8D1;

		char str1[] = {u8A4, u8A2, u8A1};
		char str2[] = {u8B4, u8B2, u8B1};
		char str3[] = {u8C4, u8C2, u8C1};
		char str4[] = {u8D4, u8D2, u8D1};

		QString tmp1 = QString("%1%2%3%4")
				.arg(QString::fromAscii(str1))
				.arg(QString::fromAscii(str2))
				.arg(QString::fromAscii(str3))
				.arg(QString::fromAscii(str4));
		safetyNets.airId1.strMode3ACode = tmp1;
		if (DEBUG) {
			tmpBuf += QString(" Mode 3/A Code Aircraft 1 : %1\n").arg(safetyNets.airId1.strMode3ACode);
		}
	}

	if (u8CPW) {
		// Subfield #3 : Predicted Conflict Position Aircraft 1 (WGS-84)
		// Defintion   : Predicted conflict position target 1 in WGS-84 Coordinates.
		// Format      : Ten-octet fixed length Data Item

		// 4 byte : Conflict Latitude in WGS-84
		// Range -90 <= latitude <= 90 deg.
		// LSB : 180/2^25 degrees
		S32 s32Lat = 0;
		F64 f64Lat = 0.0;
		rBuffer.ReadS32(&s32Lat);
		f64Lat = static_cast<F64>(s32Lat);
		f64Lat = f64Lat * (180.0 / (1024 * 1024 * 32));
		safetyNets.airId1.f64Lat = f64Lat;

		// 4 byte : Conflict Longitude in WGS-84
		// Range -180 <= latitude <= 180 deg.
		// LSB : 180/2^25 degrees
		S32 s32Lon = 0;
		F64 f64Lon = 0.0;
		rBuffer.ReadS32(&s32Lon);
		f64Lon = static_cast<F64>(s32Lon);
		f64Lon = f64Lon * (180.0 / (1024 * 1024 * 32));
		safetyNets.airId1.f64Lon = f64Lon;

		// 2 byte : Conflict Altitude
		// LSB : 25ft
		// Hmin : -1500 ft
		// Hmax : 150000 ft
		// Altitude expressed in two's complement form.
		S16 s16Alt;
		S32 s32Alt;
		F64 f64Alt;
		rBuffer.ReadS16(&s16Alt);
		f64Alt = static_cast<F64>(s16Alt);
		s32Alt = static_cast<S32>(f64Alt);
		s32Alt = s32Alt * 25;
		safetyNets.airId1.s32Alt = s32Alt;

		if (DEBUG) {
			tmpBuf += QString(" Predicted Conflict Position Aircraft 1 (WGS-84): Lat=%1, Lon=%2, Alt=%3\n")
					.arg(safetyNets.airId1.f64Lat).arg(safetyNets.airId1.f64Lon).arg(safetyNets.airId1.s32Alt);
		}
	}

	if (u8CPC) {
		// Subfield #4 : Predicted Conflict Position Aircraft 1 in Cartesian Coordinates.
		// Definition  : Predicted conflict position for the aircraft 1 involved in the conflict
		// Format      : Eight-octet fixed length Data Item

		// bit-48/33 (X-Position) Starting X-position of the conflict
		// LSB = 0.5m
		U32 u32XPOS = 0;
		rBuffer.ReadU24(&u32XPOS);
		F64 f64XPOS = 0.0;
		f64XPOS = 0.5 * u32XPOS;
		safetyNets.airId1.f64XPOS = f64XPOS;

		// bit-32/17 (Y-Position) Starting Y-position of the conflict
		// LSB = 0.5m
		U32 u32YPOS = 0;
		rBuffer.ReadU24(&u32YPOS);
		F64 f64YPOS = 0.0;
		f64YPOS = 0.5 * u32YPOS;
		safetyNets.airId1.f64YPOS = f64YPOS;

		// bit-16/1 (Z-Position) Starting Z-position of the conflict
		// LSB = 25 ft
		// Hmin = -1500 ft
		// Hmax = 150000 ft
		S16 s16ZPOS;
		S32 s32ZPOS;
		F64 f64ZPOS;
		rBuffer.ReadS16(&s16ZPOS);
		f64ZPOS = static_cast<F64>(s16ZPOS);
		s32ZPOS = static_cast<S32>(f64ZPOS);
		s32ZPOS = s32ZPOS * 25;
		safetyNets.airId1.s32ZPOS = s32ZPOS;
		if (DEBUG) {
			tmpBuf += QString(" Predicted Conflict Position Aircraft 1 in Cartesian Coordinates: X=%1, Y=%2, Z=%3\n")
					.arg(safetyNets.airId1.f64XPOS).arg(safetyNets.airId1.f64YPOS).arg(safetyNets.airId1.s32ZPOS);
		}
	}

	if (u8TT1) {
		// Subfield #5 : Time to Threshold Aircraft 1
		// Defintion   : Time to runway threshold for first approaching aircraft in a RIMCA
		// Format      : Three-octet fixed length Data Item.
		// LSB         : 1/128 sec
		// NOTE        : Time to Threshold expressed in Two's Complement.
		F64 f64TimeToThreshold = 0.0;
		U32 u32TimeToThreshold = 0;
		rBuffer.ReadU24(&u32TimeToThreshold);
		f64TimeToThreshold = (1.0 / 128) * u32TimeToThreshold;
		safetyNets.airId1.f64TimeToThreshold = f64TimeToThreshold;
		if (DEBUG) {
			tmpBuf += QString(" Time to Threshold Aircraft 1 : %1\n").arg(safetyNets.airId1.f64TimeToThreshold);
		}
	}

	if (u8DT1) {
		// Subfield #6 : Distance to Threshold Aircraft 1
		// Definition  : Distance from threshold for Aircraft 1 involved in a RIMCA.
		// Format      : Two-octet fixed length Data Item
		// bits 16/1   : Distance to Threshold
		// LSB         : 0.5m
		F64 f64DistToThreshold = 0.0;
		U16 u16DistToThreshold = 0;
		rBuffer.ReadU16(&u16DistToThreshold);
		f64DistToThreshold = (0.5) * u16DistToThreshold;
		safetyNets.airId1.f64DistToThreshold = f64DistToThreshold;
		if (DEBUG) {
			tmpBuf += QString(" Distance to Threshold Aircraft 1 : %1\n").arg(safetyNets.airId1.f64DistToThreshold);
		}
	}

	if (u8AC1) {
		// Subfield #7 : Aircraft Characteristics Aircraft 1
		// Definition  : Characteristics of Aircraft 1 involved in the Conflict
		// Format      : Variable length Data Item comprising a first part of one octet,
		//               followed by one-octet extents as necessary
		U8 u8GATOAT = 0;
		U8 u8FR1FR2 = 0;
		U8 u8RVSM   = 0;
		U8 u8HPR    = 0;
		U8 u8CMD    = 0;
		U8 u8PRI    = 0;
		U8 u8GV     = 0;

		rBuffer.ReadU8(&u8Buf);

		u8GATOAT = (u8Buf & 0xC0) >> 6;
		u8FR1FR2 = (u8Buf & 0x30) >> 4;
		u8RVSM   = (u8Buf & 0x0C) >> 2;
		u8HPR    = (u8Buf & 0x02) >> 1;
		u8EFX    = (u8Buf & 0x01);

		safetyNets.airId1.u8GATOAT = u8GATOAT;
		safetyNets.airId1.u8FR1FR2 = u8FR1FR2;
		safetyNets.airId1.u8RVSM   = u8RVSM;
		safetyNets.airId1.u8HRP    = u8HPR;

		if (DEBUG) {
			tmpBuf += QString(" Aircraft Characteristics Aircraft 1 \n");
			tmpBuf += QString("    GATOAT : %1, FR1FR2 : %2, RVSM : %3, HRP : %4\n")
					.arg(u8GATOAT).arg(u8FR1FR2).arg(u8RVSM).arg(u8HPR);
		}

		if (u8EFX) {
			U8 u8CDM = 0;
			U8 u8PRI = 0;
			U8 u8GV  = 0;

			rBuffer.ReadU8(&u8Buf);

			u8CDM = (u8Buf & 0xC0) >> 6;
			u8PRI = (u8Buf & 0x20) >> 5;
			u8GV  = (u8Buf & 0x10) >> 4;
			safetyNets.airId1.u8CDM = u8CDM;
			safetyNets.airId1.u8PRI = u8PRI;
			safetyNets.airId1.u8GV  = u8GV;
			if (DEBUG) {
				tmpBuf += QString("    CDM : %1, PRI : %2, GV : %3 \n")
						.arg(u8CDM).arg(u8PRI).arg(u8GV);
			}
		}
	}

	if (u8MS1) {
		// Subfield #8 : Mode-S Identifier Aircraft 1
		// Definition  : Aircraft Identification downloaded from Aircraft 1 involved in the conflict
		//               if equipped with a Mode-S transponder.
		// Format      : Six-octet fixed length Data Item
		// bits 48/1   : Characters 1-8(coded on 6 bits each) defining aircraft identification when
		//               a flight plan is available or the registration marking when no flight plan
		//               is available. Coding rules are provided in [4] Section 3.1.2.9
		U64 u64Buf = 0;
		rBuffer.ReadU48(&u64Buf);
		QString strModesID;
		U8 u8Tmp = 0;
		u8Tmp = static_cast<U8>( (u64Buf & 0x03FFFFFFFFFF) >> 42 );		// Character 1
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFCEFFFFFFFFF) >> 36 );		// Character 2
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFF0CFFFFFFF) >> 30);		// Character 3
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFC0FFFFFF) >> 24);		// Character 4
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFF03FFFF) >> 18);		// Character 5
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFFFC0FFF) >> 12);		// Character 6
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFFFFF0CF) >> 6);		// Character 7
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFFFFFF30));			// Character 8
		strModesID.append(QChar::fromAscii(u8Tmp));

		safetyNets.airId1.strModesID = strModesID;
		if (DEBUG) {
			tmpBuf += QString(" Mode-S Identifier Aircraft 1 : %1\n").arg(safetyNets.airId1.strModesID);
		}
	}

	if (u8FP1) {
		// Subfield #9 : Flight Plan Number Aircraft 1
		// Defintion   : Number of the Flight Plan Correlated to Aircraft 1 involved in the Conflict
		// Format      : Four-octet fixed length Data Item.
		// NBR         : Number from 0 to 99 999 999
		U32 u32NBR = 0;
		rBuffer.ReadU32(&u32NBR);

		safetyNets.airId1.u32NBR = u32NBR;
		if (DEBUG) {
			tmpBuf += QString(" Flight Plan Number Aircraft 1 : %1\n").arg(safetyNets.airId1.u32NBR);
		}
	}

	if (u8CF1) {
		// Subfield #10 : Cleared Flight Level Aircraft 1
		// Defintion    : Cleared Flight Level for Aircraft 1 involved in the Conflict
		// Format       : Two-octet fixed length Data Item
		// CFL          : Cleared Flight Level
		// LSB          : 1/4 FL
		S16 s16CFL = 0;
		rBuffer.ReadS16(&s16CFL);
		F64 f64CFL = 0.0;
		f64CFL = static_cast<F64>(s16CFL);
		f64CFL = f64CFL * (1/4);

		safetyNets.airId1.f64CFL = f64CFL;
		if (DEBUG) {
			tmpBuf += QString(" Cleared Flight Level Aircraft 1 : %1\n").arg(safetyNets.airId1.f64CFL);
		}
	}
}

/**
 * Data Item I004/171	Aircraft Identification & Characteristics 2
 * Definition : Identification & Characteristics of Aircraft 2 Involved in the Conflict
 * Format     : Compound Data Item, comprising a primary subfield of up to two octets,
 *              followed by the indicated subfields.
 */
void Cat004::I004_171(CBuffer& rBuffer)
{
	U8 u8AI1 = 0;		// Subfield #1 : Aircraft Identifier 1
	U8 u8M31 = 0;		// Subfield #2 : Mode 3/A Code Aircraft 1
	U8 u8CPW = 0;		// Subfield #3 : Predicted Conflict Position 1 (WGS84)
	U8 u8CPC = 0;		// Subfield #4 : Predicted Conflict Position 1 (Cartesian Coordinates)
	U8 u8TT1 = 0;		// Subfield #5 : Time to Threshold Aircraft 1
	U8 u8DT1 = 0;		// Subfield #6 : Distance to Threshold Aircraft 1
	U8 u8AC1 = 0;		// Subfield #7 : Aircraft Characteristics Aircraft 1
	U8 u8FX1 = 0;
	U8 u8MS1 = 0;		// Subfield #8 : Mode S Identifier Aircraft 1
	U8 u8FP1 = 0;		// Subfield #9 : Flight Plan Number Aircraft 1
	U8 u8CF1 = 0;		// Subfield #10 : Cleared Flight Level Aircraft 1
	U8 u8FX2 = 0;
	U8 u8Buf = 0;
	U8 u8EFX = 0;

	rBuffer.ReadU8(&u8Buf);
	u8AI1 = (u8Buf & 0x80) >> 7;
	u8M31 = (u8Buf & 0x40) >> 6;
	u8CPW = (u8Buf & 0x20) >> 5;
	u8CPC = (u8Buf & 0x10) >> 4;
	u8TT1 = (u8Buf & 0x08) >> 3;
	u8DT1 = (u8Buf & 0x04) >> 2;
	u8AC1 = (u8Buf & 0x02) >> 1;
	u8FX1 = (u8Buf & 0x01);

	rBuffer.ReadU8(&u8Buf);
	u8MS1 = (u8Buf & 0x80) >> 7;
	u8FP1 = (u8Buf & 0x40) >> 6;
	u8CF1 = (u8Buf & 0x20) >> 5;
	u8FX2 = (u8Buf & 0x01);

	if (DEBUG)
	{
		tmpBuf += QString("Data Item I004/171 Aircraft Identification & Characteristics 2 : \n");

		tmpBuf += QString("  Subfield #1 : Aircraft Identifier 1 : %1\n Subfield #2 : Mode 3/A Code Aircraft 1 : %2\n"
					" Subfield #3 : Predicted Conflict Position 1 (WGS84) : %3\n Subfield #4 : Predicted Conflict Position 1 (Cartesian Coordinates) : %4\n"
				   " Subfield #5 : Time to Threshold Aircraft 1 : %5\n Subfield #6 : Distance to Threshold Aircraft 1 : %6\n"
				   " Subfield #7 : Aircraft Characteristics Aircraft 1 : %7\n Subfield #8 : Mode S Identifier Aircraft 1 : %8\n"
				   " Subfield #9 : Flight Plan Number Aircraft 1 : %9\n  Subfield #10 : Cleared Flight Level Aircraft 1 : %10\n").
					arg(u8AI1).arg(u8M31).arg(u8CPW).arg(u8CPC).arg(u8TT1).arg(u8DT1).arg(u8AC1).arg(u8MS1).arg(u8FP1).arg(u8CF1);

	}

	if (u8AI1) {
		// Subfield #1 : Aircraft Identifier 1
		// Defintion   : Aircraft Identifier (in 7 characters) of Aircraft 1 Involved in the Conflict
		// Format      : Seven-octet fixed length Data Item
		// bits-56/1   : Each octet is an ASCII character defining the first aircraft
		// NOTE        : The aircraft identifier is always left adjusted. If needed, the remaining
		//               characters are filled with space character.
		QString strAircraftID;
		for (int i=0; i<7; i++) {
			rBuffer.ReadU8(&u8Buf);
			strAircraftID.append(QChar::fromAscii(u8Buf));
		}
		safetyNets.airId2.strAircraftID = strAircraftID;
		if (DEBUG) {
			tmpBuf += QString(" Aircraft Identifier 1 : %1\n").arg(safetyNets.airId2.strAircraftID);
		}
	}

	if (u8M31) {
		// Subfield #2 : Mode 3/A Code Aircraft 1
		// Definition  : Mode 3/A code (converted into octal representation) of Aircraft 1 Involved
		//               in the Conflict
		// Format      : Two-octet fixed length Data Item.
		//               16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1
		//                0   0   0   0  A4  A2  A1  B4  B2  B1  C4  C2  C1  D4  D2  D1
		U8 u8A4 =0, u8A2 =0, u8A1 =0, u8B4 =0, u8B2 =0;
		U8 u8B1 =0, u8C4 =0, u8C2 =0, u8C1 =0, u8D4 =0;
		U8 u8D2 =0, u8D1 =0;

		rBuffer.ReadU8(&u8Buf);
		u8A4 = (u8Buf & 0x08) >> 3;
		u8A2 = (u8Buf & 0x04) >> 2;
		u8A1 = (u8Buf & 0x02) >> 1;
		u8B4 = (u8Buf & 0x01);

		rBuffer.ReadU8(&u8Buf);
		u8B2 = (u8Buf & 0x80) >> 7;
		u8B1 = (u8Buf & 0x40) >> 6;
		u8C4 = (u8Buf & 0x20) >> 5;
		u8C2 = (u8Buf & 0x10) >> 4;
		u8C1 = (u8Buf & 0x08) >> 3;
		u8D4 = (u8Buf & 0x04) >> 2;
		u8D2 = (u8Buf & 0x02) >> 1;
		u8D1 = (u8Buf & 0x01);

		safetyNets.airId2.u8A4 = u8A4;
		safetyNets.airId2.u8A2 = u8A2;
		safetyNets.airId2.u8A1 = u8A1;
		safetyNets.airId2.u8B4 = u8B4;
		safetyNets.airId2.u8B2 = u8B2;
		safetyNets.airId2.u8B1 = u8B1;
		safetyNets.airId2.u8C4 = u8C4;
		safetyNets.airId2.u8C2 = u8C2;
		safetyNets.airId2.u8C1 = u8C1;
		safetyNets.airId2.u8D4 = u8D4;
		safetyNets.airId2.u8D2 = u8D2;
		safetyNets.airId2.u8D1 = u8D1;

		char str1[] = {u8A4, u8A2, u8A1};
		char str2[] = {u8B4, u8B2, u8B1};
		char str3[] = {u8C4, u8C2, u8C1};
		char str4[] = {u8D4, u8D2, u8D1};

		QString tmp1 = QString("%1%2%3%4")
				.arg(QString::fromAscii(str1))
				.arg(QString::fromAscii(str2))
				.arg(QString::fromAscii(str3))
				.arg(QString::fromAscii(str4));

		safetyNets.airId2.strMode3ACode = tmp1;
		if (DEBUG) {
			tmpBuf += QString(" Mode 3/A Code Aircraft 1 : %1\n").arg(safetyNets.airId2.strMode3ACode);
		}
	}

	if (u8CPW) {
		// Subfield #3 : Predicted Conflict Position Aircraft 1 (WGS-84)
		// Defintion   : Predicted conflict position target 1 in WGS-84 Coordinates.
		// Format      : Ten-octet fixed length Data Item

		// 4 byte : Conflict Latitude in WGS-84
		// Range -90 <= latitude <= 90 deg.
		// LSB : 180/2^25 degrees
		S32 s32Lat = 0;
		F64 f64Lat = 0.0;
		rBuffer.ReadS32(&s32Lat);
		f64Lat = static_cast<F64>(s32Lat);
		f64Lat = f64Lat * (180.0 / (1024 * 1024 * 32));
		safetyNets.airId2.f64Lat = f64Lat;

		// 4 byte : Conflict Longitude in WGS-84
		// Range -180 <= latitude <= 180 deg.
		// LSB : 180/2^25 degrees
		S32 s32Lon = 0;
		F64 f64Lon = 0.0;
		rBuffer.ReadS32(&s32Lon);
		f64Lon = static_cast<F64>(s32Lon);
		f64Lon = f64Lon * (180.0 / (1024 * 1024 * 32));
		safetyNets.airId2.f64Lon = f64Lon;

		// 2 byte : Conflict Altitude
		// LSB : 25ft
		// Hmin : -1500 ft
		// Hmax : 150000 ft
		// Altitude expressed in two's complement form.
		S16 s16Alt;
		S32 s32Alt;
		F64 f64Alt;
		rBuffer.ReadS16(&s16Alt);
		f64Alt = static_cast<F64>(s16Alt);
		s32Alt = static_cast<S32>(f64Alt);
		s32Alt = s32Alt * 25;
		safetyNets.airId2.s32Alt = s32Alt;

		if (DEBUG) {
			tmpBuf += QString(" Predicted Conflict Position Aircraft 1 (WGS-84): Lat=%1, Lon=%2, Alt=%3\n")
					.arg(safetyNets.airId2.f64Lat).arg(safetyNets.airId2.f64Lon).arg(safetyNets.airId2.s32Alt);
		}
	}

	if (u8CPC) {
		// Subfield #4 : Predicted Conflict Position Aircraft 1 in Cartesian Coordinates.
		// Definition  : Predicted conflict position for the aircraft 1 involved in the conflict
		// Format      : Eight-octet fixed length Data Item

		// bit-48/33 (X-Position) Starting X-position of the conflict
		// LSB = 0.5m
		U32 u32XPOS = 0;
		rBuffer.ReadU24(&u32XPOS);
		F64 f64XPOS = 0.0;
		f64XPOS = 0.5 * u32XPOS;
		safetyNets.airId2.f64XPOS = f64XPOS;

		// bit-32/17 (Y-Position) Starting Y-position of the conflict
		// LSB = 0.5m
		U32 u32YPOS = 0;
		rBuffer.ReadU24(&u32YPOS);
		F64 f64YPOS = 0.0;
		f64YPOS = 0.5 * u32YPOS;
		safetyNets.airId2.f64YPOS = f64YPOS;

		// bit-16/1 (Z-Position) Starting Z-position of the conflict
		// LSB = 25 ft
		// Hmin = -1500 ft
		// Hmax = 150000 ft
		S16 s16ZPOS;
		S32 s32ZPOS;
		F64 f64ZPOS;
		rBuffer.ReadS16(&s16ZPOS);
		f64ZPOS = static_cast<F64>(s16ZPOS);
		s32ZPOS = static_cast<S32>(f64ZPOS);
		s32ZPOS = s32ZPOS * 25;
		safetyNets.airId2.s32ZPOS = s32ZPOS;

		if (DEBUG) {
			tmpBuf += QString(" Predicted Conflict Position Aircraft 1 in Cartesian Coordinates: X=%1, Y=%2, Z=%3\n")
					.arg(safetyNets.airId2.f64XPOS).arg(safetyNets.airId2.f64YPOS).arg(safetyNets.airId2.s32ZPOS);
		}
	}

	if (u8TT1) {
		// Subfield #5 : Time to Threshold Aircraft 1
		// Defintion   : Time to runway threshold for first approaching aircraft in a RIMCA
		// Format      : Three-octet fixed length Data Item.
		// LSB         : 1/128 sec
		// NOTE        : Time to Threshold expressed in Two's Complement.
		F64 f64TimeToThreshold = 0.0;
		U32 u32TimeToThreshold = 0;
		rBuffer.ReadU24(&u32TimeToThreshold);
		f64TimeToThreshold = (1.0 / 128) * u32TimeToThreshold;
		safetyNets.airId2.f64TimeToThreshold = f64TimeToThreshold;
		if (DEBUG) {
			tmpBuf += QString(" Time to Threshold Aircraft 1 : %1\n").arg(safetyNets.airId2.f64TimeToThreshold);
		}
	}

	if (u8DT1) {
		// Subfield #6 : Distance to Threshold Aircraft 1
		// Definition  : Distance from threshold for Aircraft 1 involved in a RIMCA.
		// Format      : Two-octet fixed length Data Item
		// bits 16/1   : Distance to Threshold
		// LSB         : 0.5m
		F64 f64DistToThreshold = 0.0;
		U16 u16DistToThreshold = 0;
		rBuffer.ReadU16(&u16DistToThreshold);
		f64DistToThreshold = (0.5) * u16DistToThreshold;
		safetyNets.airId2.f64DistToThreshold = f64DistToThreshold;
		if (DEBUG) {
			tmpBuf += QString(" Distance to Threshold Aircraft 1 : %1\n").arg(safetyNets.airId2.f64DistToThreshold);
		}
	}

	if (u8AC1) {
		// Subfield #7 : Aircraft Characteristics Aircraft 1
		// Definition  : Characteristics of Aircraft 1 involved in the Conflict
		// Format      : Variable length Data Item comprising a first part of one octet,
		//               followed by one-octet extents as necessary
		U8 u8GATOAT = 0;
		U8 u8FR1FR2 = 0;
		U8 u8RVSM   = 0;
		U8 u8HPR    = 0;
		U8 u8CMD    = 0;
		U8 u8PRI    = 0;
		U8 u8GV     = 0;

		rBuffer.ReadU8(&u8Buf);

		u8GATOAT = (u8Buf & 0xC0) >> 6;
		u8FR1FR2 = (u8Buf & 0x30) >> 4;
		u8RVSM   = (u8Buf & 0x0C) >> 2;
		u8HPR    = (u8Buf & 0x02) >> 1;
		u8EFX    = (u8Buf & 0x01);

		safetyNets.airId2.u8GATOAT = u8GATOAT;
		safetyNets.airId2.u8FR1FR2 = u8FR1FR2;
		safetyNets.airId2.u8RVSM   = u8RVSM;
		safetyNets.airId2.u8HRP    = u8HPR;

		if (DEBUG) {
			tmpBuf += QString(" Aircraft Characteristics Aircraft 1 \n");
			tmpBuf += QString("    GATOAT : %1, FR1FR2 : %2, RVSM : %3, HRP : %4\n")
					.arg(u8GATOAT).arg(u8FR1FR2).arg(u8RVSM).arg(u8HPR);
		}

		if (u8EFX) {
			U8 u8CDM = 0;
			U8 u8PRI = 0;
			U8 u8GV  = 0;

			rBuffer.ReadU8(&u8Buf);

			u8CDM = (u8Buf & 0xC0) >> 6;
			u8PRI = (u8Buf & 0x20) >> 5;
			u8GV  = (u8Buf & 0x10) >> 4;
			safetyNets.airId2.u8CDM = u8CDM;
			safetyNets.airId2.u8PRI = u8PRI;
			safetyNets.airId2.u8GV  = u8GV;

			if (DEBUG) {
				tmpBuf += QString("    CDM : %1, PRI : %2, GV : %3 \n")
						.arg(u8CDM).arg(u8PRI).arg(u8GV);
			}
		}
	}

	if (u8MS1) {
		// Subfield #8 : Mode-S Identifier Aircraft 1
		// Definition  : Aircraft Identification downloaded from Aircraft 1 involved in the conflict
		//               if equipped with a Mode-S transponder.
		// Format      : Six-octet fixed length Data Item
		// bits 48/1   : Characters 1-8(coded on 6 bits each) defining aircraft identification when
		//               a flight plan is available or the registration marking when no flight plan
		//               is available. Coding rules are provided in [4] Section 3.1.2.9
		U64 u64Buf = 0;
		rBuffer.ReadU48(&u64Buf);
		QString strModesID;
		U8 u8Tmp = 0;
		u8Tmp = static_cast<U8>( (u64Buf & 0x03FFFFFFFFFF) >> 42 );		// Character 1
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFCEFFFFFFFFF) >> 36 );		// Character 2
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFF0CFFFFFFF) >> 30);		// Character 3
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFC0FFFFFF) >> 24);		// Character 4
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFF03FFFF) >> 18);		// Character 5
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFFFC0FFF) >> 12);		// Character 6
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFFFFF0CF) >> 6);		// Character 7
		strModesID.append(QChar::fromAscii(u8Tmp));

		u8Tmp = static_cast<U8>( (u64Buf & 0xFFFFFFFFFF30));			// Character 8
		strModesID.append(QChar::fromAscii(u8Tmp));

		safetyNets.airId2.strModesID = strModesID;

		if (DEBUG) {
			tmpBuf += QString(" Mode-S Identifier Aircraft 1 : %1\n").arg(safetyNets.airId2.strModesID);
		}
	}

	if (u8FP1) {
		// Subfield #9 : Flight Plan Number Aircraft 1
		// Defintion   : Number of the Flight Plan Correlated to Aircraft 1 involved in the Conflict
		// Format      : Four-octet fixed length Data Item.
		// NBR         : Number from 0 to 99 999 999
		U32 u32NBR = 0;
		rBuffer.ReadU32(&u32NBR);

		safetyNets.airId2.u32NBR = u32NBR;

		if (DEBUG) {
			tmpBuf += QString(" Flight Plan Number Aircraft 1 : %1\n").arg(safetyNets.airId2.u32NBR);
		}
	}

	if (u8CF1) {
		// Subfield #10 : Cleared Flight Level Aircraft 1
		// Defintion    : Cleared Flight Level for Aircraft 1 involved in the Conflict
		// Format       : Two-octet fixed length Data Item
		// CFL          : Cleared Flight Level
		// LSB          : 1/4 FL
		S16 s16CFL = 0;
		rBuffer.ReadS16(&s16CFL);
		F64 f64CFL = 0.0;
		f64CFL = static_cast<F64>(s16CFL);
		f64CFL = f64CFL * (1/4);

		safetyNets.airId2.f64CFL = f64CFL;

		if (DEBUG) {
			tmpBuf += QString(" Cleared Flight Level Aircraft 1 : %1\n").arg(safetyNets.airId2.f64CFL);
		}
	}
}

BOOL Cat004::FSPec(CBuffer& rBuffer)
{
	U8 u8;
	S16 s16Index = 0;

	do {
		rBuffer.ReadU8(&u8);

		for (S16 s16 = 0; s16 < 7; s16++)
		{
			//qDebug () << s16Index;
			++s16Index;
			if (s16Index >= MAX_FSPEC)
			{
				return FALSE;
			}
			if (u8 & (0x80 >> s16))
			{
				m_bFSPEC[s16Index] = TRUE;
			}
		}
	}while(u8 & 0x01);		// FX

	return TRUE;
}
