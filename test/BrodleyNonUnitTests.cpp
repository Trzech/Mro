#include "IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "BrodleyBinarizator.h"
#include "GrayscaleImageReader.h"
#include "Timer.h"



class BrodleyNonUnitTests: public ::testing::Test {
public:
	BrodleyNonUnitTests(){
		surrounding = 10;
	brodleyParameter = 0.9;

	}
	int surrounding;
	double brodleyParameter;
};

TEST_F(BrodleyNonUnitTests, DISABLED_lenaBrodleyBinarizatorWithIntegral) {
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

TEST_F(BrodleyNonUnitTests, DISABLED_lenaBrodleyBinarizatorWithoutIntegral) {
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

TEST_F(BrodleyNonUnitTests,  bookBrodleyBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "images/book.pgm";
	char outputFileName[] = "images/book_BrodleyBinarizatorWithIntegral.pgm";
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
TEST_F(BrodleyNonUnitTests, DISABLED_bookBrodleyBinarizatorWithoutIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "images/book.pgm";
	char outputFileName[] = "images/book_BrodleyBinarizatorWithoutIntegral.pgm";
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
