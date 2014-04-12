/*
 * SudokuReaderNonUnitTests.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "SudokuReader.h"
#include "gtest/gtest.h"

class SudokuReaderNonUnitTests: public ::testing::Test {

};


TEST_F(SudokuReaderNonUnitTests, prosteSudoku) {

	SudokuReader reader;
	reader.process("images/sudokuProste.pgm", "images/sudokuProsteWynik.pgm");
	ASSERT_TRUE(1);

}
