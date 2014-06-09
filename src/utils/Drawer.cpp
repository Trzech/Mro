/*
 * Drawer.cpp
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#include <utils/Drawer.h>

void Drawer::drawClusterBorderOnImage(std::vector<Cluster>& clusters,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		drawClusterBorderOnImage(clusters[i], imageData, rows, cols, color);
	}
}

void Drawer::drawClusterBorderOnImage(Cluster& cluster,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	int baseMin = cluster.minY * cols;
	int baseMax = cluster.maxY * cols;
	for (int j = cluster.minX; j <= cluster.maxX; ++j) {
		imageData[baseMin + j] = color;
		imageData[baseMax + j] = color;
	}

	for (int j = cluster.minY; j <= cluster.maxY; ++j) {
		imageData[j * cols + cluster.minX] = color;
		imageData[j * cols + cluster.maxX] = color;
	}
}

void Drawer::drawSudokuMeshInClusterBorderOnImage(Cluster& cluster,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	//int baseMax = cluster.maxY * cols;

	int baseMin = cluster.minY * cols;
	int tileWidth = round(cluster.getWidth() / 9.0);
	int tileHeight = round(cluster.getHeight() / 9.0);
	for (int i = 0; i <= 9; ++i) {
		int localBaseMin = baseMin + i * cols * tileHeight;

		for (int j = cluster.minX; j <= cluster.minX + 9 * tileWidth; ++j) {
			imageData[localBaseMin + j] = color;
		}

		for (int j = cluster.minY; j <= cluster.minY + 9 * tileHeight; ++j) {
			imageData[j * cols + cluster.minX + i * tileWidth] = color;

		}

	}

}
