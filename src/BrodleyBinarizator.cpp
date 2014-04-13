/*
 * IntegralBrodleyBinarizator.cpp
 *
 *  Created on: 24 mar 2014
 *      Author: mj
 */

#include "BrodleyBinarizator.h"
#include <stdlib.h>

BrodleyBinarizator::BrodleyBinarizator(unsigned char* inputBuffer, int rows,
		int cols) :
		Binarizator(inputBuffer, rows, cols) {
	// TODO Auto-generated constructor stub

}

BrodleyBinarizator::~BrodleyBinarizator() {
	// TODO Auto-generated destructor stub
}

unsigned char* BrodleyBinarizator::binarizeWithIntegral(int k, double r) {

	unsigned char *resultBuffer = allocMemory<unsigned char>(rows, cols);
	unsigned char** resultArray = Binarizator::prepareTableForOperations(
			resultBuffer, rows, cols);

	IntegralImageBuilder::buildForImage(inputArray, integralArray, rows, cols);

	double rPrzezN = r / ((2 * k + 1) * (2 * k + 1));

	for (int i = 0 + k + 1; i < rows - k; ++i) {
		for (int j = 0 + k + 1; j < cols - k; ++j) {
			int m = IntegralImageBuilder::sumInArea(integralArray, i, j, k);
			thresholdArray[i][j] = rPrzezN * m;
		}
	}

	manageBorders(thresholdArray, rows, cols, k);
	convertThresholdIntoTarget(inputArray, resultArray, thresholdArray, rows,
			cols);

	return resultBuffer;

}

