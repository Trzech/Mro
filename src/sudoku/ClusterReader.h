/*
 * ClusterReader.h
 *
 *  Created on: Jun 14, 2014
 *      Author: yuriy
 */

#ifndef CLUSTERREADER_H_
#define CLUSTERREADER_H_

#include <iostream>
#include <vector>

class ClusterReader {
public:
	ClusterReader();
	~ClusterReader();
	std::vector<double> getPropertiesVector(unsigned char* imageData, int rows, int cols);
	void rescale_image(unsigned char **a, unsigned char **b, int h1, int w1, int h2, int w2);
	void set_feature_vector(unsigned char **a, int h, int w, int n_y, int n_x, int* f_v, unsigned char tlo);
};




#endif /* CLUSTERREADER_H_ */
