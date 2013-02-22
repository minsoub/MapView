/*
 * AircraftDerivedData.h
 *
 *  Created on: 2012. 4. 13.
 *      Author: JMS
 *  Description:
 *              EUROCONTROL STANDARD DOCUMENT FOR SURVEILLANCE DATA EXCHANGE
 *              Part 17 : Category 62
 *              SDPS Track Messages
 *              - Data Item I062/380, Aircraft Derived Data.
 *              - This class describes Data Item I062/380.
 *              - Data derived directly by the aircraft. This includes data transmitted via Mode-S and ADS-B
 */

#ifndef AIRCRAFTDERIVEDDATA_H_
#define AIRCRAFTDERIVEDDATA_H_
#include <QString>
#include <QVector>
#include "../lib/BaseTypes.h"
#include "../lib/CTrackTime.h"
#include "TrajectoryIntentData.h"
#include "ModeSMBData.h"

class AircraftDerivedData {
public:
	AircraftDerivedData();
	~AircraftDerivedData();

	void Clear();

	U8 adrCHK;					// Subfield #1 : Target Address
	U8 idCHK;					// Subfield #2 : Target Identification
	U8 mhgCHK;					// Subfield #3 : Magnetic Heading
	U8 iasCHK;					// Subfield #4 : Indicated Airspeed / Mach Number
	U8 tasCHK;					// Subfield #5 : True Airspeed
	U8 salCHK;					// Subfield #6 : Selected Altitude
	U8 fssCHK;					// Subfield #7 : Final State Selected Altitude
	U8 tisCHK;					// Subfield #8 : Trajectory Intent Status
	U8 tidCHK;					// Subfield #9 : Trajectory Intent Data
	U8 comCHK;					// Subfield #10 : Communications / ACAS Capability and Flight Status
	U8 sabCHK;					// Subfield #11 : Status reported by ADS-B
	U8 acsCHK;					// Subfield #12 : ACAS Resolution Advisory Report
	U8 bvrCHK;					// Subfield #13 : Barometric Vertical Rate
	U8 gvrCHK;					// Subfield #14 : Geometric Vertical Rate
	U8 ranCHK;					// Subfield #15 : Roll Angle
	U8 tarCHK;					// Subfield #16 : Track Angle Rate
	U8 tanCHK;					// Subfield #17 : Track Angle
	U8 gspCHK;					// Subfield #18 : Ground Speed
	U8 vunCHK;					// Subfield #19 : Velocity Uncertainty
	U8 metCHK;					// Subfield #20 : Meteorological Data
	U8 emcCHK;					// Subfield #21 : Emitter Category
	U8 posCHK;					// Subfield #22 : Position Data
	U8 galCHK;					// Subfield #23 : Geometric Altitude Data
	U8 punCHK;					// Subfield #24 : Position Uncertainty Data
	U8 mbCHK;					// Subfield #25 : Mode S MB Data
	U8 iarCHK;					// Subfield #26 : Indicated Airspeed
	U8 macCHK;					// Subfield #27 : Mach Number
	U8 bpsCHK;					// Subfield #28 : Barometric Pressure Setting.

	// Subfield #1 : Target Address
	int targetAddress;			// 24 bits Target Address, A23 to A0

	// Subfield #2 : Target Identification
	QString targetId;

	// Subfield #3 : Magnetic Heading
	F64 magHeading;

	// Subfield #4 : Indicated Airspeed / Mach No
	// Note - Despite there are now two subfields (#26 and #27) reporting, respectively,
	//		the Indicated Airspeed track data and the Mach Number track data, this former
	//		subfield is kept free in order to prevent a full incompatibility with previous
	//		releases of ASTERIX Cat. 062 already implemented.
	U8 im;						// = 0 Air Speed = IAS, LSB = 2^-14 NM/s
								// = 1 Air Speed = Mach, LSB = 0.001
	F64 airSpeed;

	// Subfield #5 : True Airspeed
	int tureAirSpeed;			// LSB = 1 knot   0<= True Air Speed <= 2046 knots

