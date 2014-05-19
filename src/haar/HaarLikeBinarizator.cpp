/*
 * HaarLikeFeatures.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "HaarLikeBinarizator.h"

HaarLikeBinarizator::HaarLikeBinarizator(unsigned char* inputBuffer, int rows,
		int cols) :
		Binarizator(inputBuffer, rows, cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			thresholdArray[i][j] = 0;
		}
	}

}

HaarLikeBinarizator::~HaarLikeBinarizator() {
// TODO Auto-generated destructor stub
}

unsigned char* HaarLikeBinarizator::getResult() {
	unsigned char * returnBuffer = allocMemory<unsigned char>(rows, cols);

	memcpy(returnBuffer, thresholdBuffer, rows * cols);

	return returnBuffer;
}

void HaarLikeBinarizator::applyVertical2Filter(int rowK, int colK, double t) {

	IntegralImageBuilder::buildForImage(inputArray, integralArray, rows, cols);
	for (int i = 0 + rowK + 1; i < rows - rowK; ++i) {
		for (int j = 0 + colK + 1; j < cols - colK; ++j) {
			int black = IntegralImageBuilder::sumInArea(integralArray, i - rowK,
					j - colK, i + rowK, j);
			int white = IntegralImageBuilder::sumInArea(integralArray, i - rowK,
					j, i + rowK, j + colK);

			if ((1.0*(black))/white > t) {
				thresholdArray[i][j] = 255;
			}

		}
	}

}

void HaarLikeBinarizator::applyHorizontal2Filter(int rowK, int colK, double t) {

	IntegralImageBuilder::buildForImage(inputArray, integralArray, rows, cols);
	for (int i = 0 + rowK + 1; i < rows - rowK; ++i) {
		for (int j = 0 + colK + 1; j < cols - colK; ++j) {
			int black = IntegralImageBuilder::sumInArea(integralArray, i - rowK,
					j - colK, i, j + colK);
			int white = IntegralImageBuilder::sumInArea(integralArray, i,
					j - colK, i + rowK, j + colK);

			if ((1.0*(black))/white > t) {
				thresholdArray[i][j] = 255;
			}

		}
	}

}

void HaarLikeBinarizator::applyCrossFilter(int rowK, int colK, double t) {
	IntegralImageBuilder::buildForImage(inputArray, integralArray, rows, cols);
	for (int i = 0 + rowK + 1; i < rows - rowK; ++i) {
		for (int j = 0 + colK + 1; j < cols - colK; ++j) {
			int black = IntegralImageBuilder::sumInArea(integralArray, i - rowK,
					j - colK, i, j + colK);
			//TODO przepisać prawidłowe zakresy z zeszytu
			black += IntegralImageBuilder::sumInArea(integralArray, i - rowK,
								j - colK, i, j + colK);
			black += IntegralImageBuilder::sumInArea(integralArray, i - rowK,
								j - colK, i, j + colK);
			int white = IntegralImageBuilder::sumInArea(integralArray, i,
					j - colK, i + rowK, j + colK);
			white += IntegralImageBuilder::sumInArea(integralArray, i,
								j - colK, i + rowK, j + colK);
			white += IntegralImageBuilder::sumInArea(integralArray, i,
								j - colK, i + rowK, j + colK);
			white += IntegralImageBuilder::sumInArea(integralArray, i,
								j - colK, i + rowK, j + colK);

			if ((1.0*(black))/white > t) {
				thresholdArray[i][j] = 255;
			}

		}
	}
}
