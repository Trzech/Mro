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

struct threadArgs {
	unsigned long long int** I;
	unsigned long long int** IS;
	unsigned char** threshold;
	double k_factor;
	int R;
	int rowsMin;
	int rowsMax;
	int colsMin;
	int colsMax;
	int k;
};

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

void *calculateThreshold(void * args) {
	struct threadArgs *a = (struct threadArgs *) args;

	unsigned long long int n = (2 * a->k + 1) * (2 * a->k + 1);
	for (int i = a->rowsMin + a->k + 1; i < a->rowsMax - a->k; ++i) {
		for (int j = a->colsMin + a->k + 1; j < a->colsMax - a->k; ++j) {
			double m = (a->I[i + a->k][j + a->k]
					+ a->I[i - a->k - 1][j - a->k - 1]
					- a->I[i - a->k - 1][j + a->k]
					- a->I[i + a->k][j - a->k - 1]) * 1.0 / n;
			double ms = (a->IS[i + a->k][j + a->k]
					+ a->IS[i - a->k - 1][j - a->k - 1]
					- a->IS[i - a->k - 1][j + a->k]
					- a->IS[i + a->k][j - a->k - 1]) * 1.0 / n;
			a->threshold[i][j] = m
					* (1.0 + a->k_factor * (sqrt(ms - m * m) / R - 1.0));
		}
	}
}

struct threadArgs NiblackBinarizator::preapreStructForThread(int cols, int k,
		double k_factor, int rows, unsigned long long int** I,
		unsigned long long int** IS, unsigned char** threshold) {
	struct threadArgs a;
	a.I = I;
	a.IS = IS;
	a.R = R;
	a.colsMax = cols;
	a.colsMin = 0;
	a.k = k;
	a.k_factor = k_factor;
	a.rowsMax = rows;
	a.rowsMin = 0;
	a.threshold = threshold;
	return a;
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
	struct threadArgs a1 = preapreStructForThread(cols, k, k_factor, rows, I,
			IS, threshold);
	struct threadArgs a2 = preapreStructForThread(cols, k, k_factor, rows, I,
			IS, threshold);
	struct threadArgs a3 = preapreStructForThread(cols, k, k_factor, rows, I,
			IS, threshold);

	a1.rowsMin = 0;
	a1.rowsMax = rows / 3;
	a2.rowsMin = rows / 3;
	a2.rowsMax = (2.0 / 3.0) * rows;
	a3.rowsMin = (2.0 / 3.0) * rows;
	a3.rowsMax = rows;

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_create(&thread1, NULL, calculateThreshold, &a1);
	pthread_create(&thread2, NULL, calculateThreshold, &a2);
	pthread_create(&thread3, NULL, calculateThreshold, &a3);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	manageBorders(threshold, rows, cols, k);
	convertThresholdIntoTarget(source, target, threshold, rows, cols);

	timer.end();
	delete[] source;
	delete integralBuffer;
	delete[] I;
	delete integralSquareBuffer;
	delete[] IS;
	return resultBuffer;
}

NiblackBinarizator::NiblackBinarizator() {
	// TODO Auto-generated constructor stub

}

NiblackBinarizator::~NiblackBinarizator() {
	// TODO Auto-generated destructor stub
}

