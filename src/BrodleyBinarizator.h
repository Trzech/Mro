/*
 * IntegralBrodleyBinarizator.h
 *
 *  Created on: 24 mar 2014
 *      Author: mj
 */

#ifndef INTEGRALBRODLEYBINARIZATOR_H_
#define INTEGRALBRODLEYBINARIZATOR_H_
#include "Binarizator.h"

class BrodleyBinarizator: protected Binarizator {
private:
	unsigned char** prepareTableForOperations(unsigned char* inputBuffer,
			int rows, int cols);
public:
	BrodleyBinarizator();
	virtual ~BrodleyBinarizator();
	void binarizeWithoutIntegral(unsigned char* inputBuffer,
			unsigned char* outputBuffer, int rows, int cols, int surroundings,
			double r = 0.95);
	unsigned char * binarizeWithIntegral(unsigned char* inputBuffer, int rows, int cols,
			int surroundings, double r = 0.95);
};

#endif /* INTEGRALBRODLEYBINARIZATOR_H_ */
