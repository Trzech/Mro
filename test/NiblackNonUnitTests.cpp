#include "IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "NiblackBinarizator.h"
#include "GrayscaleImageReader.h"
#include "Timer.h"

class NiblackNonUnitTests: public ::testing::Test {
public:
	static const int surrounding = 10;
	static const double k_factor = 0.2;
};


TEST_F(NiblackNonUnitTests, lenaNiblackBinarizatorWithoutIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/lena_grayscale.pgm";
	char outputFileName[] = "images/lena_NiblackBinarizatorWithoutIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	NiblackBinarizator binarizator;

	timer.begin();
	outBuf = binarizator.binarizeWithoutIntegral(inBuf, rows, cols, NiblackNonUnitTests::surrounding,
			NiblackNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);

}
TEST_F(NiblackNonUnitTests, lenaNiblackBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/lena_grayscale.pgm";
	char outputFileName[] = "images/lena_NiblackBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	NiblackBinarizator binarizator;

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(inBuf, rows, cols, NiblackNonUnitTests::surrounding,
			NiblackNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);
}
TEST_F(NiblackNonUnitTests, DISABLED_bookNiblackBinarizatorWithoutIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/book.pgm";
	char outputFileName[] = "images/book_NiblackBinarizatorWithoutIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	NiblackBinarizator binarizator;

	timer.begin();
	outBuf = binarizator.binarizeWithoutIntegral(inBuf, rows, cols, NiblackNonUnitTests::surrounding,
			NiblackNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);

}

TEST_F(NiblackNonUnitTests, bookNiblackBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/book.pgm";
	char outputFileName[] = "images/book_NiblackBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	NiblackBinarizator binarizator;

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(inBuf, rows, cols, NiblackNonUnitTests::surrounding,
			NiblackNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);

}

