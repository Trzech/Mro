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
#include <math.h>

class SudokuReader {
public:
	SudokuReader();
	~SudokuReader();
	void process(char * inputFile, char * outputFile, int t);
	void getSudokuStringRepresentation(unsigned char* a, int rows,
			int cols, unsigned char backgroundColor, int minX, int maxX, int minY,
			int maxY, double treshold);
private:
	void extractImportantElements(unsigned char ** source, unsigned char ** target, int rows, int cols);
};

#endif /* SUDOKUREADER_H_ */
