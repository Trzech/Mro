/*
 * IntegralBrodleyBinarizator.cpp
 *
 *  Created on: 24 mar 2014
 *      Author: mj
 */

#include "BrodleyBinarizator.h"
#include <stdlib.h>

BrodleyBinarizator::BrodleyBinarizator() {
	// TODO Auto-generated constructor stub

}

BrodleyBinarizator::~BrodleyBinarizator() {
	// TODO Auto-generated destructor stub
}

unsigned char* BrodleyBinarizator::binarizeWithIntegral(
		unsigned char* inputBuffer, int rows, int cols, int k, double r) {

	unsigned char *resultBuffer;
	if ((resultBuffer = new unsigned char[rows * cols]) == NULL) {
		throw -1;
	}

	unsigned long long int *integralBuffer;
	if ((integralBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}

	unsigned char *thresholdBuffer;
	if ((thresholdBuffer = new unsigned char[rows * cols]) == NULL) {
		throw -1;
	}

	unsigned char** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);
	unsigned char** target = Binarizator::prepareTableForOperations(
			resultBuffer, rows, cols);
	unsigned char** threshold = Binarizator::prepareTableForOperations(
			thresholdBuffer, rows, cols);
	unsigned long long int** I = Binarizator::prepareTableForOperations(integralBuffer,
			rows, cols);

	IntegralImageBuilder integralImageBuilder;
	timer.begin();
	integralImageBuilder.buildForImage(source, I, rows, cols);

	double rPrzezN = r / ((2 * k + 1) * (2 * k + 1));

	for (int i = 0 + k + 1; i < rows - k; ++i) {
		for (int j = 0 + k + 1; j < cols - k; ++j) {
			int m = integralImageBuilder.sumInArea(I,i,j,k);
			threshold[i][j] = rPrzezN * m;
		}
	}

	manageBorders(threshold, rows, cols, k);
	convertThresholdIntoTarget(source, target, threshold, rows, cols);
	timer.end();
	delete integralBuffer;
	delete thresholdBuffer;
	delete[] source;
	delete[] target;
	delete[] threshold;
	delete[] I;

	return resultBuffer;

}

