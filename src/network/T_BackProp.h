/*
 * Created: 2011-02-11
 * Author : Tomasz Gaciarz
 *
 * Copyright (C) 2010 Tomasz Gaciarz.  All rights reserved.
 */

#ifndef T_Backprop_H
#define T_Backprop_H



void write_NN_to_text(const wchar_t* NN_file, int * buf, int size);
void write_NN(const wchar_t* NN_file, int * buf, int size);
void read_NN(const wchar_t* NN_file, int * buf, int max_size);


#endif // T_Backprop_H
