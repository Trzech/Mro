/*
 * Created: 2011-02-11
 * Author : Tomasz Gaciarz
 *
 * Copyright (C) 2010 Tomasz Gaciarz.  All rights reserved.
 */

#ifndef T_Backprop_H
#define T_Backprop_H




double T_sigmoid(double in);

void print(int sample_Id, double *input, int *index, int input_size);

void reco_ranking(double * confidence, int* rank_index, int input_size);


#endif // T_Backprop_H
