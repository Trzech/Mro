#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Ttiming.h"
#include "TPGM.h"
#include "BrodleyBinarizator.h"

TTiming tt;


int main(int argc, char **argv) {
	int rows, cols;
	int max_color;
	int hpos;



	tt.Begin();		//start to measure the time

	char incolorfname[] = "images/lena_grayscale.pgm";
	char outputFile[] = "images/lena_binaryzacja.pgm";

	if ((hpos = readPGMB_header(incolorfname, &rows, &cols, &max_color)) <= 0)
		exit(1);
	unsigned char *inBuf;
	if ((inBuf = new unsigned char[rows * cols]) == NULL)
		exit(1);
	unsigned char *outBuf;
	if ((outBuf = new unsigned char[rows * cols]) == NULL)
		exit(1);
	if (readPGMB_data(inBuf, incolorfname, hpos, rows, cols, max_color) == 0)
		exit(1);

	BrodleyBinarizator binarizator;
	//writting

	binarizator.binarizeWithIntegral(inBuf, outBuf, rows, cols, 15, 0.8);
	char outfname[256];
	sprintf(outfname, outputFile, incolorfname);
	if (writePGMB_image(outfname, outBuf, rows, cols, 255) == 0)
		exit(1);


	delete inBuf;
	delete outBuf;

	tt.End();	//stop and read elapsed time in ms (miliseconds)

	return 0;
}

