#include "IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "NiblackBinarizator.h"
#include "GrayscaleImageReader.h"
#include "Timer.h"

class NiblackNonUnitTests: public ::testing::Test {
public:
	int surrounding = 10;
	double k_factor = 0.2;
};


TEST_F(NiblackNonUnitTests, lenaNiblackBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/lena_grayscale.pgm";
	char outputFileName[] = "images/lena_NiblackBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	NiblackBinarizator binarizator(inBuf, rows, cols);

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(NiblackNonUnitTests::surrounding,
			NiblackNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);
}


TEST_F(NiblackNonUnitTests, DISABLED_bookNiblackBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/book.pgm";
	char outputFileName[] = "images/book_NiblackBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	NiblackBinarizator binarizator(inBuf, rows, cols);

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(NiblackNonUnitTests::surrounding,
			NiblackNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);

}





