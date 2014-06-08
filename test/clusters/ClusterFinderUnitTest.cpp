/*
 * ClusterFinderTest.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "reader/GrayscaleImageReader.h"
#include "clusters/ClusterFinder.h"
#include "gtest/gtest.h"

class ClusterFinderUnitTest: public ::testing::Test {

};

TEST_F(ClusterFinderUnitTest, cluster_5x5) {
	//given
	ClusterFinder finder;
	unsigned char data[25] =
	{0,0,0,0,0,
		0,0,255,0,0,
		0,0,255,0,0,
		0,0,255,0,0,
		0,0,0,0,0};
	unsigned char* imageBuffer = new unsigned char[25];
	memcpy(imageBuffer, data, 25);

	//when
	std::vector<Cluster> clusters = finder.findClusters(imageBuffer, 5, 5,
			1, 100);

	//then
	ASSERT_EQ(2, clusters[0].minX);
	ASSERT_EQ(2, clusters[0].maxX);
	ASSERT_EQ(1, clusters[0].minY);
	ASSERT_EQ(3, clusters[0].maxY);
	ASSERT_EQ(3, clusters[0].size);

	delete imageBuffer;
}

TEST_F(ClusterFinderUnitTest, cluster_5x5_defined_background) {
	//given
	ClusterFinder finder(255);
	unsigned char data[25] =
	{255,255,255,255,255,
		255,255,0,255,255,
		255,255,0,255,255,
		255,255,0,255,255,
		255,255,255,255,255};
	unsigned char* imageBuffer = new unsigned char[25];
	memcpy(imageBuffer, data, 25);

	//when
	std::vector<Cluster> clusters = finder.findClusters(imageBuffer, 5, 5,
			1, 100);

	//then
	ASSERT_EQ(2, clusters[0].minX);
	ASSERT_EQ(2, clusters[0].maxX);
	ASSERT_EQ(1, clusters[0].minY);
	ASSERT_EQ(3, clusters[0].maxY);
	ASSERT_EQ(3, clusters[0].size);
	delete imageBuffer;
}

