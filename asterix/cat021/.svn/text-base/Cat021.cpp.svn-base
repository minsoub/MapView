/*
 * Cat021.cpp
 *
 *  Created on: 2012. 5. 11.
 *      Author: JMS
 *  Reference :
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 21
 *              ADS-B Messages
 */

#include "Cat021.h"

Cat021::Cat021() {

}

Cat021::~Cat021() {
	// TODO Auto-generated destructor stub
}

void Cat021::Clear()
{
	tmpBuf = "";

	for (int i=0; i<MAX_FSPEC; i++) {
		m_bFSPEC[i] = FALSE;
	}

	adsb.Clear();
}


void Cat021::BufferPrint(CBuffer& rBuffer, int s, int end, QString item)
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

	//qDebug() << str;
}

void Cat021::GetPacket(CBuffer& rBuffer)
{
	index = rBuffer.GetIndex();

	// Len - 2
	U16 u16Length = 0;
	rBuffer.ReadU16(&u16Length);
	this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
	index = rBuffer.GetIndex();
	S32 s32MaxIndex = rBuffer.GetIndex() + u16Length - 3;

	m_TimeOfPacket.GetSysTime();	// set current time

	while (rBuffer.GetIndex() < s32MaxIndex)
	{
		Clear();		// Decoding category 021

		if (!FSPec(rBuffer))
		{
			qDebug() << "ADSB FSPec Error.............";
		}else {
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "000");
			index = rBuffer.GetIndex();

			tmpBuf += "FSPec ................................\n";
			QString test = "";
			for (int i=1; i<48; i++) {
				test += QString(" %1").arg(m_bFSPEC[i]);
				if (i % 8 == 0) tmpBuf += "\n";
				tmpBuf += QString ("%1 = %2, ").arg(searchItem021(i)).arg(m_bFSPEC[i]);
			}
			//qDebug() << "FSPEC value : " <<  test;
			tmpBuf += "\n";
		}

		/* I021/010 Data Source Identifer */
		if (m_bFSPEC[1]) {
			I021_010(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "010");
			index = rBuffer.GetIndex();
		}
		/* I021/040 Target Report Descriptor */
		if (m_bFSPEC[2]) {
			I021_040(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "040");
			index = rBuffer.GetIndex();
		}
		/* I021/030 Time of Day */
		if (m_bFSPEC[3]) {
			I021_030(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "030");
			index = rBuffer.GetIndex();
		}
		/* I021/130 Position in WGS-84 Co-ordinates */
		if (m_bFSPEC[4]) {
			I021_130(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "130");
			index = rBuffer.GetIndex();
		}
		/* I021/080 Target Address */
		if (m_bFSPEC[5]) {
			I021_080(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "080");
			index = rBuffer.GetIndex();
		}
		/* I021/140 Geometric Altitude */
		if (m_bFSPEC[6]) {
			I021_140(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "140");
			index = rBuffer.GetIndex();
		}
		/* I021/090 Figure of Merit */
		if (m_bFSPEC[7]) {
			I021_090(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "090");
			index = rBuffer.GetIndex();
		}
		/* I021/210 Link Technology Indicator */
		if (m_bFSPEC[8]) {
			I021_210(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "210");
			index = rBuffer.GetIndex();
		}
		/* I021/230 Roll Angle */
		if (m_bFSPEC[9]) {
			I021_230(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "230");
			index = rBuffer.GetIndex();
		}
		/* I021/145 Flight Level */
		if (m_bFSPEC[10]) {
			I021_145(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "145");
			index = rBuffer.GetIndex();
		}
		/* I021/150 Air Speed */
		if (m_bFSPEC[11]) {
			I021_150(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "150");
			index = rBuffer.GetIndex();
		}
		/* I021/151 True Airspeed */
		if (m_bFSPEC[12]) {
			I021_151(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "151");
			index = rBuffer.GetIndex();
		}
		/* I021/152 Magnetic Heading */
		if (m_bFSPEC[13]) {
			I021_152(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "152");
			index = rBuffer.GetIndex();
		}
		/* I021/155 Barometric Vertical Rate */
		if (m_bFSPEC[14]) {
			I021_155(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "155");
			index = rBuffer.GetIndex();
		}
		/* I021/157 Geometric Vertical Rate */
		if (m_bFSPEC[15]) {
			I021_157(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "157");
			index = rBuffer.GetIndex();
		}
		/* I021/160 Ground Vector */
		if (m_bFSPEC[16]) {
			I021_160(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "160");
			index = rBuffer.GetIndex();
		}
		/* I021/165 Rate Of Turn */
		if (m_bFSPEC[17]) {
			I021_165(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "165");
			index = rBuffer.GetIndex();
		}
		/* I021/170 Target Identification */
		if (m_bFSPEC[18]) {
			I021_170(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "170");
			index = rBuffer.GetIndex();
		}
		/* I021/095 Velocity Accuracy */
		if (m_bFSPEC[19]) {
			I021_095(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "095");
			index = rBuffer.GetIndex();
		}
		/* I021/032 Time of Day Accuracy */
		if (m_bFSPEC[20]) {
			I021_032(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "032");
			index = rBuffer.GetIndex();
		}
		/* I021/200 Target Status */
		if (m_bFSPEC[21]) {
			I021_200(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "200");
			index = rBuffer.GetIndex();
		}
		/* I021/020 Emitter Category */
		if (m_bFSPEC[22]) {
			I021_020(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "020");
			index = rBuffer.GetIndex();
		}
		/* I021/220 Met Information */
		if (m_bFSPEC[23]) {
			I021_220(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "220");
			index = rBuffer.GetIndex();
		}
		/* I021/146 Intermediate State Selected Altitude */
		if (m_bFSPEC[24]) {
			I021_146(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "146");
			index = rBuffer.GetIndex();
		}
		/* I021/148 Final State Selected Altitude */
		if (m_bFSPEC[26]) {
			I021_148(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "148");
			index = rBuffer.GetIndex();
		}
		/* I021/110 Trajectory Intent */
		if (m_bFSPEC[26]) {
			I021_110(rBuffer);
			this->BufferPrint(rBuffer, index, rBuffer.GetIndex(), "110");
			index = rBuffer.GetIndex();
		}

		/* Spare bit set */
		if (m_bFSPEC[27]) {
			U8 u8Buf = 0x00;
			rBuffer.ReadU8(&u8Buf);
		}
	}
}