	// Subfield #6 : Selected Altitude
	// Definition : The short-term vertical intent as described by either the FMS selected altitude,
	//				the Altitude Control Panel Selected Altitude (FCU/MCP), or the current aircrfat
	//				altitude according to the aircraft's mode of flight.
	U8 sas;						// = 0 No source information provided
								// = 1 Source Information provided
	U8 source;					// = 00 Unknown
								// = 01 Aircraft Altitude
								// = 10 FCU/MCP Selected Altitude
								// = 11 FMS Selected Altitude
	F64 alt;					// Altitude in two's complement form (LSB = 25ft, -1300ft <= Altitude <= 100000ft)

	// Subfield #7 : Final State Selected Altitude
	// Definition : The vertical intent value that corresponds wit the ATC cleared altitude, as derived
	//				from the Altitude Control Panel (FCU/MCP)
	U8 mv;						// Manage Vertical Mode
								// = 0 Not active
								// = 1 Active
	U8 ah;						// Altitude Hold
								// = 0 Not active
								// = 1 Active
	U8 am;						// Approach Mode
								// = 0 Not active
								// = 1 Active
	F64 finalAlt;				// Altitude in two's complement form (LSB = 25ft, -1300ft <= Altitude <= 100000ft)

	// Subfield #8 : Trajectory Itent Status
	U8 nav;						// = 0 Trajectory Intent Data is available for this aircraft
								// = 1 Trajectory Intent Data is not available for this aircraft
	U8 nvb;						// = 0 Trajectory Intent Data is valid
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
	U8 tidRep;					// Repetition Factor

	QVector<TrajectoryIntentData> trajectoryIntentDataList;




	// Subfield #10 : Communications/ACAS Capability and Flight Status reported by Mode-S
	U8 com;						// Communications capability of the transponder
								// = 0 No communications capability (surveillance only)
								// = 1 Comm.A and Comm.B capability
								// = 2 Comm.A, Comm.B and Uplink ELM
								// = 3 Comm.A, Comm.B, Uplink ELM and Downlink ELM
								// = 4 Level 5 Transponder capability 5 to 7 Not assigned
	U8 flStat;					// Flight Status
								// = 0 No alert, no SPI, aircraft airborne
								// = 1 No alert, no SPI, aircraft on ground
								// = 2 Alert, no SPI, aircraft airborne
								// = 3 Alert, no SPI, aircraft on ground
								// = 4 Alert, SPI, aircraft airborne or on ground
								// = 5 No alert, SPI, aircraft airborne or on ground
	U8 ssc;						// Specific service capability
								// = 0 No
								// = 1 Yes
	U8 arc;						// Altitude reporting capability
								// = 0 100 ft resolution
								// = 1 25 ft resolution
	U8 aic;						// Aircraft identification capability
								// = 0 No
								// = 1 Yes
	U8 b1a;						// BDS 1,0 bit 16
	U8 b1b;						// BDS 1,0 bits 37/40

	// Subfield #11 : Status reported by ADS-B
	U8 ac;						// 00 = unknown
								// 01 = ACAS not operational
								// 10 = ACAS operational
								// 11 = invalid
	U8 mn;						// 00 = unknown
								// 01 = Multiple navigational aids not operating
								// 10 = Multiple navigational aids operating
								// 11 = invalid
	U8 dc;						// 00 = unknown
								// 01 = Differential correction
								// 10 = No differential correction
								// 11 = invalid
	U8 gbs;						// = 0 Transponder Ground Bit not set or unknown
								// = 1 Transponder Ground Bit set
	U8 adsbStat;				// Flight Status
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
	QString advisoryMsg;

	// Subfield #13 : Barometric Vertical Rate
	F64 barometricVR;			// Barometric Vertical Rate in two's complement form
								// LSB = 6.25 feet/minute

	// Subfield #14 : Geometric Vertical Rate
	F64 geometricVR;			// Geometric Vertical Rate in two's complement form
								// LSB = 6.25 feet/minute

	// Subfield #15 : Roll Angle
	F64 rollAngle;				// Roll Angle in two's complement form
								// LSB = 0.01 degree
								// -180 <= Roll Angle <= 180

