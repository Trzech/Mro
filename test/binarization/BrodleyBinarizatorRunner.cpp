
#include "gtest/gtest.h"
#include "binarization/BrodleyBinarizator.h"
#include "reader/GrayscaleImageReader.h"
#include "binarization/IntegralImageBuilder.h"



class BrodleyBinarizatorRunner: public ::testing::Test {
public:
	BrodleyBinarizatorRunner(){
		surrounding = 10;
	brodleyParameter = 0.9;

	}
	int surrounding;
	double brodleyParameter;
};

TEST_F(BrodleyBinarizatorRunner, lenaBrodleyBinarizatorWithIntegral) {
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "test/binarization/images/source/lena_grayscale.pgm";
	char outputFileName[] = "test/binarization/images/result/lena_BrodleyBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	BrodleyBinarizator binarizator(inBuf, rows, cols);

	outBuf = binarizator.binarizeWithIntegral(surrounding, brodleyParameter);

	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;
}



TEST_F(BrodleyBinarizatorRunner,  DISABLED_bookBrodleyBinarizatorWithIntegral) {
	int rows, cols;

	GrayscaleImageReader reader;


	char inputFileName[] = "test/binarization/images/source/book.pgm";
	char outputFileName[] = "test/binarization/images/result/book_BrodleyBinarizatorWithIntegral.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;

	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	BrodleyBinarizator binarizator(inBuf, rows, cols);

	outBuf = binarizator.binarizeWithIntegral(surrounding, brodleyParameter);
	reader.writeImage(outputFileName, outBuf, rows, cols);

	delete inBuf;
	delete outBuf;


}
