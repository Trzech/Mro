/*
 * GrayscaleImageReader.h
 *
 *  Created on: Mar 29, 2014
 *      Author: mj
 */

#ifndef GRAYSCALEIMAGEREADER_H_
#define GRAYSCALEIMAGEREADER_H_
#include "ImageReader.h"

class GrayscaleImageReader: protected ImageReader {
public:
	GrayscaleImageReader();
	virtual ~GrayscaleImageReader();
	unsigned char* readDataFromFile(char *fname, int* rows, int* cols);
	void writeImage(char *fname, unsigned char *image, unsigned int rows,
			unsigned int cols, unsigned int max_color = 255);
private:
	int readHeader(char *fname, int *rows, int *cols, int *max_color);
	void readData(unsigned char *image, char *fname, int hlen, int rows,
			int cols, int max_color);
};

#endif /* GRAYSCALEIMAGEREADER_H_ */
