/*
 * DecodeAsterix.h
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 */

#ifndef DECODEASTERIX_H_
#define DECODEASTERIX_H_

#include <QString>

#include "lib/CBuffer.h"
#include "cat004/Cat004.h"
#include "cat062/Cat062.h"
#include "cat021/Cat021.h"
class DecodeAsterix {
public:
	DecodeAsterix();
	~DecodeAsterix();

	void GetPacket(CBuffer& rBuffer);
	QString toString();
	U8 getCategory() { return cat; }
	Cat062 getCat62() { return cat062; }
	Cat021 getCat21() { return cat021; }
	Cat004 getCat04() { return cat004; }
private:
	Cat004 cat004;
	Cat062 cat062;
	Cat021 cat021;

	int index;
	U8 cat;
};

#endif /* DECODEASTERIX_H_ */
