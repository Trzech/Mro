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

void ClasterFinder::detectNeighbours(unsigned long int i, unsigned char* a,
		Cluster &result, int rows, int cols) {
	if (a[i] != 0) {
		stack[write++] = i;
		a[i] = 0;
		result.addPoint(i % cols, i / cols);
	}
}

std::vector<Cluster> ClasterFinder::findClusters(unsigned char* originalA,
		int rows, int cols, int minClusterSize, int maxClusterSize) {

	std::vector<Cluster> result;
	stack = new int[2000];
	unsigned char* a = new unsigned char[rows * cols];
	memcpy(a, originalA, rows * cols);
	addBorder(a, rows, cols);

	while (true) {

		unsigned long int pixel = 0;
		for (unsigned long int i = 0; i < rows * cols; ++i) {

			if (a[i] != 0) {
				pixel = i;
				break;
			}

		}

		if (pixel == 0) {
			delete[] a;
			delete[] stack;
			return result;
		}

		a[pixel] = 0;
		read = 0;
		write = 0;
		stack[write++] = pixel;
		Cluster cluster;
		cluster.addPoint(pixel % cols, pixel / cols);
		while (read < write && cluster.size < maxClusterSize) {
			pixel = stack[read++];

			if (a[pixel + 1] != 0) {stack[write++] = pixel + 1;	a[pixel + 1] = 0;cluster.addPoint((pixel + 1) % cols, (pixel + 1) / cols);	}
			if (a[pixel - 1] != 0) {stack[write++] = pixel - 1;	a[pixel - 1] = 0;cluster.addPoint((pixel - 1) % cols, (pixel - 1) / cols);	}
			if (a[pixel + cols] != 0) {stack[write++] = pixel + cols;	a[pixel + cols] = 0;cluster.addPoint((pixel + cols) % cols, (pixel + cols) / cols);	}
			if (a[pixel - cols] != 0) {stack[write++] = pixel - cols;	a[pixel - cols] = 0;cluster.addPoint((pixel - cols) % cols, (pixel - cols) / cols);	}
			if (a[pixel + cols + 1] != 0) {stack[write++] = pixel + cols + 1;	a[pixel + cols + 1] = 0;cluster.addPoint((pixel + cols + 1) % cols, (pixel + cols + 1) / cols);	}
			if (a[pixel - cols + 1] != 0) {stack[write++] = pixel - cols + 1;	a[pixel - cols + 1] = 0;cluster.addPoint((pixel - cols + 1) % cols, (pixel - cols + 1) / cols);	}
			if (a[pixel + cols - 1] != 0) {stack[write++] = pixel + cols - 1;	a[pixel + cols - 1] = 0;cluster.addPoint((pixel + cols - 1) % cols, (pixel + cols - 1) / cols);	}
			if (a[pixel - cols - 1] != 0) {stack[write++] = pixel - cols - 1;	a[pixel - cols - 1] = 0;cluster.addPoint((pixel - cols - 1) % cols, (pixel - cols - 1) / cols);	}



		}

		if (cluster.size > minClusterSize) {
			result.push_back(cluster);
		}

	}
}

void ClasterFinder::addBorder(unsigned char* a, int rows, int cols) {

	for (int i = 0; i < cols; ++i) {
		a[i] = 0;
		a[(rows - 1) * cols + i] = 0;
	}
	for (int i = 0; i < rows; ++i) {
		a[i * cols] = 0;
		a[i * cols + cols - 1] = 0;
	}
}
