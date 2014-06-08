/*
 * ClusterAnalizator.cpp
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#include <clusters/ClusterAnalizator.h>

std::vector<Cluster> ClusterAnalizator::filterClustersWithSizeRatio(
		std::vector<Cluster> &clusters, double ratio, double accuracy) {
	std::vector<Cluster> result;
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		Cluster cluster = clusters[i];
		if (fabs(cluster.getRatio()-ratio)< accuracy) {
			result.push_back(cluster);
		}
	}
	return result;

}

Cluster ClusterAnalizator::findBiggestCluster(std::vector<Cluster>& clusters) {
	unsigned int max = 0;
	unsigned int maxIndex = 0;
	for (unsigned int i = 0; i < clusters.size(); ++i) {
			Cluster cluster = clusters[i];
			if (cluster.getSize()>max) {
				max = cluster.getSize();
				maxIndex = i;
			}
		}
	return clusters[maxIndex];
}
