/*
 * NeuralNetwork.cpp
 *
 *  Created on: 2 cze 2014
 *      Author: aldor
 */
#include <stdio.h>

#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(int nn_of_classes = 10, int nn_of_traning_sample_per_class = 100,
		int features_vector_size = 15): m_numbers_of_classes(10) {

	m_number_of_traning_samples_per_class = nn_of_traning_sample_per_class;
	m_feautures_vector_size = features_vector_size;


	// TODO Auto-generated constructor stub

}

NeuralNetwork::~NeuralNetwork() {
	// TODO Auto-generated destructor stub
}G_SAMPLES_PER_CLASS	100
#define	NR_OF_TEST_SAMPLES_PER_CLASS	50
#define	FEATURES_VECTOR_SIZE	15


void NeuralNetwork::learn(char * fname, int nr_of_vectors) {
	int nr_v_size = nr_of_vectors *	m_feautures_vector_size;
	int * features_vector = new int[nr_v_size];
	if (! read_int_feature_vectors_from_file(fname, nr_v_size, features_vector)) {
		throw "Read fom file error";
	}
	MatDoub learnData(nr_of_vectors, m_feautures_vector_size);
	VecInt learnData_index(nr_of_vectors);

	for (int i = 0; i < nr_of_vectorsl i++)
		for (int j = 0; j< m_feautures_vector_size; j++) {
			learnData[i][j] = features_vector[i * m_feauters_vector_size + j];
			learnData_index[i] = i/NR_OF
		}



}

int NeuralNetwork::read_int_feature_vectors_from_file(char* fname, long all_feature_vectors_size, int* buf)
{
	FILE *fp;
	if((fp=fopen(fname, "rb")) == NULL)
		return 0;

	fseek(fp, 0, SEEK_END);
    long flen = ftell(fp);	//file lenght
	fseek(fp, 0, SEEK_SET);


	int required_file_size = all_feature_vectors_size*sizeof(int);
	if (required_file_size != flen)
		return -1;

	int readed_freature_vectors = fread((char*)buf, flen, 1, fp);

	fclose(fp);

	if(readed_freature_vectors != 1)
		return -1;

	return readed_freature_vectors;
}
