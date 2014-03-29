#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Timer.h"
#include "BrodleyBinarizator.h"
#include "GrayscaleImageReader.h"
Timer timer;

int main(int argc, char **argv) {
	int rows, cols;

	GrayscaleImageReader reader;

	timer.begin();		//start to measure the time

	char inputFileName[] = "images/lena_grayscale.pgm";
	char outputFileName[] = "images/lena_binaryzacja.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	BrodleyBinarizator binarizator;

	outBuf = binarizator.binarizeWithIntegral(inBuf, rows, cols, 15, 0.8);
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	timer.end();	//stop and read elapsed time in ms (miliseconds)

	return 0;
}

