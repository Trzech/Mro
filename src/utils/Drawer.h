/*
 * Drawer.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef DRAWER_H_
#define DRAWER_H_
#include "clusters/Cluster.h"
#include "utils/Pixel.h"
#include <vector>
#include <stack>
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
	static void ereaseFirstClusterOnImageInRanges(unsigned char* imageData,
			int rows, int cols, unsigned char backgroundColor, int minX,
			int maxX, int minY, int maxY);
private:
	static void detectNeighbours(unsigned char* a, unsigned long int x,
			unsigned long int y, int cols,  std::stack<Pixel> & stack, unsigned char backgroundColor);

};

#endif /* DRAWER_H_ */
