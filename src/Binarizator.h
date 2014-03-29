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
	static unsigned char** prepareTableForOperations(
			unsigned char* inputBuffer, int rows, int cols);
	static unsigned long long int** prepareTableForOperations(unsigned long long int* inputBuffer, int rows, int cols);
};

#endif /* ABSTRACTBINARIZATOR_H_ */
