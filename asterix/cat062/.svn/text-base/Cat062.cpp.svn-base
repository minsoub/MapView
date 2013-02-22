/*
 * Cat062.cpp
 *
 *  Created on: 2012. 4. 10.
 *      Author: JMS
 *  Reference :
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 */
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "Cat062.h"

Cat062::Cat062() {
	// TODO Auto-generated constructor stub
}

Cat062::~Cat062() {
	// TODO Auto-generated destructor stub
}

void Cat062::Clear()
{
	tmpBuf = "";
	fileMode = 0;

	systemTrack.Clear();
	mode3A.Clear();
	mode5.Clear();
	trackStatus.Clear();
	stuAges.Clear();
	trackAges.Clear();
	measuredInfo.Clear();
	derivedData.Clear();
	flightPlanData.Clear();
	estAccuracyData.Clear();

	for (int i=0; i<MAX_FSPEC; i++) {
		m_bFSPEC[i] = FALSE;
	}
}

void Cat062::BufferPrint(CBuffer& rBuffer, int s, int end, QString item)
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
	tmpBuf = tmpBuf + str;

	//qDebug() << str;
}

void Cat062::GetPacket(CBuffer& rBuffer)
{
	index = rBuffer.GetIndex();

	// Len - 2
	U16 u16Length = 0;
	rBuffer.ReadU16(&u16Length);
	this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
	index = rBuffer.GetIndex();
	S32 s32MaxIndex = rBuffer.GetIndex() + u16Length - 3;

	m_TimeOfPacket.GetSysTime();	  // set current time

	while (rBuffer.GetIndex() < s32MaxIndex)
	{
		Clear();		// Decoding category 062

		if (!FSPec(rBuffer))
		{
			qDebug() << "System Track FSPEC Error.............";
			return;
		}else {
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
			index = rBuffer.GetIndex();

			tmpBuf += "FSPec ................................\n";
			for (int i=1; i<48; i++) {
				if (i % 8 == 0) tmpBuf += "\n";
				tmpBuf += QString ("%1 = %2, ").arg(searchItem(i)).arg(m_bFSPEC[i]);
			}
			tmpBuf += "\n";
		}

		/* I062/010 Data Source Identifier  */
		if (m_bFSPEC[1]) {
			I062_010(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "010");
			index = rBuffer.GetIndex();
		}

		/* I062/015 Service Identifation */
		if (m_bFSPEC[3]) {
			I062_015(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "015");
			index = rBuffer.GetIndex();
		}

		/* I062/070 Time of Track Information */
		if (m_bFSPEC[4]) {
			I062_070(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "070");
			index = rBuffer.GetIndex();
		}

		/* I062/105 Calculated Position In WGS-84 Co-ordinates */
		if (m_bFSPEC[5]) {
			I062_105(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "105");
			index = rBuffer.GetIndex();
		}

		/* I062/100 Calculated Track Position. (Cartesian) */
		if (m_bFSPEC[6]) {
			I062_100(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "100");
			index = rBuffer.GetIndex();
		}

		/* I062/185 Calculated Track Velocity (Cartesian) */
		if (m_bFSPEC[7]) {
			I062_185(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "185");
			index = rBuffer.GetIndex();
		}

		/* I062/210 Calculated Acceleration (Cartesian) */
		if (m_bFSPEC[8]) {
			I062_210(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "210");
			index = rBuffer.GetIndex();
		}

		/* I062/060 Track Mode 3/A Code */
		if (m_bFSPEC[9]) {
			I062_060(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "060");
			index = rBuffer.GetIndex();
		}

		/* I062/245 Target Identification */
		if (m_bFSPEC[10]) {
			I062_245(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "245");
			index = rBuffer.GetIndex();
		}

		/* I062/380 Aircraft Derived Data */
		if (m_bFSPEC[11]) {
			I062_380(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "380");
			index = rBuffer.GetIndex();
		}

		/* I062/040 Track Number */
		if (m_bFSPEC[12]) {
			I062_040(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "040");
			index = rBuffer.GetIndex();
		}

		/* I062/080 Track Status */
		if (m_bFSPEC[13]) {
			I062_080(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "080");
			index = rBuffer.GetIndex();
		}

		/* I062/290 System Track Update Ages */
		if (m_bFSPEC[14]) {
			I062_290(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "290");
			index = rBuffer.GetIndex();
		}

		/* I062/200 Mode of Movement */
		if (m_bFSPEC[15]) {
			I062_200(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "200");
			index = rBuffer.GetIndex();
		}

		/* I062/295 Track Data Ages */
		if (m_bFSPEC[16]) {
			I062_295(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "295");
			index = rBuffer.GetIndex();
		}

		/* I062/136 Measured Flight Level */
		if (m_bFSPEC[17]) {
			I062_136(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "136");
			index = rBuffer.GetIndex();
		}

		/* I062/130 Calculated Track Geometric Altitude */
		if (m_bFSPEC[18]) {
			I062_130(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "130");
			index = rBuffer.GetIndex();
		}

		/* I062/135 Calculated Track Barometric Altitude */
		if (m_bFSPEC[19]) {
			I062_135(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "135");
			index = rBuffer.GetIndex();
		}

		/* I062/220 Calculated Rate Of Climb/Descent */
		if (m_bFSPEC[20]) {
			I062_220(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "220");
			index = rBuffer.GetIndex();
		}

		/* I062/390 Flight Plan Related Data */
		if (m_bFSPEC[21]) {
			I062_390(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "390");
			index = rBuffer.GetIndex();
		}

		/* I062/270 Target size & Orientation */
		if (m_bFSPEC[22]) {
			I062_270(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "270");
			index = rBuffer.GetIndex();
		}

		/* I062/300 Vehicle Fleet Identification */
		if (m_bFSPEC[23]) {
			I062_300(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "300");
			index = rBuffer.GetIndex();
		}

		/* I062/110 Mode 5 Data reports & Extended Mode 1 Code */
		if (m_bFSPEC[24]) {
			I062_110(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "110");
			index = rBuffer.GetIndex();
		}

		/* I062/120 Track Mode 2 Code */
		if (m_bFSPEC[25]) {
			I062_120(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "120");
			index = rBuffer.GetIndex();
		}

		/* I062/510 Composed Track Number */
		if (m_bFSPEC[26]) {
			I062_510(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "510");
			index = rBuffer.GetIndex();
		}

		/* I062/500 Estimated Accuracies */
		if (m_bFSPEC[27]) {
			I062_500(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "500");
			index = rBuffer.GetIndex();
		}

		/* I062/340 Measured Information */
		if (m_bFSPEC[28]) {
			I062_340(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "340");
			index = rBuffer.GetIndex();
		}

	}
}

/**
 * Data Item I062/010	Data Source Identifier
 * Definition : Identification of the Safety Nets server sending the message.
 * Format : Two-octet fixed length Data Item.
 */
void Cat062::I062_010(CBuffer& rBuffer)
{
	U8 u8SAC = 0x00;
	U8 u8SIC = 0x00;

	rBuffer.ReadU8(&u8SAC);
	rBuffer.ReadU8(&u8SIC);

	systemTrack.sac = u8SAC;
	systemTrack.sic = u8SIC;

	// debug
	if (DEBUG)
	{
		//qDebug() << QString("SAC : %1, SIC : %2\n").arg(u8SAC).arg(u8SIC);
		tmpBuf += QString("Data Item I062/010 SAC : %1, SIC : %2\n").arg(u8SAC).arg(u8SIC);
	}
}

/**
 * Data Item I062/015	Service Identification
 * Defination : Identification of the service provided to one or more users.
 * Format     : One-Octet fixed length data item
 * NOTE       : The service identification is allocated by the system
 */
void Cat062::I062_015(CBuffer& rBuffer)
{
	U8 u8SID = 0x00;

	rBuffer.ReadU8(&u8SID);

	systemTrack.sid = u8SID;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/015 Service Identification : %1\n").arg(u8SID);
}

/**
 * Data Item I062/040	Track Number
 * Defination : Identification of a track
 * Format     : Two-Octet fixed length data item
 * Encoding Rule : This item shall be present in every ASTERIX record
 */
void Cat062::I062_040(CBuffer& rBuffer)
{
	U16 u16TN = 0;

	rBuffer.ReadU16(&u16TN);

	systemTrack.TRACK_NUM = u16TN;

	// debug
	if (DEBUG)
	{
		//qDebug() << QString("Track Number : %1\n").arg(s16TN);
		tmpBuf += QString("Data Item I062/040 Track Number : %1\n").arg(u16TN);
	}
}

/**
 * Data Item I062/060	Track Mode 3/A Code
 * Definition : Mode-3/A code converted into octal representation.
 * Format     : Two-octet fixed length Data Item
 * Structure  :
 *              bits-16/15       Spare bits set to 0
 *              bit 14     (CH)  Change in Mode 3/A
 *                               = 0   No Change
 *                               = 1   Mode 3/A has changed
 *              bit-13           Spare bits set to 0
 *              bit-12/1         Mode-3/A reply in octal representation
 * Encoding Rule : This item is optional
 */
void Cat062::I062_060(CBuffer& rBuffer)
{
	S16 s16EM1 = 0;
	rBuffer.ReadS16(&s16EM1);

	U8 u8CH = (s16EM1 & 0x2000) >> 13;
	U8 s1 = (s16EM1 & 0x0E00) >> 9;
	U8 s2 = (s16EM1 & 0x01C0) >> 6;
	U8 s3 = (s16EM1 & 0x0038) >> 3;
	U8 s4 = (s16EM1 & 0x0007);

	mode3A.chMode = u8CH;
	mode3A.mode3ACode = QString("%1%2%3%4").arg(s1).arg(s2).arg(s3).arg(s4);

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/060 Track Mode 3/A Code : %1\n").arg(mode3A.mode3ACode);
}

/**
 * Data Item I062/070	Time of Track Information
 * Definition : Absolute time stamping of the information provided in the track message,
 * 				in the form of elapsed time since last midnight, expressed as UTC.
 * Format     : Three-Octet fixed length data item.
 * LSB        : 1/128 s
 * NOTES      : 1. This is the time of the track state vector.
 *              2. The time is reset to zero at every midnight.
 */
void Cat062::I062_070(CBuffer& rBuffer)
{
	U32 u32TimeOfDay = 0x00000000;
	rBuffer.ReadU24(&u32TimeOfDay);	// 3 byte read
	F64 f64TimeOfDay = (1.0 / 128.0) * u32TimeOfDay;

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

	systemTrack.timeStamp = TimeStamp;

	S8* s8 = TimeStamp.GetStrTime();

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/070	Time of Track Information : %1\n").arg(s8);


}

/**
 * Data Item I062/080	Track Status
 * Defintion : Status of a track
 * Format    : Variable length data item comprising a first part of one Octet,
 *             followed by 1-Octet extents as necessary.
 * Structure : refer to TrackStatus.h
 *
 */
void Cat062::I062_080(CBuffer& rBuffer)
{
	U8 u8MON = 0x00;
	U8 u8SPI = 0x00;
	U8 u8MRH = 0x00;
	U8 u8SRC = 0x00;
	U8 u8CNF = 0x00;
	U8 u8FX  = 0x00;
	U8 u8Buf = 0x00;
	U8 u8SIM = 0x00;
	U8 u8TSE = 0x00;
	U8 u8TSB = 0x00;
	U8 u8FPC = 0x00;
	U8 u8AFF = 0x00;
	U8 u8STP = 0x00;
	U8 u8KOS = 0x00;
	U8 u8AMA = 0x00;
	U8 u8MD4 = 0x00;
	U8 u8ME  = 0x00;
	U8 u8MI  = 0x00;
	U8 u8MD5 = 0x00;
	U8 u8CST = 0x00;
	U8 u8PSR = 0x00;
	U8 u8SSR = 0x00;
	U8 u8MDS = 0x00;
	U8 u8ADS = 0x00;
	U8 u8SUC = 0x00;
	U8 u8AAC = 0x00;
	U8 u8SDS = 0x00;
	U8 u8EMS = 0x00;


	rBuffer.ReadU8(&u8Buf);
	u8MON = (u8Buf & 0x80) >> 7;
	u8SPI = (u8Buf & 0x40) >> 6;
	u8MRH = (u8Buf & 0x20) >> 5;
	u8SRC = (u8Buf & 0x1C) >> 2;
	u8CNF = (u8Buf & 0x02) >> 1;
	u8FX = (u8Buf & 0x01);

	trackStatus.mon = u8MON;
	trackStatus.spi = u8SPI;
	trackStatus.mrh = u8MRH;
	trackStatus.src = u8SRC;
	trackStatus.cnf = u8CNF;

	if (DEBUG) {
		tmpBuf += QString("Data Item I062/080\n");
		tmpBuf += QString("  mon : %1, spi : %2, mrh : %3, src : %4, cnf : %5 \n").
				arg(u8MON).arg(u8SPI).arg(u8MRH).arg(u8SRC).arg(u8CNF);
	}
	if (u8FX) {
		rBuffer.ReadU8(&u8Buf);
		u8SIM = (u8Buf & 0x80) >> 7;
		u8TSE = (u8Buf & 0x40) >> 6;
		u8TSB = (u8Buf & 0x20) >> 5;
		u8FPC = (u8Buf & 0x10) >> 4;
		u8AFF = (u8Buf & 0x08) >> 3;
		u8STP = (u8Buf & 0x04) >> 2;
		u8KOS = (u8Buf & 0x02) >> 1;
		u8FX  = (u8Buf & 0x01);

		trackStatus.sim = u8SIM;
		trackStatus.tse = u8TSE;
		trackStatus.tsb = u8TSB;
		trackStatus.fpc = u8FPC;
		trackStatus.aff = u8AFF;
		trackStatus.stp = u8STP;
		trackStatus.kos = u8KOS;

		if (DEBUG) {
			tmpBuf += QString("  sim : %1, tse : %2, tsb : %3, fpc : %4, aff : %5, stp : %6, kos : %7 \n").
					arg(u8SIM).arg(u8TSE).arg(u8TSB).arg(u8FPC).arg(u8AFF).arg(u8STP).arg(u8KOS);
		}
	}

	if (u8FX) {
		rBuffer.ReadU8(&u8Buf);
		u8AMA = (u8Buf & 0x80) >> 7;
		u8MD4 = (u8Buf & 0x60) >> 5;
		u8ME  = (u8Buf & 0x10) >> 4;
		u8MI  = (u8Buf & 0x08) >> 3;
		u8MD5 = (u8Buf & 0x06) >> 1;
		u8FX  = (u8Buf & 0x01);

		trackStatus.ama = u8AMA;
		trackStatus.md4 = u8MD4;
		trackStatus.me  = u8ME;
		trackStatus.mi  = u8MI;
		trackStatus.md5 = u8MD5;

		if (DEBUG) {
			tmpBuf += QString("  ama : %1, md4 : %2, me : %3, mi : %4, md5 : %5 \n").
					arg(u8AMA).arg(u8MD4).arg(u8ME).arg(u8MI).arg(u8MD5);
		}
	}

	// Structure of Third Extent
	if (u8FX) {
		rBuffer.ReadU8(&u8Buf);
		u8CST = (u8Buf & 0x80) >> 7;
		u8PSR = (u8Buf & 0x40) >> 6;
		u8SSR = (u8Buf & 0x20) >> 5;
		u8MDS = (u8Buf & 0x10) >> 4;
		u8ADS = (u8Buf & 0x08) >> 3;
		u8SUC = (u8Buf & 0x04) >> 2;
		u8AAC = (u8Buf & 0x02) >> 1;
		u8FX  = (u8Buf & 0x01);

		trackStatus.cst = u8CST;			// Costing
		trackStatus.psr = u8PSR;			// PSR only
		trackStatus.ssr = u8SSR;			// SSR only
		trackStatus.mds = u8MDS;
		trackStatus.ads = u8ADS;
		trackStatus.suc = u8SUC;
		trackStatus.aac = u8AAC;

		if (DEBUG) {
			tmpBuf += QString("  cst : %1, psr : %2, ssr : %3, mds : %4, ads : %5, suc : %6, aac : %7 \n").
					arg(u8CST).arg(u8PSR).arg(u8SSR).arg(u8MDS).arg(u8ADS).arg(u8SUC).arg(u8AAC);
		}
	}



}

