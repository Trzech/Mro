/*
 * NeuralNetwork.h
 *
 *  Created on: 2 cze 2014
 *      Author: aldor
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "network/T_BackProp.h"
#include <vector>
#include <string>

#define	NR_OF_CLASSES	10
#define	NR_OF_TRAINING_SAMPLES_PER_CLASS	100
#define	NR_OF_TEST_SAMPLES_PER_CLASS	50
#define	FEATURES_VECTOR_SIZE	15



class NeuralNetwork {
private:
	const  int m_nr_of_classes;
	int m_number_of_traning_samples_per_class;
	int m_number_of_test_samples_per_class;
	const int m_features_vector_size;
	double * m_weight;
	void normalizeVector(std::vector<double> &data) const;
	template<class T1>
	void normalizeMatrixInRows(T1 &R) const;
	int read_int_feature_vectors_from_file(const char* fname, long all_feature_vectors_size, int* buf) const;
public:
	NeuralNetwork(int feauters_vector_size = FEATURES_VECTOR_SIZE, int nr_of_classes = NR_OF_CLASSES);
	virtual ~NeuralNetwork();
	void readAndLearn(std::string filename, long traning_samples_per_class = NR_OF_TRAINING_SAMPLES_PER_CLASS);
	template <class T1, class T2>
	void learn(T1&, T2&);
	template <class T1>
	std::vector<int> find(T1&) const;
	int find(std::vector<double>&) const;
};

#endif /* NEURALNETWORK_H_ */
