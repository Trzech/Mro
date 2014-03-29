#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Timer.h"
#include "BrodleyBinarizator.h"
#include "GrayscaleImageReader.h"
Timer timer;


int main(int argc, char **argv) {
	int rows, cols;
	int max_color;
	int hpos;

	GrayscaleImageReader reader;


	timer.begin();		//start to measure the time

	char incolorfname[] = "images/lena_grayscale.pgm";
	char outputFile[] = "images/lena_binaryzacja.pgm";

	if ((hpos = reader.readHeader(incolorfname, &rows, &cols, &max_color)) <= 0)
		exit(1);
	unsigned char *inBuf;
	if ((inBuf = new unsigned char[rows * cols]) == NULL)
		exit(1);
	unsigned char *outBuf;
	if ((outBuf = new unsigned char[rows * cols]) == NULL)
		exit(1);
	if (reader.readData(inBuf, incolorfname, hpos, rows, cols, max_color) == 0)
		exit(1);

	BrodleyBinarizator binarizator;
	//writting

	binarizator.binarizeWithIntegral(inBuf, outBuf, rows, cols, 15, 0.8);
	char outfname[256];
	sprintf(outfname, outputFile, incolorfname);
	if (reader.writeImage(outfname, outBuf, rows, cols, 255) == 0)
		exit(1);


	delete inBuf;
	delete outBuf;

	timer.end();	//stop and read elapsed time in ms (miliseconds)

	return 0;
}

