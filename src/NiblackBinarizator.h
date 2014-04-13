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
	unsigned char* binarizeWithIntegral(unsigned char* inputBuffer,
			int rows, int cols, int surroundings = 10, double k_factor = 0.2);





};

#endif /* IMAGEBINARIZATOR_H_ */
