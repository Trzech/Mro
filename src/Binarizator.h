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
	Binarizator(unsigned char* inputBuffer, int rows,
			int cols);
	virtual ~Binarizator();

	template<class T>
	static T** prepareTableForOperations(T* inputBuffer);
	template<class T>
	static T* allocMemory();
protected:
	unsigned char* inputBuffer;
	unsigned char** inputArray;
	int rows;
	int cols;
	unsigned char *thresholdBuffer;
	unsigned char** thresholdArray;
	unsigned long long int *integralBuffer;
	unsigned long long int **integralArray;


	void manageBorders(unsigned char** target, int rows, int cols,
			int surroundings);
	void convertThresholdIntoTarget(unsigned char** source,
			unsigned char** target, unsigned char** threshold, int rows,
			int cols);

};

template<class T>
T** Binarizator::prepareTableForOperations(T* inputBuffer) {
	T** source = new T*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}

template<class T>
T* Binarizator::allocMemory() {
	T*resultBuffer;
	if ((resultBuffer = new T[rows * cols]) == NULL) {
		throw -1;
	}
	return resultBuffer;
}
#endif /* ABSTRACTBINARIZATOR_H_ */
