/*
 * AbstractBinarizator.cpp
 *
 *  Created on: 29 mar 2014
 *      Author: mj
 */

#include "Binarizator.h"

Binarizator::Binarizator() {
	// TODO Auto-generated constructor stub

}

Binarizator::~Binarizator() {
	// TODO Auto-generated destructor stub
}

unsigned char** Binarizator::prepareTableForOperations(
		unsigned char* inputBuffer, int rows, int cols) {
	unsigned char** source = new unsigned char*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}

double** Binarizator::prepareTableForOperations(
		double* inputBuffer, int rows, int cols) {
	double** source = new double*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}


unsigned int** Binarizator::prepareTableForOperations(unsigned int* inputBuffer,
		int rows, int cols) {
	unsigned int** source = new unsigned int*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}

unsigned long long int** Binarizator::prepareTableForOperations(
		unsigned long long int* inputBuffer, int rows, int cols) {
	unsigned long long int** source = new unsigned long long int*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}

void Binarizator::manageBorders(unsigned char** target,
		int rows, int cols, int surroundings) {
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
			if (source[i][j] > treshold[i][j]) {
				target[i][j] = 255;
			} else {
				target[i][j] = 0;
			}
		}
	}
}