/**
 * Data Item I062/100	Calculated Track Position. (Cartesian)
 * Definition : Calculated position in Cartesian co-ordinates with a resolution of 0.5m,
 * 				in two's complement form.
 * Format     : Six-octet fixed length Data Item
 * LSB        : 0.5m
 */
void Cat062::I062_100(CBuffer& rBuffer)
{
	// bit-48/25(X-Position)
	// LSB = 0.5m
	U32 u32XPOS = 0;
	rBuffer.ReadU24(&u32XPOS);
	F64 f64XPOS = 0.0;
	f64XPOS = 0.5 * u32XPOS;
	systemTrack.cartesianXpos = f64XPOS;

	// bit-25/1 (Y-Position)
	// LSB = 0.5m
	U32 u32YPOS = 0;
	rBuffer.ReadU24(&u32YPOS);
	F64 f64YPOS = 0.0;
	f64YPOS = 0.5 * u32YPOS;
	systemTrack.cartesianYpos = f64YPOS;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/100 Calculated Track Position. (Cartesian)(X, Y) = (%1, %2) \n").arg(f64XPOS).arg(f64YPOS);
}

/**
 * Data Item I062/105	Calculated Position In WGS-84 Co-ordinates
 * Definition : Calculated Position in WGS-84 Co-ordinates with a resolution of 180/2^25. degrees
 * Format    : Eight-octet fixed length Data Item
 * NOTE      : The LSB provides a resolution at least better than 0.6m.
 */
void Cat062::I062_105(CBuffer& rBuffer)
{
	// 4 byte : Conflict Latitude in WGS-84
	// Range -90 <= latitude <= 90 deg.
	// LSB : 180/2^25 degrees
	S32 s32Lat = 0;
	F64 f64Lat = 0.0;
	rBuffer.ReadS32(&s32Lat);
	f64Lat = static_cast<F64>(s32Lat);
	f64Lat = f64Lat * (180.0 / (1024 * 1024 * 32));
	systemTrack.wgsXpos = f64Lat;

	// 4 byte : Conflict Longitude in WGS-84
	// Range -180 <= latitude <= 180 deg.
	// LSB : 180/2^25 degrees
	S32 s32Lon = 0;
	F64 f64Lon = 0.0;
	rBuffer.ReadS32(&s32Lon);
	f64Lon = static_cast<F64>(s32Lon);
	f64Lon = f64Lon * (180.0 / (1024 * 1024 * 32));
	systemTrack.wgsYpos = f64Lon;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/105 Calculated Position In WGS-84 Co-ordinates (X, Y) = (%1, %2) \n").arg(f64Lat).arg(f64Lon);
}

/**
 * Data Item I062/110	Mode 5 Data reports & Extended Mode 1 Code
 * Defintion : Mode 5 Data reports & Extended Mode 1 Code
 * Format    : Compound Data Item, comprising a primary sufield of one octet,
 * 			   followed by the indicated subfields.
 * This method refer to 'Mode5.h' in source file.
 */
void Cat062::I062_110(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Sum = 0x00;
	U8 u8Pmn = 0x00;
	U8 u8Pos = 0x00;
	U8 u8Ga  = 0x00;
	U8 u8Em1 = 0x00;
	U8 u8Tos = 0x00;
	U8 u8Xp  = 0x00;
	U8 u8FX  = 0x00;

	rBuffer.ReadU8(&u8Buf);

	u8Sum = (u8Buf & 0x80) >> 7;
	u8Pmn = (u8Buf & 0x40) >> 6;
	u8Pos = (u8Buf & 0x20) >> 5;
	u8Ga  = (u8Buf & 0x10) >> 4;
	u8Em1 = (u8Buf & 0x08) >> 3;
	u8Tos = (u8Buf & 0x04) >> 2;
	u8Xp  = (u8Buf & 0x02) >> 1;
	u8FX  = (u8Buf & 0x01);

	mode5.sum = u8Sum;
	mode5.pmn = u8Pmn;
	mode5.pos = u8Pos;
	mode5.ga  = u8Ga;
	mode5.em1 = u8Em1;
	mode5.tosCHK = u8Tos;
	mode5.xp  = u8Xp;

	if (DEBUG) {
		tmpBuf += QString("Data Item I062/110\n");
		tmpBuf += QString("  sum : %1, pmn : %2, pos : %3, ga : %4, eml : %5, tosCHK : %6, xp : %7 \n").
				arg(u8Sum).arg(u8Pmn).arg(u8Pos).arg(u8Ga).arg(u8Em1).arg(u8Tos).arg(u8Xp);
	}

	// Subfield #1 : Mode 5 Summary
	if (u8FX & u8Sum) {
		U8 u8M5 = 0x00;
		U8 u8ID = 0x00;
		U8 u8DA = 0x00;
		U8 u8M1 = 0x00;
		U8 u8M2 = 0x00;
		U8 u8M3 = 0x00;
		U8 u8MC = 0x00;
		U8 u8X  = 0x00;

		rBuffer.ReadU8(&u8Buf);

		u8M5 = (u8Buf & 0x80) >> 7;
		u8ID = (u8Buf & 0x40) >> 6;
		u8DA = (u8Buf & 0x20) >> 5;
		u8M1 = (u8Buf & 0x10) >> 4;
		u8M2 = (u8Buf & 0x08) >> 3;
		u8M3 = (u8Buf & 0x04) >> 2;
		u8MC = (u8Buf & 0x02) >> 1;
		u8X  = (u8Buf & 0x01);

		mode5.m5 = u8M5;
		mode5.id = u8ID;
		mode5.m1 = u8M1;
		mode5.m2 = u8M2;
		mode5.m3 = u8M3;
		mode5.mc = u8MC;
		mode5.x  = u8X;

		if (DEBUG) {
			tmpBuf += QString("  md5 : %1, id : %2, m1 : %3, m2 : %4, m3 : %5, mc : %6, x : %7 \n").
					arg(u8M5).arg(u8ID).arg(u8M1).arg(u8M2).arg(u8M3).arg(u8MC).arg(u8X);
		}
	}

	// Subfield #2 : Mode 5 PIN/National Origin/Mission Code
	if (u8FX & u8Pmn) {
		S16 s16Pin = 0;
		U8  u8Nat  = 0x00;
		U8  u8Mis  = 0x00;

		rBuffer.ReadS16(&s16Pin);

		rBuffer.ReadU8(&u8Nat);
		rBuffer.ReadU8(&u8Mis);

		mode5.pin = s16Pin;
		mode5.nat = u8Nat;
		mode5.mis = u8Mis;

		if (DEBUG) {
			tmpBuf += QString("  pin : %1, nat : %2, mis : %3 \n").
					arg(s16Pin).arg(u8Nat).arg(u8Mis);
		}
	}

	// Subfield #3 : Mode 5 Reported Position
	if (u8FX & u8Pos) {
		// 3 byte : Latitude in WGS-84
		// Range -90 <= latitude <= 90 deg.
		// LSB : 180/2^23 degrees
		S32 s32Lat = 0;
		F64 f64Lat = 0.0;
		rBuffer.ReadS24(&s32Lat);
		f64Lat = static_cast<F64>(s32Lat);
		f64Lat = f64Lat * (180.0 / (1024 * 1024 * 8));
		mode5.lat = f64Lat;

		// 3 byte : Longitude in WGS-84
		// Range -180 <= latitude < 180 deg.
		// LSB : 180/2^23 degrees
		S32 s32Lon = 0;
		F64 f64Lon = 0.0;
		rBuffer.ReadS24(&s32Lon);
		f64Lon = static_cast<F64>(s32Lon);
		f64Lon = f64Lon * (180.0 / (1024 * 1024 * 8));
		mode5.lon = f64Lon;

		if (DEBUG) {
			tmpBuf += QString("  lat : %1, lon : %2 \n").
					arg(f64Lat).arg(f64Lon);
		}
	}

	// Subfield #4 : Mode 5 GNSS-derived Altitude
	if (u8FX & u8Ga) {
		U8 u8Res = 0x00;
		S16 s16Ga = 0;
		rBuffer.ReadS16(&s16Ga);

		u8Res = static_cast<U8>( (s16Ga & 0x4000) >> 14);
		s16Ga = (s16Ga & 0x3FFF);

		mode5.res = u8Res;
		mode5.s16Ga = s16Ga;

		if (DEBUG) {
			tmpBuf += QString("  res : %1, ga : %2 \n").
					arg(u8Res).arg(s16Ga);
		}
	}

	// Subfield #5 : Extended Mode 1 Code in Octal Representation
	if (u8FX & u8Em1) {
		S16 s16EM1 = 0;
		rBuffer.ReadS16(&s16EM1);

		U8 s1 = (s16EM1 & 0x0E00) >> 9;
		U8 s2 = (s16EM1 & 0x01C0) >> 6;
		U8 s3 = (s16EM1 & 0x0038) >> 3;
		U8 s4 = (s16EM1 & 0x0007);

		mode5.mode1Code = QString("%1%2%3%4").arg(s1).arg(s2).arg(s3).arg(s4);

		if (DEBUG) {
			tmpBuf += QString("  mode1Code : %1 \n").
					arg(mode5.mode1Code);
		}
	}

	// Subfield #6 : Time Offset for POS and GA
	// TODO: time of day
	if (u8FX & u8Tos) {
		U8 u8Tos2 = 0x00;
		F64 f64Tos = 0.0;
		rBuffer.ReadU8(&u8Tos2);

		f64Tos = (1.0/128.0) * u8Tos2;
		mode5.tos = f64Tos;

		if (DEBUG) {
			tmpBuf += QString("  Time Offset for POS and GA : %1 \n").
					arg(mode5.tos);
		}
	}

	// SubField #7 : X Pulse Presence
	if (u8FX & u8Xp) {
		U8 u8X5 = 0x00;		// X-pulse from Mode 5 Data reply or Report.
		U8 u8XC = 0x00;		// X-pulse from Mode C reply
		U8 u8X3 = 0x00;		// X-pulse from Mode 3/A reply
		U8 u8X2 = 0x00;		// X-pulse from Mode 2 reply
		U8 u8X1 = 0x00;		// X-pulse from Mode 1 reply

		rBuffer.ReadU8(&u8Buf);

		u8X5 = (u8Buf & 0x10) >> 4;
		u8XC = (u8Buf & 0x08) >> 3;
		u8X3 = (u8Buf & 0x04) >> 2;
		u8X2 = (u8Buf & 0x02) >> 1;
		u8X1 = (u8Buf & 0x01);

		mode5.x5 = u8X5;
		mode5.xc = u8XC;
		mode5.x3 = u8X3;
		mode5.x2 = u8X2;
		mode5.x1 = u8X1;

		if (DEBUG) {
			tmpBuf += QString("  X Pulse Presence  x5 : %1, xc : %2, x3 : %3, x2 : %4, x1 : %5 \n").
					arg(mode5.x5).arg(mode5.xc).arg(mode5.x3).arg(mode5.x2).arg(mode5.x1);
		}
	}
}

/**
 * Data Item I062/120	Track Mode 2 Code
 * Definition : Mode 2 code associated to the track
 * Format     : Two-Octet fixed length data item
 */
void Cat062::I062_120(CBuffer& rBuffer)
{
	S16 s16EM1 = 0;
	rBuffer.ReadS16(&s16EM1);

	U8 s1 = (s16EM1 & 0x0E00) >> 9;
	U8 s2 = (s16EM1 & 0x01C0) >> 6;
	U8 s3 = (s16EM1 & 0x0038) >> 3;
	U8 s4 = (s16EM1 & 0x0007);

	systemTrack.mode2Code = QString("%1%2%3%4").arg(s1).arg(s2).arg(s3).arg(s4);

	if (DEBUG) {
		tmpBuf += QString("Data Item I062/120\n");
		tmpBuf += QString("  Track Mode 2 Code: %1\n").
				arg(systemTrack.mode2Code);
	}
}

/**
 * Data Item I062/130	Calculated Track Geometric Altitude
 * Defintion : Vertical distance between the target and the projection of its
 *             position on the earth's ellipsoid, as defined by WGS84, in two's
 *             complement form.
 * Format    : Two-Octet fixed length data item.
 * LSB       : 6.25 ft
 * Vmin      : -1500 ft
 * Vmax      : 150000 ft
 * NOTES     : 1. LSB is requested to be thinner than 10 ft by ICAO
 *             2. The source of altitude is identified in bits (SRC) of item I062/080 Track Status
 */
