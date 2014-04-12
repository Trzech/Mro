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

unsigned char * NiblackBinarizator::binarizeWithoutIntegral(
		unsigned char* inputBuffer, int rows, int cols, int surroundings,
		double k_factor) {
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
			int sumaKwadratow = 0;
			for (int k = i - surroundings; k < i + surroundings; ++k) {
				for (int l = j - surroundings; l < j + surroundings; ++l) {
					suma += source[k][l];
					sumaKwadratow += source[k][l] * source[k][l];
				}
			}
			int n = (2 * surroundings + 1) * (2 * surroundings + 1);
			double m = suma * 1.0 / n;
			double s = sqrt(sumaKwadratow / n - m * m);

			threshold[i][j] = m * (1.0 + k_factor * (s / R - 1.0));

		}
	}

	manageBorders(threshold, rows, cols, surroundings);
	convertThresholdIntoTarget(source, threshold, threshold, rows, cols);
	timer.end();
	delete[] source;

	return resultBuffer;
}

unsigned char * NiblackBinarizator::binarizeWithIntegral(
		unsigned char* inputBuffer, int rows, int cols, int k,
		double k_factor) {

	unsigned char** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);
	//
	unsigned char *resultBuffer;

	if ((resultBuffer = new unsigned char[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned char** target = Binarizator::prepareTableForOperations(
			resultBuffer, rows, cols);
	//
	unsigned char *thresholdBuffer;
	if ((thresholdBuffer = new unsigned char[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned char** threshold = Binarizator::prepareTableForOperations(
			thresholdBuffer, rows, cols);
	//
	unsigned long long int *integralBuffer;
	if ((integralBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned long long int** I = Binarizator::prepareTableForOperations(
			integralBuffer, rows, cols);
	//
	unsigned long long int *integralSquareBuffer;
	if ((integralSquareBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned long long int** IS = Binarizator::prepareTableForOperations(
			integralSquareBuffer, rows, cols);
	//



	timer.begin();

	IntegralImageBuilder integralImageBuilder;

	integralImageBuilder.buildForImageWithSquares(source, I, IS, rows, cols);

	unsigned long long int n = (2 * k + 1) * (2 * k + 1);

	for (int i = 0 + k + 1; i < rows - k; ++i) {
		for (int j = 0 + k + 1; j < cols - k; ++j) {
			double m = integralImageBuilder.sumInArea(I,i,j,k) * 1.0 / n;
			double ms = integralImageBuilder.sumInArea(IS,i,j,k) * 1.0 / n;
			threshold[i][j] = m * (1.0 + k_factor * (sqrt(ms - m * m) / R - 1.0));

		}
	}

 	manageBorders(threshold, rows, cols, k);
	convertThresholdIntoTarget(source, target, threshold, rows, cols);

	timer.end();
	delete[] source;
	delete integralBuffer;
	delete[] I;
	delete integralSquareBuffer;
	delete[] IS;
	return resultBuffer;
	delete[] threshold;
	return thresholdBuffer;
}

NiblackBinarizator::NiblackBinarizator() {
	// TODO Auto-generated constructor stub

}

NiblackBinarizator::~NiblackBinarizator() {
	// TODO Auto-generated destructor stub
}

