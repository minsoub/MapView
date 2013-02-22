/*
 * TrajectoryIntent.cpp
 *
 *  Created on: 2012. 5. 14.
 *      Author: JMS
 *  Description : Trajectory Intent Data
 *                Data Item I021/110, Trajectory Intent
 *                Structure of Subfield #2
 */

#include "TrajectoryIntent.h"

TrajectoryIntent::TrajectoryIntent() {
	// TODO Auto-generated constructor stub
	tca		= 0x00;
	nc			= 0x00;
	tcpNum	= 0;
	altitude	= 0.0;
	lat		= 0.0;
	lon		= 0.0;
	pointType	= 0;
	td			= 0x00;
	tra		= 0x00;
	toa		= 0x00;
	tov		= 0.0;
	ttr		= 0.0;
}

TrajectoryIntent::~TrajectoryIntent() {
	// TODO Auto-generated destructor stub
}
