/*
 * GrayscaleImageReader.h
 *
 *  Created on: Mar 29, 2014
 *      Author: mj
 */

#ifndef GRAYSCALEIMAGEREADER_H_
#define GRAYSCALEIMAGEREADER_H_
#include "ImageReader.h"

class GrayscaleImageReader : protected ImageReader {
public:
	GrayscaleImageReader();
	virtual ~GrayscaleImageReader();
	int readHeader(char *fname, int *rows, int *cols, int *max_color);
	int readData(unsigned char *image, char *fname, int hlen, int rows, int cols, int max_color);
	int writeImage(char *fname, unsigned char *image, int rows,  int cols, int max_color);
};

#endif /* GRAYSCALEIMAGEREADER_H_ */
