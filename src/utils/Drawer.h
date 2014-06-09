/*
 * Drawer.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef DRAWER_H_
#define DRAWER_H_
#include "clusters/Cluster.h"
#include <vector>
#include <math.h>

class Drawer {
public:
	static void drawClusterBorderOnImage(std::vector<Cluster> & clusters,
			unsigned char* imageData, int rows, int cols, unsigned char color =
					0);
	static void drawClusterBorderOnImage(Cluster & cluster,
			unsigned char* imageData, int rows, int cols, unsigned char color =
					0);
	static void drawSudokuMeshInClusterBorderOnImage(Cluster & cluster,
			unsigned char* imageData, int rows, int cols, unsigned char color =
					0);

};

#endif /* DRAWER_H_ */
