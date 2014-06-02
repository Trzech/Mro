/*
 * ClusterFinderRunner.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */


#include "reader/GrayscaleImageReader.h"
#include "clusters/ClusterFinder.h"
#include "gtest/gtest.h"

class ClusterFinderRunner: public ::testing::Test {

};


TEST_F(ClusterFinderRunner, lettersClusters_draw_border) {
	GrayscaleImageReader imageReader;
	ClusterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("test/clusters/images/source/lettersClusters.pgm",
			&rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 1, 200);
	imageReader.writeImage("test/clusters/images/result/lettersClusters_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;

}

TEST_F(ClusterFinderRunner, smileWithBigCluster_draw_border) {
	GrayscaleImageReader imageReader;
	ClusterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("test/clusters/images/source/smileWithBigCluster.pgm",
			&rows, &cols);
	finder.drawBordersOfClusters(imageBuffer, rows, cols, 0, 200);
	imageReader.writeImage("test/clusters/images/result/smileWithBigCluster_result.pgm", imageBuffer,
			rows, cols);
	delete imageBuffer;

}





