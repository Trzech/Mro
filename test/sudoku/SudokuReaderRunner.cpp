#include "sudoku/SudokuReader.h"
#include "gtest/gtest.h"

#include "reader/GrayscaleImageReader.h"
#include "binarization/SauvolaBinarizator.h"
#include "clusters/ClusterFinder.h"
#include "clusters/ClusterAnalizator.h"
#include "utils/Drawer.h"

class SudokuReaderRunner: public ::testing::Test {

};

TEST_F(SudokuReaderRunner, justTests) {
	//given
	int rows, cols;
	GrayscaleImageReader reader;
	char inputFileName[] = "test/sudoku/images/source/93987_4.pgm";
	char outputFileName[] = "test/sudoku/images/result/93987_2.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;
	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	// Binarize
	SauvolaBinarizator binarizator(inBuf, rows, cols);
	outBuf = binarizator.binarizeWithIntegral(10, 0.2);

	// FindClusters
	ClusterFinder finder(255);
	std::vector<Cluster> clusters = finder.findClusters(outBuf, rows, cols, 50,
			1000000);

	// FindBiggestSquareCluster
	std::vector<Cluster> squareClusters =
			ClusterAnalizator::filterClustersWithSizeRatio(clusters, 1.0, 0.1);
	Cluster biggestSquareCluster = ClusterAnalizator::findBiggestCluster(
			clusters);

	//Remove frame
	Drawer::ereaseFirstClusterOnImageInRanges(outBuf, rows, cols, 255,
			biggestSquareCluster.minX, biggestSquareCluster.maxX,
			biggestSquareCluster.minY, biggestSquareCluster.maxY);

	// Draw cluster border
	Drawer::drawSudokuMeshInClusterBorderOnImage(biggestSquareCluster, outBuf,
			rows, cols, 0);
	//when

	//then
	reader.writeImage(outputFileName, outBuf, rows, cols);
	delete inBuf;
	delete outBuf;

}

