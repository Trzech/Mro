#include "sudoku/SudokuReader.h"
#include "gtest/gtest.h"
#include "dirent.h"
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>

class SudokuReaderTest: public ::testing::Test {

};

bool arraysAreEqual(double * numbersExpectedResult, double * numbers) {
	bool result = true;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			double expected = numbersExpectedResult[i * 9 + j];
			double actual = numbers[i * 9 + j];
			if (expected != actual) {
				result = false;
				printf("Expected %f but was %f\n", expected, actual);
			}
		}
	}
	return result;
}

TEST_F(SudokuReaderTest, recognizesWhereAreTheNumbersCorrectly) {
	DIR *dir;
	struct dirent *ent;
	const char* directoryName = "test/sudoku/images/source/";
	if ((dir = opendir(directoryName)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (strstr(ent->d_name, ".pgm")) {
				char* filenameWithoutExtension = ent->d_name;
				*strrchr(filenameWithoutExtension, '.') = 0; // cuts extension

				char inputFileName[50] = { '\0' };
				char txtFileName[50] = { '\0' };

				strcat(inputFileName, "test/sudoku/images/source/");
				strcat(inputFileName, filenameWithoutExtension);
				strcpy(txtFileName, inputFileName);
				strcat(txtFileName, ".txt");
				strcat(inputFileName, ".pgm");
				printf("%s\n", inputFileName);

				SudokuReader sudokuReader(true);

				FILE * fp = fopen(txtFileName, "rb");
				char a;
				double numbersExpectedResult[9 * 9];
				for (int i = 0; i < 9; ++i) {
					for (int j = 0; j < 9; ++j) {
						fscanf(fp, "%c", &a);
						if (a == '0') {
							numbersExpectedResult[i * 9 + j] = 0.0;
						} else {
							numbersExpectedResult[i * 9 + j] = 1.0;
						}
					}
					fscanf(fp, "%c", &a);
				}
				fclose(fp);

				//when
				double * numbers = sudokuReader.getNumberRepresetation(
						inputFileName);

				//then

				EXPECT_TRUE(arraysAreEqual(numbersExpectedResult, numbers));

				delete[] numbers;
			}
		}
		closedir(dir);
	} else {
		/* could not open directory */
		perror("Error with directory opening");
	}
}

TEST_F(SudokuReaderTest, DISABLED_recognizesNumbersCorrectly) {
	DIR *dir;
	struct dirent *ent;
	const char* directoryName = "test/sudoku/images/source/";
	if ((dir = opendir(directoryName)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (strstr(ent->d_name, ".pgm")) {
				char* filenameWithoutExtension = ent->d_name;
				*strrchr(filenameWithoutExtension, '.') = 0; // cuts extension

				char inputFileName[50] = { '\0' };
				char txtFileName[50] = { '\0' };

				strcat(inputFileName, "test/sudoku/images/source/");
				strcat(inputFileName, filenameWithoutExtension);
				strcpy(txtFileName, inputFileName);
				strcat(txtFileName, ".txt");
				strcat(inputFileName, ".pgm");
				printf("%s\n", inputFileName);
				SudokuReader sudokuReader(true);

				FILE * fp = fopen(txtFileName, "rb");
				char a;
				double numbersExpectedResult[9 * 9];
				for (int i = 0; i < 9; ++i) {
					for (int j = 0; j < 9; ++j) {
						fscanf(fp, "%c", &a);
						numbersExpectedResult[i * 9 + j] = atoi(&a);
					}
					fscanf(fp, "%c", &a);
				}
				fclose(fp);

				//when
				double * numbers = sudokuReader.getNumberRepresetation(
						inputFileName);

				//then

				EXPECT_TRUE(arraysAreEqual(numbersExpectedResult, numbers));

				delete[] numbers;
			}
		}
		closedir(dir);
	} else {
		/* could not open directory */
		perror("Error with directory opening");
	}
}
