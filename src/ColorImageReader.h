/*
 * ColorImageReader.h
 *
 *  Created on: Mar 29, 2014
 *      Author: mj
 */

#ifndef COLORIMAGEREADER_H_
#define COLORIMAGEREADER_H_
#include "ImageReader.h"

class ColorImageReader : protected ImageReader {
public:
	ColorImageReader();
	virtual ~ColorImageReader();
	int readHeader(char *fname, int *rows, int *cols, int *max_color);
	int readData(unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, char *fname, int hlen, int rows, int cols, int max_color);
	int writeImage(char *fname, unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, int rows,  int cols, int max_color);
};

#endif /* COLORIMAGEREADER_H_ */
