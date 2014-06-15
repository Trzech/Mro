/*
 * ClusterReaderUnitTest.cp
 *
 *  Created on: Jun 14, 2014
 *      Author: yuriy
 */
#include "sudoku/ClusterReader.h"
#include "gtest/gtest.h"

class ClusterReaderUnitTest: public ::testing::Test {

};

TEST_F(ClusterReaderUnitTest, WhenFeatureVectorIsCorrect) {

	unsigned char* imageData = new unsigned char[10*20];

	for(int i=0; i < 200; i++) {
		imageData[i] = 255;
	}

	int rows = 10;
	int cols = 20;

	ClusterReader cr;
	std::vector<double> fv = cr.getPropertiesVector(imageData,rows,cols);

	double result = 0;

	std::vector<double>::iterator it;
    for( it=fv.begin(); it!=fv.end(); ++it ) {
	 result += *it;
    }

    ASSERT_EQ(0, result);
}