/**
 * Data Item I021/010	Data Source Identifier
 * Definition : Identification of the ADS-B station providing information
 * Format : Two-octet fixed length Data Item.
 */
void Cat021::I021_010(CBuffer& rBuffer)
{
	U8 u8SAC = 0x00;
	U8 u8SIC = 0x00;

	rBuffer.ReadU8(&u8SAC);
	rBuffer.ReadU8(&u8SIC);

	adsb.sac = u8SAC;
	adsb.sic = u8SIC;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I021/010 SAC : %1, SIC : %2\n").arg(u8SAC).arg(u8SIC);
	}
}

/**
 * Data Item I021/020	Emitter Category
 * Definition : Characteristics of the originating ADS-B unit
 * Format     : One-Octet fixed length data item.
 * ECAT       : Emitter Category
 * 		1 = light aircraft <= 7000 kg
 * 		2 = reserved
 * 		3 = 7000 kg < medium aircraft < 136000 kg
 * 		4 = reserved
 * 		5 = 136000 kg <= heavy aircraft
 * 		6 = highly manoeuvrable (5g acceleration capability) and high speed(>400 knots cruise)
 * 		7 to 9 = reserved
 * 		10 = rotocraft
 * 		11 = glider / sailplane
 * 		12 = lighter-than-air
 * 		13 = unmannned aerial vehicle
 * 		14 = space / transatmospheric vehicle
 * 		15 = ultralight / handglider / paraglider
 * 		16 = parachutist / skydiver
 * 		17 to 19 = reserved
 * 		20 = surface emegency vehicle
 * 		21 = surface service vehicle
 * 		22 = fixed ground or tethered obstruction
 * 		23 to 24 = reserved
 */
void Cat021::I021_020(CBuffer& rBuffer)
{
	U8 u8Ecat = 0x00;

	rBuffer.ReadU8(&u8Ecat);

	adsb.ecat = u8Ecat;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I021/020 Emitter Category : %1\n").arg(adsb.ecat);
	}
}

/**
 * Data Item I021/030 Time of Day
 * Definition : Absolute time stamping of the message in the form of elapsed time
 *              since last midnight
 * Format     : Three-octet fixed length Data Item
 */
