/*
 * exception.h
 *
 *  Created on: 14 cze 2014
 *      Author: aldor
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

class MroException: public std::exception {
	std::string m_msg;
public:
	MroException(std::string msg) {
		m_msg = msg;
	}
	  virtual const char* what() const _GLIBCXX_USE_NOEXCEPT {
	    	return m_msg.c_str();
	    }

	    virtual ~MroException() {

	    }

};




#endif /* EXCEPTION_H_ */
