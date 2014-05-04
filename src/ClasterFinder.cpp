/*
 * ClasterFinder.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "ClasterFinder.h"

ClasterFinder::ClasterFinder() {
	// TODO Auto-generated constructor stub

}

ClasterFinder::~ClasterFinder() {
	// TODO Auto-generated destructor stub
}

void ClasterFinder::detectNeighbours(int i, unsigned char* a) {
	if (a[i] != 0) {stack[write++] = i;	a[i] = 0;}
}

Cluster ClasterFinder::findClusters(unsigned char* a, int rows, int cols) {

	addBorder(a, rows, cols);

	int pixel;

	for (int i = 0; i < rows * cols; ++i) {

		if (a[i] != 0) {
			pixel = i;
			break;
		}

	}
	a[pixel] = 0;
	read = 0;
	write = 0;
	stack[write++] = pixel;

	while (read < write ) {
		pixel = stack[read++];

		int i = pixel + 1;
		detectNeighbours(i, a);
		i = pixel - 1;
		detectNeighbours(i, a);
		i = pixel + cols;
		detectNeighbours(i, a);
		i = pixel - cols;
		detectNeighbours(i, a);
		i = pixel + cols + 1;
		detectNeighbours(i, a);
		i = pixel - cols + 1;
		detectNeighbours(i, a);
		i = pixel + cols - 1;
		detectNeighbours(i, a);
		i = pixel - cols - 1;
		detectNeighbours(i, a);
	}

	return result;
}

void ClasterFinder::addBorder(unsigned char* a, int rows, int cols) {

	for (int i = 0; i < cols; ++i) {
		a[i] = 0;
		a[(rows - 1)*cols + i] = 0;
	}
	for (int i = 0; i < rows; ++i) {
		a[i*cols] = 0;
		a[i*cols+cols - 1] = 0;
	}
}
