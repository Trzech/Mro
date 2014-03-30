/*
 * ImageBinarizator.cpp
 *
 *  Created on: 22 mar 2014
 *      Author: mj
 */

#include "NiblackBinarizator.h"
#include <math.h>
#include <stdlib.h>

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

	manageBorders(source, threshold, rows, cols, surroundings);
	convertThresholdIntoTarget(source, threshold, rows, cols);
	delete[] source;

	return resultBuffer;
}

unsigned char * NiblackBinarizator::binarizeWithIntegral(
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

	unsigned long long int *integralBuffer;
	if ((integralBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned long long int** integral = Binarizator::prepareTableForOperations(
			integralBuffer, rows, cols);

	unsigned long long int *integralSquareBuffer;
	if ((integralSquareBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned long long int** integralSquare =
			Binarizator::prepareTableForOperations(integralSquareBuffer, rows,
					cols);

	IntegralImageBuilder integralImageBuilder;
	integralImageBuilder.buildForImageWithSquares(source, integral,
			integralSquare, rows, cols);

	for (int i = 0 + surroundings + 1; i < rows - surroundings; ++i) {
		for (int j = 0 + surroundings + 1; j < cols - surroundings; ++j) {

			double m = integralImageBuilder.mean(integral, i, j, surroundings);
			double s = sqrt(
					integralImageBuilder.mean(integralSquare, i, j,
							surroundings) - m * m);

			threshold[i][j] = m * (1.0 + k_factor * (s / R - 1.0));

		}
	}

	manageBorders(source, threshold, rows, cols, surroundings);
	convertThresholdIntoTarget(source, threshold, rows, cols);
	delete[] source;
	delete integralBuffer;
	delete[] integral;
	delete integralSquareBuffer;
	delete[] integralSquare;
	return resultBuffer;
}

NiblackBinarizator::NiblackBinarizator() {
	// TODO Auto-generated constructor stub

}

NiblackBinarizator::~NiblackBinarizator() {
	// TODO Auto-generated destructor stub
}