void Cat021::I021_030(CBuffer& rBuffer)
{
	U32 u32TimeOfDay = 0x00000000;
	rBuffer.ReadU24(&u32TimeOfDay);	// 3 byte read
	F64 f64TimeOfDay = (1.0 / 128) * u32TimeOfDay;

	S32 s32TimeOfDay = static_cast<S32>( f64TimeOfDay );		// Int part of time
	f64TimeOfDay -= s32TimeOfDay;								// Frac part of time

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

	adsb.timeStamp = TimeStamp;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I021/030 Time of Day : %1 \n").arg(adsb.timeStamp.toString());
	}
}

/**
 * Data Item I021/032 Time of Day Accuracy
 * Definition : The maximum difference between the actual time of applicability of
 * 				the reported position and the time reported in the Time of Day item (I021/030)
 * Format     : One-Octet fixed length data item
 * LSB		  : 2^-8 s = 1/256 s
 */
void Cat021::I021_032(CBuffer& rBuffer)
{
	U8 u8TimeOfDay = 0x00;
	rBuffer.ReadU8(&u8TimeOfDay);	   // 1 byte read
	F64 f64TimeOfDay = (1.0 / 256.0) * u8TimeOfDay;

	adsb.timeofdayAccuracy = f64TimeOfDay;

	// debug
	if (DEBUG)
	{
		tmpBuf += QString("Data Item I021/032 Time of Day Accuracy: %1 \n").arg(adsb.timeofdayAccuracy);
	}
}

/**
 * Data Item I021/040 Target Report Descriptor
 * Definition : Type and characteristics of the data as transmitted by a system.
 * Format     : Two-Octet fixed length data item.
 */
void Cat021::I021_040(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;

	rBuffer.ReadU8(&u8Buf);

	adsb.u8DCR = (u8Buf & 0x80) >> 7;
	adsb.u8GBS = (u8Buf & 0x40) >> 6;
	adsb.u8SIM = (u8Buf & 0x20) >> 5;
	adsb.u8TST = (u8Buf & 0x10) >> 4;
	adsb.u8RAB = (u8Buf & 0x08) >> 3;
	adsb.u8SAA = (u8Buf & 0x04) >> 2;
	adsb.u8SPI = (u8Buf & 0x02) >> 1;

	rBuffer.ReadU8(&u8Buf);

	adsb.u8ATP = (u8Buf & 0xE0) >> 5;
	adsb.u8ARC = (u8Buf & 0x18) >> 3;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/040 Target Report Descriptor \n");
		tmpBuf += QString("  DCR : %1,  GBS : %2, SIM : %3, TST : %4, RAB : %5, "
				"SAA : %6, SPI : %7, ATP : %8, ARC : %9 \n")
				.arg(adsb.u8DCR).arg(adsb.u8GBS).arg(adsb.u8SIM).arg(adsb.u8TST)
				.arg(adsb.u8RAB).arg(adsb.u8SAA).arg(adsb.u8SPI).arg(adsb.u8ATP)
				.arg(adsb.u8ARC);
	}
}

/**
 * Data Item I021/080, Target Address
 * Definition : Target address(emitter identifier) assigned uniquely to each target
 * Format     : Three-octet fixed length Data Item
 *              24-bits address, A23 to A0
 */
void Cat021::I021_080(CBuffer& rBuffer)
{
	U32 u32Buf = 0;

	rBuffer.ReadU24(&u32Buf);

	adsb.targetAddr = u32Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/080 Target Address %1\n").arg(adsb.targetAddr);
	}
}

/**
 * Data Item I021/090 Figure of Merit
 * Definition : ADS figure of merit (FOM) provided by the aircraft avionics
 * Format     : Two-octet fixed length Data Item
 *
 * bits-16/15 (AC)	00 = unknown
 * 						01 = ACAS not operational
 * 						10 = ACAS operational
 * 						11 = invalid
 * bits-14/13 (MN)	00 = unknown
 * 						01 = Multiple navigational aids not operating
 * 						10 = Multiple navigational aids operating
 * 						11 = invalid
 * bits-12/11 (DC)	00	= unknown
 * 						01 = Differential correction
 * 						10 = No differential correction
 * 						11 = invalid
 * bits-4/1   (PA)	Position Accuracy
 *
 * NOTE - bits-4/1 (PA) code the "Navigational Uncertainty Categories - Position" as
 * 		described in the ADS-B MASPS[Ref.3]
 */
