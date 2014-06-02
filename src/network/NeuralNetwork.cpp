/*
 * NeuralNetwork.cpp
 *
 *  Created on: 2 cze 2014
 *      Author: aldor
 */

#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {
	// TODO Auto-generated constructor stub

}

NeuralNetwork::~NeuralNetwork() {
	// TODO Auto-generated destructor stub
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
