/*
 * ADSBCls.cpp
 *
 *  Created on: 2012. 5. 11.
 *      Author: JMS
 *  Description : ADS-B data structure
 */

#include "ADSBCls.h"

ADSBCls::ADSBCls() {
	// TODO Auto-generated constructor stub
	Clear();
}

ADSBCls::~ADSBCls() {
	// TODO Auto-generated destructor stub
}

void ADSBCls::Clear()
{
	sac = 0x00;
	sic = 0x00;

	timeofdayAccuracy = 0.0;

	u8DCR = 0x00;
	u8GBS = 0x00;
	u8SIM = 0x00;
	u8TST = 0x00;
	u8RAB = 0x00;
	u8SAA = 0x00;
	u8SPI = 0x00;
	u8ATP = 0x00;
	u8ARC = 0x00;

	targetAddr = 0;

	u8AC = 0x00;
	u8MN = 0x00;
	u8DC = 0x00;
	u8PA = 0x00;

	u8VelocityAccur = 0x00;

	tisCHK	= 0x00;			// Trajectory Intent Status check
	tidCHK	= 0x00;			// Trajectory Intent Data check

	nav		= 0x00;
	nvb		= 0x00;

	trajectoryList.clear();

	lat = 0.0;
	lon = 0.0;
	alt = 0.0;
	fl  = 0.0;

	sas = 0x00;
	source = 0x00;
	intermediateAlt = 0.0;

	mv = 0x00;
	ah = 0x00;
	am = 0x00;
	finalStateAlt = 0.0;

	targetId = "";

	targetStatus = 0x00;

	dti = 0x00;
	mds = 0x00;
	uat = 0x00;
	vdl = 0x00;
	otr = 0x00;

	wsCHK = 0x00;
	wdCHK = 0x00;
	tmpCHK = 0x00;
	trbCHK = 0x00;
	windSpeed = 0;
	windDirection = 0;
	temperature = 0.0;
	turbulence = 0;

	rollAngle = 0.0;
}
