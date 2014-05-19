/*
 * SudokuReader.h
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#ifndef SUDOKUREADER_H_
#define SUDOKUREADER_H_
#include "../haar/HaarLikeBinarizator.h"
#include "../binarization/Binarizator.h"

class SudokuReader {
public:
	SudokuReader();
	~SudokuReader();
	void process(char * inputFile, char * outputFile, int t);
private:
	void extractImportantElements(unsigned char ** source, unsigned char ** target, int rows, int cols);
};

#endif /* SUDOKUREADER_H_ */
