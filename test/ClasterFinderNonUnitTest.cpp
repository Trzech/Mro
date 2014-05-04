/*
 * ClasterFinderNonUnitTest.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "ClasterFinder.h"

/*
 * HaarLikeBinarizatorTest.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "GrayscaleImageReader.h"
#include "ClasterFinder.h"
#include "gtest/gtest.h"

class ClasterFinderNonUnitTest: public ::testing::Test {

};

TEST_F(ClasterFinderNonUnitTest, DISABLED_clusters_20x20) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/clusters_20x20.pgm", &rows, &cols);
	finder.findClusters(imageBuffer, rows, cols);
	imageReader.writeImage("images/clusters_20x20_result.pgm", imageBuffer, rows, cols);
	delete imageBuffer;

	ASSERT_TRUE(1);

}

TEST_F(ClasterFinderNonUnitTest, 2_clusters) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/twoClusters.pgm", &rows, &cols);
	finder.findClusters(imageBuffer, rows, cols);
	imageReader.writeImage("images/twoClusters_result.pgm", imageBuffer, rows, cols);
	delete imageBuffer;

	ASSERT_TRUE(1);

}