void Cat062::I062_130(CBuffer& rBuffer)
{
	S16 s16Alt = 0;
	F64 f64Alt = 0.0;
	rBuffer.ReadS16(&s16Alt);

	f64Alt = static_cast<F64>(s16Alt);
	f64Alt = 6.25 * f64Alt;

	systemTrack.altGeo = f64Alt;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/130 Calculated Track Geometric Altitude = (%1) \n").arg(f64Alt);
}

/**
 * Data Item I062/135	Calculated Track Barometric Altitude
 * Definition : Calculated Barometric Altitude of the track, in two's complement form
 * Format     : Two-Octet fixed length data item.
 * LSB        : 1/4 FL = 25 ft
 * Vmin       : -15 FL
 * Vmax       : 1500 FL
 * NOTE       : ICAO specifies a range between -10 FL and 1267 FL for Mode C
 */
void Cat062::I062_135(CBuffer& rBuffer)
{
	U8 u8QNH = 0x00;
	S16 s16Alt = 0;
	F64 f64Alt = 0.0;

	rBuffer.ReadS16(&s16Alt);

	u8QNH = (s16Alt & 0x8000) >> 15;
	s16Alt = (s16Alt & 0x7FFF);
	//tmpBuf += QString("%1\n").arg(s16Alt);
	f64Alt = static_cast<F64>(s16Alt);
	//tmpBuf += QString("%1\n").arg(f64Alt);
	f64Alt =  f64Alt * 0.25;		// FL

	systemTrack.qnhApply = u8QNH;
	systemTrack.altBar = f64Alt;

	// debug
	if (DEBUG) {
		tmpBuf += QString("Data Item I062/135 Calculated Track Barometric QNH = (%1), Altitude = (%2) \n")
					.arg(u8QNH).arg(f64Alt);
		//if (f64Alt == 416000) {
		//	fileMode = 1;
		//}
	}
}

/**
 * Data Item I062/136	Measured Flight Level
 * Defintion : Last valid and credible flight level used to update the track, in two's complement form.
 * Structure : Two-Octet fixed length data item.
 * LSB       : 1/4 FL
 * Vmin      : -15 FL
 * Vmax      : 1500 FL
 * NOTES
 * 	1. The criteria to determine the credibility of the flight level are Tracker dependent.
 *  2. Credible means : within reasonable range of change with respect to the previous detection.
 *  3. ICAO specifies a range between -10FL and 1267 FL for Mode C
 *  4. This item includes the barometric altitude received from ADS-B
 */
void Cat062::I062_136(CBuffer& rBuffer)
{
	S16 s16FL = 0;
	F64 f64FL = 0.0;

	rBuffer.ReadS16(&s16FL);
	f64FL = static_cast<F64>(s16FL);

	f64FL = f64FL * 0.25;		// unit : FL

	systemTrack.measuredFL = f64FL;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/136 Measured Flight Level = (%1) \n").arg(f64FL);
}

/**
 * Data Item I062/185	Calculated Track Velocity (Cartesian)
 * Definition : Calculated track velocity expressed in Cartesian co-ordinates,
 * 				in two's complement form.
 * Format     : Four-octet fixed length Data Item.
 * Vx         : (LSB) = 0.25 m/s   -8192m/s <= Vx <= 8191.75 m/s
 * Vy         : (LSB) = 0.25 m/s   -8192m/s <= Vy <= 8191.75 m/s
 * NOTE       : The y-axis points to the Geographical North at the location of the target.
 */
void Cat062::I062_185(CBuffer& rBuffer)
{

	S16 s16VX = 0;
	S16 s16VY = 0;
	F64 f64VX = 0.0;
	F64 f64VY = 0.0;
	F64 heading = 0.0;
	int g_speed = 0;
	double PI = 3.14159265;

	rBuffer.ReadS16(&s16VX);
	rBuffer.ReadS16(&s16VY);

	f64VX = static_cast<S16>(s16VX);
	f64VY = static_cast<S16>(s16VY);

	f64VX = 0.25 * f64VX;
	f64VY = 0.25 * f64VY;

	systemTrack.vx = f64VX;
	systemTrack.vy = f64VY;

	systemTrack.speed = sqrt(f64VX*f64VX + f64VY*f64VY);

	g_speed = (int)((systemTrack.speed + 5) / 10);
	if (fabs(systemTrack.speed) < 0) {
		heading = 0.0;
	}else if(fabs(systemTrack.speed) - fabs(f64VY) > 0)
	{
		heading = 90.0 - (180.0 / PI) * acos(f64VX/systemTrack.speed);
		if (f64VY < 0) {
			heading = 180.0 - heading;
		}
	}else {
		heading = (f64VY > 0) ? 0.0 : 180.0;
	}

	if (heading < 0.0) {
		heading = heading + 360.0;
	}else if(heading > 360.0) {
		heading = heading - 360.0;
	}
	systemTrack.heading = heading;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/185 Calculated Track Velocity (Cartesian) (speed, heading) = (%1, %2) \n")
		.arg(systemTrack.speed).arg(heading);
}

/**
 * Data Item I062/200 Mode of Movement
 * Definition : Calculated Mode of Movement of a traget
 * Format     : One-Octet fixed length data item.
 *
 */
