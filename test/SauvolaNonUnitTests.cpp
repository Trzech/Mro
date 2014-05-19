#include "IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "SauvolaBinarizator.h"
#include "GrayscaleImageReader.h"
#include "Timer.h"

class SauvolaNonUnitTests: public ::testing::Test {
public:
	int surrounding = 10;
	double k_factor = 0.2;
};


TEST_F(SauvolaNonUnitTests, lenaSauvolaBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/lena_grayscale.pgm";
	char outputFileName[] = "images/lena_SauvolaBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	SauvolaBinarizator binarizator(inBuf, rows, cols);

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(SauvolaNonUnitTests::surrounding,
			SauvolaNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);
}


TEST_F(SauvolaNonUnitTests, DISABLED_bookSauvolaBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "images/book.pgm";
	char outputFileName[] = "images/book_SauvolaBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	SauvolaBinarizator binarizator(inBuf, rows, cols);

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(SauvolaNonUnitTests::surrounding,
			SauvolaNonUnitTests::k_factor);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 1000);

}





