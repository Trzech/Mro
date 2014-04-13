/*
 * HaarLikeFeatures.h
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#ifndef HaarLikeBinarizator_H_
#define HaarLikeBinarizator_H_
#include <stdlib.h>
#include "Binarizator.h"

class HaarLikeBinarizator {
public:
	HaarLikeBinarizator();
	~HaarLikeBinarizator();
	unsigned char * binarizeVertical2(unsigned char* inputBuffer, int rows,
				int cols, int surroundings, double t = 0.95);
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
