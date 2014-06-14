#include "binarization/IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "binarization/SauvolaBinarizator.h"
#include "reader/GrayscaleImageReader.h"

class SauvolaBinarizatorRunner: public ::testing::Test {
public:
	int surrounding = 10;
	double k_factor = 0.2;
};


TEST_F(SauvolaBinarizatorRunner, lenaSauvolaBinarizatorWithIntegral) {
	int rows, cols;
	GrayscaleImageReader reader;
	char inputFileName[] = "test/binarization/images/source/lena_grayscale.pgm";
	char outputFileName[] = "test/binarization/images/result/lena_SauvolaBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;
	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);
	SauvolaBinarizator binarizator(inBuf, rows, cols);
	outBuf = binarizator.binarizeWithIntegral(SauvolaBinarizatorRunner::surrounding,
			SauvolaBinarizatorRunner::k_factor);
	reader.writeImage(outputFileName, outBuf, rows, cols);
	delete[] inBuf;
	delete[] outBuf;

}


TEST_F(SauvolaBinarizatorRunner, DISABLED_bookSauvolaBinarizatorWithIntegral) {
	int rows, cols;
	GrayscaleImageReader reader;

	char inputFileName[] = "test/binarization/images/source/book.pgm";
	char outputFileName[] = "test/binarization/images/result/book_SauvolaBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);
	SauvolaBinarizator binarizator(inBuf, rows, cols);
	outBuf = binarizator.binarizeWithIntegral(SauvolaBinarizatorRunner::surrounding,
			SauvolaBinarizatorRunner::k_factor);
	reader.writeImage(outputFileName, outBuf, rows, cols);
	delete[] inBuf;
	delete[] outBuf;

}





