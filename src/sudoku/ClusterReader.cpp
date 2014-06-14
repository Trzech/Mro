/*
 * ClusterReader.cpp
 *
 *  Created on: Jun 14, 2014
 *      Author: yuriy
 */

#include "ClusterReader.h"

ClusterReader::ClusterReader() {

}

ClusterReader::~ClusterReader() {
	// TODO Auto-generated destructor stub
}

std::vector<double> ClusterReader::getPropertiesVector(unsigned char* imageData, int rows, int cols) {

	int h2,w2;

	h2 = 90;
	w2 = 45;

	unsigned char  *outBuf = new unsigned char[h2*w2];

	unsigned char ** a =  new unsigned char* [rows];
	unsigned char ** b =  new unsigned char* [h2];

	for (int i=0; i< rows ; ++i){
		a[i] = imageData + i * cols;		//tablica wejsciowa
	}

	for (int i=0; i< h2 ; ++i){
		b[i] = outBuf + i * w2;		//tablica wyjsciowa
	}

	rescale_image(a, b, rows, cols, h2, w2);

	int f_v[5*3];
	set_feature_vector(b, h2, w2, 5, 3, f_v, 255);


	std::vector<double> result;

	for(int i=0; i < 15; ++i) {
		result.push_back((double)f_v[i]);
	}

	delete[] b;

	return  result;
}

void ClusterReader::rescale_image(unsigned char **a, unsigned char **b, int h1, int w1, int h2, int w2) {

	int y1,x1,y2,x2;
	float scale_x = (float)w1/(float)w2;
	float scale_y = (float)h1/(float)h2;

	for (y2=0; y2<h2 ; y2++){
		y1 = (int)(y2*scale_y + 0.5);
		if ( y1>(h1-1) ) y1--;

		for (x2=0; x2<w2 ; x2++){
			x1 = (int)(x2*scale_x + 0.5);
			if ( x1>(w1-1) ) x1--;

			b[y2][x2] = a[y1][x1];

		}//for x
	}//for y
}

void ClusterReader::set_feature_vector(unsigned char **a, int h, int w, int n_y, int n_x, int* f_v, unsigned char tlo) {
	int i,j, y1,y2,x1,x2,y,x;
		int n_h = h/n_y;	//wysokosc pojedynczego obszaru
		int n_w = w/n_x;	//szerokosc pojedynczego obszaru


		for (i=0; i< (n_y*n_x); i++) f_v[i] = 0;

		for (i=0; i<n_y; i++){
			for (j=0; j<n_x; j++){

				y1 = i*n_h; y2 = y1+n_h;
				x1 = j*n_w; x2 = x1+n_w;

				for (y=y1; y<y2; y++){
					for (x=x1; x<x2; x++){

						if ( a[y][x] != tlo )
							f_v[i*n_x + j] += 1;

					}//for x
				}//for y

			}//for j
		}//for i
}
