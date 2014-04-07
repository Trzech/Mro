/*
 * AbstractBinarizator.h
 *
 *  Created on: 29 mar 2014
 *      Author: mj
 */

#ifndef ABSTRACTBINARIZATOR_H_
#define ABSTRACTBINARIZATOR_H_
#include "IntegralImageBuilder.h"
#include "Timer.h"

class Binarizator {
public:
	Binarizator();
	virtual ~Binarizator();
	static unsigned char** prepareTableForOperations(
			unsigned char* inputBuffer, int rows, int cols);
	static unsigned long long int** prepareTableForOperations(unsigned long long int* inputBuffer, int rows, int cols);
	static double** prepareTableForOperations(double* inputBuffer, int rows, int cols);
	static unsigned int** prepareTableForOperations(
			unsigned int* inputBuffer, int rows, int cols);
protected:
	Timer timer;
	void manageBorders(
			unsigned char** target, int rows, int cols, int surroundings);
	void convertThresholdIntoTarget(unsigned char** source,
			unsigned char** target,unsigned char** threshold, int rows, int cols);
};

#endif /* ABSTRACTBINARIZATOR_H_ */
