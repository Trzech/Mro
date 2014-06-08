/*
 * ClusterAnalizatorUnitTest.cpp
 *
 *      Author: mj
 */

#include "gtest/gtest.h"
#include "clusters/Cluster.h"
#include "clusters/ClusterAnalizator.h"

class ClusterAnalizatorUnitTest: public ::testing::Test {

};



TEST_F(ClusterAnalizatorUnitTest, filtersByRatioCorrectly) {
	//given
	Cluster cluster1;
	cluster1.addPoint(0,0);
	cluster1.addPoint(1,20);
	Cluster cluster2;
	cluster2.addPoint(0,0);
	cluster2.addPoint(20,20);

	std::vector<Cluster> clusters;
	clusters.push_back(cluster1);
	clusters.push_back(cluster2);

	//when
	std::vector<Cluster> result = ClusterAnalizator::filterClustersWithSizeRatio(clusters, 1, 0.01);

	//then
	ASSERT_EQ(1, result.size());
	ASSERT_EQ(21, result[0].getWidth());
	ASSERT_EQ(21, result[0].getHeight());

}

TEST_F(ClusterAnalizatorUnitTest, findsBiggestClusterCorrectly) {
	//given
	Cluster cluster1;
	cluster1.addPoint(0,0);
	cluster1.addPoint(1,20);
	Cluster cluster2;
	cluster2.addPoint(0,0);
	cluster2.addPoint(20,20);

	std::vector<Cluster> clusters;
	clusters.push_back(cluster1);
	clusters.push_back(cluster2);

	//when
	Cluster result = ClusterAnalizator::findBiggestCluster(clusters);

	//then

	ASSERT_EQ(21, result.getWidth());
	ASSERT_EQ(21, result.getHeight());

}

