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
#include "../binarization/Binarizator.h"

class HaarLikeBinarizator: protected Binarizator {
public:
	HaarLikeBinarizator(unsigned char* inputBuffer, int rows, int cols);
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
	void applyVertical2Filter(int rowsSurroundings, int colsSurroundings,
			double t);

	/**
	 *
	 * ###########
	 * ###########
	 * ###########
	 * ___________
	 * ___________
	 * ___________
	 *
	 */
	void applyHorizontal2Filter(int rowsSurroundings, int colsSurroundings,
			double t);

	/**
	 * ___###___
	 * ___###___
	 * ___###___
	 * #########
	 * #########
	 * #########
	 * ___###___
	 * ___###___
	 * ___###___
	 */
	void applyCrossFilter(int rowsSurroundings, int colsSurroundings,
			double t);

	/*
	 * zrobić jeszcze takie metody
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
