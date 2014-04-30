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

void ClasterFinder::addBorder(unsigned char** array, int rows, int cols) {

	for (int i = 0; i < cols; ++i) {
		array[0][i] = 0;
		array[rows - 1][i] = 0;
	}
	for (int i = 0; i < rows; ++i) {
		array[i][0] = 0;
		array[i][cols - 1] = 0;
	}
}
