/*
 * SudokuReader.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "SudokuReader.h"

SudokuReader::SudokuReader() {

}

SudokuReader::~SudokuReader() {
	// TODO Auto-generated destructor stub
}

void SudokuReader::recognizeNumbers(Cluster biggestSquareCluster,
		std::vector<Cluster> clusterInSizeOfNumbers, bool* result) {
	int tileWidth = biggestSquareCluster.getWidth() / 9;
	int tileHeiht = biggestSquareCluster.getHeight() / 9;
	for (int j = 0; j < 9; ++j) {
		for (int i = 0; i < 9; ++i) {
			std::vector<Cluster> clustersInThisArea =
					getClustersInThisArea(i, j, tileWidth, tileHeiht,
							biggestSquareCluster, clusterInSizeOfNumbers);
			if (clustersInThisArea.size() > 0) {
				result[j * 9 + i] = true;
			} else {
				result[j * 9 + i] = false;
			}
		}
	}
}

std::vector<Cluster> SudokuReader::getClustersInThisArea(int i , int j, int tileWidth, int tileHeiht, Cluster biggestSquareCluster, std::vector<Cluster> clustersInSizeOfNumbers) {
	int xMin = i * tileWidth + biggestSquareCluster.minX; // tutuaj to musi być jeszcze przesunięte do poczatku ramki sudoku (a nie od początku obrazka!)
	int xMax = (i + 1) * tileWidth + biggestSquareCluster.minX;
	int yMin = j * tileHeiht + biggestSquareCluster.minY;
	int yMax = (j + 1) * tileHeiht + biggestSquareCluster.minY;
	std::vector<Cluster> clustersInCorrectPlace =
			ClusterAnalizator::filterClustersInPlacementRange(
					clustersInSizeOfNumbers, xMin, xMax, yMin, yMax);

	return clustersInCorrectPlace;

}

bool* SudokuReader::getNumberRepresetation(char* imageFilename) {
	//given
	int rows, cols;
	GrayscaleImageReader reader;
	unsigned char *inBuf;
	unsigned char *outBuf;
	inBuf = reader.readDataFromFile(imageFilename, &rows, &cols);

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
	bool * isANumber = new bool[9 * 9];
	recognizeNumbers(biggestSquareCluster, clusterInSizeOfNumbers, isANumber);
	delete inBuf;
	delete outBuf;
	return isANumber;

}
