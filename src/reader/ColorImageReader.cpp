/*
 * ColorImageReader.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: mj
 */

#include "ColorImageReader.h"

ColorImageReader::ColorImageReader() {
	// TODO Auto-generated constructor stub

}

ColorImageReader::~ColorImageReader() {
	// TODO Auto-generated destructor stub
}


int ColorImageReader::readHeader(char *fname, int *rows, int *cols, int *max_color){

	FILE *fp;
	size_t flen, hlen;
	char signature[3];

	if((fp=fopen(fname, "rb")) == NULL)
		return 0;

	fseek(fp, 0, SEEK_END);
    flen = ftell(fp);	//file lenght
	fseek(fp, 0, SEEK_SET);

	fgets(signature, sizeof(signature), fp);
	if (signature[0] != 'P' || signature[1] != '6')
		{ fclose(fp); return 0; }	//probably not pgm binary file...

	ImageReader::skipComments(fp);
	fscanf(fp, "%d", cols);
	ImageReader::skipComments(fp);
	fscanf(fp, "%d", rows);
	ImageReader::skipComments(fp);
	fscanf(fp, "%d", max_color);
	fgetc(fp);

	hlen = ftell(fp); //header lenght
	fclose(fp);
	if ( (*rows) * 3*(*cols) != (flen-hlen) )	//we assume only one picture in the file
		return 0;

	return hlen;
}

int ColorImageReader::readData(unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, char *fname, int hlen, int rows, int cols, int max_color){
	long i, wxh;
	FILE *fp;

	if (max_color>255) return 0;	//for now only 1 byte color values

	if((fp=fopen(fname, "rb")) == NULL)
		return 0;

	fseek(fp, hlen, SEEK_SET);

	wxh = rows*cols;
	for(i=0;i<wxh;i++){
		imageR[i] = (unsigned char)fgetc(fp);
		imageG[i] = (unsigned char)fgetc(fp);
		imageB[i] = (unsigned char)fgetc(fp);
	}

	fclose(fp);

	return 1;
}

int ColorImageReader::writeImage(char *fname, unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, int rows,  int cols, int max_color){
	long i, wxh;
	FILE *fp;

	if((fp = fopen(fname, "wb")) == NULL)
		return(0);

	fprintf(fp, "P6\n%d %d\n# eyetom.com\n%d\n", cols, rows, max_color);

	wxh = rows*cols;
	for(i=0;i<wxh;i++){      /* Write the image in pixel interleaved format. */
		fputc(imageR[i], fp);
		fputc(imageG[i], fp);
		fputc(imageB[i], fp);
	}

	fclose(fp);
	return(1);
}
