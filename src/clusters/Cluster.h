/*
 * Cluster.h
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_
#include <limits.h>

class Cluster {
public:
	Cluster();
	~Cluster();
	void addPoint(unsigned int x,unsigned  int y);
	unsigned int minX;
	unsigned int minY;
	unsigned int maxX;
	unsigned int maxY;
	unsigned int size;

	unsigned int getWidth();
	unsigned int getHeight();
	double getRatio();

};

#endif /* CLUSTER_H_ */
