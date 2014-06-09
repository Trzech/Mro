/*
 * NeuralNetwork.h
 *
 *  Created on: 2 cze 2014
 *      Author: aldor
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_
define NN_OCR_H

#define	NR_OF_CLASSES	10
#define	NR_OF_TRAINING_SAMPLES_PER_CLASS	100
#define	NR_OF_TEST_SAMPLES_PER_CLASS	50
#define	FEATURES_VECTOR_SIZE	15



class NeuralNetwork {
private:
	const  int m_numbers_of_classes;
	int m_number_of_traning_samples_per_class;
	int m_number_of_test_samples_per_class;
	int m_feautures_vector_size;
public:
	NeuralNetwork();
	virtual ~NeuralNetwork();

	int read_int_feature_vectors_from_file(char* fname, long all_feature_vectors_size, int* buf);
};

#endif /* NEURALNETWORK_H_ */
