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
	Cluster cluster = findClusters(a, rows, cols, minClusterSize,
			maxClusterSize);
	for (int i = cluster.minX; i <= cluster.maxX; ++i) {
		a[cluster.minY * cols + i] = color;
		a[cluster.maxY * cols + i] = color;
	}
	for (int i = cluster.minY; i <= cluster.maxY; ++i) {
		a[i * cols + cluster.minX] = color;
		a[i * cols + cluster.maxX] = color;
	}
}

void ClasterFinder::detectNeighbours(int i, unsigned char* a, Cluster &result,
		int rows, int cols) {
	if (a[i] != 0) {
		stack[write++] = i;
		a[i] = 0;
		result.addPoint(i % cols, i / cols);
	}
}

Cluster ClasterFinder::findClusters(unsigned char* originalA, int rows,
		int cols, int minClusterSize, int maxClusterSize) {
	Cluster result;
	stack = new int[1000];
	unsigned char* a = new unsigned char[rows * cols];
	memcpy(a, originalA, rows * cols);
	addBorder(a, rows, cols);

	int pixel = -1;

	for (int i = 0; i < rows * cols; ++i) {

		if (a[i] != 0) {
			pixel = i;
			break;
		}

	}

	if (pixel == -1) {
		return result;
	}

	a[pixel] = 0;
	read = 0;
	write = 0;
	stack[write++] = pixel;
	result.addPoint(pixel % cols, pixel / cols);

	while (read < write) {
		pixel = stack[read++];

		int i = pixel + 1;
		detectNeighbours(i, a, result, rows, cols);
		i = pixel - 1;
		detectNeighbours(i, a, result, rows, cols);
		i = pixel + cols;
		detectNeighbours(i, a, result, rows, cols);
		i = pixel - cols;
		detectNeighbours(i, a, result, rows, cols);
		i = pixel + cols + 1;
		detectNeighbours(i, a, result, rows, cols);
		i = pixel - cols + 1;
		detectNeighbours(i, a, result, rows, cols);
		i = pixel + cols - 1;
		detectNeighbours(i, a, result, rows, cols);
		i = pixel - cols - 1;
		detectNeighbours(i, a, result, rows, cols);
	}
	delete[] stack;
	delete[] a;
	return result;
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
