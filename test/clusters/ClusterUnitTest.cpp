/*
 * ClusterFinderTest.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "gtest/gtest.h"
#include "clusters/Cluster.h"

class ClusterUnitTest: public ::testing::Test {

};



TEST_F(ClusterUnitTest, findsWidthCorrectly) {
	//given
	Cluster cluster;
	cluster.addPoint(0,0);
	cluster.addPoint(1,2);
	//when
	unsigned int result = cluster.getWidth();

	//then
	ASSERT_EQ(2, result);

}

TEST_F(ClusterUnitTest, findsHeightCorrectly) {
	//given
	Cluster cluster;
	cluster.addPoint(0,0);
	cluster.addPoint(1,2);
	//when
	unsigned int result = cluster.getHeight();

	//then
	ASSERT_EQ(3, result);

}

TEST_F(ClusterUnitTest, findsRatioCorrectly) {
	//given
	Cluster cluster;
	cluster.addPoint(0,0);
	cluster.addPoint(99,199);
	//when
	double result = cluster.getRatio();

	//then
	ASSERT_DOUBLE_EQ(0.5, result);

}

