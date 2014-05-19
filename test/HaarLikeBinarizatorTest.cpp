/*
 * HaarLikeBinarizatorTest.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "HaarLikeBinarizator.h"
#include "GrayscaleImageReader.h"

#include "gtest/gtest.h"

class HaarLikeBinarizatorTest: public ::testing::Test {

};

TEST_F(HaarLikeBinarizatorTest, prosteSudoku) {
	GrayscaleImageReader imageReader;

	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/sudokuProste.pgm", &rows, &cols);
	HaarLikeBinarizator binarizator(imageBuffer, rows, cols);
	binarizator.applyVertical2Filter(1, 1, 300);
	binarizator.applyHorizontal2Filter(1, 1, 300);
	unsigned char* resultBuffer = binarizator.getResult();

	imageReader.writeImage("images/sudokuProsteWynik.pgm", resultBuffer, rows, cols);
	delete imageBuffer;
	delete resultBuffer;

	ASSERT_TRUE(1);

}
TEST_F(HaarLikeBinarizatorTest, sudokuZdjecie) {
	GrayscaleImageReader imageReader;

	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/sudokuZdjecie.pgm", &rows, &cols);
	HaarLikeBinarizator binarizator(imageBuffer, rows, cols);
	binarizator.applyVertical2Filter(20, 4, 1.25);
	binarizator.applyHorizontal2Filter(4, 20, 1.25);
	unsigned char* resultBuffer = binarizator.getResult();

	imageReader.writeImage("images/sudokuZdjecieWynik.pgm", resultBuffer, rows, cols);
	delete imageBuffer;
	delete resultBuffer;
	ASSERT_TRUE(1);

}
TEST_F(HaarLikeBinarizatorTest, sudokuGazeta) {
	GrayscaleImageReader imageReader;

	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/sudokuGazeta.pgm", &rows, &cols);
	HaarLikeBinarizator binarizator(imageBuffer, rows, cols);
	binarizator.applyVertical2Filter(20, 4, 1.25);
	binarizator.applyHorizontal2Filter(4, 20, 1.25);
	unsigned char* resultBuffer = binarizator.getResult();

	imageReader.writeImage("images/sudokuGazetaWynik.pgm", resultBuffer, rows, cols);
	delete imageBuffer;
	delete resultBuffer;
	ASSERT_TRUE(1);

}

TEST_F(HaarLikeBinarizatorTest, sudokuPole) {
	GrayscaleImageReader imageReader;

	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/sudokuPole.pgm", &rows, &cols);
	HaarLikeBinarizator binarizator(imageBuffer, rows, cols);
	binarizator.applyVertical2Filter(20, 4, 1.25);
	binarizator.applyHorizontal2Filter(4, 20, 1.25);
	unsigned char* resultBuffer = binarizator.getResult();

	imageReader.writeImage("images/sudokuPoleWynik.pgm", resultBuffer, rows, cols);
	delete imageBuffer;
	delete resultBuffer;
	ASSERT_TRUE(1);

}