	// Subfield #16 : Track Angle Rate
	// NOTES
	//		1. A positive value represents a right turn, whereas a negative value represents
	//		   a left turn.
	//		2. Value 15 means 15o/s or above.
	U8 ti;						// Turn Indicator
								// 00 = Not aviaible
								// 01 = Left
								// 10 = Right
								// 11 = Straight
	F64 rateOfTurn;				// Rate of Turn in two's complement form
								// LSB = 2^-2 = 1/4
								// -15 o/s <= Rate of Turn <= 15 o/s

	// Subfield #17 : Track Angle
	F64 trackAngle;				// Track Angle
								// LSB = 360/2^16 = approx. 0.0055 o

	// Subfield #18 : Ground Speed
	F64 groundSpeed;			// Ground Speed in two's complement form reference to WGS84
								// LSB = 2^14 NM/s    ~=  0.22 kt
								// -2 NM/s <= Ground Speed < 2 NM/s

	// Subfield #19 : Velocity Uncertainty
	// NOTES - Velocity Uncertainty category of the least accurate velocity component.
	U8 vunCategory;		// Velocity Uncertainty Category

	// Subfield #20 : Met Data
	U8 ws;						// = 0 Not valid Wind Speed
								// = 1 Valid Wind Speeed
	U8 wd;						// = 0 Not valid Wind Direction
								// = 1 Valid Wind Speed
	U8 tmp;						// = 0 Not valid Temperature
								// = 1 Valid Temperature
	U8 trb;						// = 0 Not valid Turbulence
								// = 1 Valid Turbulence
	F64 windSpeed;				// Wind Speed
								// LSB = 1 knot
								// 0 <= Wind Speed <= 300
	F64 windDirection;			// Wind Direction
								// LSB = 1 deg
								// 1 <= Wind Direction <= 360
	F64 temperature;			// Temperature in degrees celsius
								// LSB = 0.25  oC
								// -100 oC <= Temperature <= 100 oC
	int turbulence;				// Turbulence
								// Integer between 0 and 15 inclusive

	// Subfield #21 : Emitter Category
	U8 ecat;					// 1 = light aircraft <= 7000 kg
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
	F64 posLatitude;			// In WGS.84 in two's complement form
								// Range -90 <= Latitude < 90 deg
								// LSB = 180/2^23 deg
	F64 posLongitude;			// In WGS.84 in two's complement form
								// Range -180 <= Latitude < 180 deg
								// LSB = 180/2^23 deg

	// Subfield #23 : Geometric Altitude
	// NOTES - LSB is required to be thinner than 10 ft by ICAO
	F64 geoAltitude;			// Altitude in two's complement form
								// -1500 ft <= Altitude <= 150000 ft
								// LSB = 6.25 ft

	// Subfield #24 : Position Uncertainty
	//TODO: What type????
	U8 pun;						// Position Uncertainty

	// Subfield #25 : MODE S MB DATA
	// Format : Repetitive starting with an one-octet Field Repetition Indicator (REP)
	//			followed by at least one BDS report comprising one seven octet BDS
	//			register and one octet BDS code.
	U8 bdsRep;					// REP
	QVector<ModeSMBData> modeSMBDataList;

	// Subfield #26 : Indicated Airspeed
	int indicatedSpd;			// Indicated Airspeed
								// 0 Kt <= Indicated Airpseed <= 1100 Kt
								// LSB = 1 Kt

	// Subfield #27 : Mach Number
	F64 machNum;				// Mach Number
								// 0 <= Mach Number <= 4.096
								// LSB = Mach 0.008

	// Subfield #28 : Barometric Pressure Setting (derived from Mode S BDS 4,0)
	// NOTE - BPS is the barometric pressure setting of the aircraft minus 800 mb.
	F64 bps;					// Barometric Pressure Setting
								// LSB = 0.1 mb
								// -0ft <= BPS <= 409.5 mb

};

#endif /* AIRCRAFTDERIVEDDATA_H_ */
