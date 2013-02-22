/*
 * AirPlaneModel.h
 *
 *  Created on: 2012. 4. 30.
 *      Author: JMS
 *  Description : Track 데이터를 모델로 구성한다.
 */

#ifndef AIRPLANEMODEL_H_
#define AIRPLANEMODEL_H_
#include "../item/AirPlaneItem.h"
#include "../item/AirPlaneTextItem.h"
#include "../item/LinkItem.h"

class AirPlaneModel {
public:
	AirPlaneModel();
	~AirPlaneModel();

	void setItem1(AirPlaneItem* item) { item1 = item; }
	void setItem2(AirPlaneTextItem* item) { item2 = item; }
	void setItem3(LinkItem* item) { item3 = item; }
	AirPlaneItem* getItem1() { return item1; }
	AirPlaneTextItem* getItem2() { return item2; }

private:
	AirPlaneItem* item1;
	AirPlaneTextItem* item2;
	LinkItem* item3;
};

#endif /* AIRPLANEMODEL_H_ */
