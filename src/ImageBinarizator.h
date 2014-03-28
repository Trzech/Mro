/*
 * ImageBinarizator.h
 *
 *  Created on: 22 mar 2014
 *      Author: mj
 */

#ifndef IMAGEBINARIZATOR_H_
#define IMAGEBINARIZATOR_H_

class ImageBinarizator {
public:
	ImageBinarizator();
	virtual ~ImageBinarizator();
	void binarize(unsigned char* inputBuffer, unsigned char* outputBuffer,
			int rows, int cols);
	void binarize(unsigned char* inputBuffer, unsigned char* outputBuffer,
			int rows, int cols, int surroundings, double k_factor);

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
