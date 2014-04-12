/*
 * SudokuReader.cpp
 *
 *  Created on: 12 kwi 2014
 *      Author: mj
 */

#include "SudokuReader.h"

SudokuReader::SudokuReader() {


}

SudokuReader::~SudokuReader() {
	// TODO Auto-generated destructor stub
}

void SudokuReader::process(char* inputFile, char* outputFile) {
	int rows;
	int cols;
	unsigned char* imageBuffer;
	imageBuffer = imageReader.readDataFromFile(inputFile, &rows, &cols);
	unsigned char** source;
	source = Binarizator::prepareTableForOperations(imageBuffer, rows, cols);
	unsigned char* resultBuffer;
	if ((resultBuffer = new unsigned char[(rows) * (cols)]) == NULL) {
		throw -1;
	}
	unsigned char** target;
	target = Binarizator::prepareTableForOperations(resultBuffer, rows, cols);

	extractImportantElements(source, target, rows, cols);

	imageReader.writeImage(outputFile, resultBuffer, rows, cols);
	delete imageBuffer;
	delete resultBuffer;
	delete[] source;
	delete[] target;
}

void SudokuReader::extractImportantElements(unsigned char** source,
		unsigned char** target, int rows, int cols) {


}
