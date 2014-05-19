/*
 * IntegralImageBuilderTest.cpp
 *
 *  Created on: 24 mar 2014
 *      Author: mj
 */

#include "binarization/IntegralImageBuilder.h"

#include "gtest/gtest.h"
#include "binarization/Binarizator.h"

class IntegralImageBuilderTest: public ::testing::Test {

};

TEST_F(IntegralImageBuilderTest, exampleFromBook) {
	//given
	int rows = 3;
	int cols = 3;
	unsigned char inputBuffer[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	unsigned long long int* integralBuffer;
	if ((integralBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned char** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);
	unsigned long long int** integral = Binarizator::prepareTableForOperations(
			integralBuffer, rows, cols);

	//when
	IntegralImageBuilder integralImageBuilder;
	integralImageBuilder.buildForImage(source, integral, rows, cols);

	//then
	ASSERT_EQ(1, integral[0][0]);
	ASSERT_EQ(3, integral[0][1]);
	ASSERT_EQ(6, integral[0][2]);
	ASSERT_EQ(5, integral[1][0]);
	ASSERT_EQ(12, integral[1][1]);
	ASSERT_EQ(21, integral[1][2]);
	ASSERT_EQ(12, integral[2][0]);
	ASSERT_EQ(27, integral[2][1]);
	ASSERT_EQ(45, integral[2][2]);

	delete[] source;
	delete[] integral;
	delete integralBuffer;

}

TEST_F(IntegralImageBuilderTest, meanExampleFromBook) {
	//given
	int rows = 5;
	int cols = 5;

	unsigned long long int inputBuffer[] = { 0, 0, 0, 0, 0, 0, 1, 3, 6, 0, 0, 5, 12, 21,
			0, 0, 12, 27, 45, 0, 0, 0, 0, 0, 0 };
	unsigned long long int** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);

	//when
	IntegralImageBuilder integralImageBuilder;
	double mean = (integralImageBuilder.sumInArea(source, 2, 2, 1)*1.0)/9;

	//then
	ASSERT_EQ(5, mean);

	delete[] source;
}

TEST_F(IntegralImageBuilderTest, meanOfOne) {
	//given
	int rows = 5;
	int cols = 5;
	unsigned char inputBuffer[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	unsigned long long int* integralBuffer;
	if ((integralBuffer = new unsigned long long int[rows * cols]) == NULL) {
		throw -1;
	}
	unsigned char** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);
	unsigned long long int** integral = Binarizator::prepareTableForOperations(
			integralBuffer, rows, cols);

	//when
	IntegralImageBuilder integralImageBuilder;
	integralImageBuilder.buildForImage(source, integral, rows, cols);
	double mean = (integralImageBuilder.sumInArea(integral, 2, 2, 1)*1.0)/9;

	//then
	ASSERT_EQ(1, mean);

	delete[] source;
	delete[] integral;
	delete integralBuffer;

}
TEST_F(IntegralImageBuilderTest, meanExampleFromBookUsingCoordinates) {
	//given
	int rows = 5;
	int cols = 5;

	unsigned long long int inputBuffer[] = { 0, 0, 0, 0, 0, 0, 1, 3, 6, 0, 0, 5, 12, 21,
			0, 0, 12, 27, 45, 0, 0, 0, 0, 0, 0 };
	unsigned long long int** source = Binarizator::prepareTableForOperations(inputBuffer,
			rows, cols);

	//when
	IntegralImageBuilder integralImageBuilder;
	double mean = (integralImageBuilder.sumInArea(source, 1,1,3,3)*1.0)/9;

	//then
	ASSERT_EQ(5, mean);

	delete[] source;
}
