/*
 * ClasterFinder.h
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#ifndef CLASTERFINDER_H_
#define CLASTERFINDER_H_
#include "Cluster.h"

class ClasterFinder {
public:
	ClasterFinder();
	~ClasterFinder();
	Cluster findClusters(unsigned char* array, int row, int cols);
private:
	void addBorder(unsigned char* array, int row, int cols);
	inline void detectNeighbours(int i, unsigned char* a);
	Cluster result;
	 int read;
	 int write;
	int stack[10000];

};

#endif /* CLASTERFINDER_H_ */
