#include "sudoku/SudokuReader.h"
#include "gtest/gtest.h"

class SudokuReaderUnitTest: public ::testing::Test {

};

TEST_F(SudokuReaderUnitTest, copiesTileDataCorrectly) {
	//given
	SudokuReader reader;

	unsigned char imageData[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }; // 3x4 image

	int cols = 3;
	Cluster cluster;
	cluster.addPoint(1, 1);
	cluster.addPoint(2, 3);
	//when
	unsigned char * result = reader.geTileData(imageData, cols, cluster);

	//then
	int tileCols = cluster.getWidth();
	ASSERT_DOUBLE_EQ(result[0 * tileCols + 0], 5);
	ASSERT_DOUBLE_EQ(result[0 * tileCols + 1], 6);
	ASSERT_DOUBLE_EQ(result[1 * tileCols + 0], 8);
	ASSERT_DOUBLE_EQ(result[1 * tileCols + 1], 9);
	ASSERT_DOUBLE_EQ(result[2 * tileCols + 0], 11);
	ASSERT_DOUBLE_EQ(result[2 * tileCols + 1], 12);

	delete result;

}

