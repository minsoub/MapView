/*
 * AircraftDerivedData.cpp
 *
 *  Created on: 2012. 4. 13.
 *      Author: JMS
 */

#include "AircraftDerivedData.h"

AircraftDerivedData::AircraftDerivedData() {
	// TODO Auto-generated constructor stub
	Clear();


}

AircraftDerivedData::~AircraftDerivedData() {
	// TODO Auto-generated destructor stub
}

void AircraftDerivedData::Clear()
{
	adrCHK = 0x00;					// Subfield #1 : Target Address
	idCHK = 0x00;					// Subfield #2 : Target Identification
	mhgCHK = 0x00;					// Subfield #3 : Magnetic Heading
	iasCHK = 0x00;					// Subfield #4 : Indicated Airspeed / Mach Number
	tasCHK = 0x00;					// Subfield #5 : True Airspeed
	salCHK = 0x00;					// Subfield #6 : Selected Altitude
	fssCHK = 0x00;					// Subfield #7 : Final State Selected Altitude
	tisCHK = 0x00;					// Subfield #8 : Trajectory Intent Status
	tidCHK = 0x00;					// Subfield #9 : Trajectory Intent Data
	comCHK = 0x00;					// Subfield #10 : Communications / ACAS Capability and Flight Status
	sabCHK = 0x00;					// Subfield #11 : Status reported by ADS-B
	acsCHK = 0x00;					// Subfield #12 : ACAS Resolution Advisory Report
	bvrCHK = 0x00;					// Subfield #13 : Barometric Vertical Rate
	gvrCHK = 0x00;					// Subfield #14 : Geometric Vertical Rate
	ranCHK = 0x00;					// Subfield #15 : Roll Angle
	tarCHK = 0x00;					// Subfield #16 : Track Angle Rate
	tanCHK = 0x00;					// Subfield #17 : Track Angle
	gspCHK = 0x00;					// Subfield #18 : Ground Speed
	vunCHK = 0x00;					// Subfield #19 : Velocity Uncertainty
	metCHK = 0x00;					// Subfield #20 : Meteorological Data
	emcCHK = 0x00;					// Subfield #21 : Emitter Category
	posCHK = 0x00;					// Subfield #22 : Position Data
	galCHK = 0x00;					// Subfield #23 : Geometric Altitude Data
	punCHK = 0x00;					// Subfield #24 : Position Uncertainty Data
	mbCHK = 0x00;					// Subfield #25 : Mode S MB Data
	iarCHK = 0x00;					// Subfield #26 : Indicated Airspeed
	macCHK = 0x00;					// Subfield #27 : Mach Number
	bpsCHK = 0x00;					// Subfield #28 : Barometric Pressure Setting.


	// Subfield #1 : Target Address
	targetAddress = 0;			// 24 bits Target Address, A23 to A0

	// Subfield #2 : Target Identification
	targetId = "";

	// Subfield #3 : Magnetic Heading
	magHeading = 0.0;

	// Subfield #4 : Indicated Airspeed / Mach No
	// Note - Despite there are now two subfields (#26 and #27) reporting, respectively,
	//		the Indicated Airspeed track data and the Mach Number track data, this former
	//		subfield is kept free in order to prevent a full incompatibility with previous
	//		releases of ASTERIX Cat. 062 already implemented.
	im = 0x00;						// = 0 Air Speed = IAS, LSB = 2^-14 NM/s
								// = 1 Air Speed = Mach, LSB = 0.001
	airSpeed = 0.0;

	// Subfield #5 : True Airspeed
	tureAirSpeed = 0;			// LSB = 1 knot   0<= True Air Speed <= 2046 knots

	// Subfield #6 : Selected Altitude
	// Definition : The short-term vertical intent as described by either the FMS selected altitude,
	//				the Altitude Control Panel Selected Altitude (FCU/MCP), or the current aircrfat
	//				altitude according to the aircraft's mode of flight.
	sas = 0x00;						// = 0 No source information provided
								// = 1 Source Information provided
	source = 0x00;					// = 00 Unknown
								// = 01 Aircraft Altitude
								// = 10 FCU/MCP Selected Altitude
								// = 11 FMS Selected Altitude
	alt = 0.0;					// Altitude in two's complement form (LSB = 25ft, -1300ft <= Altitude <= 100000ft)

	// Subfield #7 : Final State Selected Altitude
	// Definition : The vertical intent value that corresponds wit the ATC cleared altitude, as derived
	//				from the Altitude Control Panel (FCU/MCP)
	mv = 0x00;						// Manage Vertical Mode
								// = 0 Not active
								// = 1 Active
	ah = 0x00;						// Altitude Hold
								// = 0 Not active
								// = 1 Active
	am = 0x00;						// Approach Mode
								// = 0 Not active
								// = 1 Active
	finalAlt = 0.0;				// Altitude in two's complement form (LSB = 25ft, -1300ft <= Altitude <= 100000ft)

	// Subfield #8 : Trajectory Itent Status
	nav = 0x00;						// = 0 Trajectory Intent Data is available for this aircraft
								// = 1 Trajectory Intent Data is not available for this aircraft
	nvb = 0x00;						// = 0 Trajectory Intent Data is valid
								// = 1 Trajectory Intent Data is not valid

	// Subfield #9 : Trajectory Intent Data
	// Format : Repetitive Data Item starting with a one-octet Field Repetition Indicator (REP) followed
	//          by at least one Trajectory Intent Point comprising fifteen octets.
	// NOTES
	//		1. NC is set to one when the aircraft will not fly the path described by the TCP data.
	//		2. TCP numbers start from zero.
	//		3. LT = Lateral Type
	//		4. VT = Vertical Type
	//		5. TOV gives the estimated time before reaching the point. It is defined as the
	//			absolute time from midnight.
	//		6. TOV is meaningfull only if TOA is set to 0.
	tidRep = 0x00;					// Repetition Factor

	trajectoryIntentDataList.clear();




	// Subfield #10 : Communications/ACAS Capability and Flight Status reported by Mode-S
	com = 0x00;						// Communications capability of the transponder
								// = 0 No communications capability (surveillance only)
								// = 1 Comm.A and Comm.B capability
								// = 2 Comm.A, Comm.B and Uplink ELM
								// = 3 Comm.A, Comm.B, Uplink ELM and Downlink ELM
								// = 4 Level 5 Transponder capability 5 to 7 Not assigned
	flStat = 0x00;					// Flight Status
								// = 0 No alert, no SPI, aircraft airborne
								// = 1 No alert, no SPI, aircraft on ground
								// = 2 Alert, no SPI, aircraft airborne
								// = 3 Alert, no SPI, aircraft on ground
								// = 4 Alert, SPI, aircraft airborne or on ground
								// = 5 No alert, SPI, aircraft airborne or on ground
	ssc = 0x00;						// Specific service capability
								// = 0 No
								// = 1 Yes
	arc = 0x00;						// Altitude reporting capability
								// = 0 100 ft resolution
								// = 1 25 ft resolution
	aic = 0x00;						// Aircraft identification capability
								// = 0 No
								// = 1 Yes
	b1a = 0x00;						// BDS 1,0 bit 16
	b1b = 0x00;						// BDS 1,0 bits 37/40

	// Subfield #11 : Status reported by ADS-B
	ac = 0x00;						// 00 = unknown
								// 01 = ACAS not operational
								// 10 = ACAS operational
								// 11 = invalid
	mn = 0x00;						// 00 = unknown
								// 01 = Multiple navigational aids not operating
								// 10 = Multiple navigational aids operating
								// 11 = invalid
	dc = 0x00;						// 00 = unknown
								// 01 = Differential correction
								// 10 = No differential correction
								// 11 = invalid
	gbs = 0x00;						// = 0 Transponder Ground Bit not set or unknown
								// = 1 Transponder Ground Bit set
	adsbStat = 0x00;				// Flight Status
								// = 0 No emergency
								// = 1 General emergency
								// = 2 Lifeguard / medical
								// = 3 Minimum fuel
								// = 4 No communications
								// = 5 Unlawful interference
								// = 7 Unknown

	// Subfield #12 : ACAS Resolution Advisory Report
	// Definition : Currently active Resolution Advisory (RA), if any, generated by the
	//				ACAS associated with the transponder transmitting the report and
	//				threat identity data.
	// Format     : Seven-octet fixed length Data Item
	advisoryMsg = "";

	// Subfield #13 : Barometric Vertical Rate
	barometricVR = 0.0;			// Barometric Vertical Rate in two's complement form
								// LSB = 6.25 feet/minute

	// Subfield #14 : Geometric Vertical Rate
	geometricVR = 0.0;			// Geometric Vertical Rate in two's complement form
								// LSB = 6.25 feet/minute

	// Subfield #15 : Roll Angle
	rollAngle = 0.0;				// Roll Angle in two's complement form
								// LSB = 0.01 degree
								// -180 <= Roll Angle <= 180

	// Subfield #16 : Track Angle Rate
	// NOTES
	//		1. A positive value represents a right turn, whereas a negative value represents
	//		   a left turn.
	//		2. Value 15 means 15o/s or above.
	ti = 0x00;						// Turn Indicator
								// 00 = Not aviaible
								// 01 = Left
								// 10 = Right
								// 11 = Straight
	rateOfTurn = 0.0;				// Rate of Turn in two's complement form
								// LSB = 2^-2 = 1/4
								// -15 o/s <= Rate of Turn <= 15 o/s

	// Subfield #17 : Track Angle
	trackAngle = 0.0;				// Track Angle
								// LSB = 360/2^16 = approx. 0.0055 o

	// Subfield #18 : Ground Speed
	groundSpeed = 0.0;			// Ground Speed in two's complement form reference to WGS84
								// LSB = 2^14 NM/s    ~=  0.22 kt
								// -2 NM/s <= Ground Speed < 2 NM/s

	// Subfield #19 : Velocity Uncertainty
	// NOTES - Velocity Uncertainty category of the least accurate velocity component.
	vunCategory = 0x00;		// Velocity Uncertainty Category

	// Subfield #20 : Met Data
	ws = 0x00;						// = 0 Not valid Wind Speed
								// = 1 Valid Wind Speeed
	wd = 0x00;						// = 0 Not valid Wind Direction
								// = 1 Valid Wind Speed
	tmp = 0x00;						// = 0 Not valid Temperature
								// = 1 Valid Temperature
	trb = 0x00;						// = 0 Not valid Turbulence
								// = 1 Valid Turbulence
	windSpeed = 0.0;				// Wind Speed
								// LSB = 1 knot
								// 0 <= Wind Speed <= 300
	windDirection = 0.0;			// Wind Direction
								// LSB = 1 deg
								// 1 <= Wind Direction <= 360
	temperature = 0.0;			// Temperature in degrees celsius
								// LSB = 0.25  oC
								// -100 oC <= Temperature <= 100 oC
	turbulence = 0;				// Turbulence
								// Integer between 0 and 15 inclusive

	// Subfield #21 : Emitter Category
	ecat = 0x00;					// 1 = light aircraft <= 7000 kg
								// 2 = reserved
								// 3 = 7000 kg < medium aircrfat < 136000 kg
								// 4 = reserved
								// 5 = 136000 kg <= heavy aircraft
								// 6 = highly manoeuvrable (5g acceleration capability) and high speed (>400 knots cruise)
								// 7 to 9 = reserved
								// 10 = rotocraft
								// 11 = glider / sailplane
								// 12 = lighter-than-air
								// 13 = unmanned aerial vehicle
								// 14 = space / transatmospheric vehicle
								// 15 = ultralight / handglider / paraglider
								// 16 = parachutist / skydiver
								// 17 to 19 = reserved
								// 20 = surface emergency vehicle
								// 21 = surface service vehicle
								// 22 = fixed ground or tethered obstruction
								// 23 to 24 = reserved

	// Subfield #22 : Position
	// NOTES - Positive longitue indicates East. Positive latitude indicates North.
	posLatitude = 0.0;			// In WGS.84 in two's complement form
								// Range -90 <= Latitude < 90 deg
								// LSB = 180/2^23 deg
	posLongitude = 0.0;			// In WGS.84 in two's complement form
								// Range -180 <= Latitude < 180 deg
								// LSB = 180/2^23 deg

	// Subfield #23 : Geometric Altitude
	// NOTES - LSB is required to be thinner than 10 ft by ICAO
	geoAltitude = 0.0;			// Altitude in two's complement form
								// -1500 ft <= Altitude <= 150000 ft
								// LSB = 6.25 ft

	// Subfield #24 : Position Uncertainty
	//TODO: What type????
	pun = 0x00;						// Position Uncertainty

	// Subfield #25 : MODE S MB DATA
	// Format : Repetitive starting with an one-octet Field Repetition Indicator (REP)
	//			followed by at least one BDS report comprising one seven octet BDS
	//			register and one octet BDS code.
	bdsRep = 0x00;					// REP
	modeSMBDataList.clear();

	// Subfield #26 : Indicated Airspeed
	indicatedSpd = 0;			// Indicated Airspeed
								// 0 Kt <= Indicated Airpseed <= 1100 Kt
								// LSB = 1 Kt

	// Subfield #27 : Mach Number
	machNum = 0.0;				// Mach Number
								// 0 <= Mach Number <= 4.096
								// LSB = Mach 0.008

	// Subfield #28 : Barometric Pressure Setting (derived from Mode S BDS 4,0)
	// NOTE - BPS is the barometric pressure setting of the aircraft minus 800 mb.
	bps = 0.0;					// Barometric Pressure Setting
								// LSB = 0.1 mb
								// -0ft <= BPS <= 409.5 mb

}
