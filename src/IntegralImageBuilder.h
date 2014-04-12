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
			unsigned long long int** outputBuffer, int rows, int cols);
	void buildForImageWithSquares(unsigned char** inputBuffer,
			unsigned long long int** outputBuffer,
			unsigned long long int** outputSquareBuffer, int rows, int cols);
	int sumInArea(unsigned long long int** integral, int rowOfpixel, int colOfPixel, int surrounding);

};

#endif /* INTEGRALIMAGEBUILDER_H_ */
