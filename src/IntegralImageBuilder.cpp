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

void IntegralImageBuilder::buildForImage(unsigned char** inputArray, unsigned long long int** outputArray, int rows, int cols){
	int sum = 0;
	for (int j = 0; j < cols; ++j) {
		sum += inputArray[0][j];
		outputArray[0][j] =  sum;
	}

	for (int i = 1; i < rows; ++i) {
		sum = 0;
		for (int j = 0; j < cols; ++j) {
			sum += inputArray[i][j];
			outputArray[i][j] =  sum + outputArray[i-1][j];
		}
	}
}



void IntegralImageBuilder::buildForImageWithSquares(unsigned char** inputArray,
		unsigned long long int** outputArray,
		unsigned long long int** outputSquareArray, int rows, int cols){
	int sum = 0;
	int sumSquare = 0;
	for (int j = 0; j < cols; ++j) {
		sum += inputArray[0][j];
		outputArray[0][j] =  sum;

		sumSquare += inputArray[0][j]*inputArray[0][j];
		outputSquareArray[0][j] =  sumSquare;
	}

	for (int i = 1; i < rows; ++i) {
		sum = 0;
		sumSquare = 0;
		for (int j = 0; j < cols; ++j) {
			sum += inputArray[i][j];
			outputArray[i][j] =  sum + outputArray[i-1][j];

			sumSquare += inputArray[i][j]*inputArray[i][j];
			outputSquareArray[i][j] =  sumSquare + outputSquareArray[i-1][j];
		}
	}
}





int IntegralImageBuilder::sumInArea(unsigned long long int** I, int i, int j, int k){
	//uwaga! nie uzględniono wartości brzegowych.
	return (I[i + k][j + k] + I[i - k - 1][j - k - 1]
						- I[i - k - 1][j + k] - I[i + k][j - k - 1]);
}