void Cat062::I062_200(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Trans = 0x00;
	U8 u8Long = 0x00;
	U8 u8Vert = 0x00;

	rBuffer.ReadU8(&u8Buf);

	u8Trans = (u8Buf & 0xC0) >> 6;
	u8Long  = (u8Buf & 0x30) >> 4;
	u8Vert  = (u8Buf & 0x0C) >> 2;

	systemTrack.u8Trans = u8Trans;
	systemTrack.u8Long  = u8Long;
	systemTrack.u8Vert  = u8Vert;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/200 Mode of Movement (trans = %1, long = %2, vert = %3 \n")
		.arg(u8Trans).arg(u8Long).arg(u8Vert);
}

/**
 * Data Item I062/210	Calculated Acceleration (Cartesian)
 * Definition : Calculated Acceleration of the target expressed in Cartesian co-ordinates,
 * 				in two's complement form.
 * Format     : Two-octet fixed length Data item.
 * LSB        : 0.25 m/s^2
 * NOTES
 * 		1. The y-axis points to the Geographical North at the location of the target.
 * 		2. Maximum value means maximum value or above.
 */
void Cat062::I062_210(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	F64 f64Ax = 0.0;
	F64 f64Ay = 0.0;

	rBuffer.ReadU8(&u8Buf);

	f64Ax = static_cast<F64>(u8Buf);
	f64Ax = f64Ax * 0.25;

	rBuffer.ReadU8(&u8Buf);

	f64Ay = static_cast<F64>(u8Buf);
	f64Ay = f64Ay * 0.25;

	systemTrack.ax = f64Ax;
	systemTrack.ay = f64Ay;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/210 Calculated Acceleration (Cartesian) : (x, y) = (%1, %2) \n")
		.arg(f64Ax).arg(f64Ay);
}

/**
 * Data Item I062/220	Calculated Rate Of Climb/Descent
 * Defintion : Calculated rate of Climb/Descent of an aircraft in two's complement form.
 * Format    : Two-Octet fixed length data item.
 * LSB       : 6.25 feet/mimute
 * NOTES
 * 		A positive value indicates a climb, whereas a negative value indicates a descent.
 */
void Cat062::I062_220(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;

	rBuffer.ReadS16(&s16Buf);

	f64Buf = s16Buf;
	f64Buf = f64Buf * 0.25;  // 6.25;

	systemTrack.climb_descent = f64Buf;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/220 Calculated Rate Of Climb/Descent = (%1) \n")
		.arg(f64Buf);
}

/**
 * Data Item I062/245	Target Identification
 * Definition : Target (aircraft or vehicle) identification in 8 characters.
 * Format     : Seven-octet fixed length Data item.
 *
 * STI = 00	Callsign or registeration downlinked from target
 *     = 01	Callsign not downlinked from target
 *     = 10 Registeration not downlinked from target.
 *     = 11 Invalid
 *
 * NOTEST
 * 		1. For coding, see section 3.8.2.9 of [Ref.3]
 * 		2. As the Callsign of the target can already be transmitted (thanks to I062/380
 * 		   Subfield #25 if downlinked from the aircrfat or thanks to I062/390 Subfield #2
 * 		   if the target is correlated to a flight plan), and in order to avoid confusion
 *         at end user's side, this item SHALL not be used..
 */
void Cat062::I062_245(CBuffer& rBuffer)
{
	U64 u64Buf = 0;
	U8  u8Buf  = 0x00;
	U8  u8STI  = 0x00;
	U8  u8Ch1  = 0x00;
	U8  u8Ch2  = 0x00;
	U8  u8Ch3  = 0x00;
	U8  u8Ch4  = 0x00;
	U8  u8Ch5  = 0x00;
	U8  u8Ch6  = 0x00;
	U8  u8Ch7  = 0x00;
	U8  u8Ch8  = 0x00;

	rBuffer.ReadU8(&u8Buf);
	u8STI = (u8Buf & 0xC0) >> 6;

	rBuffer.ReadU48(&u64Buf);

	u8Ch1 = (U8)((u64Buf & 0x0000FC0000000000) >> 42);
	u8Ch2 = (U8)((u64Buf & 0x000003F000000000) >> 36);
	u8Ch3 = (U8)((u64Buf & 0x0000000FC0000000) >> 30);
	u8Ch4 = (U8)((u64Buf & 0x000000003F000000) >> 24);
	u8Ch5 = (U8)((u64Buf & 0x0000000000FC0000) >> 18);
	u8Ch6 = (U8)((u64Buf & 0x000000000003F000) >> 12);
	u8Ch7 = (U8)((u64Buf & 0x0000000000000FC0) >> 6);
	u8Ch8 = (U8) (u64Buf & 0x000000000000003F);

	char ch[8];
	//= { CharacterValue(u8Ch1), CharacterValue(u8Ch2), CharacterValue(u8Ch3), CharacterValue(u8Ch4),
	//		CharacterValue(u8Ch5), CharacterValue(u8Ch6), CharacterValue(u8Ch7), CharacterValue(u8Ch8) };
	//qDebug() << u8Ch1 << u8Ch2 << u8Ch3 << u8Ch4 << u8Ch5 << u8Ch6 << u8Ch7 << u8Ch8 << "\n";

	sprintf(ch, "%c%c%c%c%c%c%c%c", u8Ch1, u8Ch2, u8Ch3,
			u8Ch4, u8Ch5, u8Ch6, u8Ch7, u8Ch8);

	//qDebug() << ch;

	systemTrack.u8STI      = u8STI;
	systemTrack.callsign = QString("%1").arg(ch);

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/245 Target Identification : STI = (%1), Callsign = (%2) \n")
					.arg(systemTrack.u8STI).arg(systemTrack.callsign);
}

/**
 * Data Item I062/270	Target Size & Orientation
 * Definition : Target size defined as length and width of the detected target,
 * 				and orientation.
 * Format     : Variable length Data Item comprising a first part of one octet,
 * 				followed by one-octet extends as necessary.
 */
void Cat062::I062_270(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Len = 0x00;
	U8 u8Ori = 0x00;
	U8 u8Wit = 0x00;
	U8 u8FX  = 0x00;
	F64 f64Ori = 0.0;

	rBuffer.ReadU8(&u8Buf);

	u8Len = (u8Buf >> 1) & 0x7F;
	u8FX  = (u8Buf & 0x01);

	if (u8FX) {
		rBuffer.ReadU8(&u8Buf);
		u8Ori = (u8Buf >> 1) & 0x7F;
		u8FX  = (u8Buf & 0x01);

		f64Ori = static_cast<F64>(u8Ori);
		f64Ori = f64Ori * 2.81;
	}

	if (u8FX) {
		rBuffer.ReadU8(&u8Buf);
		u8Wit = (u8Buf >> 1) & 0x7F;
		u8FX  = (u8Buf & 0x01);
	}
	systemTrack.targetLength = u8Len;
	systemTrack.orientation  = f64Ori;
	systemTrack.targetWidth  = u8Wit;

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/270	Target Size & Orientation : targetLength=%1, orientation=%2, targetWidth=%3 \n")
		.arg(u8Len).arg(f64Ori).arg(u8Wit);
}

/**
 * Data Item I062/290	System Track Update Ages
 * Definition : Ages of the last plot/local track/target report update for each
 * 				sensor type.
 * Format     : Compound Data Item, comprising a primary subfield of up to two
 * 				octets, followed by the indicated subfields.
 * NOTES
 * 	1. Except for Track Age, the ages are counted from Data Item I062/070, Time Of
 * 	   Track Information, using the following formula:
 * 		Age = Time of track informatioin - Time of last detection used to update the track.
 * 	2. The time of last detection is derived from monosensor category time of day
 * 	3. If the data has never been received, then the corresponding subfield is not sent.
 * 	4. Maximum value means maximum value or above.
 */
void Cat062::I062_290(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;
	F64 f64Buf = 0.0;

	rBuffer.ReadU8(&u8Buf);

	stuAges.trkCHK = (u8Buf & 0x80) >> 7;
	stuAges.psrCHK = (u8Buf & 0x40) >> 6;
	stuAges.ssrCHK = (u8Buf & 0x20) >> 5;
	stuAges.mdsCHK = (u8Buf & 0x10) >> 4;
	stuAges.adsCHK = (u8Buf & 0x08) >> 3;
	stuAges.esCHK  = (u8Buf & 0x04) >> 2;
	stuAges.vdlCHK = (u8Buf & 0x02) >> 1;
	u8Fx           = (u8Buf & 0x01);

	// debug
	if (DEBUG) {
		tmpBuf += QString("Data Item I062/290	System Track Update Ages /n");
		tmpBuf += QString("   trkCHK : %1, psrCHK : %2, ssrCHK : %3, mdsCHK : %4, adsCHK : %5, esCHK : %6, vdlCHK : %7\n")
						.arg(stuAges.trkCHK).arg(stuAges.psrCHK).arg(stuAges.ssrCHK).arg(stuAges.mdsCHK)
						.arg(stuAges.adsCHK).arg(stuAges.esCHK).arg(stuAges.vdlCHK);
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		stuAges.uatCHK = (u8Buf & 0x80) >> 7;
		stuAges.lopCHK = (u8Buf & 0x40) >> 6;
		stuAges.mltCHK = (u8Buf & 0x20) >> 5;

		u8Fx = (u8Buf & 0x01);
		if (DEBUG)
			tmpBuf += QString("   uatCHK : %1, lopCHK : %2, mltCHK : %3\n")
						.arg(stuAges.uatCHK).arg(stuAges.lopCHK).arg(stuAges.mltCHK);
	}

	// Track age
	if (stuAges.trkCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.trk = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   TRK : %1\n").arg(stuAges.trk);
	}

	// PSR age
	if (stuAges.psrCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.psr = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   PSR : %1\n").arg(stuAges.psr);
	}

	// SSR age
	if (stuAges.ssrCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.ssr = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   SSR : %1\n").arg(stuAges.ssr);
	}

	// Mode S age
	if (stuAges.mdsCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.mds = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   MDS : %1\n").arg(stuAges.mds);
	}

	// ADS-C age
	if (stuAges.adsCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.ads = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   ADS : %1\n").arg(stuAges.ads);
	}

	// ADS-B Extended Squitter age
	if (stuAges.esCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.es = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   ES : %1\n").arg(stuAges.es);
	}

	// ADS-B VDL Mode 4 age
	if (stuAges.vdlCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.vdl = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   VDL : %1\n").arg(stuAges.vdl);
	}

	// ADS-B UAT age
	if (stuAges.uatCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.uat = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   UAT : %1\n").arg(stuAges.uat);
	}

	// Loop age
	if (stuAges.lopCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.lop = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   LOP : %1\n").arg(stuAges.lop);
	}

	// Multilateration age
	if (stuAges.mltCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		stuAges.mlt = f64Buf;
		if (DEBUG)
			tmpBuf += QString("   MLT : %1\n").arg(stuAges.mlt);
	}
}

/**
 * Data Item I062/295	Track Data Ages
 * Definition : Ages of the data provided.
 * Format     : Compound Data Item, comprising a primary subfield of up to five
 * 				octets, followed by the indicated subfields.
 * NOTES
 * 		In all the subfields, the age is the time delay since the value was measured.
 */
void Cat062::I062_295(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;
	F64 f64Buf = 0.0;

	rBuffer.ReadU8(&u8Buf);

	trackAges.mflCHK = (u8Buf & 0x80) >> 7;
	trackAges.md1CHK = (u8Buf & 0x40) >> 6;
	trackAges.md2CHK = (u8Buf & 0x20) >> 5;
	trackAges.mdaCHK = (u8Buf & 0x10) >> 4;
	trackAges.md4CHK = (u8Buf & 0x08) >> 3;
	trackAges.md5CHK = (u8Buf & 0x04) >> 2;
	trackAges.mhgCHK = (u8Buf & 0x02) >> 1;
	u8Fx = (u8Buf & 0x01);

	// debug
	if (DEBUG)
		tmpBuf += QString("Data Item I062/295	Track Data Ages /n");
		tmpBuf += QString("   mflCHK : %1, md1CHK : %2, md2CHK : %3, mdaCHK : %4, md4CHK : %5, md5CHK : %6, mhgCHK : %7\n")
						.arg(trackAges.mflCHK).arg(trackAges.md1CHK).arg(trackAges.md2CHK).arg(trackAges.mdaCHK)
						.arg(trackAges.md4CHK).arg(trackAges.md5CHK).arg(trackAges.mhgCHK);

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		trackAges.iasCHK = (u8Buf & 0x80) >> 7;
		trackAges.tasCHK = (u8Buf & 0x40) >> 6;
		trackAges.salCHK = (u8Buf & 0x20) >> 5;
		trackAges.fssCHK = (u8Buf & 0x10) >> 4;
		trackAges.tidCHK = (u8Buf & 0x08) >> 3;
		trackAges.comCHK = (u8Buf & 0x04) >> 2;
		trackAges.sabCHK = (u8Buf & 0x02) >> 1;
		u8Fx = (u8Buf & 0x01);
		// debug
		if (DEBUG)
			tmpBuf += QString("   iasCHK : %1, tasCHK : %2, salCHK : %3, fssCHK : %4, tidCHK : %5, comCHK : %6, sabCHK : %7\n")
							.arg(trackAges.iasCHK).arg(trackAges.tasCHK).arg(trackAges.salCHK).arg(trackAges.fssCHK)
							.arg(trackAges.tidCHK).arg(trackAges.comCHK).arg(trackAges.sabCHK);
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		trackAges.acsCHK = (u8Buf & 0x80) >> 7;
		trackAges.bvrCHK = (u8Buf & 0x40) >> 6;
		trackAges.gvrCHK = (u8Buf & 0x20) >> 5;
		trackAges.ranCHK = (u8Buf & 0x10) >> 4;
		trackAges.tarCHK = (u8Buf & 0x08) >> 3;
		trackAges.tanCHK = (u8Buf & 0x04) >> 2;
		trackAges.gspCHK = (u8Buf & 0x02) >> 1;
		u8Fx = (u8Buf & 0x01);
		// debug
		if (DEBUG)
			tmpBuf += QString("   acsCHK : %1, bvrCHK : %2, gvrCHK : %3, ranCHK : %4, tarCHK : %5, tanCHK : %6, gspCHK : %7\n")
							.arg(trackAges.acsCHK).arg(trackAges.bvrCHK).arg(trackAges.gvrCHK).arg(trackAges.ranCHK)
							.arg(trackAges.tarCHK).arg(trackAges.tanCHK).arg(trackAges.gspCHK);
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		trackAges.vunCHK = (u8Buf & 0x80) >> 7;
		trackAges.metCHK = (u8Buf & 0x40) >> 6;
		trackAges.emcCHK = (u8Buf & 0x20) >> 5;
		trackAges.posCHK = (u8Buf & 0x10) >> 4;
		trackAges.galCHK = (u8Buf & 0x08) >> 3;
		trackAges.punCHK = (u8Buf & 0x04) >> 2;
		trackAges.mbCHK = (u8Buf & 0x02) >> 1;
		u8Fx = (u8Buf & 0x01);
		// debug
		if (DEBUG)
			tmpBuf += QString("   vunCHK : %1, metCHK : %2, emcCHK : %3, posCHK : %4, galCHK : %5, punCHK : %6, mbCHK : %7\n")
							.arg(trackAges.vunCHK).arg(trackAges.metCHK).arg(trackAges.emcCHK).arg(trackAges.posCHK)
							.arg(trackAges.galCHK).arg(trackAges.punCHK).arg(trackAges.mbCHK);
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		trackAges.iarCHK = (u8Buf & 0x80) >> 7;
		trackAges.macCHK = (u8Buf & 0x40) >> 6;
		trackAges.bpsCHK = (u8Buf & 0x20) >> 5;
		u8Fx = (u8Buf & 0x01);
		// debug
		if (DEBUG)
			tmpBuf += QString("   iarCHK : %1, macCHK : %2, bpsCHK : %3\n")
							.arg(trackAges.iarCHK).arg(trackAges.macCHK).arg(trackAges.bpsCHK);
	}

	// Structure of Subfield #1 : Measured Flight Level Age
	if (trackAges.mflCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.mfl = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Measured Flight Level Age : %1\n")
							.arg(trackAges.mfl);
	}

	// Structure of Subfield #2 : Mode 1 Age
	if (trackAges.md1CHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.md1 = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #2 : Mode 1 Age : %1\n")
							.arg(trackAges.md1);
	}

	// Structure of Subfield #3 : Mode 2 Age
	if (trackAges.md2CHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.md2 = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #3 : Mode 2 Age : %1\n")
							.arg(trackAges.md2);
	}

	// Structure of Subfield #4 : Mode 3/A Age
	if (trackAges.mdaCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.mda = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #4 : Mode 3/A Age : %1\n")
							.arg(trackAges.mda);
	}

	// Structure of Subfield #5 : Mode 4 Age
	if (trackAges.md4CHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.md4 = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #5 : Mode 4 Age : %1\n")
							.arg(trackAges.md4);
	}

	// Structure of Subfield #6 : Mode 5 Age
	if (trackAges.md5CHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.md5 = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #6 : Mode 5 Age : %1\n")
							.arg(trackAges.md5);
	}

	// Structure of Subfield #7 : Magnetic Heading Age
	if (trackAges.mhgCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.mhg = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #7 : Magnetic Heading Age : %1\n")
							.arg(trackAges.mhg);
	}

	// Structure of Subfield #8 : Indicated Airspeed / Mach Nb Age
	if (trackAges.iasCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.ias = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #8 : Indicated Airspeed / Mach Nb Age : %1\n")
							.arg(trackAges.ias);
	}

	// Structure of Subfield #9 : True Airspeed Age
	if (trackAges.tasCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.tas = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #9 : True Airspeed Age : %1\n")
							.arg(trackAges.tas);
	}

	// Structure of Subfield #10 : Selected Altitude Age
	if (trackAges.salCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.sal = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #10 : Selected Altitude Age : %1\n")
							.arg(trackAges.sal);
	}

	// Structure of Subfield #11 : Final State Selected Altitude Age
	if (trackAges.fssCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.fss = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #11 : Final State Selected Altitude Age : %1\n")
							.arg(trackAges.fss);
	}

	// Structure of Subfield #12 : Trajectory Intent Age
	if (trackAges.tidCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.tid = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #12 : Trajectory Intent Age : %1\n")
							.arg(trackAges.tid);
	}

	// Structure of Subfield #13 : Communication/ACAS Capability and Flight Status Age
	if (trackAges.comCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.com = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #13 : Communication/ACAS Capability and Flight Status Age : %1\n")
							.arg(trackAges.com);
	}

	// Structure of Subfield #14 : Status Reported by ADS-B Age
	if (trackAges.sabCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.sab = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #14 : Status Reported by ADS-B Age : %1\n")
							.arg(trackAges.sab);
	}

	// Structure of Subfield #15 : ACAS Resolution Advisory Report Age
	if (trackAges.acsCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.acs = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #15 : ACAS Resolution Advisory Report Age : %1\n")
							.arg(trackAges.acs);
	}

	// Structure of Subfield #16 : Barometric Vertical Rate Age
	if (trackAges.bvrCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.bvr = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #16 : Barometric Vertical Rate Age : %1\n")
							.arg(trackAges.bvr);
	}

	// Structure of Subfield #17 : Geometrical Vertical Rate Age
	if (trackAges.gvrCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.gvr = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #17 : Geometrical Vertical Rate Age : %1\n")
							.arg(trackAges.gvr);
	}

	// Structure of Subfield #18 : Roll Angle Age
	if (trackAges.ranCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.ran = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #18 : Roll Angle Age : %1\n")
							.arg(trackAges.ran);
	}

	// Structure of Subfield #19 : Track Angle Rate Age
	if (trackAges.tarCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.tar = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #19 : Track Angle Rate Age : %1\n")
							.arg(trackAges.tar);
	}

	// Structure of Subfield #20 : Track Angle Age
	if (trackAges.tanCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.tan = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #20 : Track Angle Age : %1\n")
							.arg(trackAges.tan);
	}

	// Structure of Subfield #21 : Ground Speed Age
	if (trackAges.gspCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.gsp = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #21 : Ground Speed Age : %1\n")
							.arg(trackAges.gsp);
	}

	// Structure of Subfield #22 : Velocity Uncertainty Age
	if (trackAges.vunCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.vun = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #22 : Velocity Uncertainty Age : %1\n")
							.arg(trackAges.vun);
	}

	// Structure of Subfield #23 : Meteorological Data Age
	if (trackAges.metCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.met = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #23 : Meteorological Data Age : %1\n")
							.arg(trackAges.met);
	}

	// Structure of Subfield #24 : Emitter Category Age
	if (trackAges.emcCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.emc = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #24 : Emitter Category Age : %1\n")
							.arg(trackAges.emc);
	}

	// Structure of Subfield #25 : Position Age
	if (trackAges.posCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.pos = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #25 : Position Age : %1\n")
							.arg(trackAges.pos);
	}

	// Structure of Subfield #26 : Geometric Altitude Age
	if (trackAges.galCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.gal = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #26 : Geometric Altitude Age : %1\n")
							.arg(trackAges.gal);
	}

	// Structure of Subfield #27 : Position Uncertainty Age
	if (trackAges.punCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.pun = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #27 : Position Uncertainty Age : %1\n")
							.arg(trackAges.pun);
	}

	// Structure of Subfield #28 : Mode S MB Data Age
	if (trackAges.mbCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.mb = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #28 : Mode S MB Data Age : %1\n")
							.arg(trackAges.mb);
	}

	// Structure of Subfield #29 : Indicated Airspeed Data Age
	if (trackAges.iarCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.iar = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #29 : Indicated Airspeed Data Age : %1\n")
							.arg(trackAges.iar);
	}

	// Structure of Subfield #30 : Mach Number Data Age
	if (trackAges.macCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.mac = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #30 : Mach Number Data Age : %1\n")
							.arg(trackAges.mac);
	}

	// Structure of Subfield #31 : Barometric Pressure Setting Data Age
	if (trackAges.bpsCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;
		trackAges.bps = f64Buf;
		// debug
		if (DEBUG)
			tmpBuf += QString("   Structure of Subfield #31 : Barometric Pressure Setting Data Age : %1\n")
							.arg(trackAges.bps);
	}
}

/**
 * Data Item I062/300	Vehicle Feet Identification
 * Definition : Vehicle fleet identification number
 * Format     : One octet fixed length Data item.
 *
 *  (VFI)
 *  	= 0 Unknown
 *  	= 1 ATC equipment maintenance
 *  	= 2 Airport maintenance
 *  	= 3 Fire
 *  	= 4 Bird scarer
 *  	= 5 Snow plough
 *  	= 6 Runway sweeper
 *  	= 7 Emergency
 *  	= 8 Police
 *  	= 9 Bus
 *  	= 10 Tug (push/tow)
 *  	= 11 Grass cutter
 *  	= 12 Fuel
 *  	= 13 Baggage
 *  	= 14 Catering
 *  	= 15 Aircraft maintenance
 *  	= 16 Flyco (follow me)
 */
void Cat062::I062_300(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;

	rBuffer.ReadU8(&u8Buf);

	systemTrack.vfi = u8Buf;
	if (DEBUG)
		tmpBuf += QString("Data Item I062/300	Vehicle Feet Identification : %1\n").arg(systemTrack.vfi);
}

/**
 * Data Item I062/340	Measured Information
 * Definition : All measured data related to the last report used to update the
 * 				track. These data are not used for ADS-B.
 * Format     : Compound Data Item, comprising a primary subfield of one octet,
 * 				followed by the indicated subfields.
 *
 */
