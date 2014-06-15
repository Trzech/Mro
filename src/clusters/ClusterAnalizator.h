/*
 * ClusterAnalizator.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef CLUSTERANALIZATOR_H_
#define CLUSTERANALIZATOR_H_
#include "Cluster.h"
#include <vector>
#include <math.h>

class ClusterAnalizator {
public:
	static std::vector<Cluster> filterClustersWithSizeRatio(
			std::vector<Cluster> &clusters, double ratio,
			double accuracy = 0.1);

	static Cluster findBiggestCluster(std::vector<Cluster> &clusters);
	static std::vector<Cluster> filterClustersInSizeRange(std::vector<Cluster> &clusters, int minWidth, int maxWidth, int minHeight, int maxHeight);
	static std::vector<Cluster> filterClustersInPlacementRange(std::vector<Cluster> &clusters, int minX, int maxX, int minY, int maxY);
	static std::vector<Cluster> filterClustersStartingInRange(std::vector<Cluster> &clusters, int minX, int maxX, int minY, int maxY);
};

#endif /* CLUSTERANALIZATOR_H_ */
