#include "binarization/IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "binarization/SauvolaBinarizator.h"
#include "reader/GrayscaleImageReader.h"
#include "utils/Timer.h"

class SauvolaNonUnitTests: public ::testing::Test {
public:
	int surrounding = 10;
	double k_factor = 0.2;
};


TEST_F(SauvolaNonUnitTests, lenaSauvolaBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;

	char inputFileName[] = "test/binarization/images/source/lena_grayscale.pgm";
	char outputFileName[] = "test/binarization/images/result/lena_SauvolaBinarizatorWithIntegral.pgm";
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

	char inputFileName[] = "test/binarization/images/source/book.pgm";
	char outputFileName[] = "test/binarization/images/result/book_SauvolaBinarizatorWithIntegral.pgm";
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