void Cat062::I062_340(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;

	rBuffer.ReadU8(&u8Buf);

	measuredInfo.sidCHK = (u8Buf & 0x80) >> 7;
	measuredInfo.posCHK = (u8Buf & 0x40) >> 6;
	measuredInfo.heiCHK = (u8Buf & 0x20) >> 5;
	measuredInfo.mdcCHK = (u8Buf & 0x10) >> 4;
	measuredInfo.mdaCHK = (u8Buf & 0x08) >> 3;
	measuredInfo.typCHK = (u8Buf & 0x04) >> 2;
	u8Fx = (u8Buf & 0x01);

	if (DEBUG) {
		tmpBuf += QString("Data Item I062/340	Measured Information /n");
		tmpBuf += QString("   sidCHK : %1, posCHK : %2, heiCHK : %3, mdcCHK : %4, mdaCHK : %5, typCHK : %6\n")
						.arg(measuredInfo.sidCHK).arg(measuredInfo.posCHK).arg(measuredInfo.heiCHK).arg(measuredInfo.mdcCHK)
						.arg(measuredInfo.mdaCHK).arg(measuredInfo.typCHK);
	}

	// Structure of Subfield #1 : Sensor Identification
	if (measuredInfo.sidCHK) {
		rBuffer.ReadU8(&u8Buf);
		measuredInfo.sic = u8Buf;

		rBuffer.ReadU8(&u8Buf);
		measuredInfo.sac = u8Buf;

		if (DEBUG) {
			tmpBuf += QString("   Structure of Subfield #1 : Sensor Identification  sic : %1, sac : %2\n")
							.arg(measuredInfo.sic).arg(measuredInfo.sac);
		}
	}

	// Structure of Subfield #2 : Measured Position
	if (measuredInfo.posCHK) {
		F64 f64RHO = 0.0;
		F64 f64THETA = 0.0;
		S16 s16Buf = 0;

		rBuffer.ReadS16(&s16Buf);
		f64RHO = static_cast<F64>(s16Buf);

		f64RHO = f64RHO * (1.0/256.0);		// LSB = 1/256 NM

		rBuffer.ReadS16(&s16Buf);
		f64THETA = static_cast<F64>(s16Buf);

		f64THETA = f64THETA * (360.0 / (1024 * 64));		// LSB = 360 / 2^16 = 0.0055

		measuredInfo.rho = f64RHO;
		measuredInfo.theta = f64THETA;

		if (DEBUG) {
			tmpBuf += QString("   Structure of Subfield #2 : Measured Position  rho : %1, theta : %2\n")
							.arg(measuredInfo.rho).arg(measuredInfo.theta);
		}
	}

	// Structure of Subfield #3 : Measured 3-D Height
	if (measuredInfo.heiCHK) {
		S16 s16Buf = 0;
		F64 f64H = 0.0;

		rBuffer.ReadS16(&s16Buf);
		f64H = static_cast<F64>(s16Buf);

		f64H = f64H * 25.0;			// LSB = 25 feet

		measuredInfo.height = f64H;
		if (DEBUG) {
			tmpBuf += QString("   Structure of Subfield #3 : Measured 3-D Height  height : %1\n")
							.arg(measuredInfo.height);
		}
	}

	// Structure of Subfield #4 : Last Measured Mode C Code
	if (measuredInfo.mdcCHK) {
		U16 u16Buf = 0;
		F64 f64Buf = 0.0;

		rBuffer.ReadU16(&u16Buf);

		measuredInfo.v = (u16Buf & 0x8000) >> 15;
		measuredInfo.g = (u16Buf & 0x4000) >> 14;

		f64Buf = static_cast<F64>( u16Buf & 0x3FFF);
		f64Buf = f64Buf * 0.25;				// LSB = 1/4 FL

		measuredInfo.modeC = f64Buf;

		if (DEBUG) {
			tmpBuf += QString("   Structure of Subfield #4 : Last Measured Mode C Code  v : %1, g : %2, modeC : %3\n")
							.arg(measuredInfo.v).arg(measuredInfo.g).arg(measuredInfo.modeC);
		}
	}

	// Structure of Subfield #5 : Last Measured Mode 3/A Code
	if (measuredInfo.mdaCHK) {
		U16 u16Buf = 0;

		rBuffer.ReadU16(&u16Buf);

		measuredInfo.v2 = (u16Buf & 0x8000) >> 15;
		measuredInfo.g2 = (u16Buf & 0x4000) >> 14;
		measuredInfo.l  = (u16Buf & 0x2000) >> 13;

		U8 s1 = (u16Buf & 0x0E00) >> 9;
		U8 s2 = (u16Buf & 0x01C0) >> 6;
		U8 s3 = (u16Buf & 0x0038) >> 3;
		U8 s4 = (u16Buf & 0x0007);

		measuredInfo.mode3A = QString("%1%2%3%4").arg(s1).arg(s2).arg(s3).arg(s4);

		if (DEBUG) {
			tmpBuf += QString("   Structure of Subfield #5 : Last Measured Mode 3/A Code  v : %1, g : %2, l : %3, mode3a: %4\n")
							.arg(measuredInfo.v2).arg(measuredInfo.g2).arg(measuredInfo.l).arg(measuredInfo.mode3A);
		}
	}

	// Structure of Subfield #6 : Report Type
	if (measuredInfo.typCHK) {

		rBuffer.ReadU8(&u8Buf);

		measuredInfo.typ = (u8Buf & 0xE0) >> 5;
		measuredInfo.sim = (u8Buf & 0x10) >> 4;
		measuredInfo.rab = (u8Buf & 0x80) >> 3;
		measuredInfo.tst = (u8Buf & 0x40) >> 2;

		if (DEBUG) {
			tmpBuf += QString("   Structure of Subfield #6 : Report Type  typ : %1, sim : %2, rab : %3, tst : %4\n")
							.arg(measuredInfo.typ).arg(measuredInfo.sim).arg(measuredInfo.rab).arg(measuredInfo.tst);
		}
	}
}

/**
 * Data Item I062/380	Aircraft Derived Data
 * Definition : Data derived directly by the aircraft. This includes data transmitted
 * 				via Mode-S and ADS-B.
 * Format     : Compound Data Item, comprising a primary subfield of up to four octets,
 * 				followed by the indicated subfields.
 *
 */
