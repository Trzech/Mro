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

unsigned char* BrodleyBinarizator::binarizeWithoutIntegral(
		unsigned char* inputBuffer, int rows, int cols, int surroundings,
		double r) {
	unsigned char *resultBuffer;

	if ((resultBuffer = new unsigned char[rows * cols]) == NULL) {
		throw -1;
	}

	unsigned char** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);
	unsigned char** threshold = Binarizator::prepareTableForOperations(
			resultBuffer, rows, cols);

	timer.begin();

	for (int i = 0 + surroundings; i < rows - surroundings; ++i) {
		for (int j = 0 + surroundings; j < cols - surroundings; ++j) {
			int suma = 0;
			for (int k = i - surroundings; k <= i + surroundings; ++k) {
				for (int l = j - surroundings; l <= j + surroundings; ++l) {
					suma += source[k][l];

				}
			}
			int n = (2 * surroundings + 1) * (2 * surroundings + 1);
			double m = suma * 1.0 / n;
			threshold[i][j] = r * m;
		}
	}

	manageBorders(source, threshold, rows, cols, surroundings);
	convertThresholdIntoTarget(source, threshold, rows, cols);
	timer.end();
	delete[] source;
	delete[] threshold;

	return resultBuffer;
}





unsigned char* BrodleyBinarizator::binarizeWithIntegral(
		unsigned char* inputBuffer, int rows, int cols, int surroundings,
		double r) {
	unsigned char *resultBuffer;

	if ((resultBuffer = new unsigned char[rows * cols]) == NULL) {
		throw -1;
	}

	unsigned long long int *integralBuffer;
	if ((integralBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}

	unsigned char** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);
	unsigned char** threshold = Binarizator::prepareTableForOperations(
			resultBuffer, rows, cols);
	unsigned long long int** integral = Binarizator::prepareTableForOperations(
			integralBuffer, rows, cols);

	IntegralImageBuilder integralImageBuilder;
	timer.begin();
	integralImageBuilder.buildForImage(source, integral, rows, cols);

	for (int i = 0 + surroundings + 1; i < rows - surroundings; ++i) {
		for (int j = 0 + surroundings + 1; j < cols - surroundings; ++j) {
			double m = integralImageBuilder.mean(integral, i, j, surroundings);
			threshold[i][j] = r * m;

		}
	}

	manageBorders(source, threshold, rows, cols, surroundings);

	convertThresholdIntoTarget(source, threshold, rows, cols);
	timer.end();
	delete integralBuffer;
	delete[] source;
	delete[] threshold;
	delete[] integral;

	return resultBuffer;

}

