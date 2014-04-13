/*
 * HaarLikeFeatures.h
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#ifndef HaarLikeBinarizator_H_
#define HaarLikeBinarizator_H_
#include <stdlib.h>
#include <string.h>
#include "Binarizator.h"

class HaarLikeBinarizator: protected Binarizator {
public:
	HaarLikeBinarizator(unsigned char* inputBuffer, int rows,
			int cols);
	~HaarLikeBinarizator();
	unsigned char * getResult();
	/**
	 * Ramka kwadratowa tego typu
	 * ######_____
	 * ######_____
	 * ######_____
	 * ######_____
	 * ######_____
	 *
	 */
	void applyVertical2Filter(int surroundings, int t = 50);
	void applyHorizontal2Filter(int surroundings, int t = 50);
	/*
	 * rozbić takie metody
	 *
	 * ######_____
	 * ######_____
	 * ######_____
	 * ######_____
	 * ######_____
	 *
	 * ###########
	 * ###########
	 * ###########
	 * ___________
	 * ___________
	 * ___________
	 *
	 * __#####__
	 * __#####__
	 * __#####__
	 * __#####__
	 *
	 *
	 * ___________
	 * ___________
	 * ###########
	 * ###########
	 * ___________
	 * ___________
	 */
};

#endif /* HaarLikeBinarizator_H_ */
