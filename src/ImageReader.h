/*
 * ImageReader.h
 *
 *  Created on: Mar 29, 2014
 *      Author: mj
 */

#ifndef IMAGEREADER_H_
#define IMAGEREADER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <exception>

class ImageReader {
public:
	ImageReader();
	virtual ~ImageReader();
	virtual int readHeader(char *fname, int *rows, int *cols, int *max_color) = 0;
protected:
	void skipComments(FILE *fp);
};

#endif /* IMAGEREADER_H_ */
