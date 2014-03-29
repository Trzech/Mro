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
unsigned long long int** Binarizator::prepareTableForOperations(
		unsigned long long int* inputBuffer, int rows, int cols) {
	unsigned long long int** source = new unsigned long long int*[rows];
	for (int i = 0; i < rows; ++i) {
		source[i] = inputBuffer + i * cols;
	}
	return source;
}

