/*
 * Created: 2011-11-04
 * Author : Tomasz G¹ciarz
 * 
 * Copyright (C) 2011.  All rights reserved.
 */

#if !defined(DEF_TPGM)
#define DEF_TPGM

int readPGMB_header(char *fname, int *rows, int *cols, int *max_color);
int readPGMB_data(unsigned char *image, char *fname, int hlen, int rows, int cols, int max_color);
int writePGMB_image(char *fname, unsigned char *image, int rows,  int cols, int max_color);

int readPPMB_header(char *fname, int *rows, int *cols, int *max_color);
int readPPMB_data(unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, char *fname, int hlen, int rows, int cols, int max_color);
int writePPMB_image(char *fname, unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, int rows,  int cols, int max_color);

#endif
