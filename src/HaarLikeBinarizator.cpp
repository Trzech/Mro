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
	for (int i = 0 ; i < rows ; ++i) {
		for (int j = 0; j < cols ; ++j) {
			thresholdArray[i][j] = 0;
		}
	}

}

HaarLikeBinarizator::~HaarLikeBinarizator() {
// TODO Auto-generated destructor stub
}

unsigned char* HaarLikeBinarizator::getResult() {
	unsigned char * returnBuffer = allocMemory<unsigned char>(rows, cols);

	memcpy(returnBuffer, thresholdBuffer, rows*cols);

	return returnBuffer;
}

void HaarLikeBinarizator::applyVertical2Filter(int k, int t) {

	IntegralImageBuilder::buildForImage(inputArray, integralArray, rows, cols);
	for (int i = 0 + k + 1; i < rows - k; ++i) {
		for (int j = 0 + k + 1; j < cols - k; ++j) {
			int black = IntegralImageBuilder::sumInArea(integralArray, i - k,
					j - k, i + k, j);
			int white = IntegralImageBuilder::sumInArea(integralArray, i - k, j,
					i + k, j + k);

			if (abs(black - white) > t) {
				thresholdArray[i][j] = 255;
			}

		}
	}

}

void HaarLikeBinarizator::applyHorizontal2Filter(int k, int t) {

	IntegralImageBuilder::buildForImage(inputArray, integralArray, rows, cols);
		for (int i = 0 + k + 1; i < rows - k; ++i) {
			for (int j = 0 + k + 1; j < cols - k; ++j) {
				int black = IntegralImageBuilder::sumInArea(integralArray, i - k,
						j - k, i, j+k);
				int white = IntegralImageBuilder::sumInArea(integralArray, i, j -k ,
						i + k, j + k);

				if (abs(black - white) > t) {
					thresholdArray[i][j] = 255;
				}

			}
		}

}
