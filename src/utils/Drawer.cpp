/*
 * Drawer.cpp
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#include <utils/Drawer.h>

void Drawer::drawClusterBorderOnImage(std::vector<Cluster>& clusters,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	for (unsigned int i = 0;  i < clusters.size(); ++i) {
		drawClusterBorderOnImage( clusters[i],
				imageData, rows, cols, color);
	}
}

void Drawer::drawClusterBorderOnImage(Cluster& cluster,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	int baseMin, baseMax;
	baseMin = cluster.minY * cols;
	baseMax = cluster.maxY * cols;
	for (int j = cluster.minX; j <= cluster.maxX; ++j) {
		imageData[baseMin + j] = color;
		imageData[baseMax + j] = color;
	}

	for (int j = cluster.minY; j <= cluster.maxY; ++j) {
		imageData[j * cols + cluster.minX] = color;
		imageData[j * cols + cluster.maxX] = color;
	}
}