void Cat062::I062_380(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;
	U16 u16Buf = 0;
	S16 s16Buf = 0;
	S32 s32Buf = 0;
	F64 f64Buf = 0.0;

	rBuffer.ReadU8(&u8Buf);

	derivedData.adrCHK = (u8Buf & 0x80) >> 7;
	derivedData.idCHK  = (u8Buf & 0x40) >> 6;
	derivedData.mhgCHK = (u8Buf & 0x20) >> 5;
	derivedData.iasCHK = (u8Buf & 0x10) >> 4;
	derivedData.tasCHK = (u8Buf & 0x08) >> 3;
	derivedData.salCHK = (u8Buf & 0x04) >> 2;
	derivedData.fssCHK = (u8Buf & 0x02) >> 1;
	u8Fx = (u8Buf & 0x01);

	// debug
	if (DEBUG) {
		tmpBuf += QString("Data Item I062/380	Aircraft Derived Data /n");
		tmpBuf += QString("   adrCHK : %1, idCHK : %2, mhgCHK : %3, iasCHK : %4, tasCHK : %5, salCHK : %6, fssCHK : %7\n")
						.arg(derivedData.adrCHK).arg(derivedData.idCHK).arg(derivedData.mhgCHK).arg(derivedData.iasCHK)
						.arg(derivedData.tasCHK).arg(derivedData.salCHK).arg(derivedData.fssCHK);
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		derivedData.tisCHK = (u8Buf & 0x80) >> 7;
		derivedData.tidCHK = (u8Buf & 0x40) >> 6;
		derivedData.comCHK = (u8Buf & 0x20) >> 5;
		derivedData.sabCHK = (u8Buf & 0x10) >> 4;
		derivedData.acsCHK = (u8Buf & 0x08) >> 3;
		derivedData.bvrCHK = (u8Buf & 0x04) >> 2;
		derivedData.gvrCHK = (u8Buf & 0x02) >> 1;
		u8Fx = (u8Buf & 0x01);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   tisCHK : %1, tidCHK : %2, comCHK : %3, sabCHK : %4, acsCHK : %5, bvrCHK : %6, gvrCHK : %7\n")
							.arg(derivedData.tisCHK).arg(derivedData.tidCHK).arg(derivedData.comCHK).arg(derivedData.sabCHK)
							.arg(derivedData.acsCHK).arg(derivedData.bvrCHK).arg(derivedData.gvrCHK);
		}
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		derivedData.ranCHK = (u8Buf & 0x80) >> 7;
		derivedData.tarCHK = (u8Buf & 0x40) >> 6;
		derivedData.tanCHK = (u8Buf & 0x20) >> 5;
		derivedData.gspCHK = (u8Buf & 0x10) >> 4;
		derivedData.vunCHK = (u8Buf & 0x08) >> 3;
		derivedData.metCHK = (u8Buf & 0x04) >> 2;
		derivedData.emcCHK = (u8Buf & 0x02) >> 1;
		u8Fx = (u8Buf & 0x01);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   ranCHK : %1, tarCHK : %2, tanCHK : %3, gspCHK : %4, vunCHK : %5, metCHK : %6, emcCHK : %7\n")
							.arg(derivedData.ranCHK).arg(derivedData.tarCHK).arg(derivedData.tanCHK).arg(derivedData.gspCHK)
							.arg(derivedData.vunCHK).arg(derivedData.metCHK).arg(derivedData.emcCHK);
		}
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		derivedData.posCHK = (u8Buf & 0x80) >> 7;
		derivedData.galCHK = (u8Buf & 0x40) >> 6;
		derivedData.punCHK = (u8Buf & 0x20) >> 5;
		derivedData.mbCHK = (u8Buf & 0x10) >> 4;
		derivedData.iarCHK = (u8Buf & 0x08) >> 3;
		derivedData.macCHK = (u8Buf & 0x04) >> 2;
		derivedData.bpsCHK = (u8Buf & 0x02) >> 1;
		u8Fx = (u8Buf & 0x01);
		// debug
		if (DEBUG) {
			tmpBuf += QString("   posCHK : %1, galCHK : %2, punCHK : %3, mbCHK : %4, iarCHK : %5, macCHK : %6, bpsCHK : %7\n")
							.arg(derivedData.posCHK).arg(derivedData.galCHK).arg(derivedData.punCHK).arg(derivedData.mbCHK)
							.arg(derivedData.iarCHK).arg(derivedData.macCHK).arg(derivedData.bpsCHK);
		}
	}

	// Subfield #1 : Target Address
	if (derivedData.adrCHK) {
		U32 u24Buf = 0;
		rBuffer.ReadU24(&u24Buf);

		derivedData.targetAddress = u24Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #1 : Target Address = %1\n")
							.arg(derivedData.targetAddress);
		}
	}

	// Subfield #2 : Target Identification
	if (derivedData.idCHK) {
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

		derivedData.targetId = QString(ch);  // QString("%1%2%3%4%5%6%7%8").arg(u8Ch1).arg(u8Ch2).arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6).arg(u8Ch7).arg(u8Ch8);
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #2 : Target Identification = %1\n")
							.arg(derivedData.targetId);
		}
	}

	// Subfield #3 : Magnetic Heading
	if (derivedData.mhgCHK) {

		rBuffer.ReadS16(&s16Buf);

		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * (360.0 / (1024.0 * 64.0));	// LSB = 360 / 2^16

		derivedData.magHeading = f64Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #3 : Magnetic Heading = %1\n")
							.arg(derivedData.magHeading);
		}
	}

	// Subfield #4 : Indicated Airspeed/ Mach Number
	if (derivedData.iasCHK) {

		rBuffer.ReadU16(&u16Buf);

		derivedData.im = (u16Buf & 0x8000) >> 15;
		s16Buf = (u16Buf & 0x7FFF);
		f64Buf = static_cast<F64>(s16Buf);

		if (derivedData.im) {
			f64Buf = f64Buf * 0.002;		// Air Speed = Mach, LSB(Bit-1) = 0.001
		}else {
			f64Buf = f64Buf * (1.0 / (1024.0 * 16.0));  // Air Speed = IAS, LSB(Bit-1) = 2^-14 NM/s
		}
		derivedData.airSpeed = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #4 : Indicated Airspeed/ Mach Number im=%1, airSpeed=%2\n")
							.arg(derivedData.im).arg(derivedData.airSpeed);
		}

	}

	// Subfield #5 : True Airspeed
	if (derivedData.tasCHK) {

		rBuffer.ReadU16(&u16Buf);

		derivedData.tureAirSpeed = u16Buf;	// 0 <= True Air Speed <= 2046 Knots

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #5 : True Airspeed = %1\n")
							.arg(derivedData.tureAirSpeed);
		}
	}

	// Subfield #6 : Selected Altitude
	if (derivedData.salCHK) {

		rBuffer.ReadU16(&u16Buf);

		derivedData.sas = (u16Buf & 0x8000) >> 15;
		derivedData.source = (u16Buf & 0x6000) >> 13;

		s16Buf = (u16Buf & 0x1FFF);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 25.0;				// LSB = 25ft

		derivedData.alt = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #6 : Selected Altitude sas = %1, source = %2, alt = %3\n")
							.arg(derivedData.sas).arg(derivedData.source).arg(derivedData.alt);
		}
	}

	// Subfield #7 : Final State Selected Altitude
	if (derivedData.fssCHK) {

		rBuffer.ReadU16(&u16Buf);

		derivedData.mv = (u16Buf & 0x8000) >> 15;
		derivedData.ah = (u16Buf & 0x4000) >> 14;
		derivedData.am = (u16Buf & 0x2000) >> 13;

		s16Buf = (u16Buf & 0x1FFF);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 25.0;			// LSB = 25ft

		derivedData.finalAlt = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #7 : Final State Selected Altitude mv = %1, ah = %2, am = %3, finalAlt = %4\n")
							.arg(derivedData.mv).arg(derivedData.ah).arg(derivedData.am).arg(derivedData.finalAlt);
		}
	}

	// Subfield #8 : Trajectory Intent Status
	if (derivedData.tisCHK) {
		rBuffer.ReadU8(&u8Buf);

		derivedData.nav = (u8Buf & 0x80) >> 7;
		derivedData.nvb = (u8Buf & 0x40) >> 6;

		// FX field ??? => what?

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #8 : Trajectory Intent Status nav = %1, nvb = %2\n")
							.arg(derivedData.nav).arg(derivedData.nvb);
		}
	}

	// Subfield #9 : Trajectory Intent Data
	if (derivedData.tidCHK) {
		rBuffer.ReadU8(&u8Buf);

		derivedData.tidRep = u8Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #9 : Trajectory Intent Data tidRep = %1\n")
							.arg(derivedData.tidRep);
		}

		for (U8 i = 0; i<derivedData.tidRep; i++) {
			TrajectoryIntentData tmp;

			rBuffer.ReadU8(&u8Buf);
			tmp.tidTca = (u8Buf & 0x80) >> 7;
			tmp.tidNc  = (u8Buf & 0x40) >> 6;
			tmp.tidTcpNum = (u8Buf & 0x3F);

			rBuffer.ReadS16(&s16Buf);
			f64Buf = static_cast<F64>(s16Buf);
			f64Buf = f64Buf * 10.0;		// LSB = 10ft,  -1500ft <= altitude <= 150000 ft
			tmp.tidAltitude = f64Buf;

			rBuffer.ReadS24(&s32Buf);
			f64Buf = static_cast<F64>(s32Buf);
			f64Buf = f64Buf * (180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23
			tmp.tidLatitude = f64Buf;

			rBuffer.ReadS24(&s32Buf);
			f64Buf = static_cast<F64>(s32Buf);
			f64Buf = f64Buf * (180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23
			tmp.tidLongitude = f64Buf;

			rBuffer.ReadU8(&u8Buf);
			tmp.tidPointType = (u8Buf & 0xF0) >> 4;
			tmp.tidTd        = (u8Buf & 0x0C) >> 2;
			tmp.tidTra       = (u8Buf & 0x02) >> 1;
			tmp.tidToa       = (u8Buf & 0x01);

			rBuffer.ReadS24(&s32Buf);
			f64Buf = static_cast<F64>(s32Buf);
			f64Buf = f64Buf * 1.0;			// LSB = 1 second
			tmp.tidTov = f64Buf;

			rBuffer.ReadU16(&u16Buf);
			f64Buf = static_cast<F64>(s16Buf);
			f64Buf = f64Buf * 0.01;			// LSB = 0.01 NM,  0 <= TTR <= 655.36 NM
			tmp.tidTtr = f64Buf;

			derivedData.trajectoryIntentDataList.insert(i, tmp);

			// debug
			if (DEBUG) {
				tmpBuf += QString("       tidTca = %1, tidNc = %2, tidTcpNum = %3, Alt = %4, Lat = %5, Lon = %6 \n")
								.arg(tmp.tidTca).arg(tmp.tidNc).arg(tmp.tidTcpNum).arg(tmp.tidAltitude).arg(tmp.tidLatitude).arg(tmp.tidLongitude);
				tmpBuf += QString("       tidPointType = %1, tidTd = %2, tidTra = %3, tidToa = %4, tidTov = %5, tidTtr = %6 \n")
												.arg(tmp.tidPointType).arg(tmp.tidTd).arg(tmp.tidTra).arg(tmp.tidToa).arg(tmp.tidTov).arg(tmp.tidTtr);
			}
		}
	}

	// Subfield #10 : Communications / ACAS Capability and Flight Status
	if (derivedData.comCHK) {
		rBuffer.ReadU16(&u16Buf);

		derivedData.com    = (u16Buf & 0xE000) >> 13;
		derivedData.flStat = (u16Buf & 0x1C00) >> 10;
		derivedData.ssc    = (u16Buf & 0x0080) >> 7;
		derivedData.arc    = (u16Buf & 0x0040) >> 6;
		derivedData.aic    = (u16Buf & 0x0020) >> 5;
		derivedData.b1a    = (u16Buf & 0x0010) >> 4;
		derivedData.b1b    = (u16Buf & 0x000F);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #10 : Communications / ACAS Capability and Flight Status \n");
			tmpBuf += QString("         com = %1, flStat = %2, ssc = %3, arc = %4, aic = %5, b1a = %6, b1b = %7 \n")
							.arg(derivedData.com).arg(derivedData.flStat).arg(derivedData.ssc).arg(derivedData.arc)
							.arg(derivedData.aic).arg(derivedData.b1a).arg(derivedData.b1b);
		}
	}

	// Subfield #11 : Status reported by ADS-B
	if (derivedData.sabCHK) {
		rBuffer.ReadU16(&u16Buf);

		derivedData.ac    = (u16Buf & 0xC000) >> 14;
		derivedData.mn    = (u16Buf & 0x3000) >> 12;
		derivedData.dc    = (u16Buf & 0x0C00) >> 10;
		derivedData.gbs   = (u16Buf & 0x0200) >> 9;
		derivedData.adsbStat = (u16Buf & 0x0007);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #11 : Status reported by ADS-B \n");
			tmpBuf += QString("         ac = %1, mn = %2, dc = %3, gbs = %4, adsbStat = %5 \n")
							.arg(derivedData.ac).arg(derivedData.mn).arg(derivedData.dc).arg(derivedData.gbs)
							.arg(derivedData.adsbStat);
		}
	}

	// Subfield #12 : ACAS Resolution Advisory Report
	if (derivedData.acsCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		U8  u8Ch5  = 0x00;
		U8  u8Ch6  = 0x00;
		U8  u8Ch7  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);
		rBuffer.ReadU8(&u8Ch5);
		rBuffer.ReadU8(&u8Ch6);
		rBuffer.ReadU8(&u8Ch7);

		derivedData.advisoryMsg = QString("%1%2%3%4%5%6%7").arg(u8Ch1).arg(u8Ch2)
								.arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6).arg(u8Ch7);
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #12 : ACAS Resolution Advisory Report : %1 \n").arg(derivedData.advisoryMsg);
		}
	}

	// Subfield #13 : Barometric Vertical Rate
	if (derivedData.bvrCHK) {
		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);

		f64Buf = f64Buf * 6.25;			// 6.25 feet/minute

		derivedData.barometricVR = f64Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #13 : Barometric Vertical Rate : %1 \n").arg(derivedData.barometricVR);
		}
	}

	// Subfield #14 : Geometric Vertical Rate
	if (derivedData.gvrCHK) {
		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);

		f64Buf = f64Buf * 6.25;			// 6.25 feet/minute

		derivedData.geometricVR = f64Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #14 : Geometric Vertical Rate : %1 \n").arg(derivedData.geometricVR);
		}
	}

	// Subfield #15 : Roll Angle
	if (derivedData.ranCHK) {
		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);

		f64Buf = f64Buf * 0.01;			// 0.01 degree,  -180 <= Roll Angle <= 180

		derivedData.rollAngle = f64Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #15 : Roll Angle : %1 \n").arg(derivedData.rollAngle);
		}
	}

	// Subfield #16 : Track Angle Rate
	if (derivedData.tarCHK) {
		rBuffer.ReadU16(&u16Buf);

		derivedData.ti = (u16Buf & 0x8000) >> 15;
		f64Buf = static_cast<F64>((u16Buf & 0x00FF) >> 1);

		f64Buf = f64Buf * 0.25;		// 2^-2 = 1 / 4 o/s
		derivedData.rateOfTurn = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #16 : Track Angle Rate ti = %1, rateOfturn = %2 \n")
					.arg(derivedData.ti).arg(derivedData.rateOfTurn);
		}
	}

	// Subfield #17 : Tarck Angle
	if (derivedData.tanCHK) {
		rBuffer.ReadS16(&s16Buf);

		f64Buf = static_cast<F64>(s16Buf);

		f64Buf = f64Buf * (360.0 / (1024.0 * 64.0));		// 360 / 2^16 o
		derivedData.trackAngle = f64Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #17 : Tarck Angle = %1 \n").arg(derivedData.trackAngle);
		}
	}

	// Subfield #18 : Ground Speed
	if (derivedData.gspCHK) {
		rBuffer.ReadS16(&s16Buf);

		f64Buf = static_cast<F64>(s16Buf);

		f64Buf = f64Buf * ( 1.0 / (1024.0 * 16.0));			// LSB = 2^-14 NM/s = 0.22 kt
		derivedData.groundSpeed = f64Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #18 : Ground Speed = %1 \n").arg(derivedData.groundSpeed);
		}
	}

	// Subfield #19 : Velocity Uncertainty
	if (derivedData.vunCHK) {
		rBuffer.ReadU8(&u8Buf);
		derivedData.vunCategory = u8Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #19 : Velocity Uncertainty = %1 \n").arg(derivedData.vunCategory);
		}
	}

	// Subfield #20 : Meteorological Data
	if (derivedData.metCHK) {
		rBuffer.ReadU8(&u8Buf);

		derivedData.ws = (u8Buf & 0x80) >> 7;
		derivedData.wd = (u8Buf & 0x40) >> 6;
		derivedData.tmp = (u8Buf & 0x20) >> 5;
		derivedData.trb = (u8Buf & 0x10) >> 4;

		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 1;	// LSB = 1 knot  0 <= Wind Speed <= 300
		derivedData.windSpeed = f64Buf;

		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 1;	// LSB = 1 degree  1 <= Wind Direction <= 360
		derivedData.windDirection = f64Buf;

		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 0.25;	// LSB = 0.25 oC  -100 <= Wind Speed <= 100
		derivedData.temperature = f64Buf;

		rBuffer.ReadU8(&u8Buf);
		derivedData.turbulence = u8Buf;		// Integer between 0 and 15 inclusive.

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #20 : Meteorological Data \n");
			tmpBuf += QString("         ws : %1, wd : %2, tmp : %3, trb : %4")
					.arg(derivedData.ws).arg(derivedData.wd).arg(derivedData.tmp).arg(derivedData.trb);
			tmpBuf += QString("         windSpeed : %1, windDirection : %2, temperature : %3, turbulence : %4")
								.arg(derivedData.turbulence).arg(derivedData.windDirection).arg(derivedData.temperature).arg(derivedData.turbulence);
		}
	}

	// Subfield #21 : Emitter Category
	if (derivedData.emcCHK) {
		rBuffer.ReadU8(&u8Buf);
		derivedData.ecat = u8Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #21 : Emitter Category = %1 \n").arg(derivedData.ecat);
		}
	}

	// Subfield #22 : Position Data
	if (derivedData.posCHK) {
		rBuffer.ReadS24(&s32Buf);
		f64Buf = static_cast<F64>(s32Buf);
		f64Buf = f64Buf * (180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23
		derivedData.posLatitude = f64Buf;

		rBuffer.ReadS24(&s32Buf);
		f64Buf = static_cast<F64>(s32Buf);
		f64Buf = f64Buf * (180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23
		derivedData.posLongitude = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #22 : Position Data Lat = %1, Lon = %2\n")
					.arg(derivedData.posLatitude).arg(derivedData.posLongitude);
		}
	}

	// Subfield #23 : Geometric Altitude Data
	if (derivedData.galCHK) {
		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 6.25;			// LSB = 6.25 ft
		derivedData.geoAltitude = f64Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #23 : Geometric Altitude Data = %1\n")
					.arg(derivedData.geoAltitude);
		}
	}

	// Subfield #24 : Position Uncertainty Data
	if (derivedData.punCHK) {
		rBuffer.ReadU8(&u8Buf);
		derivedData.pun = u8Buf;
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #24 : Position Uncertainty Data = %1\n")
					.arg(derivedData.pun);
		}
	}

	// Subfield #25 : Mode S MB Data
	if (derivedData.mbCHK) {
		rBuffer.ReadU8(&u8Buf);
		derivedData.bdsRep = u8Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #25 : Mode S MB Data rep = %1\n")
					.arg(derivedData.bdsRep);
		}

		for (U8 i=0; i<u8Buf; i++) {
			ModeSMBData tmp;

			U8  u8Ch1  = 0x00;
			U8  u8Ch2  = 0x00;
			U8  u8Ch3  = 0x00;
			U8  u8Ch4  = 0x00;
			U8  u8Ch5  = 0x00;
			U8  u8Ch6  = 0x00;
			U8  u8Ch7  = 0x00;

			rBuffer.ReadU8(&u8Ch1);
			rBuffer.ReadU8(&u8Ch2);
			rBuffer.ReadU8(&u8Ch3);
			rBuffer.ReadU8(&u8Ch4);
			rBuffer.ReadU8(&u8Ch5);
			rBuffer.ReadU8(&u8Ch6);
			rBuffer.ReadU8(&u8Ch7);

			tmp.msgMbData = QString("%1%2%3%4%5%6%7").arg(u8Ch1).arg(u8Ch2)
									.arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6).arg(u8Ch7);

			rBuffer.ReadU8(&u8Buf);
			tmp.bds1 = (u8Buf & 0xF0) >> 4;
			tmp.bds2 = (u8Buf & 0x0F);

			derivedData.modeSMBDataList.insert(i, tmp);

			// debug
			if (DEBUG) {
				tmpBuf += QString("         msgMbData = %1, bds1 = %2, bds2 = %3\n")
						.arg(tmp.msgMbData).arg(tmp.bds1).arg(tmp.bds2);
			}

		}
	}

	// Subfield #26 : Indicated Airspeed
	if (derivedData.iarCHK) {
		rBuffer.ReadU16(&u16Buf);

		derivedData.indicatedSpd = u16Buf;		// LSB = 1 Kt		0 Kt <= Indicated AirSpeed <= 1100 Kt

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #26 : Indicated Airspeed = %1\n")
					.arg(derivedData.indicatedSpd);
		}
	}

	// Subfield #27 : Mach Number
	if (derivedData.macCHK) {
		rBuffer.ReadU16(&u16Buf);
		f64Buf = static_cast<F64>(u16Buf);

		f64Buf = f64Buf * 0.008;		// LSB = Mach 0.008		0<= Mach Number <= 4.096
		derivedData.machNum = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #27 : Mach Number = %1\n")
					.arg(derivedData.machNum);
		}
	}

	// Subfield #28 : Barometric Pressure Setting
	if (derivedData.bpsCHK) {
		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 0.1;			// LSB = 0.1mb
		derivedData.bps = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #28 : Barometric Pressure Setting = %1\n")
					.arg(derivedData.bps);
		}
	}
}

/**
 * Data Item I062/390	Flight Plan Related Data
 * Definition : All flight plan related information, provided by ground-based systems.
 * Format     : Compound Data Item, comprising a primary subfield of up to there octets,
 * 				followed by the indicated subfields.
 */
