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

TEST_F(ClasterFinderNonUnitTest, zGimpa) {
	GrayscaleImageReader imageReader;
	ClasterFinder finder;
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile("images/clusterPico.pgm", &rows, &cols);
	finder.findClusters(imageBuffer, rows, cols);
	imageReader.writeImage("images/twoClustersWynik.pgm", imageBuffer, rows, cols);
	delete imageBuffer;

	ASSERT_TRUE(1);

}
