/*
 * ReportOption.h
 *
 *  Created on: 2012. 5. 9.
 *      Author: JMS
 *  Description : Track Report Option 데이터 블록에 표시할 옵션 데이터를 관리한다.
 */

#ifndef REPORTOPTION_H_
#define REPORTOPTION_H_

#include <QString>

class ReportOption {
public:
	ReportOption();
	~ReportOption();

	bool trackNumber;
	bool assignedFL;
	bool warning;
	bool ssr;
	bool callsing;
	bool modec;
	bool velocity;
	int  blockCount;
	void Clear();

	QString trackNumberText();
	QString assignedFLText();
	QString warningText();
	QString ssrText();
	QString callsingText();
	QString modecText();
	QString velocityText();
	int     getBlockCount() { return blockCount; };
};

#endif /* REPORTOPTION_H_ */
