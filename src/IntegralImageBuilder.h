/*
 * IntegralImageBuilder.h
 *
 *  Created on: 24 mar 2014
 *      Author: mj
 */

#ifndef INTEGRALIMAGEBUILDER_H_
#define INTEGRALIMAGEBUILDER_H_

class IntegralImageBuilder {
public:
	IntegralImageBuilder();
	virtual ~IntegralImageBuilder();
	void buildForImage(unsigned char** inputBuffer,
			unsigned char** outputBuffer, int rows, int cols);
	double mean(unsigned char** integral, int i, int j, int k);
};

#endif /* INTEGRALIMAGEBUILDER_H_ */