void Cat021::I021_090(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8AC  = 0x00;
	U8 u8MN  = 0x00;
	U8 u8DC  = 0x00;
	U8 u8PA  = 0x00;

	rBuffer.ReadU8(&u8Buf);

	u8AC = (u8Buf & 0xC0) >> 6;
	u8MN = (u8Buf & 0x30) >> 4;
	u8DC = (u8Buf & 0x0C) >> 2;

	rBuffer.ReadU8(&u8PA);

	adsb.u8AC = u8AC;
	adsb.u8MN = u8MN;
	adsb.u8DC = u8DC;
	adsb.u8PA = u8PA;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/090 Figure of Merit\n");
		tmpBuf += QString("  AC = %1, MN = %2, DC = %3, PA = %4\n").arg(u8AC).arg(u8MN).arg(u8DC).arg(u8PA);
	}
}

/**
 * Data Item I021/095 Velocity Accuracy
 * Definition : Velocity uncertainty category of the least accurate velocity component.
 * Format     : One-octet fixed length Data Item
 *
 * NOTE - bits-4/1 (PA) code the "Navigational Uncertainty Categories - Position" as
 * 		described in the ADS-B MASPS[Ref.3]
 */
void Cat021::I021_095(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;

	rBuffer.ReadU8(&u8Buf);

	adsb.u8VelocityAccur = u8Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/095 Velocity Accuracy : %1\n").arg(u8Buf);
	}
}

/**
 * Data Item I021/110 Trajectory Intent
 * Definition : Reports indicating the 4D intended trajectory of the aircraft.
 * Format     : Compound Data Item, comprising a primary subfield of one octet, followed
 *              by the indicated subfields.
 */
