/*
 * ClasterFinder.h
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#ifndef CLASTERFINDER_H_
#define CLASTERFINDER_H_
#include "Cluster.h"
#include "Binarizator.h"
#include "Pixel.h"
#include <string.h>
#include <vector>

class ClasterFinder {
public:
	ClasterFinder();
	~ClasterFinder();
	std::vector<Cluster> findClusters(unsigned char* a, int rows, int cols,
			int minClusterSize, int maxClusterSize);
	void drawBordersOfClusters(unsigned char* a, int rows, int cols,
			int minClusterSize, int maxClusterSize);
private:
	void addBorder(unsigned char** array, int row, int cols);
	inline void detectNeighbours(unsigned char** a, unsigned long int x,
			unsigned long int y, Cluster &result, int rows, int cols);

	int read;
	int write;
	Pixel * stack;

};

#endif /* CLASTERFINDER_H_ */