void Cat062::I062_390(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U16 u16Buf = 0;
	U32 u32Buf = 0;
	F64 f64Buf = 0.0;
	U8 u8Fx  = 0x00;

	rBuffer.ReadU8(&u8Buf);

	flightPlanData.tagCHK = (u8Buf & 0x80) >> 7;
	flightPlanData.csnCHK = (u8Buf & 0x40) >> 6;
	flightPlanData.ifiCHK = (u8Buf & 0x20) >> 5;
	flightPlanData.fctCHK = (u8Buf & 0x10) >> 4;
	flightPlanData.tacCHK = (u8Buf & 0x08) >> 3;
	flightPlanData.wtcCHK = (u8Buf & 0x04) >> 2;
	flightPlanData.depCHK = (u8Buf & 0x02) >> 1;
	u8Fx = (u8Buf & 0x01);

	// debug
	if (DEBUG) {
		tmpBuf += QString("Data Item I062/390	Flight Plan Related Data /n");
		tmpBuf += QString("   tagCHK : %1, csnCHK : %2, ifiCHK : %3, fctCHK : %4, tacCHK : %5, wtcCHK : %6, depCHK : %7\n")
						.arg(flightPlanData.tagCHK).arg(flightPlanData.csnCHK).arg(flightPlanData.ifiCHK).arg(flightPlanData.fctCHK)
						.arg(flightPlanData.tacCHK).arg(flightPlanData.wtcCHK).arg(flightPlanData.depCHK);
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		flightPlanData.dstCHK = (u8Buf & 0x80) >> 7;
		flightPlanData.rdsCHK = (u8Buf & 0x40) >> 6;
		flightPlanData.cflCHK = (u8Buf & 0x20) >> 5;
		flightPlanData.ctlCHK = (u8Buf & 0x10) >> 4;
		flightPlanData.todCHK = (u8Buf & 0x08) >> 3;
		flightPlanData.astCHK = (u8Buf & 0x04) >> 2;
		flightPlanData.stsCHK = (u8Buf & 0x02) >> 1;
		u8Fx = (u8Buf & 0x01);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   dstCHK : %1, rdsCHK : %2, cflCHK : %3, ctlCHK : %4, todCHK : %5, astCHK : %6, stsCHK : %7\n")
							.arg(flightPlanData.dstCHK).arg(flightPlanData.rdsCHK).arg(flightPlanData.cflCHK).arg(flightPlanData.ctlCHK)
							.arg(flightPlanData.todCHK).arg(flightPlanData.astCHK).arg(flightPlanData.stsCHK);
		}
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		flightPlanData.stdCHK = (u8Buf & 0x80) >> 7;
		flightPlanData.staCHK = (u8Buf & 0x40) >> 6;
		flightPlanData.pemCHK = (u8Buf & 0x20) >> 5;
		flightPlanData.pecCHK = (u8Buf & 0x10) >> 4;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   stdCHK : %1, staCHK : %2, pemCHK : %3, pecCHK : %4\n")
							.arg(flightPlanData.stdCHK).arg(flightPlanData.staCHK).arg(flightPlanData.pemCHK).arg(flightPlanData.pecCHK);
		}
	}

	// Subfield #1 : FPPS identification Tag
	if (flightPlanData.tagCHK) {
		rBuffer.ReadU8(&u8Buf);
		flightPlanData.sac = u8Buf;
		rBuffer.ReadU8(&u8Buf);
		flightPlanData.sic = u8Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #1 : FPPS identification Tag   sac = %1, sic = %2 \n")
							.arg(flightPlanData.sac).arg(flightPlanData.sic);
		}
	}

	// Subfield #2 : Callsign
	if (flightPlanData.csnCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		U8  u8Ch5  = 0x00;
		U8  u8Ch6  = 0x00;
		U8  u8Ch7  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);
		rBuffer.ReadU8(&u8Ch5);
		rBuffer.ReadU8(&u8Ch6);
		rBuffer.ReadU8(&u8Ch7);

		//if (!u8Ch1) {
			char str[7];
			memset(str, 0x00, sizeof(str));
			sprintf(str, "%c%c%c%c%c%c%c", u8Ch1, u8Ch2, u8Ch3,
				u8Ch4, u8Ch5, u8Ch6, u8Ch7);

			//qDebug() << "Str : " << str;

			//tmpBuf += QString("string  : %1").arg(str);

			flightPlanData.callsign = QString("%1").arg(str);  // QString("%1%2%3%4%5%6%7").arg(u8Ch1).arg(u8Ch2).arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6).arg(u8Ch7);

		//}else {
		//	flightPlanData.callsign = "";
		//}

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #2 : Callsign =  %1 \n")
						.arg(flightPlanData.callsign);
		}
	}

	// Subfield #3 : IFPS_FLIGHT_ID
	if (flightPlanData.ifiCHK) {
		rBuffer.ReadU32(&u32Buf);

		flightPlanData.typ = (u32Buf & 0xC0000000) >> 30;
		flightPlanData.nbr = (u32Buf & 0x3FFFFFFF);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #3 : IFPS_FLIGHT_ID typ = %1, nbr = %2 \n")
							.arg(flightPlanData.typ).arg(flightPlanData.nbr);
		}
	}

	// Subfield #4 : Flight Category
	if (flightPlanData.fctCHK) {
		rBuffer.ReadU8(&u8Buf);
		flightPlanData.cat  = (u8Buf & 0xC0) >> 6;
		flightPlanData.fr   = (u8Buf & 0x30) >> 4;
		flightPlanData.rvsm = (u8Buf & 0x0C) >> 2;
		flightPlanData.hpr  = (u8Buf & 0x02) >> 1;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #4 : Flight Category cat = %1, fr = %2, rvsm = %3, hpr = %4 \n")
							.arg(flightPlanData.cat).arg(flightPlanData.fr).arg(flightPlanData.rvsm).arg(flightPlanData.hpr);
		}
	}

	// Subfield #5 : Type of Aircraft
	if (flightPlanData.tacCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		S8  u8Str[4];
		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);

		memset(u8Str, 0x00, sizeof(u8Str));
		sprintf(u8Str, "%c%c%c%c", u8Ch1, u8Ch2, u8Ch3, u8Ch4);

		flightPlanData.typeAircraft = QString(u8Str);  // QString("%1%2%3%4").arg(u8Ch1).arg(u8Ch2).arg(u8Ch3).arg(u8Ch4);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #5 : Type of Aircraft = %1 \n")
							.arg(flightPlanData.typeAircraft);
		}
	}

	// Subfield #6 : Wake turbulence Category
	if (flightPlanData.wtcCHK) {
		rBuffer.ReadU8(&u8Buf);

		S8 s8Str = (char)u8Buf;
		flightPlanData.wtc = QString("%1").arg(s8Str);
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #6 : Wake turbulence Category = %1 \n")
							.arg(flightPlanData.wtc);
		}
	}

	// Subfield #7 : Departure Airport
	if (flightPlanData.depCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);

		if (u8Ch1) {
			S8 u8Str[4];
			memset(u8Str, 0x00, sizeof(u8Str));
			sprintf(u8Str, "%c%c%c%c", u8Ch1, u8Ch2, u8Ch3, u8Ch4);

			tmpBuf += QString(" dep : %1, binary : %2").arg(u8Str).arg(QString("%1%2%3%4").arg(u8Ch1).arg(u8Ch2).arg(u8Ch3).arg(u8Ch4));

			flightPlanData.depAirport = QString(u8Str);  // QString("%1%2%3%4").arg(u8Ch1).arg(u8Ch2).arg(u8Ch3).arg(u8Ch4);

			// debug
			if (DEBUG) {
				tmpBuf += QString("   Subfield #7 : Departure Airport= %1 \n")
							.arg(flightPlanData.depAirport);
			}
		}else {
			flightPlanData.depAirport = "";
		}
	}

	// Subfield #8 : Destination Airport
	if (flightPlanData.dstCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);

		S8 u8Str[4];
		memset(u8Str, 0x00, sizeof(u8Str));
		sprintf(u8Str, "%c%c%c%c", u8Ch1, u8Ch2, u8Ch3, u8Ch4);

		flightPlanData.destAirport = QString("%1").arg(u8Str);  // QString("%1%2%3%4").arg(u8Ch1).arg(u8Ch2).arg(u8Ch3).arg(u8Ch4);

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #8 : Destination Airport = %1 \n")
							.arg(flightPlanData.destAirport);
		}
	}

	// Subfield #9 : Runway Designation
	if (flightPlanData.rdsCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);

		flightPlanData.nu1 = QString("%1").arg(u8Ch1);
		flightPlanData.nu2 = QString("%1").arg(u8Ch2);
		flightPlanData.ltr = QString("%1").arg(u8Ch3);

		S8 u8Str[3];
		memset(u8Str, 0x00, sizeof(u8Str));
		sprintf(u8Str, "%c%c%c", u8Ch1, u8Ch2, u8Ch3);
		flightPlanData.rway = QString("%1").arg(u8Str);
		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #9 : Runway Designation nu1 = %1, nu2 = %2, ltr = %3, rway = %4 \n")
							.arg(flightPlanData.nu1).arg(flightPlanData.nu2).arg(flightPlanData.ltr).arg(flightPlanData.rway);
		}
	}

	// Subfield #10 : Current Cleared Flight Level
	if (flightPlanData.cflCHK) {
		rBuffer.ReadU16(&u16Buf);

		f64Buf = static_cast<F64>(u16Buf);
		f64Buf = f64Buf * 0.25;				// LSB = 1/4 FL
		flightPlanData.cfl = f64Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #10 : Current Cleared Flight Level = %1 \n")
							.arg(flightPlanData.cfl);
		}
	}

	// Subfield #11 : Current Control Position
	if (flightPlanData.ctlCHK) {
		rBuffer.ReadU8(&u8Buf);
		flightPlanData.centre = u8Buf;

		rBuffer.ReadU8(&u8Buf);
		flightPlanData.position = u8Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #11 : Current Control Position  centre = %1, position = %2 \n")
							.arg(flightPlanData.centre).arg(flightPlanData.position);
		}
	}

	// Subfield #12 : Time of Departure / Arrival
	if (flightPlanData.todCHK) {
		rBuffer.ReadU8(&u8Buf);
		flightPlanData.rep = u8Buf;

		// debug
		if (DEBUG) {
			tmpBuf += QString("   Subfield #12 : Time of Departure / Arrival rep = %1 \n")
							.arg(flightPlanData.rep);
		}

		for (U8 i=0; i<u8Buf; i++) {
			TimeOfDepArrData tmp;

			rBuffer.ReadU8(&u8Buf);
			tmp.typ = (u8Buf & 0xF8) >> 3;
			tmp.day = (u8Buf & 0x06) >> 1;

			rBuffer.ReadU8(&u8Buf);
			tmp.hor = (u8Buf & 0x1F);
			rBuffer.ReadU8(&u8Buf);
			tmp.min = (u8Buf & 0x3F);

			rBuffer.ReadU8(&u8Buf);
			tmp.avs = (u8Buf & 0x80) >> 7;
			tmp.sec = (u8Buf & 0x3F);

			flightPlanData.timeOfDepArrList.insert(i, tmp);

			// debug
			if (DEBUG) {
				tmpBuf += QString("        type = %1, day = %2, hor = %3, min = %4, avs = %5, sec = %6 \n")
								.arg(tmp.typ).arg(tmp.day).arg(tmp.hor).arg(tmp.min).arg(tmp.avs).arg(tmp.sec);
			}
		}
	}

	// Subfield #13 : Aircraft Stand
	if (flightPlanData.astCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		U8  u8Ch5  = 0x00;
		U8  u8Ch6  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);
		rBuffer.ReadU8(&u8Ch5);
		rBuffer.ReadU8(&u8Ch6);

		flightPlanData.aircraftStand = QString("%1%2%3%4%5%6").arg(u8Ch1).arg(u8Ch2)
								.arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6);

		// debug
		if (DEBUG) {
			tmpBuf += QString("    Subfield #13 : Aircraft Stand = %1 \n")
							.arg(flightPlanData.aircraftStand);
		}
	}

	// Subfield #14 : Stand Status
	if (flightPlanData.stsCHK) {
		rBuffer.ReadU8(&u8Buf);

		flightPlanData.emp = (u8Buf & 0xC0) >> 6;
		flightPlanData.avl = (u8Buf & 0x30) >> 4;

		// debug
		if (DEBUG) {
			tmpBuf += QString("    Subfield #14 : Stand Status  emp = %1, avl = %2 \n")
							.arg(flightPlanData.emp).arg(flightPlanData.avl);
		}
	}

	// Subfield #15 : Standard Instrument Departure
	if (flightPlanData.stdCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		U8  u8Ch5  = 0x00;
		U8  u8Ch6  = 0x00;
		U8  u8Ch7  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);
		rBuffer.ReadU8(&u8Ch5);
		rBuffer.ReadU8(&u8Ch6);
		rBuffer.ReadU8(&u8Ch7);

		flightPlanData.standardInstrumentDep = QString("%1%2%3%4%5%6%7").arg(u8Ch1).arg(u8Ch2)
								.arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6).arg(u8Ch7);

		// debug
		if (DEBUG) {
			tmpBuf += QString("    Subfield #15 : Standard Instrument Departure = %1 \n")
							.arg(flightPlanData.standardInstrumentDep);
		}
	}

	// Subfield #16 : Standard Instrument Arrival
	if (flightPlanData.staCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		U8  u8Ch5  = 0x00;
		U8  u8Ch6  = 0x00;
		U8  u8Ch7  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);
		rBuffer.ReadU8(&u8Ch5);
		rBuffer.ReadU8(&u8Ch6);
		rBuffer.ReadU8(&u8Ch7);

		flightPlanData.standardInstrumentArr = QString("%1%2%3%4%5%6%7").arg(u8Ch1).arg(u8Ch2)
								.arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6).arg(u8Ch7);

		// debug
		if (DEBUG) {
			tmpBuf += QString("    Subfield #16 : Standard Instrument Arrival = %1 \n")
							.arg(flightPlanData.standardInstrumentArr);
		}
	}

	// Subfield #17 : Pre-emergency Mode 3/A code
	if (flightPlanData.pemCHK) {
		rBuffer.ReadU16(&u16Buf);

		flightPlanData.va = (u16Buf & 0x1000) >> 12;

		U8 s1 = (u16Buf & 0x0E00) >> 9;
		U8 s2 = (u16Buf & 0x01C0) >> 6;
		U8 s3 = (u16Buf & 0x0038) >> 3;
		U8 s4 = (u16Buf & 0x0007);

		flightPlanData.mode3A = QString("%1%2%3%4").arg(s1).arg(s2).arg(s3).arg(s4);

		// debug
		if (DEBUG) {
			tmpBuf += QString("    Subfield #17 : Pre-emergency Mode 3/A code  va = %1, mode3A = %2 \n")
							.arg(flightPlanData.va).arg(flightPlanData.mode3A);
		}
	}

	// Subfield #18 : Pre-emergency Callsign
	if (flightPlanData.pecCHK) {
		U8  u8Ch1  = 0x00;
		U8  u8Ch2  = 0x00;
		U8  u8Ch3  = 0x00;
		U8  u8Ch4  = 0x00;
		U8  u8Ch5  = 0x00;
		U8  u8Ch6  = 0x00;
		U8  u8Ch7  = 0x00;

		rBuffer.ReadU8(&u8Ch1);
		rBuffer.ReadU8(&u8Ch2);
		rBuffer.ReadU8(&u8Ch3);
		rBuffer.ReadU8(&u8Ch4);
		rBuffer.ReadU8(&u8Ch5);
		rBuffer.ReadU8(&u8Ch6);
		rBuffer.ReadU8(&u8Ch7);

		flightPlanData.pre_callsign = QString("%1%2%3%4%5%6%7").arg(u8Ch1).arg(u8Ch2)
								.arg(u8Ch3).arg(u8Ch4).arg(u8Ch5).arg(u8Ch6).arg(u8Ch7);

		// debug
		if (DEBUG) {
			tmpBuf += QString("    Subfield #18 : Pre-emergency Callsign = %1 \n")
							.arg(flightPlanData.pre_callsign);
		}
	}

}

