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
	static void buildForImage(unsigned char** inputArray,
			unsigned long long int** outputArray, int rows, int cols);
	static void buildForImageWithSquares(unsigned char** inputArray,
			unsigned long long int** outputArray,
			unsigned long long int** outputSquareArray, int rows, int cols);
	static int sumInArea(unsigned long long int** integral, int rowOfpixel, int colOfPixel, int surrounding);

};

#endif /* INTEGRALIMAGEBUILDER_H_ */
