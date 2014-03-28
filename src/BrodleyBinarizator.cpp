/*
 * IntegralBrodleyBinarizator.cpp
 *
 *  Created on: 24 mar 2014
 *      Author: mj
 */

#include "BrodleyBinarizator.h"
#include "IntegralImageBuilder.h"
#include <stdlib.h>

BrodleyBinarizator::BrodleyBinarizator() {
	// TODO Auto-generated constructor stub

}

BrodleyBinarizator::~BrodleyBinarizator() {
	// TODO Auto-generated destructor stub
}

void BrodleyBinarizator::binarizeWithoutIntegral(unsigned char* inputBuffer,
		unsigned char* outputBuffer, int rows, int cols, int surroundings,
		double r) {
	unsigned char** source = prepareTableForOperations(inputBuffer, rows, cols);
	unsigned char** target = prepareTableForOperations(outputBuffer, rows,
			cols);

	for (int i = 0 + surroundings; i < rows - surroundings; ++i) {
		for (int j = 0 + surroundings; j < cols - surroundings; ++j) {
			int suma = 0;
			for (int k = i - surroundings; k < i + surroundings; ++k) {
				for (int l = j - surroundings; l < j + surroundings; ++l) {
					suma += source[k][l];

				}
			}
			int n = (2 * surroundings + 1) * (2 * surroundings + 1);
			double m = suma * 1.0 / n;
			int threshold = r * m;
			if (source[i][j] > threshold) {
				target[i][j] = 255;
			} else {
				target[i][j] = 0;
			}
		}
	}

	delete[] source;
	delete[] target;
}

void BrodleyBinarizator::binarizeWithIntegral(unsigned char* inputBuffer,
		unsigned char* outputBuffer, int rows, int cols, int surroundings,
		double r) {
	unsigned char *integralBuffer;
	if ((integralBuffer = new unsigned char[rows * cols]) == NULL)
		exit(1);

	unsigned char** source = prepareTableForOperations(inputBuffer, rows, cols);
	unsigned char** target = prepareTableForOperations(outputBuffer, rows,
			cols);
	unsigned char** integral = prepareTableForOperations(outputBuffer, rows,
			cols);

	IntegralImageBuilder integralImageBuilder;
	integralImageBuilder.buildForImage(source, integral, rows, cols);

	for (int i = 0 + surroundings; i < rows - surroundings; ++i) {
		for (int j = 0 + surroundings; j < cols - surroundings; ++j) {

			double m = integralImageBuilder.mean(integral, i, j, surroundings);
			int threshold = r * m;
			if (source[i][j] > threshold) {
				target[i][j] = 255;
			} else {
				target[i][j] = 0;
			}
		}
	}

	delete integralBuffer;
	delete[] source;
	delete[] target;
	delete[] integral;

}

unsigned char** BrodleyBinarizator::prepareTableForOperations(
		unsigned char* inputBuffer, int rows, int cols) {
	unsigned char** source = new unsigned char*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}