/**
 * Data Item I062/500	Estimated Accuracies
 * Definition : Overview of all important accuracies
 * Format     : Compound Data Item, comprising a primary subfield of up to two
 *              octets, followed by the indicated subfields.
 */
void Cat062::I062_500(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	S16 s16Buf = 0;
	U16 u16Buf = 0;
	F64 f64Buf = 0.0;
	U8 u8Fx  = 0x00;

	rBuffer.ReadU8(&u8Buf);

	estAccuracyData.apcCHK = (u8Buf & 0x80) >> 7;
	estAccuracyData.covCHK = (u8Buf & 0x40) >> 6;
	estAccuracyData.apwCHK = (u8Buf & 0x20) >> 5;
	estAccuracyData.agaCHK = (u8Buf & 0x10) >> 4;
	estAccuracyData.abaCHK = (u8Buf & 0x08) >> 3;
	estAccuracyData.atvCHK = (u8Buf & 0x04) >> 2;
	estAccuracyData.aaCHK  = (u8Buf & 0x02) >> 1;
	u8Fx = (u8Buf & 0x01);

	// debug
	if (DEBUG) {
		tmpBuf += QString("Data Item I062/500	Estimated Accuracies  \n");
		tmpBuf += QString("    apcCHK = %1, covCHK = %2, apwCHK = %3, agaCHK = %4, abaCHK = %5, atvCHK = %6, aaCHK = %7 \n")
						.arg(estAccuracyData.apcCHK).arg(estAccuracyData.covCHK).arg(estAccuracyData.apwCHK).arg(estAccuracyData.agaCHK)
						.arg(estAccuracyData.abaCHK).arg(estAccuracyData.atvCHK).arg(estAccuracyData.aaCHK);
	}

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		estAccuracyData.arcCHK = (u8Buf & 0x80) >> 7;

		tmpBuf += QString("    arcCHK = %1 \n")
						.arg(estAccuracyData.arcCHK);
	}

	// Subfield #1 : Estimated Accuracy Of Track Position (Cartesian)
	if (estAccuracyData.apcCHK) {
		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 0.5;		// LSB = 0.5 m

		estAccuracyData.apc_x = f64Buf;

		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 0.5;		// LSB = 0.5 m

		estAccuracyData.apc_y = f64Buf;

		tmpBuf += QString("    Subfield #1 : Estimated Accuracy Of Track Position (Cartesian) apc_x = %1, apc_y = %2 \n")
						.arg(estAccuracyData.apc_x).arg(estAccuracyData.apc_y);
	}

	// Subfield #2 : XY covariance component
	// Notes :
	//		1. XY covariance component = sign { Cov(X,Y) } * sqrt{abs[Cov(X,Y)]}
	//		2. The maximum value for the (unsigned) XY covariance component is 16.383 km.
	if (estAccuracyData.covCHK) {
		rBuffer.ReadU16(&u16Buf);
		f64Buf = static_cast<F64>(u16Buf);
		f64Buf = f64Buf * 0.5;		// LSB = 0.5 m

		estAccuracyData.cov = f64Buf;

		tmpBuf += QString("    Subfield #2 : XY covariance component cov = %1 \n")
						.arg(estAccuracyData.cov);
	}

	// Subfield #3 : Estimated Accuracy Of Track Position (WGS-84)
	if (estAccuracyData.apwCHK) {
		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * ( 180.0 / (1024.0 * 1024.0 * 32.0));		// LSB = 180/2^25 degrees

		estAccuracyData.apw_lat = f64Buf;

		rBuffer.ReadS16(&s16Buf);
		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * ( 180.0 / (1024.0 * 1024.0 * 32.0));		// LSB = 180/2^25 degrees

		estAccuracyData.apw_lon = f64Buf;

		tmpBuf += QString("    Subfield #3 : Estimated Accuracy Of Track Position (WGS-84) apw_lat = %1, apw_lon = %2 \n")
						.arg(estAccuracyData.apw_lat).arg(estAccuracyData.apw_lon);
	}

	// Subfield #4 : Estimated Accuracy Of Calculated Track Geometric Altitude
	if (estAccuracyData.agaCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 6.25;			// LSB = 6.25 ft

		estAccuracyData.aga = f64Buf;

		tmpBuf += QString("    Subfield #4 : Estimated Accuracy Of Calculated Track Geometric Altitude = %1 \n")
						.arg(estAccuracyData.aga);
	}

	// Subfield #5 : Estimated Accuracy Of Calculated Track Barometric Altitude
	if (estAccuracyData.abaCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;			// LSB = 1/4 FL

		estAccuracyData.aba = f64Buf;

		tmpBuf += QString("    Subfield #5 : Estimated Accuracy Of Calculated Track Barometric Altitude = %1 \n")
						.arg(estAccuracyData.aba);
	}
	// Subfield #6 : Estimated Accuracy Of Track Velocity (Cartesian)
	if (estAccuracyData.atvCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;			// LSB = 0.25 m/s

		estAccuracyData.atv_x = f64Buf;

		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;			// LSB = 0.25 m/s

		estAccuracyData.atv_y = f64Buf;

		tmpBuf += QString("    Subfield #6 : Estimated Accuracy Of Track Velocity (Cartesian) atv_x = %1, atv_y = %2 \n")
						.arg(estAccuracyData.atv_x).arg(estAccuracyData.atv_y);
	}

	// Subfield #7 : Estimated Accuracy Of Acceleration (Cartesian)
	if (estAccuracyData.aaCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;			// LSB = 0.25 m/s^2

		estAccuracyData.aa_x = f64Buf;

		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 0.25;			// LSB = 0.25 m/s^2

		estAccuracyData.aa_y = f64Buf;

		tmpBuf += QString("    Subfield #7 : Estimated Accuracy Of Acceleration (Cartesian) aa_x = %1, aa_y = %2 \n")
						.arg(estAccuracyData.aa_x).arg(estAccuracyData.aa_y);
	}

	// Subfield #8 : Estimated Accuracy Of Rate Of Climb/Descent
	if (estAccuracyData.arcCHK) {
		rBuffer.ReadU8(&u8Buf);
		f64Buf = static_cast<F64>(u8Buf);
		f64Buf = f64Buf * 6.25;			// LSB = 6.25 feet/minute

		estAccuracyData.arc = f64Buf;

		tmpBuf += QString("    Subfield #8 : Estimated Accuracy Of Rate Of Climb/Descent = %1 \n")
						.arg(estAccuracyData.arc);
	}
}

/**
 * Data Item I062/510	Composed Track Number
 * Definition : Identification of a system track
 * Structure  : Extendible data item, comprising a first part of three octets (Master
 * 				Track Number), followed by three-octet extents (Slave Tracks Numbers)
 */
void Cat062::I062_510(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;
	U16 u16Buf = 0;

	rBuffer.ReadU8(&u8Buf);

	systemTrack.systemUnitId1 = u8Buf;

	rBuffer.ReadU16(&u16Buf);
	systemTrack.trackNum1 = (u16Buf & 0xFFFE) >> 1;

	u8Fx = (u16Buf & 0x0001);
	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		systemTrack.systemUnitId2 = u8Buf;

		rBuffer.ReadU16(&u16Buf);
		systemTrack.trackNum2 = (u16Buf & 0xFFFE) >> 1;
	}

	// debug
	if (DEBUG) {
		tmpBuf += QString("Data Item I062/510	Composed Track Number  \n");
		tmpBuf += QString("    systemUnitId1 = %1, trackNum1 = %2, systemUnitId2 = %3, trackNum2 = %4 \n")
						.arg(systemTrack.systemUnitId1).arg(systemTrack.trackNum1).arg(systemTrack.systemUnitId2).arg(systemTrack.trackNum2);
	}

}

BOOL Cat062::FSPec(CBuffer& rBuffer)
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


/**
 * 입력된 SSR 코드를 리턴한다.
 */
QString Cat062::getSSRCode()
{
	if (mode3A.mode3ACode != "" && mode3A.mode3ACode != "0000") {
		return mode3A.mode3ACode;
	}else {	// Mini Plan ssr code
		return flightPlanData.mode3A;
	}
}

/**
 * 입력된 Track Number 를 리턴한다.
 */
int Cat062::getTrackNum()
{
	return systemTrack.TRACK_NUM;
}

/**
 * 입력된 Callsign 를 리턴한다.
 */
QString Cat062::getCallsign()
{
	return flightPlanData.callsign;
}

/**
 * return Time of track information
 */
QString Cat062::getAccurDt()
{
	//printf("getAccurDt char %s\n", m_TimeOfPacket.toString());
	//qDebug() << "getAccurDt QString: " << QString(m_TimeOfPacket.toString());

	return QString("%1").arg(systemTrack.timeStamp.toString());
}

/**
 * return Latitude (I062/105 Calculated Position in WGS-84 Co-ordinates.)
 */
double Cat062::getLatitude()
{
	return systemTrack.wgsXpos;
}

/**
 * return Longitude (I062/105 Calculated Position in WGS-84 Co-ordinates.)
 */
double Cat062::getLongitude()
{
	return systemTrack.wgsYpos;
}

/**
 * return Speed (I062/185  Calculated Track Velocity (Cartesian) )
 */
double Cat062::getSpeed()
{
	return systemTrack.speed;
}

/**
 * return Heading (I062/185  Calculated Track Velocity (Cartesian) )
 */
double Cat062::getHeading()
{
	return systemTrack.heading;
}

/**
 * return Measured Flight Level (Data Item I062/136 Measured Flight Level)
 */
int Cat062::getMltAltitude()
{
	return (int) systemTrack.measuredFL;
}

/**
 * return Altitude (I062/135, Calculated Track Barometric Altitude)
 */
int Cat062::getAltitude()
{
	return (int) systemTrack.altBar;
}

/**
 * return QNH correction applied (I062/135, Calculated Track Barometric Altitude)
 */
S8 Cat062::getQNH()
{
	return systemTrack.qnhApply;
}

/**
 * return Calculated Rate of Climb/Descent
 */
int Cat062::getClimbDescent()
{
	return (int) systemTrack.climb_descent;
}

/**
 * return Special Position Indicator (0, 1)
 */
S8 Cat062::getSPI()
{
	return trackStatus.spi;
}

/**
 * return Barometric / Geometric
 */
S8 Cat062::getMRH()
{
	return trackStatus.mrh;
}

/**
 * return Confirmed / Tentative track
 */
S8 Cat062::getCNF()
{
	return trackStatus.cnf;
}

/**
 * return Actual/Simulated
 */
S8 Cat062::getSIM()
{
	return trackStatus.sim;
}

/**
 * return last track
 */
S8 Cat062::getTSE()
{
	return trackStatus.tse;
}

/**
 * return Flight plan correlated
 */
S8 Cat062::getFPC()
{
	return trackStatus.fpc;
}

/**
 * return Coasting
 */
S8 Cat062::getCST()
{
	return trackStatus.cst;
}

/**
 * return PSR Track
 */
S8 Cat062::getPSR()
{
	return trackStatus.psr;
}

/**
 * return SSR Track
 */
S8 Cat062::getSSR()
{
	return trackStatus.ssr;
}

/**
 * return Mode S Track
 */
S8 Cat062::getMDS()
{
	return trackStatus.mds;
}

/**
 * return ADS-B Track
 */
S8 Cat062::getADS()
{
	return trackStatus.ads;
}

/**
 * return GAT/OAT : 비행형식
 */
S8 Cat062::getFlType()
{
	return flightPlanData.cat;
}

/**
 * return FR1/FR2 비행규칙
 */
S8 Cat062::getFlRule()
{
	return flightPlanData.fr;
}

/**
 * return RVSM
 */
S8 Cat062::getRVSM()
{
	return flightPlanData.rvsm;
}

/**
 * return Priority Flight Type
 */
S8 Cat062::getHPR()
{
	return flightPlanData.hpr;
}

/**
 * return Aircraft type
 */
QString Cat062::getAirType()
{
	return flightPlanData.typeAircraft;
}

/**
 * return Wake Turbulence Category
 */
QString Cat062::getWtType()
{
	return flightPlanData.wtc;
}

/**
 * return Departure Airport
 */
QString Cat062::getDepAd()
{
	return flightPlanData.depAirport;
}

/**
 * return Destination Airport
 */
QString Cat062::getDesAd()
{
	return flightPlanData.destAirport;
}

/**
 * return Runway Designation
 */
QString Cat062::getRwayNo()
{
	return flightPlanData.rway;  // nu1+flightPlanData.nu2 +flightPlanData.ltr;
}

/**
 * return Current cleared Flight level (허가된 비행고도)
 */
int Cat062::getCFL()
{
	return (int) flightPlanData.cfl;
}
/**
 * return Cetre identification
 */
S8 Cat062::getCetre()
{
	return flightPlanData.centre;
}

/**
 * return Control Position identification
 */
S8 Cat062::getPos()
{
	return flightPlanData.position;
}

bool Cat062::miniPlanCheck()
{
	if (m_bFSPEC[21]) {
		return true;
	}else {
		return false;
	}
}
