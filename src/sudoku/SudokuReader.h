/*
 * SudokuReader.h
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#ifndef SUDOKUREADER_H_
#define SUDOKUREADER_H_
#include "reader/GrayscaleImageReader.h"
#include "binarization/SauvolaBinarizator.h"
#include "clusters/ClusterFinder.h"
#include "clusters/ClusterAnalizator.h"
#include "utils/Drawer.h"
class SudokuReader {
public:
	SudokuReader();
	~SudokuReader();
	double * getNumberRepresetation(char * imageFilename);
	unsigned char* geTileData(unsigned char* imageData,int cols, Cluster& cluster);

private:
	void recognizeNumbers(unsigned char* imageData, int rows, int cols, Cluster biggestSquareCluster,
			std::vector<Cluster> clusterInSizeOfNumbers, double* result);
	std::vector<Cluster> getClustersInThisArea(int i , int j, int tileWidth, int tileHeiht, Cluster biggestSquareCluster, std::vector<Cluster> clusterInSizeOfNumbers);
};

#endif /* SUDOKUREADER_H_ */
