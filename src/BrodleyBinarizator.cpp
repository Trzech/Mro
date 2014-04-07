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
	unsigned char** target = Binarizator::prepareTableForOperations(
			resultBuffer, rows, cols);
	unsigned char** treshold = Binarizator::prepareTableForOperations(
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
			treshold[i][j] = r * m;
		}
	}

	manageBorders(treshold, rows, cols, surroundings);
	convertThresholdIntoTarget(source, target, treshold, rows, cols);
	timer.end();
	delete[] source;
	delete[] target;
	delete[] treshold;

	return resultBuffer;
}

unsigned char* BrodleyBinarizator::binarizeWithIntegral(
		unsigned char* inputBuffer, int rows, int cols, int k, double r) {

	unsigned char *resultBuffer;
	if ((resultBuffer = new unsigned char[rows * cols]) == NULL) {
		throw -1;
	}

	unsigned int *integralBuffer;
	if ((integralBuffer = new unsigned int[rows * cols]) == NULL) {
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
	unsigned char** threshold= Binarizator::prepareTableForOperations(
			thresholdBuffer, rows, cols);
	unsigned int** I = Binarizator::prepareTableForOperations(integralBuffer,
			rows, cols);

	IntegralImageBuilder integralImageBuilder;
	timer.begin();
	integralImageBuilder.buildForImage(source, I, rows, cols);

	double rPrzezN = r / ((2 * k + 1) * (2 * k + 1));

	for (int i = 0 + k + 1; i < rows - k; ++i) {
		for (int j = 0 + k + 1; j < cols - k; ++j) {
			//double m = integralImageBuilder.mean(integral, i, j, surroundings);

			int m = (I[i + k][j + k] + I[i - k - 1][j - k - 1]
					- I[i - k - 1][j + k] - I[i + k][j - k - 1]);

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

