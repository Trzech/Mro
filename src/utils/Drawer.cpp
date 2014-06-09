/*
 * Drawer.cpp
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#include <utils/Drawer.h>

void Drawer::drawClusterBorderOnImage(std::vector<Cluster>& clusters,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		drawClusterBorderOnImage(clusters[i], imageData, rows, cols, color);
	}
}

void Drawer::drawClusterBorderOnImage(Cluster& cluster,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	int baseMin = cluster.minY * cols;
	int baseMax = cluster.maxY * cols;
	for (int j = cluster.minX; j <= cluster.maxX; ++j) {
		imageData[baseMin + j] = color;
		imageData[baseMax + j] = color;
	}

	for (int j = cluster.minY; j <= cluster.maxY; ++j) {
		imageData[j * cols + cluster.minX] = color;
		imageData[j * cols + cluster.maxX] = color;
	}
}

void Drawer::drawSudokuMeshInClusterBorderOnImage(Cluster& cluster,
		unsigned char* imageData, int rows, int cols, unsigned char color) {
	//int baseMax = cluster.maxY * cols;

	int baseMin = cluster.minY * cols;
	int tileWidth = round(cluster.getWidth() / 9.0);
	int tileHeight = round(cluster.getHeight() / 9.0);
	for (int i = 0; i <= 9; ++i) {
		int localBaseMin = baseMin + i * cols * tileHeight;

		for (int j = cluster.minX; j <= cluster.minX + 9 * tileWidth; ++j) {
			imageData[localBaseMin + j] = color;
		}

		for (int j = cluster.minY; j <= cluster.minY + 9 * tileHeight; ++j) {
			imageData[j * cols + cluster.minX + i * tileWidth] = color;

		}

	}

}
inline void Drawer::detectNeighbours(unsigned char* a, unsigned long int x,
		unsigned long int y, int cols, std::stack<Pixel> & stack,
		unsigned char backgroundColor) {
	if (a[y * cols + x] != backgroundColor) {
		stack.push(Pixel(x, y));
		a[y * cols + x] = backgroundColor;
	}
}
void Drawer::ereaseFirstClusterOnImageInRanges(unsigned char* a, int rows,
		int cols, unsigned char backgroundColor, int minX, int maxX, int minY,
		int maxY) {
	// TODO: this solution is only temporary! It is one big copy/paste from ClusterFinder
	std::stack<Pixel> stack;
	Pixel pixel(0, 0);
	for (unsigned long int i = minY; i <= maxY; ++i) {
		for (unsigned long int j = minX; j <= maxX; ++j) {
			if (a[i * cols + j] != backgroundColor) {
				a[i * cols + j] = backgroundColor;
				pixel.y = i;
				pixel.x = j;
				stack.push(pixel);

				while (!stack.empty()) {
					pixel = stack.top();
					stack.pop();

					unsigned long int x = pixel.x - 1;
					unsigned long int y = pixel.y - 1;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

					x = pixel.x + 1;
					y = pixel.y - 1;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

					x = pixel.x;
					y = pixel.y - 1;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

					x = pixel.x - 1;
					y = pixel.y;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

					x = pixel.x + 1;
					y = pixel.y;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

					x = pixel.x - 1;
					y = pixel.y + 1;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

					x = pixel.x;
					y = pixel.y + 1;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

					x = pixel.x + 1;
					y = pixel.y + 1;
					if (a[y * cols + x] != backgroundColor) {
						stack.push(Pixel(x, y));
						a[y * cols + x] = backgroundColor;
					}

				}
				return;

			}

		}

	}
}

