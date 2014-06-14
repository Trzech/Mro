/*
 * NeuralNetworkTest.cpp
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

 *
 *  Created on: 14 cze 2014
 *      Author: aldor
 */
#include "gtest/gtest.h"

#include "network/NeuralNetwork.h"
#include "originNN.h"

class NeuralNetworkTest: public ::testing::Test {

};

TEST_F(NeuralNetworkTest, concept_test_originNN) {

	NeuralNetwork first;
	first.readAndLearn("test/network/data/nauka_cyfry5x3.dat");
	MatDoub testData = read_test_data("test/network/data/testy_cyfry5x3.dat", FEATURES_VECTOR_SIZE, NR_OF_TEST_SAMPLES_PER_CLASS, NR_OF_CLASSES );
	std::vector<int> result = first.find(testData);
	ASSERT_EQ(result[0], 0);
	ASSERT_EQ(result[55], 1);
	ASSERT_EQ(result.size(), NR_OF_TEST_SAMPLES_PER_CLASS * NR_OF_CLASSES);
	for (int i = 1; i < NR_OF_CLASSES * NR_OF_TEST_SAMPLES_PER_CLASS; i+= NR_OF_TEST_SAMPLES_PER_CLASS)
		ASSERT_EQ(result[i], i/NR_OF_TEST_SAMPLES_PER_CLASS);

}

TEST_F(NeuralNetworkTest, test_vector_find_cluster) {

	NeuralNetwork first;
	first.readAndLearn("test/network/data/nauka_cyfry5x3.dat");
	MatDoub testData = read_test_data("test/network/data/testy_cyfry5x3.dat", FEATURES_VECTOR_SIZE, NR_OF_TEST_SAMPLES_PER_CLASS, NR_OF_CLASSES );
	std::vector<double> testVector;
	for (int j = 0, len = testData.ncols(); j < len; j++)
		testVector.push_back(testData[0][j]);
	int result = first.find(testVector);
	ASSERT_EQ(result, 0);

}
