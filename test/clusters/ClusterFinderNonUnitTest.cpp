/*
 * ClusterFinderNonUnitTest.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */



/*
 * HaarLikeBinarizatorTest.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "reader/GrayscaleImageReader.h"
#include "clusters/ClusterFinder.h"
#include "gtest/gtest.h"

class ClusterFinderNonUnitTest: public ::testing::Test {

};

TEST_F(ClusterFinderNonUnitTest, cluster_5x5) {
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

TEST_F(ClusterFinderNonUnitTest, clusters_20x20) {
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

TEST_F(ClusterFinderNonUnitTest, lettersClusters_draw_border) {
	GrayscaleImageReader imageReader;
	ClusterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("test/clusters/images/source/lettersClusters.pgm",
			&rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 1, 200);
	imageReader.writeImage("test/clusters/images/result/lettersClusters_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;
	ASSERT_TRUE(1);

}

TEST_F(ClusterFinderNonUnitTest, smileWithBigCluster_draw_border) {
	GrayscaleImageReader imageReader;
	ClusterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("test/clusters/images/source/smileWithBigCluster.pgm",
			&rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 0, 200);
	imageReader.writeImage("test/clusters/images/result/smileWithBigCluster_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;
	ASSERT_TRUE(1);

}





