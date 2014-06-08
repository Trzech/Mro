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

class ClusterAnalizator {
	std::vector<Cluster> filterClustersWithSizeRatio(
			std::vector<Cluster> &clusters, double ratio,
			double accuracy = 0.1);
};

#endif /* CLUSTERANALIZATOR_H_ */
