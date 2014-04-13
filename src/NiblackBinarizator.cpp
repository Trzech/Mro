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



	// TODO ten kwadrat wyłamuje się ze schematu dziedziczenia. naprawic to jakos - może nie liczyć w takim razie integrali w konstruktorze
	unsigned long long int *integralSquareBuffer;
	if ((integralSquareBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned long long int** IS = Binarizator::prepareTableForOperations(integralSquareBuffer, rows, cols);
	//
	IntegralImageBuilder::buildForImageWithSquares(inputArray, integralArray, IS, rows, cols);

	unsigned long long int n = (2 * k + 1) * (2 * k + 1);

	for (int i = 0 + k + 1; i < rows - k; ++i) {
		for (int j = 0 + k + 1; j < cols - k; ++j) {
			double m = IntegralImageBuilder::sumInArea(integralArray,i,j,k) * 1.0 / n;
			double ms = IntegralImageBuilder::sumInArea(IS,i,j,k) * 1.0 / n;
			thresholdArray[i][j] = m * (1.0 + k_factor * (sqrt(ms - m * m) / R - 1.0));

		}
	}

 	manageBorders(thresholdArray, rows, cols, k);
	convertThresholdIntoTarget(inputArray, resultArray, thresholdArray, rows, cols);


	delete integralBuffer;
	delete integralSquareBuffer;
	delete[] IS;
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