void Cat021::I021_110(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;

	rBuffer.ReadU8(&u8Buf);

	adsb.tisCHK = (u8Buf & 0x80) >> 7;
	adsb.tidCHK = (u8Buf & 0x40) >> 6;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/100 Trajectory Intent (TIS = %1, TID = %2)\n").arg(adsb.tisCHK).arg(adsb.tidCHK);
	}
	u8Fx = (u8Buf & 0x01);

	// Structure of Subfield #1 : Trajectory Intent Status
	if (u8Fx && adsb.tisCHK) {
		rBuffer.ReadU8(&u8Buf);

		adsb.nav = (u8Buf & 0x80) >> 7;
		adsb.nvb = (u8Buf & 0x40) >> 6;

		if (DEBUG) {
			tmpBuf += QString("  Subfield #1 : Trajectory Intent Status   nav = %1, nvb = %2\n").arg(adsb.nav).arg(adsb.nvb);
		}
	}

	// Structure of Subfield #2 : Trajectory Intent Data
	// Format : Repetitive Data Item starting with a one-octet field Repetition
	//          Indicator(REP) followed by at least one Trajectory Intent Point
	//          comprising fifteen octets
	if (u8Fx && adsb.tidCHK) {
		rBuffer.ReadU8(&u8Buf);

		adsb.trajectorRep = u8Buf;
		if (DEBUG) {
			tmpBuf += QString("    Subfield #2 : Trajectory Intent Data trajectorRep = %1\n").arg(adsb.trajectorRep);
		}

		for (int i=0; i<adsb.trajectorRep; i++) {
			TrajectoryIntent data;

			rBuffer.ReadU8(&u8Buf);
			data.tca = (u8Buf & 0x80) >> 7;
			data.nc  = (u8Buf & 0x40) >> 6;
			data.tcpNum = (u8Buf & 0x3F);

			// Altitude
			S16 s16Alt = 0;
			F64 f64Alt = 0.0;
			rBuffer.ReadS16(&s16Alt);

			f64Alt = static_cast<F64>(s16Alt);
			f64Alt = 10.0 * f64Alt;
			data.altitude = f64Alt;

			// Latitude, Longitude
			S32 s32Lat = 0;
			S32 s32Lon = 0;
			F64 f64Buf = 0.0;

			rBuffer.ReadS24(&s32Lat);
			f64Buf = static_cast<F64>(s32Lat);
			f64Buf = f64Buf * ( 180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23 degrees
			data.lat = f64Buf;

			rBuffer.ReadS24(&s32Lon);
			f64Buf = static_cast<F64>(s32Lon);
			f64Buf = f64Buf * ( 180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23 degrees
			data.lon = f64Buf;

			rBuffer.ReadU8(&u8Buf);
			data.pointType = (u8Buf & 0xF0) >> 4;
			data.td  = (u8Buf & 0xC0) >> 2;
			data.tra = (u8Buf & 0x02) >> 1;
			data.toa = (u8Buf & 0x01);

			S32 s32Buf = 0;
			S16 s16Buf = 0;

			rBuffer.ReadS24(&s32Buf);		// time
			f64Buf = static_cast<F64>(s32Buf);
			data.tov = f64Buf;

			rBuffer.ReadS16(&s16Buf);
			f64Buf = static_cast<F64>(s16Buf);
			data.ttr = 0.01 * f64Buf;

			adsb.trajectoryList.append(data);

			if (DEBUG) {
				tmpBuf += QString("     tca = %1, nc = %2, tcpNum = %3, alt = %4, pointType = %5, td = %6, "
						"tra = %7, toa = %8, tov = %9, ttr = %10\n")
						.arg(data.tca).arg(data.nc).arg(data.tcpNum).arg(data.altitude).arg(data.pointType).arg(data.td)
						.arg(data.tra).arg(data.toa).arg(data.tov).arg(data.ttr);
			}
		}
	}
}

/**
 * Data Item I021/130, Position in WGS-84 Co-ordinates
 * Definition : Position in WGS-84 Co-ordinates
 * Format     : Six-octet fixed length Data Item.
 */
void Cat021::I021_130(CBuffer& rBuffer)
{
	// Latitude, Longitude
	S32 s32Lat = 0;
	S32 s32Lon = 0;
	F64 f64Buf = 0.0;

//	rBuffer.ReadS24(&s32Buf);
//	f64Buf = static_cast<F64>(s32Buf);
//	f64Buf = f64Buf * (180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23
//	tmp.tidLatitude = f64Buf;
//
//	rBuffer.ReadS24(&s32Buf);
//	f64Buf = static_cast<F64>(s32Buf);
//	f64Buf = f64Buf * (180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23
//	tmp.tidLongitude = f64Buf;
//
//	S32 s32Lat = 0;
//	F64 f64Lat = 0.0;
//	rBuffer.ReadS32(&s32Lat);
//	f64Lat = static_cast<F64>(s32Lat);
//	f64Lat = f64Lat * (180.0 / (1024 * 1024 * 32));
//	systemTrack.wgsXpos = f64Lat;


	rBuffer.ReadS24(&s32Lat);
	tmpBuf += QString("Lat %1 ").arg(s32Lat);
	f64Buf = static_cast<F64>(s32Lat);
	f64Buf = f64Buf * ( 180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23 degrees
	adsb.lat = f64Buf;

	rBuffer.ReadS24(&s32Lon);
	tmpBuf += QString("Lon %1 ").arg(s32Lon);
	f64Buf = static_cast<F64>(s32Lon);
	f64Buf = f64Buf * ( 180.0 / (1024.0 * 1024.0 * 8.0));		// LSB = 180/2^23 degrees
	adsb.lon = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/130, Position in WGS-84 Co-ordinates (lat = %1, lon = %2)\n")
				.arg(adsb.lat).arg(adsb.lon);
	}
}

/**
 * Data Item I021/140 Geometric Altitude
 * Definition : Minimum Altitude from a plane tangent to the earth's ellipsoid,
 * 				defined by WGS-84, in two's complement form.
 * Format     : Two-Octet fixed length data item.
 * LSB        : 6.25 ft (-1500 ft <= Altitude <= 150000 ft)
 *
 * NOTES
 * 				LSB is required to be thinner than 10 ft by ICAO
 */
void Cat021::I021_140(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadS16(&s16Buf);
	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * 6.25;

	adsb.alt = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/140 Geometric Altitude (alt = %1)\n")
				.arg(adsb.alt);
	}
}

/**
 * Data Item I021/145 Flight Level
 * Definition : Flight Level from barometric measurements, not QNH corrected, in
 * 				two's complement form.
 * Format     : Two-Octet fixed length data item
 */
