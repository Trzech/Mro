/*
 * SudokuReader.h
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#ifndef SUDOKUREADER_H_
#define SUDOKUREADER_H_
#include "GrayscaleImageReader.h"
#include "Binarizator.h"

class SudokuReader {
public:
	SudokuReader();
	~SudokuReader();
	void process(char * inputFile, char * outputFile);
private:
	GrayscaleImageReader imageReader;
	void extractImportantElements(unsigned char ** source, unsigned char ** target, int rows, int cols);
};

#endif /* SUDOKUREADER_H_ */
