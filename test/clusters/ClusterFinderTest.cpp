/*
 * ClusterFinderTest.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "reader/GrayscaleImageReader.h"
#include "clusters/ClusterFinder.h"
#include "gtest/gtest.h"

class ClusterFinderTest: public ::testing::Test {

};

TEST_F(ClusterFinderTest, cluster_5x5) {
	GrayscaleImageReader imageReader;
	ClusterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("test/clusters/images/source/cluster_5x5.pgm", &rows,
			&cols);
	std::vector<Cluster> clusters = finder.findClusters(imageBuffer, rows, cols,
			1, 100);
	delete imageBuffer;

	ASSERT_EQ(2, clusters[0].minX);
	ASSERT_EQ(2, clusters[0].maxX);
	ASSERT_EQ(1, clusters[0].minY);
	ASSERT_EQ(3, clusters[0].maxY);
	ASSERT_EQ(3, clusters[0].size);

}

TEST_F(ClusterFinderTest, clusters_20x20) {
	GrayscaleImageReader imageReader;
	ClusterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("test/clusters/images/source/clusters_20x20.pgm",
			&rows, &cols);
	std::vector<Cluster> clusters = finder.findClusters(imageBuffer, rows, cols,
			1, 100);

	delete imageBuffer;
	ASSERT_EQ(1, clusters[0].minX);
	ASSERT_EQ(3, clusters[0].maxX);
	ASSERT_EQ(4, clusters[0].minY);
	ASSERT_EQ(15, clusters[0].maxY);
	ASSERT_EQ(14, clusters[0].size);

}




