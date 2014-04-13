/*
 * ImageBinarizator.cpp
 *
 *  Created on: 22 mar 2014
 *      Author: mj
 */

#include "NiblackBinarizator.h"
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
const double R = 128.0;

unsigned char * NiblackBinarizator::binarizeWithIntegral(int k,
		double k_factor) {

	unsigned char *resultBuffer = allocMemory<unsigned char>(rows, cols);
	unsigned char** resultArray = Binarizator::prepareTableForOperations(
			resultBuffer, rows, cols);

	// TODO Żeby zachować konwencję należałoby przenieść to do pola tej klasy.
	unsigned long long int *integralSquareBuffer = allocMemory<
			unsigned long long int>(rows, cols);
	unsigned long long int** integralSquareArray =
			Binarizator::prepareTableForOperations(integralSquareBuffer, rows,
					cols);
	IntegralImageBuilder::buildForImageWithSquares(inputArray, integralArray,
			integralSquareArray, rows, cols);

	unsigned long long int n = (2 * k + 1) * (2 * k + 1);

	for (int i = 0 + k + 1; i < rows - k; ++i) {
		for (int j = 0 + k + 1; j < cols - k; ++j) {
			double m = IntegralImageBuilder::sumInArea(integralArray, i, j, k)
					* 1.0 / n;
			double ms = IntegralImageBuilder::sumInArea(integralSquareArray, i,
					j, k) * 1.0 / n;
			thresholdArray[i][j] = m
					* (1.0 + k_factor * (sqrt(ms - m * m) / R - 1.0));

		}
	}

	manageBorders(thresholdArray, rows, cols, k);
	convertThresholdIntoTarget(inputArray, resultArray, thresholdArray, rows,
			cols);

	delete integralSquareBuffer;
	delete[] integralSquareArray;
	delete[] resultArray;
	return resultBuffer;
}

NiblackBinarizator::NiblackBinarizator(unsigned char* inputBuffer, int rows,
		int cols) :
		Binarizator(inputBuffer, rows, cols) {
	// TODO Auto-generated constructor stub

}

NiblackBinarizator::~NiblackBinarizator() {
	// TODO Auto-generated destructor stub
}

