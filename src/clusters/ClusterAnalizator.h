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
};

#endif /* CLUSTERANALIZATOR_H_ */
