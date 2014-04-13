/*
 * AbstractBinarizator.cpp
 *
 *  Created on: 29 mar 2014
 *      Author: mj
 */

#include "Binarizator.h"

void Binarizator::changeImage(unsigned char* inputBuffer, int rows, int cols) {
	freeMemory();
	this->inputBuffer = inputBuffer;
	this->rows = rows;
	this->cols = cols;
	inputArray = prepareTableForOperations(inputBuffer, rows, cols);
	thresholdBuffer = allocMemory<unsigned char>(rows, cols);
	thresholdArray = prepareTableForOperations(thresholdBuffer, rows, cols);
	integralBuffer = allocMemory<unsigned long long int>(rows, cols);
	integralArray = prepareTableForOperations(integralBuffer, rows, cols);
}

Binarizator::Binarizator(unsigned char* inputBuffer, int rows, int cols) {
	changeImage(inputBuffer, rows, cols);
}

void Binarizator::freeMemory() {
	if (thresholdArray != NULL) {
		delete[] thresholdArray;
	}
	if (thresholdBuffer != NULL) {
		delete thresholdBuffer;
	}
	if (inputArray != NULL) {
		delete[] inputArray;
	}
	if (integralBuffer != NULL) {
		delete integralBuffer;
	}
	if (integralArray != NULL) {
		delete[] integralArray;
	}
}

Binarizator::~Binarizator() {
	freeMemory();
}

void Binarizator::manageBorders(unsigned char** target, int rows, int cols,
		int surroundings) {
	for (int i = surroundings + 1; i <= rows - surroundings; ++i) {
		for (int j = 0; j <= surroundings; ++j) {
			target[i][j] = target[i][surroundings + 1];
		}
	}
	for (int i = surroundings + 1; i <= rows - surroundings; ++i) {
		for (int j = cols - surroundings; j < cols; ++j) {
			target[i][j] = target[i][cols - surroundings - 1];
		}
	}
	for (int i = 0; i <= surroundings; ++i) {
		for (int j = 0; j < cols; ++j) {
			target[i][j] = target[surroundings + 1][j];
		}
	}
	for (int i = rows - surroundings; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			target[i][j] = target[rows - surroundings - 1][j];
		}
	}

}

void Binarizator::convertThresholdIntoTarget(unsigned char** source,
		unsigned char** target, unsigned char** treshold, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (source[i][j] >= treshold[i][j]) {
				target[i][j] = 255;
			} else {
				target[i][j] = 0;
			}
		}
	}
}

