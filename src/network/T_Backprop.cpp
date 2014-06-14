
#include "nr3.h"

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

