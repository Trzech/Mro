#include "IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "BrodleyBinarizator.h"
#include "GrayscaleImageReader.h"
#include "Timer.h"

int surrounding = 15;
double brodleyParameter = 0.9;

class NonUnitTests: public ::testing::Test {

};

TEST_F(NonUnitTests, lenaBrodleyBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "images/lena_grayscale.pgm";
	char outputFileName[] = "images/lena_BrodleyBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	BrodleyBinarizator binarizator;

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(inBuf, rows, cols, surrounding, brodleyParameter);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 500);
}

TEST_F(NonUnitTests, lenaBrodleyBinarizatorWithoutIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "images/lena_grayscale.pgm";
	char outputFileName[] = "images/lena_BrodleyBinarizatorWithoutIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	BrodleyBinarizator binarizator;

	timer.begin();
	outBuf = binarizator.binarizeWithoutIntegral(inBuf, rows, cols, surrounding, brodleyParameter);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 500);

}
