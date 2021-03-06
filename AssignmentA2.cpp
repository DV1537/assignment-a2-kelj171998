// AssignmentA2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <crtdbg.h>  
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Triangle.hpp"
#include "Polygon.hpp"

double* ReadFileAndStoreValues(std::string fileName, int& numOfElements);
void IdentifyShapeToCalcArea(double coordinates[], const int numOfElements);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int num = 0;
	double* arr = ReadFileAndStoreValues("poly.txt", num);
	IdentifyShapeToCalcArea(arr, num);

	delete[] arr;

	getchar();
}

void IdentifyShapeToCalcArea(double coordinates[], const int numOfElements) {
	Shape* shape = nullptr;

	/* These numbers are how many coordinates the file has 
	 * both x and y coordinates are counted.
	 */
	const int numOfCoordsForPoint = 2;
	const int numOfCoordsForLine = 4;
	const int numOfCoordsForTriangle = 6;

	if (numOfElements == numOfCoordsForPoint) {
		shape = new Point(coordinates[0], coordinates[1]);
	}
	else if (numOfElements == numOfCoordsForLine) {
		shape = new Line(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
	}
	else if (numOfElements == numOfCoordsForTriangle) {
		shape = new Triangle(coordinates[0], coordinates[1], coordinates[2], coordinates[3], coordinates[4], coordinates[5]);
	}
	else {
		shape = new Polygon(coordinates, numOfElements);
	}

	const double MAX_DECIMALS = 1000.0;
	std::cout << "Input: ";
	for (int i = 0; i < numOfElements; i++) {
		std::cout << round(MAX_DECIMALS * coordinates[i]) / MAX_DECIMALS << " ";
	}

	std::cout << "\tArea: " << round(MAX_DECIMALS * shape->area()) / MAX_DECIMALS << std::endl;

	delete shape;
}

double* ReadFileAndStoreValues(std::string fileName, int& numOfElements) {
	std::ifstream file = std::ifstream(fileName);

	if (file.fail()) {
		std::cout << "Error: Couldn't open file!";
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	double readNum = 0.0;
	int currentSize = 2;
	double* coordinates = new double[currentSize];
	while (file >> readNum) {

		if (numOfElements < currentSize) {
			coordinates[numOfElements] = readNum;
		}
		else {
			double* tempCopy = new double[currentSize + numOfElements];

			// Copy array
			for (int i = 0; i < numOfElements; i++) {
				tempCopy[i] = coordinates[i];
			}
			delete[] coordinates;
			coordinates = nullptr;

			coordinates = tempCopy;
			currentSize += numOfElements;

			coordinates[numOfElements] = readNum;
		}
		numOfElements++;
	}

	file.close();

	if (numOfElements % 2 != 0) {
		std::cout << "Error: Wrong file format!";
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	return coordinates;
}
