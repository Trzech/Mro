/*
 * SudokuReader.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "SudokuReader.h"
#include "ClusterReader.h"

SudokuReader::~SudokuReader() {
}

unsigned char* SudokuReader::geTileData(unsigned char* imageData,
		int colsInOriginalImage, Cluster& cluster) {
	unsigned int tileCols = cluster.getWidth();
	unsigned char* tileData = new unsigned char[cluster.getSize()];
	unsigned char* basePlaceInOriginalImage = imageData
			+ cluster.minY * colsInOriginalImage + cluster.minX;
	for (unsigned int i = 0; i < cluster.getHeight(); ++i) {
		unsigned char* placeInOriginalImage = basePlaceInOriginalImage
				+ i * colsInOriginalImage;
		unsigned char* placeInTileData = tileData + i * tileCols;
		memcpy(placeInTileData, placeInOriginalImage, tileCols);
	}
	return tileData;
}

void SudokuReader::recognizeNumbers(unsigned char* imageData, int rows,
		int cols, Cluster biggestSquareCluster,
		std::vector<Cluster> clusterInSizeOfNumbers, double* result) {
	int tileWidth = biggestSquareCluster.getWidth() / 9;
	int tileHeiht = biggestSquareCluster.getHeight() / 9;
	ClusterReader clusterReader;
	for (int j = 0; j < 9; ++j) {
		for (int i = 0; i < 9; ++i) {
			std::vector<Cluster> clustersInThisArea =
					getClustersStartingInThisArea(i, j, tileWidth, tileHeiht,
							biggestSquareCluster, clusterInSizeOfNumbers);
			if (clustersInThisArea.size() > 0) {
				Cluster cluster = clustersInThisArea[0];
				if (debugIsOn) {
					Drawer::drawClusterBorderOnImage(cluster, imageData, rows,
							cols, 0);
				}
				unsigned char* tileData = geTileData(imageData, cols, cluster);
				std::vector<double> testVector = clusterReader.getPropertiesVector(tileData, cluster.getHeight(), cluster.getWidth());
				result[j * 9 + i] = m_neuralNetwork.find(testVector);
				delete tileData;
			} else {
				result[j * 9 + i] = 0.0;
			}
		}
	}
}

std::vector<Cluster> SudokuReader::getClustersStartingInThisArea(int i, int j,
		int tileWidth, int tileHeiht, Cluster biggestSquareCluster,
		std::vector<Cluster> clustersInSizeOfNumbers) {
	int xMin = i * tileWidth + biggestSquareCluster.minX; // tutuaj to musi być jeszcze przesunięte do poczatku ramki sudoku (a nie od początku obrazka!)
	int xMax = (i + 1) * tileWidth + biggestSquareCluster.minX;
	int yMin = j * tileHeiht + biggestSquareCluster.minY;
	int yMax = (j + 1) * tileHeiht + biggestSquareCluster.minY;
	std::vector<Cluster> clustersInCorrectPlace =
			ClusterAnalizator::filterClustersStartingInRange(
					clustersInSizeOfNumbers, xMin, xMax, yMin, yMax);

	return clustersInCorrectPlace;

}

double* SudokuReader::getNumberRepresetation(char* imageFilename) {
	//given
	int rows, cols;
	GrayscaleImageReader reader;
	unsigned char *inBuf;
	unsigned char *outBuf;
	inBuf = reader.readDataFromFile(imageFilename, &rows, &cols);

	// Binarize
	SauvolaBinarizator binarizator(inBuf, rows, cols);
	outBuf = binarizator.binarizeWithIntegral(15, 0.15);

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
					biggestSquareCluster.getWidth() / (9 * 6),
					biggestSquareCluster.getWidth() / (9 * 2),
					biggestSquareCluster.getHeight() / 30,
					biggestSquareCluster.getHeight() / 9);

	//Filter clusters by place
	double * numbers = new double[9 * 9];

	recognizeNumbers(outBuf, rows, cols, biggestSquareCluster,
			clusterInSizeOfNumbers, numbers);

	if (debugIsOn) {
//		Drawer::drawSudokuMeshInClusterBorderOnImage(biggestSquareCluster,
//				outBuf, rows, cols, 0);
		char debugImageFilename[50];

		strcpy(debugImageFilename, "test/sudoku/images/result/");
		strcat(debugImageFilename, strrchr(imageFilename, '/'));

		reader.writeImage(debugImageFilename, outBuf, rows, cols, 255);

	}
	delete inBuf;
	delete outBuf;
	return numbers;

}
