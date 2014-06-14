#include "sudoku/SudokuReader.h"
#include "gtest/gtest.h"



class SudokuReaderTest: public ::testing::Test {

};

TEST_F(SudokuReaderTest, justTests) {
	char inputFileName[] = "test/sudoku/images/source/93987_4.pgm";
	char txtFileName[] = "test/sudoku/images/source/93987_4.txt";
	SudokuReader sudokuReader;
	double * numbers = sudokuReader.getNumberRepresetation(inputFileName);


	FILE * fp = fopen(txtFileName, "rb");
	char a;
	bool numbersExpectedResult[9][9];
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			fscanf(fp, "%c", &a);
			if (a == '0') {
				numbersExpectedResult[i][j] = false;
			} else {
				numbersExpectedResult[i][j] = true;
			}
		}
		fscanf(fp, "%c", &a);
	}
	fclose(fp);

	//then

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			ASSERT_EQ( numbersExpectedResult[i][j], numbers[i*9+j] );
		}
	}


	delete [] numbers;

}

