/*
 * Base64.h
 *
 *  Created on: 2012. 6. 7.
 *      Author: JMS
 */

#ifndef BASE64_H_
#define BASE64_H_
#include <string>

class Base64 {
public:
	Base64();
	~Base64();
	std::string base64_encode(unsigned char const* , unsigned int len);
	std::string base64_decode(std::string const& s);
};

#endif /* BASE64_H_ */
