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

void IntegralImageBuilder::buildForImage(unsigned char** inputBuffer, unsigned char** outputBuffer, int rows, int cols){
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

double IntegralImageBuilder::mean(unsigned char** integral, int i, int j, int k){
	int a = integral[i-k][j-k];
	int b = integral[i-k][j+k];
	int c = integral[i+k][j-k];
	int d = integral[i+k][j+k];
	int n = (2*k+1)*(2*k+1);
	return (c+a-b-d)*1.0/n;
}

