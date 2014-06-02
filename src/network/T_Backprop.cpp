
#include "nr3.h"
#include "nn_ocr.h"

char * smaple_name = "0123456789";


//	sigmoid function
double T_sigmoid(double in)
{
	return (double)(1.0/(1.0+exp(-in)));
}

void print(int sample_Id, double *input, int *index, int input_size)
{
	std::cout.setf(ios::fixed, ios::floatfield);
	std::cout.setf(ios::showpoint);
	std::cout.precision(2);

	cout <<  smaple_name[sample_Id] << "-> ";

    for ( int i = 0; i < input_size; i++ )
		cout << index[i] << ":" << input[i] << " ";
    cout << endl;
} 

void reco_ranking(double * confidence, int* rank_index, int input_size)
{
	int i,j,maxind, maxindval;
	double maxval;

	for(j=0; j<input_size; j++) rank_index[j]=j;

	for(j=0; j<(input_size-1); j++){

		maxval = confidence[j];
		maxind = j;
		maxindval = rank_index[maxind];

		for(i=j+1; i<input_size; i++){
			if ( confidence[i] > maxval ) {	
				maxval = confidence[i];
				maxind = i;
				maxindval = rank_index[maxind];
			}
		}

		confidence[maxind] = confidence[j];
		rank_index[maxind] = rank_index[j];

		rank_index[j] = maxindval;
		confidence[j] = maxval;
	}
}

void train_nn(MatDoub &A, VecInt &A_id, double *w)
{
	int i, j;

	int xn = FEATURES_VECTOR_SIZE;
	int yn = NR_OF_CLASSES;

	double x[ FEATURES_VECTOR_SIZE ];
	double y[ NR_OF_CLASSES ];
	double d[ NR_OF_CLASSES ];
	double *W; 

	double beta = 0.3;
	double delta;
	double sum;


	//na poczatku nadajemy wagom wartosci przypadkowe
	srand((unsigned)(25));
	for (i=0; i<(xn+1)*yn; i++) { w[i] = (double)(rand())/(RAND_MAX/2);} //-1 < w[i] < 1	//sigmoid

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
		for(j=0; j<xn; j++) x[j] = A[sample_index][j];
		
		//tworzymy wektor spodziewanych na wyjsciu wartosci
		for(i=0; i<yn; i++) d[i]=0.0; d[sample_class_id]=1.0;	//sigmoid


		for(i=0; i< yn; i++){

			W = w + i*(xn+1);
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
		if ( (iter%1000 == 0) || (iter==(num_iter-1)) ) {
			
			double mse = 0;										//mean square error
			for(i=0; i< yn; i++)
				mse += (d[i]-y[i]) * (d[i]-y[i]);

			mse /= 2.0;
			cout << mse << endl;
		}

	}//for iter

}


int test_nn(MatDoub &B, VecInt &B_id, double *w)
{
	int i, j;
	double *W, sum;
	double x[ FEATURES_VECTOR_SIZE ];
	double y[ NR_OF_CLASSES ];
	int rank_index[ NR_OF_CLASSES ];
	int total_errors = 0;


	int xn = FEATURES_VECTOR_SIZE;
	int yn = NR_OF_CLASSES;

	//test na zbiorze testowym B
	int n;
	int brows = B.nrows();

	for (n=0; n<brows; n++)			//dla wszystkich probek ze zbioru testowego
	{
		for(j=0; j<xn; j++) x[j] = B[n][j];		//tworzymy wektor wejsciowy

		int sample_Id = B_id[n];

		//wyliczamy wyjscia
		for(i=0; i< yn; i++){

			W = w + i*(xn+1);					//wskaznik na wagi powiazane z danym wyjsciem
			sum=0.0;
			
			for(j=0; j<xn; j++)	 sum += W[j] * x[j];

			sum += W[xn];								
			y[i] = T_sigmoid(sum);	

		}//for i

		
		reco_ranking(y, rank_index, NR_OF_CLASSES);		//sortujemy rozpoznania od najlepszych do najgorszych

		if (sample_Id != rank_index[0] ) total_errors++;

		print(sample_Id, y, rank_index, NR_OF_CLASSES);

		if ( n>0 && (n%49 == 0) ) {
			double stop = 0;	
		}

	}//n

	return total_errors;
}
