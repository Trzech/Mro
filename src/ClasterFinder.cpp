/*
 * ClasterFinder.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "ClasterFinder.h"

ClasterFinder::ClasterFinder() {

}

ClasterFinder::~ClasterFinder() {
}

void ClasterFinder::drawBordersOfClusters(unsigned char* a, int rows, int cols,
		int minClusterSize, int maxClusterSize) {
	unsigned char color = 100;
	std::vector<Cluster> clusters = findClusters(a, rows, cols, minClusterSize,
			maxClusterSize);
	int baseMin, baseMax;
	for (int i = 0; i < clusters.size(); ++i) {
		baseMin = clusters[i].minY * cols;
		baseMax = clusters[i].maxY * cols;
		for (int j = clusters[i].minX; j <= clusters[i].maxX; ++j) {
			a[baseMin + j] = color;
			a[baseMax + j] = color;
		}

		for (int j = clusters[i].minY; j <= clusters[i].maxY; ++j) {
			a[j * cols + clusters[i].minX] = color;
			a[j * cols + clusters[i].maxX] = color;
		}
	}
}

std::vector<Cluster> ClasterFinder::findClusters(unsigned char* originalA,
		 int rows,  int cols,  int minClusterSize,
		 int maxClusterSize) {

	std::vector<Cluster> result;
	stack = new Pixel[10000000];
	unsigned char* aBuff = new unsigned char[rows * cols];
	memcpy(aBuff, originalA, rows * cols);
	unsigned char ** a = Binarizator::prepareTableForOperations(aBuff, rows,
			cols);
	addBorder(a, rows, cols);

	while (true) {

		Pixel pixel(0, 0);
		for (unsigned long int i = 0; i < rows; ++i) {
			for (unsigned long int j = 0; j < cols; ++j) {
				if (a[i][j] != 0) {
					pixel.y = i;
					pixel.x = j;
					break;
				}

			}
			if (pixel.x != 0 || pixel.y != 0) {
				break;
			}
		}

		if (pixel.x == 0 && pixel.y == 0) {
			delete[] a;
			delete[] stack;
			return result;
		}

		a[pixel.y][pixel.x] = 0;
		read = 0;
		write = 0;
		stack[write++] = pixel;
		Cluster cluster;
		cluster.addPoint(pixel.x, pixel.y);
		while (read < write) {
			pixel = stack[read++];
			detectNeighbours(a, pixel.x - 1, pixel.y - 1, cluster, rows, cols);
			detectNeighbours(a, pixel.x - 1, pixel.y, cluster, rows, cols);
			detectNeighbours(a, pixel.x - 1, pixel.y + 1, cluster, rows, cols);
			detectNeighbours(a, pixel.x, pixel.y - 1, cluster, rows, cols);
			detectNeighbours(a, pixel.x, pixel.y + 1, cluster, rows, cols);
			detectNeighbours(a, pixel.x + 1, pixel.y - 1, cluster, rows, cols);
			detectNeighbours(a, pixel.x + 1, pixel.y, cluster, rows, cols);
			detectNeighbours(a, pixel.x + 1, pixel.y + 1, cluster, rows, cols);

		}

		if (cluster.size > minClusterSize && cluster.size < maxClusterSize) {
			result.push_back(cluster);
		}

	}
}

void ClasterFinder::addBorder(unsigned char** a, int rows, int cols) {

	for (int i = 0; i < cols; ++i) {
		a[0][i] = 0;
		a[rows - 1][i] = 0;
	}
	for (int i = 0; i < rows; ++i) {
		a[i][0] = 0;
		a[i][cols - 1] = 0;
	}
}

inline void ClasterFinder::detectNeighbours(unsigned char** a,
		unsigned long int x, unsigned long int y, Cluster& result, int rows,
		int cols) {
	if (a[y][x] != 0) {
		stack[write++] = Pixel(x, y);
		a[y][x] = 0;
		result.addPoint(x, y);
	}

}
