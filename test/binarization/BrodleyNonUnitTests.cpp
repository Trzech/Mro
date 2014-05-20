
#include "gtest/gtest.h"
#include "binarization/BrodleyBinarizator.h"
#include "reader/GrayscaleImageReader.h"
#include "utils/Timer.h"
#include "binarization/IntegralImageBuilder.h"



class BrodleyNonUnitTests: public ::testing::Test {
public:
	BrodleyNonUnitTests(){
		surrounding = 10;
	brodleyParameter = 0.9;

	}
	int surrounding;
	double brodleyParameter;
};

TEST_F(BrodleyNonUnitTests, lenaBrodleyBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "test/binarization/images/source/lena_grayscale.pgm";
	char outputFileName[] = "test/binarization/images/result/lena_BrodleyBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	BrodleyBinarizator binarizator(inBuf, rows, cols);

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(surrounding, brodleyParameter);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 500);
}



TEST_F(BrodleyNonUnitTests,  DISABLED_bookBrodleyBinarizatorWithIntegral) {
	Timer timer;
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "test/binarization/images/source/book.pgm";
	char outputFileName[] = "test/binarization/images/result/book_BrodleyBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	BrodleyBinarizator binarizator(inBuf, rows, cols);

	timer.begin();
	outBuf = binarizator.binarizeWithIntegral(surrounding, brodleyParameter);
	double time = timer.end();
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;

	ASSERT_LT(time, 500);

}