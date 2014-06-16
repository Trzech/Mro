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
		if (fabs(cluster.getRatio() - ratio) < accuracy) {
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
		if (cluster.getSize() > max) {
			max = cluster.getSize();
			maxIndex = i;
		}
	}
	return clusters[maxIndex];
}

std::vector<Cluster> ClusterAnalizator::filterClustersInSizeRange(
		std::vector<Cluster>& clusters, int minWidth, int maxWidth,
		int minHeight, int maxHeight) {
	std::vector<Cluster> result;
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		Cluster cluster = clusters[i];
		if (cluster.getHeight() >= minHeight && cluster.getWidth() >= minWidth
				&& cluster.getHeight() <= maxHeight
				&& cluster.getWidth() <= maxWidth) {
			result.push_back(cluster);
		}
	}
	return result;
}

std::vector<Cluster> ClusterAnalizator::filterClustersInPlacementRange(
		std::vector<Cluster>& clusters, int minX, int maxX, int minY,
		int maxY) {
	std::vector<Cluster> result;
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		Cluster cluster = clusters[i];
		if (cluster.minX >= minX && cluster.maxX <= maxX && cluster.minY >= minY
				&& cluster.maxY <= maxY) {
			result.push_back(cluster);
		}
	}
	return result;
}

std::vector<Cluster> ClusterAnalizator::filterClustersStartingInRange(
		std::vector<Cluster>& clusters, int minX, int maxX, int minY,
		int maxY) {
	std::vector<Cluster> result;
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		Cluster cluster = clusters[i];
		if (cluster.minX >= minX && cluster.minX <= maxX && cluster.minY >= minY
				&& cluster.minY <= maxY) {
			result.push_back(cluster);
		}
	}
	return result;
}

std::vector<Cluster> ClusterAnalizator::filterClustersWithCenterInRange(
		std::vector<Cluster>& clusters, int minX, int maxX, int minY,
		int maxY) {
	std::vector<Cluster> result;
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		Cluster cluster = clusters[i];
		int clusterXCenter = (cluster.minX + cluster.maxX) / 2;
		int clusterYCenter = (cluster.minY + cluster.maxY) / 2;
		if (clusterXCenter >= minX && clusterXCenter <= maxX && clusterYCenter >= minY
				&& clusterYCenter <= maxY) {
			result.push_back(cluster);
		}
	}
	return result;
}
