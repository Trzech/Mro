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

void ClasterFinder::detectNeighbours(int i, unsigned char* a, Cluster &result, int rows, int cols) {
	if (a[i] != 0) {
		stack[write++] = i;
		a[i] = 0;
		result.addPoint(i%cols, i/cols);
	}
}

Cluster ClasterFinder::findClusters(unsigned char* a, int rows, int cols,
		int minClusterSize, int maxClusterSize) {
	Cluster result;
	stack = new int[1000];
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
