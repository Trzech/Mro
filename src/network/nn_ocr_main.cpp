/*
 * Created: 2012-12-11
 * Author : Tomasz Gaciarz
 *
 * Copyright (C) 2012 Tomasz Gaciarz.  All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include "nr3.h"
#include "nn_ocr.h"

void train_nn(MatDoub &A, VecInt &A_id, double *w);
int test_nn(MatDoub &B, VecInt &B_id, double *w);


int read_int_feature_vectors_from_file(char* fname, long all_feature_vectors_size, int* buf)
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

void normalizacja_Macierzy_w_wierszach(MatDoub &R)
{
	int iw, ik;
	iw=R.nrows();
	ik=R.ncols();
	
	for(Int i=0;i<iw;i++)
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

/*
int main (int argc,char *argv[])
{
	int nr_of_vectors = NR_OF_TRAINING_SAMPLES_PER_CLASS * NR_OF_CLASSES;

	//wczytanie wektorow cech probek treningowych
	int *data_buf = new int[nr_of_vectors * FEATURES_VECTOR_SIZE];

	if ( !read_int_feature_vectors_from_file("nauka_cyfry5x3.dat",
		nr_of_vectors *	FEATURES_VECTOR_SIZE, data_buf) )
		return -1;


	//tworzymy macierz z wektorami probek treningowych i wektor powiazanych z nimi indeksow (0 - 9)
	MatDoub A(nr_of_vectors, FEATURES_VECTOR_SIZE);
	VecInt A_ID(nr_of_vectors);
	
	int i,j;
	
	for(i=0;  i < nr_of_vectors;  i++){
		
		
		for(j=0;  j < FEATURES_VECTOR_SIZE;  j++){
				A[i][j] = data_buf[i*FEATURES_VECTOR_SIZE + j];
			}
			A_ID[i] = i/NR_OF_TRAINING_SAMPLES_PER_CLASS;
	}

	delete [] data_buf;

	//wczytanie wektorow cech probek testowych
	nr_of_vectors = NR_OF_TEST_SAMPLES_PER_CLASS * NR_OF_CLASSES;

	data_buf = new int[nr_of_vectors * FEATURES_VECTOR_SIZE];

	if ( !read_int_feature_vectors_from_file("testy_cyfry5x3.dat",
		nr_of_vectors * FEATURES_VECTOR_SIZE, data_buf) )
		return -1;

	//tworzymy macierz z wektorami probek testowych i wektor powiazanych z nimi indeksow (0 - 9)
	MatDoub B(nr_of_vectors, FEATURES_VECTOR_SIZE);
	VecInt B_ID(nr_of_vectors);

	for(i=0;  i < nr_of_vectors;  i++){
		for(j=0;  j < FEATURES_VECTOR_SIZE;  j++){
			B[i][j] = data_buf[i*FEATURES_VECTOR_SIZE + j];
		}
		B_ID[i] = i/NR_OF_TEST_SAMPLES_PER_CLASS;
	}

	delete [] data_buf;
	

	normalizacja_Macierzy_w_wierszach(A);
	normalizacja_Macierzy_w_wierszach(B);

	//wektor wag dla trenowanej sieci neuronowej
	double w[ (FEATURES_VECTOR_SIZE+1)*NR_OF_CLASSES ];		//+1 dodatkowe wejscie dla biasu
	
	train_nn(A, A_ID, w);
	int errors = test_nn(B, B_ID, w);

	return 0;
}
*/
