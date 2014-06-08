/*
 * Cluster.cpp
 *
 *  Created on: 28 kwi 2014
 *      Author: mj
 */

#include "Cluster.h"

Cluster::Cluster() {
	minX = UINT_MAX;
	minY = UINT_MAX;
	maxX = 0;
	maxY = 0;
	size = 0;

}

Cluster::~Cluster() {
	// TODO Auto-generated destructor stub
}

void Cluster::addPoint(unsigned int x, unsigned int y) {
	this->size++;
	if (x > this->maxX) {
		this->maxX = x;
	}
	if (x < this->minX) {
		this->minX = x;
	}
	if (y > this->maxY) {
		this->maxY = y;
	}
	if (y < this->minY) {
		this->minY = y;
	}
}

unsigned int Cluster::getWidth() {
	return this->maxX - this->minX + 1;
}

unsigned int Cluster::getHeight() {
	return this->maxY - this->minY + 1;
}

unsigned int Cluster::getSize() {
	return getWidth()*getHeight();
}

double Cluster::getRatio() {
	double width = 1.0 * getWidth();
	double height = 1.0 * getHeight();
	return width / height;
}
