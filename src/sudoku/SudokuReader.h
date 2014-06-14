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
	bool * getNumberRepresetation(char * imageFilename);

private:
	void recognizeNumbers(Cluster biggestSquareCluster,
			std::vector<Cluster> clusterInSizeOfNumbers, bool* result);
	std::vector<Cluster> getClustersInThisArea(int i , int j, int tileWidth, int tileHeiht, Cluster biggestSquareCluster, std::vector<Cluster> clusterInSizeOfNumbers);
};

#endif /* SUDOKUREADER_H_ */