void Cat021::I021_145(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadS16(&s16Buf);
	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * 0.25;		// 1/4 FL

	adsb.fl = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/145 Flight Level (FL = %1)\n")
				.arg(adsb.fl);
	}
}

/**
 * Data Item I021/146 Intermediate State Selected Altitude
 * Definition : The short-term vertical intent as described by either the FMS selected altitude,
 * 				the Altitude Control Panel Selected Altitude, or the current aircraft altitude
 * 				according to the aircraft's mode of flight.
 * Format     : Two-Octet fixed length data item.
 */
void Cat021::I021_146(CBuffer& rBuffer)
{
	U16 u16Buf = 0;
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadU16(&u16Buf);

	adsb.sas = (u16Buf & 0x8000) >> 15;
	adsb.source = (u16Buf & 0x6000) >> 13;

	s16Buf = (u16Buf & 0x1FFF);
	f64Buf = static_cast<F64>(s16Buf);
	f64Buf = f64Buf * 25.0;			// 25 ft
	adsb.intermediateAlt = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("I021/146 Intermediate State Selected Altitude (sas = %1, soruce = %2, alt = %3)\n")
				.arg(adsb.sas).arg(adsb.source).arg(adsb.intermediateAlt);
	}
}

/**
 * Data Item I021/148 Final State Selected Altitude
 * Definition : The vertical intent value that corresponds with the ATC cleared altitude,
 * 				as derived from the Altitude Control Panel.
 * Format     : Two-Octet fixed length data item.
 */
void Cat021::I021_148(CBuffer& rBuffer)
{
	U16 u16Buf = 0;
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadU16(&u16Buf);

	adsb.mv = (u16Buf & 0x8000) >> 15;
	adsb.ah = (u16Buf & 0x4000) >> 14;
	adsb.am = (u16Buf & 0x2000) >> 13;

	s16Buf = (u16Buf & 0x1FFF);
	f64Buf = static_cast<F64>(s16Buf);
	f64Buf = f64Buf * 25.0;			// 25 ft
	adsb.finalStateAlt = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("I021/148 Final State Selected Altitude (mv = %1, ah = %2, am = %3, alt = %4)\n")
				.arg(adsb.mv).arg(adsb.ah).arg(adsb.am).arg(adsb.finalStateAlt);
	}
}

/**
 * Data Item I021/150 Air Speed
 * Definition : Calculated Air Speed (Element of Air Vector)
 * Format     : Two-Octet fixed length data item
 *
 * Air Speed( IAS or Mach)
 * If IAS, LAB = 2^-14 NM/s
 * If Mach, LSB = 0.001
 */
void Cat021::I021_150(CBuffer& rBuffer)
{
	U16 u16Buf = 0;
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadU16(&u16Buf);

	adsb.im = (u16Buf & 0x8000) >> 15;

	s16Buf = (u16Buf & 0x7FFF);
	f64Buf = static_cast<F64>(s16Buf);

	if (adsb.im) {		// IAS
		f64Buf = f64Buf * (1.0 / (2.0 * 1024.0 * 16.0));
	}else {				// Mach
		f64Buf = f64Buf * 0.001;		// LSB = 0.001
	}

	adsb.airSpeed = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/150 Air Speed (im = %1, Air Speed = %2)\n")
				.arg(adsb.im).arg(adsb.airSpeed);
	}
}

/**
 * Data Item I021/151 True Airspeed
 * Definition : True Air Speed
 * Format     : Two-Octet fixed length data item.
 * LSB        : 1 knot
 */
void Cat021::I021_151(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadS16(&s16Buf);

	adsb.trueAirSpeed = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/151 True Airspeed (True Airspeed = %1)\n")
				.arg(adsb.trueAirSpeed);
	}
}

/**
 * Data Item I021/152 Magnetic Heading
 * Definition : Magnetic Heading (Element of Air Vector)
 * Format     : Two-Octet fixed length data item
 * LSB        : 360 / 2^16 = 0.0055
 */
void Cat021::I021_152(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadS16(&s16Buf);

	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * (360.0 / (1024.0 * 64.0));				// LSB = 360/2^16

	adsb.magHeading = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/152 Magnetic Heading (Magnetic Heading = %1)\n")
				.arg(adsb.magHeading);
	}
}

