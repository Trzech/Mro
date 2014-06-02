#include <iostream>
using namespace std;


int partition(double* input, int* index, int p, int r)
{
    double pivot = input[r];

    while ( p < r )
    {
        //while ( input[p] < pivot )
		while ( input[p] > pivot )
            p++;

        //while ( input[r] > pivot )
		while ( input[r] < pivot )
            r--;

        if ( input[p] == input[r] )
            p++;
        else if ( p < r )
        {
            double tmp = input[p];
            input[p] = input[r];
            input[r] = tmp;

            index[p] = r;
            index[r] = p;
        }
    }

    return r;
}

void quicksort(double* input, int* index, int p, int r)
{
    if ( p < r )
    {
        int j = partition(input, index, p, r);        
        quicksort(input, index, p, j-1);
        quicksort(input, index, j+1, r);
    }
}


/*
void quicksort(double* tablica, int *index, int x, int y)
{
	double temp,v;
	int i,j;
	i=x;
	j=y;
	v= tablica[(x+y)/2];
	do
	{
		while (tablica[i]>v) i++;
		while (v>tablica[j]) j--;
		if (i<=j)
		{
			temp=tablica[i];
			tablica[i]=tablica[j];
			tablica[j]=temp;
			index[i] = j;
			index[j] = i;
			i++;
			j--;
		}
	}
	while (i<=j);
	if (x<j) quicksort(tablica,index, x,j);
	if (i<y) quicksort(tablica,index, i,y);
}
*/
