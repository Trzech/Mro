/*
 * ImageBinarizator.cpp
 *
 *  Created on: 22 mar 2014
 *      Author: mj
 */

#include "NiblackBinarizator.h"
#include <math.h>

const double R = 128.0;

void NiblackBinarizator::binarize(unsigned char* inputBuffer,
		unsigned char* outputBuffer, int rows, int cols) {
	int defaultSurroundings = 10;
	double defaultKFactor = 0.2;
	binarize(inputBuffer, outputBuffer, rows, cols, defaultSurroundings,
			defaultKFactor);
}

void NiblackBinarizator::binarizeInnerPart(unsigned char** source,
		unsigned char** target, int rows, int cols, int surroundings,
		double k_factor) {
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
			int n = (2 * surroundings) * (2 * surroundings);
			double m = suma * 1.0 / n;
			double s = sqrt(sumaKwadratow / n - m * m);
			int threshold = m * (1.0 + k_factor * (s / R - 1.0));
			if (source[i][j] > threshold) {
				target[i][j] = 255;
			} else {
				target[i][j] = 0;
			}
		}
	}
}

int NiblackBinarizator::controlled(int x, int xMax){
	if (x < 0) {
		return -x;
	} else {
		if (x > xMax ) {
			return xMax-(x%xMax);
		} else {
			return x;
		}
	}
}

void NiblackBinarizator::binarizeWithMirroring(unsigned char** source,
		unsigned char** target, int iMin, int iMax, int jMin, int jMax,
		int surroundings, double k_factor) {
	for (int i = iMin; i < iMax; ++i) {
		for (int j = jMin; j < jMax; ++j) {
			int suma = 0;
			int sumaKwadratow = 0;
			for (int k = i - surroundings; k < i + surroundings; ++k) {
				for (int l = j - surroundings; l < j + surroundings; ++l) {
					int r = controlled(k, iMax-1);
					int c = controlled(l, jMax-1);
					suma += source[r][c];
					sumaKwadratow += source[r][c] * source[r][c];
				}
			}
			int n = (2 * surroundings) * (2 * surroundings);
			double m = suma * 1.0 / n;
			double s = sqrt(sumaKwadratow / n - m * m);
			int threshold = m * (1.0 + k_factor * (s / R - 1.0));
			if (source[i][j] > threshold) {
				target[i][j] = 255;
			} else {
				target[i][j] = 0;
			}
		}
	}
}

void NiblackBinarizator::binarizeBorderPart(unsigned char** source,
		unsigned char** target, int rows, int cols, int surroundings,
		double k_factor) {
	//top
	binarizeWithMirroring(source, target, 0, surroundings,0, cols,
			surroundings, k_factor);
	//left
	binarizeWithMirroring(source, target,  surroundings,
			rows - surroundings, 0, surroundings,surroundings, k_factor);
	//right

	binarizeWithMirroring(source, target,
			surroundings, rows - surroundings, cols - surroundings, cols,surroundings, k_factor);
	//bottom
	binarizeWithMirroring(source, target, rows - surroundings, rows, 0, cols,
			surroundings, k_factor);
}



void NiblackBinarizator::binarize(unsigned char* inputBuffer,
		unsigned char* outputBuffer, int rows, int cols, int surroundings,
		double k_factor) {
	unsigned char** source = Binarizator::prepareTableForOperations(inputBuffer, rows, cols);
	unsigned char** target = Binarizator::prepareTableForOperations(outputBuffer, rows,
			cols);

	binarizeInnerPart(source, target, rows, cols, surroundings, k_factor);
	binarizeBorderPart(source, target, rows, cols, surroundings, k_factor);

	delete[] source;
	delete[] target;
}

NiblackBinarizator::NiblackBinarizator() {
	// TODO Auto-generated constructor stub

}

NiblackBinarizator::~NiblackBinarizator() {
	// TODO Auto-generated destructor stub
}