/**
 * Data Item I021/155 Barometric Vertical Rate
 * Definition : barometric Vertical Rate, in two's complement form.
 * Format     : Two-Octet fixed length data item.
 * LSB        : 6.15 feet/minute
 */
void Cat021::I021_155(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadS16(&s16Buf);

	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * 6.25;			// LSB = 6.25 feet/minute

	adsb.barVerticalRate = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/155 Barometric Vertical Rate = %1\n")
				.arg(adsb.barVerticalRate);
	}
}

/**
 * Data Item I021/157 Geometric Vertical Rate
 * Definition : Geometric Vertical Rate, in two's compelement form, with reference to WGS-84
 * Format     : Two-Octet fixed length data item.
 * LSB        : 6.25 feet/minute
 */
void Cat021::I021_157(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadS16(&s16Buf);

	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * 6.25;			// LSB = 6.25 feet/minute

	adsb.geoVerticalRate = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/157 Geometric Vertical Rate = %1\n")
				.arg(adsb.geoVerticalRate);
	}
}

/**
 * Data Item I021/160 Ground Vector
 * Definition : Ground Speed and Track Angle elements of Ground Vector
 * Format     : Four-Octet fixed length data item
 * LSB        : Ground Speed = 2^-14
 *              Track Angle  = 360 / 2^16
 */
void Cat021::I021_160(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;
	rBuffer.ReadS16(&s16Buf);

	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * 0.22;   // (1.0 / (1024.0 * 16.0));			// LSB = 2^-14 NM/s  -2 NM/s ≤ Ground Speed < 2 NM/s

	adsb.groundSpeed = f64Buf;

	rBuffer.ReadS16(&s16Buf);

	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * (360.0 / (1024.0 * 64.0));			// LSB = 360/2^16

	adsb.trackAngle = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/160 Ground Vector  Groud Speed= %1, Track Angle : %2\n")
				.arg(adsb.groundSpeed).arg(adsb.trackAngle);
	}
}

/**
 * Data Item I021/165 Rate Of Turn
 * Definition : Rate of Turn, in two's complement form.
 * Format     : Variable length data item, comprising a first part of one-octet,
 *              followed by a one-octet extent as necessary
 *
 */
void Cat021::I021_165(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;

	rBuffer.ReadU8(&u8Buf);

	adsb.ti = (u8Buf & 0xC0) >> 6;

	u8Fx = (u8Buf & 0x01);

	if (u8Fx) {
		rBuffer.ReadU8(&u8Buf);

		s16Buf = (u8Buf & 0xFE) >> 1;
		f64Buf = static_cast<F64>(s16Buf);

		f64Buf = f64Buf * 0.25;
		adsb.rateOfTurn = f64Buf;
	}
	if (DEBUG) {
		tmpBuf += QString("Data Item I021/165 Rate Of Turn  ti= %1, rate of trun : %2\n")
				.arg(adsb.ti).arg(adsb.rateOfTurn);
	}
}

/**
 * Data Item I021/170 Target Identification
 * Definition : Target (aircraft or vehicle) identification in 8 characters,
 *              as reported by the target
 * Format     : Six-octet fixed length Data Item.
 * bits-48/1  : Characters 1-8 (coded on 6 Bits each) defining target identification
 *              when flight plan is available or the registration marking when no
 *              flight plan is available. Coding rules are provided in [5] Section 3.1.2.9
 */
void Cat021::I021_170(CBuffer& rBuffer)
{
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

	adsb.targetId = QString("%1").arg(ch);

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/170 Target Identification = %1\n")
				.arg(adsb.targetId);
	}
}

/**
 * Data Item I021/200 Taret Status
 * Definition : Status of the target
 * Format     : One-octet fixed length Data Item
 */
void Cat021::I021_200(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;

	rBuffer.ReadU8(&u8Buf);

	adsb.targetStatus = u8Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/200 Taret Status = %1\n")
				.arg(adsb.targetStatus);
	}
}

/**
 * Data Item I021/210 Link Technology Indicator
 * Definition : Indication of which ADS link technology has been used to send the
 *              target report.
 * Format     : One-octet fixed length Data Item
 */
