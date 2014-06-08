/*
 * ClusterFinder.h
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#ifndef CLASTERFINDER_H_
#define CLASTERFINDER_H_
#include "Cluster.h"
#include "../binarization/Binarizator.h"
#include "../utils/Pixel.h"
#include <string.h>
#include <vector>
#include <stack>

class ClusterFinder {
public:
	ClusterFinder(	unsigned char backgroundColor = 0);
	~ClusterFinder();
	unsigned char backgroundColor;
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
	std::stack<Pixel> stack;

};

#endif /* CLASTERFINDER_H_ */
