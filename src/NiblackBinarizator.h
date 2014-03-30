/*
 * ImageBinarizator.h
 *
 *  Created on: 22 mar 2014
 *      Author: mj
 */

#ifndef IMAGEBINARIZATOR_H_
#define IMAGEBINARIZATOR_H_
#include "Binarizator.h"

class NiblackBinarizator: protected Binarizator {
public:
	NiblackBinarizator();
	virtual ~NiblackBinarizator();
	unsigned char* binarizeWithoutIntegral(unsigned char* inputBuffer,
			int rows, int cols, int surroundings = 10, double k_factor = 0.2);
	unsigned char* binarizeWithIntegral(unsigned char* inputBuffer,
			int rows, int cols, int surroundings = 10, double k_factor = 0.2);

private:
	void binarizeInnerPart(unsigned char** source, unsigned char** target,
			int rows, int cols, int surroundings, double k_factor);
	void binarizeBorderPart(unsigned char** source, unsigned char** target,
			int rows, int cols, int surroundings, double k_factor);
	unsigned char** prepareTableForOperations(unsigned char* inputBuffer,
			int rows, int cols);
	void binarizeWithMirroring(unsigned char** source, unsigned char** target,
			int xmin, int xmax, int ymin, int ymax, int surroundings,
			double k_factor);
	int controlled(int x, int xMax);
};

#endif /* IMAGEBINARIZATOR_H_ */
