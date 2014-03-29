/*
 * AbstractBinarizator.h
 *
 *  Created on: 29 mar 2014
 *      Author: mj
 */

#ifndef ABSTRACTBINARIZATOR_H_
#define ABSTRACTBINARIZATOR_H_

class Binarizator {
public:
	Binarizator();
	virtual ~Binarizator();
protected:
	unsigned char** prepareTableForOperations(
			unsigned char* inputBuffer, int rows, int cols);
};

#endif /* ABSTRACTBINARIZATOR_H_ */
