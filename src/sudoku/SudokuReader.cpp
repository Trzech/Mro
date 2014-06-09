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

void SudokuReader::process(char* inputFile, char* outputFile, int t) {

}

void SudokuReader::getSudokuStringRepresentation(unsigned char* a, int rows,
		int cols, unsigned char backgroundColor, int minX, int maxX, int minY,
		int maxY, double treshold = 0.98) {
	bool isNotEmpty[9][9] = { false };
	printf("\n");
	int tileWidth = round((maxX - minX) / 9.0);
	int tileHeight = round((maxY - minY) / 9.0);

	int baseOfFrame = minY*cols + minX;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			int backgroundPixels = 0;
			int baseOfTile = baseOfFrame + i * tileHeight * cols + j * tileWidth;
			for (int x = 0; x < tileWidth; ++x) {
				for (int y = 0; y < tileHeight; ++y) {
					if(a[baseOfTile + y*cols + x]==backgroundColor){
						backgroundPixels++;
					}
				}
			}

			if (backgroundPixels / (1.0 * tileHeight * tileWidth) < treshold) {
				isNotEmpty[i][j] = true;
			}
		}
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			printf(isNotEmpty[i][j] ? "number " : "empty ");
		}
		printf("\n");

	}
	printf("\n");
}

void SudokuReader::extractImportantElements(unsigned char** source,
		unsigned char** target, int rows, int cols) {

}

