/*
 * NeuralNetwork.cpp
 *
 *  Created on: 2 cze 2014
 *      Author: aldor
 */
#include <stdio.h>

#include "utils/exception.h"

#include "network/NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(int features_vector_size, int nn_of_classes): m_nr_of_classes(nn_of_classes),
	m_features_vector_size(features_vector_size)
{

   m_weight = new double[(m_features_vector_size + 1) * m_nr_of_classes];


}
void  NeuralNetwork::normalizeMatrixInRows(MatDoub &R) const
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
void NeuralNetwork::normalizeVector(std::vector<double> &data) const{

	int ik;
	ik =  data.size();

	double s=0.0;
	// obliczenie i-tego wiersza i jego normy
	for(int j=0;j<ik;j++) {
		s += data[j] * data[j];
		s = sqrt(s);
		data[j]/=s;
	}


}



NeuralNetwork::~NeuralNetwork() {

   delete[] m_weight;
}

void NeuralNetwork::learn(MatDoub &A, VecInt &A_id)
{
        int i, j;

        int xn = m_features_vector_size;
        int yn = m_nr_of_classes;

        double x[ m_features_vector_size ];
        double y[ m_nr_of_classes ];
        double d[ m_nr_of_classes ];
        double *W;

        double beta = 0.3;
        double delta;
        double sum;


        //na poczatku nadajemy wagom wartosci przypadkowe
        srand((unsigned)(25));
        for (i=0; i<(xn+1)*yn; i++) { m_weight[i] = (double)(rand())/(RAND_MAX/2);} //-1 < w[i] < 1	//sigmoid

        int arows = A.nrows();

        //learning
        long num_iter = 300000;	//ilosc losowo wybieranych probek ze zbioru uczacego, prezentowanych sieci

        srand((unsigned)(27));

        for (int iter=0; iter<num_iter; iter++)
        {
                //wybieramy losowo probke ze zbioru treningowego A i uczymy siec
                int sample_index = rand() % arows;
                int sample_class_id = A_id[sample_index];
                //tworzymy wektor wejsciowy
                for ( j = 0; j<xn; j++) x[j] = A[sample_index][j];
                //tworzymy wektor spodziewanych na wyjsciu wartosci
                for(i=0; i<yn; i++)
                        d[i]=0.0;
                d[sample_class_id]=1.0;	//sigmoid

                for(i=0; i< yn; i++) {

                        W = m_weight + i*(xn+1);
                        sum=0;
                        for(j=0; j<xn; j++)
                                sum += W[j] * x[j];

                        sum += W[xn];										//dodajemy bias
                        //sigmoidalna funkcja przejscia
                        y[i] = T_sigmoid(sum);								//obliczmy odpowiedz na wyjsciu y[i]
                        delta = y[i]*(1.0-y[i]) * (d[i]-y[i]);				//obliczamy blad delta
                        for(j=0; j<xn; j++)									//korygujemy wagi
                                W[j] += beta*delta*x[j];

                        W[xn] += beta*delta;

                }//for i


                //co n-ta probke wypisujemy blad sieci
/*                if ( (iter%1000 == 0) || (iter==(num_iter-1)) ) {
                        for(i=0; i< yn; i++)
                                mse += (d[i]-y[i]) * (d[i]-y[i]);

                        mse /= 2.0;

                        //std::cout <<"blad sieci "<< mse << std::endl;
                }
*/
        }//for iter

}



int NeuralNetwork::find(std::vector<double>& data) const {


	normalizeVector(data);
	int i, j;

    double *W, sum;
    double  * x  = new double[ data.size() ];
    double y[ m_nr_of_classes ];
    int rank_index[ m_nr_of_classes ];


    int xn = data.size();// m_features_vector_size;
    int yn = m_nr_of_classes;

	//test na zbiorze testowym B

	for(j=0; j<xn; j++)
			x[j] = data[j];		//tworzymy wektor wejsciowy
	for(i=0; i< yn; i++) {
					W = m_weight + i*(xn+1);					//wskaznik na wagi powiazane z danym wyjsciem
					sum=0.0;
					for(j=0; j<xn; j++)
							sum += W[j] * x[j];

					sum += W[xn];
					y[i] = T_sigmoid(sum);

	}//for i
	reco_ranking(y, rank_index, m_nr_of_classes);		//sortujemy rozpoznania od najlepszych do najgorszych
	delete [] x;
	return rank_index[0];
}



std::vector<int> NeuralNetwork::find(MatDoub& data) const{
	int i, j;
	std::vector<int> result;
	normalizeMatrixInRows(data);
	double *W, sum;
	double x[ m_features_vector_size ];
	double y[ m_nr_of_classes ];
	int rank_index[ m_nr_of_classes ];


	int xn = m_features_vector_size;
	int yn = m_nr_of_classes;

	//test na zbiorze testowym B
	int n;
	int brows = data.nrows();

	for (n=0; n<brows; n++)			//dla wszystkich probek ze zbioru testowego
	{
			for(j=0; j<xn; j++) x[j] = data[n][j];		//tworzymy wektor wejsciowy
	//	int sample_Id = B_id[n];
			//wyliczamy wyjscia
			for(i=0; i< yn; i++) {
					W = m_weight + i*(xn+1);					//wskaznik na wagi powiazane z danym wyjsciem
					sum=0.0;
					for(j=0; j<xn; j++)
						sum += W[j] * x[j];

					sum += W[xn];
					y[i] = T_sigmoid(sum);

			}//for i
			reco_ranking(y, rank_index, m_nr_of_classes);		//sortujemy rozpoznania od najlepszych do najgorszych
			//rank_index wyniki?
			result.push_back(rank_index[0]);
			//if (sample_Id != rank_index[0] ) total_errors++;
	//	print(sample_Id, y, rank_index, m_nr_of_classes);

	}//n
    return result;
}




void NeuralNetwork::readAndLearn(std::string filename, long traning_samples_per_class) {

	long nr_of_vectors = traning_samples_per_class * m_nr_of_classes;

	int * data_buf = new int[nr_of_vectors * m_features_vector_size];
	read_int_feature_vectors_from_file(filename.c_str(), nr_of_vectors * m_features_vector_size, data_buf);
	MatDoub learn_data(nr_of_vectors, m_features_vector_size);
 	VecInt learn_ID(nr_of_vectors);

 	int i,j;

 	for(i=0;  i < nr_of_vectors;  i++){
 		for(j=0;  j < m_features_vector_size;  j++){
 				learn_data[i][j] = data_buf[i*m_features_vector_size + j];
 			}
 			learn_ID[i] = i/traning_samples_per_class;
 	}

 	delete [] data_buf;
 	normalizeMatrixInRows(learn_data);
 	learn(learn_data, learn_ID);



}


int NeuralNetwork::read_int_feature_vectors_from_file(const char* fname, long feature_vector_size, int* buf) const
{
	FILE *fp;
	if((fp=fopen(fname, "rb")) == NULL)
		throw MroException("File not found!");

	fseek(fp, 0, SEEK_END);
    long flen = ftell(fp);	//file lenght
	fseek(fp, 0, SEEK_SET);


	long required_file_size = feature_vector_size *sizeof(int);
	if (required_file_size != flen) {
		fclose(fp);
		printf("requred: %f, actual: %f", required_file_size, flen);
		throw MroException("Size of file doesnt match required file size!");
	}
	long readed_freature_vectors = fread((char*)buf, flen, 1, fp);

	fclose(fp);

	if(readed_freature_vectors != 1)
		throw MroException("Unable to read!");

	return readed_freature_vectors;
}
