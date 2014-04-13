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

	template<class T>
	static T** prepareTableForOperations(T* inputBuffer, int rows, int cols);
	template<class T>
	static T* allocMemory(int rows, int cols);
protected:
	Timer timer;
	void manageBorders(unsigned char** target, int rows, int cols,
			int surroundings);
	void convertThresholdIntoTarget(unsigned char** source,
			unsigned char** target, unsigned char** threshold, int rows,
			int cols);

};

template<class T>
T** Binarizator::prepareTableForOperations(T* inputBuffer, int rows, int cols) {
	T** source = new T*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}

template<class T>
T* Binarizator::allocMemory(int rows, int cols) {
	T*resultBuffer;
	if ((resultBuffer = new T[rows * cols]) == NULL) {
		throw -1;
	}
	return resultBuffer;
}
#endif /* ABSTRACTBINARIZATOR_H_ */
