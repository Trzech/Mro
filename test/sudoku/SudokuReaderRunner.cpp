#include "sudoku/SudokuReader.h"
#include "gtest/gtest.h"



class SudokuReaderRunner: public ::testing::Test {

};

TEST_F(SudokuReaderRunner, justTests) {
	char inputFileName[] = "test/sudoku/images/source/93987_4.pgm";
	char txtFileName[] = "test/sudoku/images/source/93987_4.txt";
	SudokuReader sudokuReader;
	bool * isANumber = sudokuReader.getNumberRepresetation(inputFileName);


	FILE * fp = fopen(txtFileName, "rb");
	char a;
	bool isANumberCorrect[9][9];
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			fscanf(fp, "%c", &a);
			if (a == '0') {
				isANumberCorrect[i][j] = false;
			} else {
				isANumberCorrect[i][j] = true;
			}
		}
		fscanf(fp, "%c", &a);
	}
	fclose(fp);

	//then

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			ASSERT_EQ( isANumberCorrect[i][j], isANumber[i*9+j] );
		}
	}


	delete [] isANumber;

}

