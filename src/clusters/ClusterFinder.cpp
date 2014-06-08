/*
 * ClasterFinder.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "ClusterFinder.h"

ClusterFinder::ClusterFinder(unsigned char backgroundColor) {
	this->backgroundColor = backgroundColor;
}

ClusterFinder::~ClusterFinder() {
}

std::vector<Cluster> ClusterFinder::findClusters(unsigned char* originalA,
		int rows, int cols, int minClusterSize, int maxClusterSize) {

	std::vector<Cluster> result;
	unsigned char* aBuff = new unsigned char[rows * cols];
	memcpy(aBuff, originalA, rows * cols);
	unsigned char ** a = Binarizator::prepareTableForOperations(aBuff, rows,
			cols);
	addBorder(a, rows, cols);

	while (true) {
		Pixel pixel(0, 0);
		for (unsigned long int i = 0; i < rows; ++i) {
			for (unsigned long int j = 0; j < cols; ++j) {
				if (a[i][j] != this->backgroundColor) {
					a[i][j] = this->backgroundColor;
					pixel.y = i;
					pixel.x = j;
					stack.push(pixel);
					Cluster cluster;
					cluster.addPoint(pixel.x, pixel.y);
					while (!stack.empty()) {
						pixel = stack.top();
						stack.pop();
						detectNeighbours(a, pixel.x - 1, pixel.y - 1, cluster,
								rows, cols);
						detectNeighbours(a, pixel.x + 1, pixel.y - 1, cluster,
								rows, cols);
						detectNeighbours(a, pixel.x, pixel.y - 1, cluster, rows,
								cols);
						detectNeighbours(a, pixel.x - 1, pixel.y, cluster, rows,
								cols);
						detectNeighbours(a, pixel.x + 1, pixel.y, cluster, rows,
								cols);
						detectNeighbours(a, pixel.x - 1, pixel.y + 1, cluster,
								rows, cols);
						detectNeighbours(a, pixel.x, pixel.y + 1, cluster, rows,
								cols);
						detectNeighbours(a, pixel.x + 1, pixel.y + 1, cluster,
								rows, cols);

					}

					if (cluster.size > minClusterSize
							&& cluster.size < maxClusterSize) {
						result.push_back(cluster);
					}

				}

			}

		}
		delete[] a;
		return result;

	}
}

void ClusterFinder::addBorder(unsigned char** a, int rows, int cols) {

	for (int i = 0; i < cols; ++i) {
		a[0][i] = this->backgroundColor;
		a[rows - 1][i] = this->backgroundColor;
	}
	for (int i = 0; i < rows; ++i) {
		a[i][0] = this->backgroundColor;
		a[i][cols - 1] = this->backgroundColor;
	}
}

inline void ClusterFinder::detectNeighbours(unsigned char** a,
		unsigned long int x, unsigned long int y, Cluster& result, int rows,
		int cols) {
	if (a[y][x] != this->backgroundColor) {
		stack.push(Pixel(x, y));
		a[y][x] = this->backgroundColor;
		result.addPoint(x, y);
	}

}
