/*
 * ReportOption.cpp
 *
 *  Created on: 2012. 5. 9.
 *      Author: JMS
 *  Description : Track Report Option 데이터 블록에 표시할 옵션 데이터를 관리한다.
 */

#include "ReportOption.h"

ReportOption::ReportOption() {
	// TODO Auto-generated constructor stub
	trackNumber	= false;
	assignedFL	= false;
	warning		= false;
	ssr			= true;
	callsing		= true;
	modec			= false;
	velocity		= true;
	blockCount  = 10;		// default
}

ReportOption::~ReportOption() {
	// TODO Auto-generated destructor stub
}

/**
 * All option clear
 */
void ReportOption::Clear()
{
	trackNumber	= false;
	assignedFL	= false;
	warning		= false;
	ssr			= false;
	callsing		= false;
	modec			= false;
	velocity		= false;
	blockCount  = 10;		// default
}

QString ReportOption::trackNumberText()
{
	if (trackNumber) return "True";
	else return "False";
}
QString ReportOption::assignedFLText()
{
	if (assignedFL) return "True";
	else  return "False";
}
QString ReportOption::warningText()
{
	if (warning) return "True";
	else  return "False";
}
QString ReportOption::ssrText()
{
	if(ssr) return "True";
	else return "False";
}
QString ReportOption::callsingText()
{
	if(callsing) return "True";
	else return "False";
}
QString ReportOption::modecText()
{
	if(modec) return "True";
	else return "False";
}
QString ReportOption::velocityText()
{
	if(velocity) return "True";
	else return "False";
}
