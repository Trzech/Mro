/*
 * ClasterFinderNonUnitTest.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "ClasterFinder.h"

/*
 * HaarLikeBinarizatorTest.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "GrayscaleImageReader.h"
#include "ClasterFinder.h"
#include "gtest/gtest.h"

class ClasterFinderNonUnitTest: public ::testing::Test {

};

TEST_F(ClasterFinderNonUnitTest, cluster_5x5) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/cluster_5x5.pgm", &rows,
			&cols);
	std::vector<Cluster> clusters = finder.findClusters(imageBuffer, rows, cols,
			1, 100);
	imageReader.writeImage("images/cluster_5x5_result.pgm", imageBuffer, rows,
			cols);
	delete imageBuffer;

	ASSERT_EQ(2, clusters[0].minX);
	ASSERT_EQ(2, clusters[0].maxX);
	ASSERT_EQ(1, clusters[0].minY);
	ASSERT_EQ(3, clusters[0].maxY);
	ASSERT_EQ(3, clusters[0].size);

}

TEST_F(ClasterFinderNonUnitTest, DISABLED_clusters_20x20) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/clusters_20x20.pgm",
			&rows, &cols);
	std::vector<Cluster> clusters = finder.findClusters(imageBuffer, rows, cols,
			1, 100);
	imageReader.writeImage("images/clusters_20x20_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;
	ASSERT_EQ(1, clusters[0].minX);
	ASSERT_EQ(3, clusters[0].maxX);
	ASSERT_EQ(4, clusters[0].minY);
	ASSERT_EQ(15, clusters[0].maxY);
	ASSERT_EQ(14, clusters[0].size);

}

TEST_F(ClasterFinderNonUnitTest, DISABLED_lettersClusters_draw_border) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/lettersClusters.pgm",
			&rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 1, 200);
	imageReader.writeImage("images/lettersClusters_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;
	ASSERT_TRUE(1);

}

TEST_F(ClasterFinderNonUnitTest, DISABLED_smileWithBigCluster_draw_border) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/smileWithBigCluster.pgm",
			&rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 0, 200);
	imageReader.writeImage("images/smileWithBigCluster_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;
	ASSERT_TRUE(1);

}

TEST_F(ClasterFinderNonUnitTest, book_inversed_1000_draw_border) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/book_inversed_1000.pgm",
			&rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 50, 100);
	imageReader.writeImage("images/book_inversed_1000_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;
	ASSERT_TRUE(1);

}

TEST_F(ClasterFinderNonUnitTest, sudokuZdjecieWynik_kawrat_draw_border) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile(
			"images/sudokuZdjecieWynik_kawrat.pgm", &rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 1000, 10000);
	imageReader.writeImage("images/sudokuZdjecieWynik_kawrat_border_result.pgm",
			imageBuffer, rows, cols);
	delete imageBuffer;
	ASSERT_TRUE(1);

}

