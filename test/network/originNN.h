/*
 * originNN.h
 *
 *  Created on: 14 cze 2014
 *      Author: aldor
 */

#ifndef ORIGINNN_H_
#define ORIGINNN_H_
#include "network/nr3.h"
#include "utils/exception.h"


int read_int_feature_vectors_from_file(const char* fname, long all_feature_vectors_size, int* buf)
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
template <class T1>
void normalizacja_Macierzy_w_wierszach(T1 &R)
{
	int iw, ik;
	iw=R.nrows();
	ik=R.ncols();

	for(int i=0;i<iw;i++)
	{
		double s=0.0;

		// obliczenie i-tego wiersza i jego normy
		for(int j=0;j<ik;j++)
			s+=R[i][j]*R[i][j];

		// normalizacja i-tego wiersza
		s = sqrt(s);
		for(int j=0;j<ik;j++)
		{
			R[i][j]/=s;
		}

	}
}
MatDoub read_test_data(const char * filename, const int features_vector_size, const int nr_of_test_sampels_per_class, const int nr_of_classes) {
	//wczytanie wektorow cech probek testowych
	int nr_of_vectors = nr_of_test_sampels_per_class * nr_of_classes;
	int i,j;
	int *data_buf = new int[nr_of_vectors * features_vector_size];
	if ( !read_int_feature_vectors_from_file(filename,
		nr_of_vectors * features_vector_size, data_buf) )
		throw MroException("read eror");

		//tworzymy macierz z wektorami probek testowych i wektor powiazanych z nimi indeksow (0 - 9)
		MatDoub B(nr_of_vectors, features_vector_size);

		for(i=0;  i < nr_of_vectors;  i++){
			for(j=0;  j < features_vector_size;  j++){
				B[i][j] = data_buf[i*features_vector_size + j];
			}
		}

		delete [] data_buf;



		//wektor wag dla trenowanej sieci neuronowej
		return B;



}



#endif /* ORIGINNN_H_ */
