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

TEST_F(ClasterFinderNonUnitTest, DISABLED_clusters_20x20) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/clusters_20x20.pgm",
			&rows, &cols);
	finder.findClusters(imageBuffer, rows, cols, 1, 100);
	imageReader.writeImage("images/clusters_20x20_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;

	ASSERT_TRUE(1);

}

TEST_F(ClasterFinderNonUnitTest, cluster_5x5) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/cluster_5x5.pgm", &rows,
			&cols);
	Cluster cluster = finder.findClusters(imageBuffer, rows, cols, 1, 100);
	imageReader.writeImage("images/cluster_5x5_result.pgm", imageBuffer, rows,
			cols);
	delete imageBuffer;

	ASSERT_EQ(2, cluster.minX);
	ASSERT_EQ(2, cluster.maxX);
	ASSERT_EQ(1, cluster.minY);
	ASSERT_EQ(3, cluster.maxY);
	ASSERT_EQ(3, cluster.size);

}

TEST_F(ClasterFinderNonUnitTest, clusters_20x20) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/clusters_20x20.pgm", &rows,
			&cols);
	Cluster cluster = finder.findClusters(imageBuffer, rows, cols, 1, 100);
	imageReader.writeImage("images/clusters_20x20_result.pgm", imageBuffer, rows,
			cols);
	delete imageBuffer;
	ASSERT_EQ(1, cluster.minX);
	ASSERT_EQ(3, cluster.maxX);
	ASSERT_EQ(4, cluster.minY);
	ASSERT_EQ(15, cluster.maxY);
	ASSERT_EQ(14, cluster.size);

}

TEST_F(ClasterFinderNonUnitTest, lettersClusters_draw_border) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/lettersClusters.pgm", &rows,
			&cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 1, 100);
	imageReader.writeImage("images/lettersClusters_result.pgm", imageBuffer, rows,
			cols);
	delete imageBuffer;
	ASSERT_TRUE(1);

}
