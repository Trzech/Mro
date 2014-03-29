/*
 * ImageReader.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: mj
 */

#include "ImageReader.h"

ImageReader::ImageReader() {
	// TODO Auto-generated constructor stub

}

ImageReader::~ImageReader() {
	// TODO Auto-generated destructor stub
}

void ImageReader::skipComments(FILE *fp){
	int ch;
	char line[256];

	while ((ch = fgetc(fp)) != EOF && isspace(ch))
		;
	if (ch == '#') {
		fgets(line, sizeof(line), fp);
		skipComments(fp);
	} else
		fseek(fp, -1, SEEK_CUR);
}

