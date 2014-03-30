/*
 * IntegralImageBuilder.cpp
 *
 *  Created on: 24 mar 2014
 *      Author: mj
 */

#include "IntegralImageBuilder.h"

IntegralImageBuilder::IntegralImageBuilder() {
	// TODO Auto-generated constructor stub

}

IntegralImageBuilder::~IntegralImageBuilder() {
	// TODO Auto-generated destructor stub
}

void IntegralImageBuilder::buildForImage(unsigned char** inputBuffer, unsigned long long int** outputBuffer, int rows, int cols){
	int sum = 0;
	for (int j = 0; j < cols; ++j) {
		sum += inputBuffer[0][j];
		outputBuffer[0][j] =  sum;
	}

	for (int i = 1; i < rows; ++i) {
		sum = 0;
		for (int j = 0; j < cols; ++j) {
			sum += inputBuffer[i][j];
			outputBuffer[i][j] =  sum + outputBuffer[i-1][j];
		}
	}
}

void IntegralImageBuilder::buildForImageWithSquares(unsigned char** inputBuffer,
		unsigned long long int** outputBuffer,
		unsigned long long int** outputSquareBuffer, int rows, int cols){
	int sum = 0;
	int sumSquare = 0;
	for (int j = 0; j < cols; ++j) {
		sum += inputBuffer[0][j];
		outputBuffer[0][j] =  sum;

		sumSquare += inputBuffer[0][j]*inputBuffer[0][j];
		outputSquareBuffer[0][j] =  sumSquare;
	}

	for (int i = 1; i < rows; ++i) {
		sum = 0;
		sumSquare = 0;
		for (int j = 0; j < cols; ++j) {
			sum += inputBuffer[i][j];
			outputBuffer[i][j] =  sum + outputBuffer[i-1][j];

			sumSquare += inputBuffer[i][j]*inputBuffer[i][j];
			outputSquareBuffer[i][j] =  sumSquare + outputSquareBuffer[i-1][j];
		}
	}
}



double IntegralImageBuilder::mean(unsigned long long int** integral, int i, int j, int k){
	//uwaga! nie uzględniono wartości brzegowych.
	unsigned long long int a = integral[i-k-1][j-k-1];
	unsigned long long int b = integral[i-k-1][j+k];
	unsigned long long int d = integral[i+k][j-k-1];
	unsigned long long int c = integral[i+k][j+k];
	unsigned long long int n = (2*k+1)*(2*k+1);
	return (c+a-b-d)*1.0/n;
}