void Cat021::I021_210(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;

	rBuffer.ReadU8(&u8Buf);

	adsb.dti = (u8Buf & 0x10) >> 4;
	adsb.mds = (u8Buf & 0x08) >> 3;
	adsb.uat = (u8Buf & 0x04) >> 2;
	adsb.vdl = (u8Buf & 0x02) >> 1;
	adsb.otr = (u8Buf & 0x01);

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/210 Link Technology Indicator DTI = %1, MDS = %2, UAT = %3, VDL = %4, OTR = %5\n")
				.arg(adsb.dti).arg(adsb.mds).arg(adsb.uat).arg(adsb.vdl).arg(adsb.otr);
	}
}

/**
 * Data Item I021/200 Met Information
 *
 */
void Cat021::I021_220(CBuffer& rBuffer)
{
	U8 u8Buf = 0x00;
	U8 u8Fx  = 0x00;
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;

	rBuffer.ReadU8(&u8Buf);

	adsb.wsCHK = (u8Buf & 0x80) >> 7;
	adsb.wdCHK = (u8Buf & 0x40) >> 6;
	adsb.tmpCHK = (u8Buf & 0x20) >> 5;
	adsb.trbCHK = (u8Buf & 0x10) >> 4;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/200 Met Information WS = %1, WD = %2, TMP = %3, TRB = %4\n")
				.arg(adsb.wsCHK).arg(adsb.wdCHK).arg(adsb.tmpCHK).arg(adsb.trbCHK);
	}

	u8Fx = (u8Buf & 0x01);

	// Structure of Subfield #1 : Wind Speed
	if (u8Fx && adsb.wsCHK) {
		rBuffer.ReadS16(&s16Buf);

		adsb.windSpeed = s16Buf;

		if (DEBUG) {
			tmpBuf += QString("    Wind Speed = %1\n").arg(adsb.windSpeed);
		}
	}

	// Structure of Subfield #2 : Wind Direction
	if (u8Fx && adsb.wdCHK) {
		rBuffer.ReadS16(&s16Buf);

		adsb.windDirection = s16Buf;

		if (DEBUG) {
			tmpBuf += QString("    Wind Direction = %1\n").arg(adsb.windDirection);
		}
	}

	// Structure of Subfield #3 : Temperature
	if (u8Fx && adsb.tmpCHK) {
		rBuffer.ReadS16(&s16Buf);

		f64Buf = static_cast<F64>(s16Buf);
		f64Buf = f64Buf * 0.25;

		adsb.temperature = f64Buf;

		if (DEBUG) {
			tmpBuf += QString("    Temperature = %1\n").arg(adsb.temperature);
		}
	}

	// Structure of Subfield #4 : Turbulence
	if (u8Fx && adsb.trbCHK) {
		rBuffer.ReadS16(&s16Buf);

		adsb.turbulence = s16Buf;

		if (DEBUG) {
			tmpBuf += QString("    Turbulence = %1\n").arg(adsb.turbulence);
		}
	}
}

/**
 * Data Item I021/230 Roll Angle
 * Definition : The roll angle, in two's complement form, of an aircraft executing a turn
 * Format     : A two byte fixed length data item.
 * LSB        : 0.01 degree
 *              -180 <= Roll Angle <= 180
 */
void Cat021::I021_230(CBuffer& rBuffer)
{
	S16 s16Buf = 0;
	F64 f64Buf = 0.0;

	rBuffer.ReadS16(&s16Buf);

	f64Buf = static_cast<F64>(s16Buf);

	f64Buf = f64Buf * 0.01;

	adsb.rollAngle = f64Buf;

	if (DEBUG) {
		tmpBuf += QString("Data Item I021/230 Roll Angle = %1\n")
				.arg(adsb.rollAngle);
	}
}

BOOL Cat021::FSPec(CBuffer& rBuffer)
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

				//printf("%d=%d ", s16Index, m_bFSPEC[s16Index]);
			}
		}
	}while(u8 & 0x01);		// FX

	return TRUE;
}

QString Cat021::getCallsign()
{
	return adsb.targetId;
}

double  Cat021::getLatitude()
{
	return adsb.lat;
}
double  Cat021::getLongitude()
{
	return adsb.lon;
}
double  Cat021::getSpeed()
{
	return adsb.groundSpeed;
}
double  Cat021::getHeading()
{
	return adsb.trackAngle;
}
double  Cat021::getAltitude()
{
	return adsb.fl;
}
