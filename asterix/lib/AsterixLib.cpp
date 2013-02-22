/*
 * AsterixLib.cpp
 *
 *  Created on: 2012. 4. 20.
 *      Author: JMS
 */

#include "AsterixLib.h"

AsterixLib::AsterixLib() {
	// TODO Auto-generated constructor stub
	tmpBuf = "";
	DEBUG = 0x01;		// debug : 0x01, not debug : 0x00

	for (int i=0; i<MAX_FSPEC; i++) {
		m_bFSPEC[i] = FALSE;
	}
}

AsterixLib::~AsterixLib() {
	// TODO Auto-generated destructor stub
}

void AsterixLib::Clear()
{
	tmpBuf = "";

	for (int i=0; i<MAX_FSPEC; i++) {
		m_bFSPEC[i] = FALSE;
	}
}

QString AsterixLib::toString()
{
	return tmpBuf;
}

U8 AsterixLib::CharacterValue(U8 bb)
{
	U8 retVal = 0x00;

	switch(bb) {
	case 0x00:
		retVal = 0x20;	// space
		break;
	case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07: case 0x08:
	case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0E: case 0x0F: case 0x10:
	case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
	case 0x19: case 0x1A:
		retVal = (U8)(bb + 0x40);
		break;
	case 0x20:
	case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
	case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
		retVal = bb;
		break;
	default:
		retVal = 0x20;
		break;
	}
	return retVal;
}

QString AsterixLib::searchItem004(int idx)
{
	QString msg;

	switch(idx) {
	case 1:
		msg = "I004/010"; break;
	case 2:
		msg = "I004/000"; break;
	case 3:
		msg = "I004/015"; break;
	case 4:
		msg = "I004/020"; break;
	case 5:
		msg = "I004/040"; break;
	case 6:
		msg = "I004/045"; break;
	case 7:
		msg = "I004/060"; break;
	case 8:
		msg = "I004/030"; break;
	case 9:
		msg = "I004/170"; break;
	case 10:
		msg = "I004/120"; break;
	case 11:
		msg = "I004/070"; break;
	case 12:
		msg = "I004/076"; break;
	case 13:
		msg = "I004/074"; break;
	case 14:
		msg = "I004/075"; break;
	case 15:
		msg = "I004/100"; break;
	case 16:
		msg = "I004/035"; break;
	case 17:
		msg = "I004/171"; break;
	case 18:
		msg = "I004/110"; break;
	default:
		msg = "Not defined"; break;
	}
	return msg;
}
/**
 * Cat62 아이템 명칭을 리턴한다.
 */
QString AsterixLib::searchItem(int idx) {
	QString msg;
	switch(idx) {
	case 1:
		msg =  "I062/010"; break;
	case 2:
		msg = "Spare"; break;
	case 3:
		msg = "I062/015"; break;
	case 4:
		msg = "I062/070"; break;
	case 5:
		msg = "I062/105"; break;
	case 6:
		msg = "I062/100"; break;
	case 7:
		msg = "I062/185"; break;
	case 8:
		msg = "I062/210"; break;
	case 9:
		msg = "I062/060"; break;
	case 10:
		msg = "I062/245"; break;
	case 11:
		msg = "I062/380"; break;
	case 12:
		msg = "I062/040"; break;
	case 13:
		msg = "I062/080"; break;
	case 14:
		msg = "I062/290"; break;
	case 15:
		msg = "I062/200"; break;
	case 16:
		msg = "I062/295"; break;
	case 17:
		msg = "I062/136"; break;
	case 18:
		msg = "I062/130"; break;
	case 19:
		msg = "I062/135"; break;
	case 20:
		msg = "I062/220"; break;
	case 21:
		msg = "I062/390"; break;
	case 22:
		msg = "I062/270"; break;
	case 23:
		msg = "I062/300"; break;
	case 24:
		msg = "I062/110"; break;
	case 25:
		msg = "I062/120"; break;
	case 26:
		msg = "I062/510"; break;
	case 27:
		msg = "I062/500"; break;
	case 28:
		msg = "I062/340"; break;
	default:
		msg = "Not defined"; break;
	}
	return msg;
}
QString AsterixLib::searchItem021(int idx)
{
	QString msg;

	switch(idx) {
	case 1:
		msg = "I021/010";	break;
	case 2:
		msg = "I021/040"; break;
	case 3:
		msg = "I021/030"; break;
	case 4:
		msg = "I021/130"; break;
	case 5:
		msg = "I021/080"; break;
	case 6:
		msg = "I021/140"; break;
	case 7:
		msg = "I021/090"; break;
	case 8:
		msg = "I021/210"; break;
	case 9:
		msg = "I021/230"; break;
	case 10:
		msg = "I021/145"; break;
	case 11:
		msg = "I021/150"; break;
	case 12:
		msg = "I021/151"; break;
	case 13:
		msg = "I021/152"; break;
	case 14:
		msg = "I021/155"; break;
	case 15:
		msg = "I021/157"; break;
	case 16:
		msg = "I021/160"; break;
	case 17:
		msg = "I021/165"; break;
	case 18:
		msg = "I021/170"; break;
	case 19:
		msg = "I021/095"; break;
	case 20:
		msg = "I021/032"; break;
	case 21:
		msg = "I021/200"; break;
	case 22:
		msg = "I021/020"; break;
	case 23:
		msg = "I021/220"; break;
	case 24:
		msg = "I021/146"; break;
	case 25:
		msg = "I021/148"; break;
	case 26:
		msg = "I021/110"; break;
	default:
		msg = "Not defined"; break;
	}

	return msg;
}
