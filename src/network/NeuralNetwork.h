/*
 * NeuralNetwork.h
 *
 *  Created on: 2 cze 2014
 *      Author: aldor
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

class NeuralNetwork {
public:
	NeuralNetwork();
	virtual ~NeuralNetwork();
	int read_int_feature_vectors_from_file(char* fname, long all_feature_vectors_size, int* buf);
};

#endif /* NEURALNETWORK_H_ */
