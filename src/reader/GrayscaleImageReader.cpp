/*
 * GrayscaleImageReader.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: mj
 */

#include "GrayscaleImageReader.h"

GrayscaleImageReader::GrayscaleImageReader() {
	// TODO Auto-generated constructor stub

}

GrayscaleImageReader::~GrayscaleImageReader() {
	// TODO Auto-generated destructor stub
}

int GrayscaleImageReader::readHeader(char *fname, int *rows, int *cols,
		int *max_color) {

	FILE *fp;
	size_t flen, hlen;
	char signature[3];

	if ((fp = fopen(fname, "rb")) == NULL)
		return 0;

	fseek(fp, 0, SEEK_END);
	flen = ftell(fp);	//file lenght
	fseek(fp, 0, SEEK_SET);

	fgets(signature, sizeof(signature), fp);
	if (signature[0] != 'P' || signature[1] != '5') {
		fclose(fp);
		return 0;
	}	//probably not pgm binary file...

	ImageReader::skipComments(fp);
	fscanf(fp, "%d", cols);
	ImageReader::skipComments(fp);
	fscanf(fp, "%d", rows);
	ImageReader::skipComments(fp);
	fscanf(fp, "%d", max_color);
	fgetc(fp);

	hlen = ftell(fp); //header lenght
	fclose(fp);
	if ((*rows) * (*cols) != (flen - hlen))	//we assume only one picture in the file
		return 0;

	return hlen;
}

void GrayscaleImageReader::readData(unsigned char *image, char *fname, int hlen,
		int rows, int cols, int max_color) {

	FILE *fp;
	if ((fp = fopen(fname, "rb")) == NULL) {
		throw -1;
	}

	fseek(fp, hlen, SEEK_SET);
	int readedrows = fread(image, cols, rows, fp);
	fclose(fp);

	if (rows != readedrows) {
		throw -1;
	}

}

void GrayscaleImageReader::writeImage(char *fname, unsigned char *image,
		unsigned int rows, unsigned int cols, unsigned int max_color) {
	FILE *fp;

	if ((fp = fopen(fname, "wb")) == NULL) {
		throw -1;
	}

	fprintf(fp, "P5\n%d %d\n# eyetom.com\n%d\n", cols, rows, max_color);

	if (rows != fwrite(image, cols, rows, fp)) {
		fclose(fp);
		throw -1;
	}

	fclose(fp);
}

unsigned char* GrayscaleImageReader::readDataFromFile(char *fileName, int* rows,
		int* cols) {
	int headerPossition;
	int maxColor;

	if ((headerPossition = readHeader(fileName, rows, cols, &maxColor)) <= 0) {
		throw -1;
	}

	unsigned char *result;
	if ((result = new unsigned char[(*rows) * (*cols)]) == NULL) {
		throw -1;
	}

	readData(result, fileName, headerPossition, *rows, *cols, maxColor);
	return result;
}
