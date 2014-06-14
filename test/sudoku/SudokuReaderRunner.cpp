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
	char inputFileName[] = "test/sudoku/images/source/93987_1.pgm";
	char outputFileName[] = "test/sudoku/images/result/93987_2.pgm";
	unsigned char *inBuf;
	unsigned char *outBuf;
	inBuf = reader.readDataFromFile(inputFileName, &rows, &cols);

	// Binarize
	SauvolaBinarizator binarizator(inBuf, rows, cols);
	outBuf = binarizator.binarizeWithIntegral(15, 0.25);

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

	//Filter clusters by size
	std::vector<Cluster> clusterInSizeOfNumbers =
			ClusterAnalizator::filterClustersInSizeRange(clusters,
					biggestSquareCluster.getWidth() / 90,
					biggestSquareCluster.getWidth(),
					biggestSquareCluster.getHeight() / 30,
					biggestSquareCluster.getHeight());

	//Filter clusters by place
	int tileWidth = biggestSquareCluster.getWidth() / 9;
	int tileHeiht = biggestSquareCluster.getHeight() / 9;

	for (int j = 0; j < 9; ++j) {
		for (int i = 0; i < 9; ++i) {
			int xMin = i * tileWidth + biggestSquareCluster.minX; // tutuaj to musi być jeszcze przesunięte do poczatku ramki sudoku (a nie od początku obrazka!)
			int xMax = (i + 1) * tileWidth + biggestSquareCluster.minX;
			int yMin = j * tileHeiht + biggestSquareCluster.minY;
			int yMax = (j + 1) * tileHeiht + biggestSquareCluster.minY;
			std::vector<Cluster> clusterInCorrectPlace =
					ClusterAnalizator::filterClustersInPlacementRange(
							clusterInSizeOfNumbers, xMin, xMax, yMin, yMax);
			if (clusterInCorrectPlace.size() > 0) {
				printf("cyfra ");
			} else {
				printf("empty ");
			}
		}
		printf(".\n");
	}

	//then
	SudokuReader sudokuReader;
	sudokuReader.getSudokuStringRepresentation(outBuf, rows, cols, 255,
			biggestSquareCluster.minX, biggestSquareCluster.maxX,
			biggestSquareCluster.minY, biggestSquareCluster.maxY, 0.98);

	// Draw cluster border
	Drawer::drawSudokuMeshInClusterBorderOnImage(biggestSquareCluster, outBuf,
			rows, cols, 0);

	reader.writeImage(outputFileName, outBuf, rows, cols);
	delete inBuf;
	delete outBuf;

}

