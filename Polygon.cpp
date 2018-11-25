#include "pch.h"
#include "Polygon.hpp"
#include <cmath>
#include <iostream>

Polygon::Polygon(double* coordinates) {
	this->coordinates = coordinates;
}

Polygon::Polygon(double* coordinates, const int numOfCoordinates) {
	this->coordinates = coordinates;
	this->numOfCoordinates = numOfCoordinates;
}

Polygon::~Polygon() {
	
}

std::string Polygon::getType() const {
	return "Polygon";
}

double Polygon::area() {

	// Separate x and y coordinates into two arrays
	int halfSize = numOfCoordinates / 2;
	double* arrX = new double[halfSize];
	double* arrY = new double[halfSize];

	int indexEvenX = 0;
	int indexOddY = 0;
	for (int i = 0; i < halfSize; i++) {
		indexEvenX = 2 * i;
		indexOddY = 2 * i + 1;

		arrX[i] = this->coordinates[indexEvenX];
		arrY[i] = this->coordinates[indexOddY];
	}

	double area = 0.0;
	double sum = 0.0;
	int lastIndex = halfSize - 1;

	for (int i = 0; i < halfSize; i++) {
		sum += (arrX[lastIndex] + arrX[i]) *
			   (arrY[lastIndex] - arrY[i]);
		lastIndex = i;
	}

	delete[] arrX;
	delete[] arrY;

	area = abs(sum / 2.0);

	if (!isConvex())
		area = -1.0;

	return area;
}

double Polygon::circumference() {

	// Separate x and y coordinates into two arrays
	int halfSize = numOfCoordinates / 2;
	double* coordX = new double[halfSize];
	double* coordY = new double[halfSize];

	for (int i = 0; i < halfSize; i++) {
		coordX[i] = this->coordinates[2 * i];
		coordY[i] = this->coordinates[2 * i + 1];
	}

	// Add all distances from point to point
	double sum = 0.0;
	int lastValidIndex = halfSize - 1;
	int sides = 0;
	for (int i = 0; i < lastValidIndex; i++) { 
		sum += abs(sqrt(pow((coordX[i + 1] - coordX[i]), 2) + pow((coordY[i + 1] - coordY[i]), 2)));
		sides++;
	}
	sum += abs(sqrt(pow((coordX[lastValidIndex] - coordX[0]), 2) + pow((coordY[lastValidIndex] - coordY[0]), 2)));
	sides++; // Add last side

	delete[] coordX;
	delete[] coordY;

	return sum / sides;
}

Polygon::Vertex Polygon::position() {

	// Separate x and y coordinates into two arrays
	int halfSize = numOfCoordinates / 2;
	double* coordX = new double[halfSize];
	double* coordY = new double[halfSize];

	for (int i = 0; i < halfSize; i++) {
		coordX[i] = this->coordinates[2 * i];
		coordY[i] = this->coordinates[2 * i + 1];
	}

	double sumX = 0.0;
	double sumY = 0.0;
	double partialSignedArea = 0.0;
	double signedArea = 0.0;
	double centerX = 0.0;
	double centerY = 0.0;
	const int lastIndex = halfSize - 1;

	for (int i = 0; i < lastIndex; i++) {
		partialSignedArea = coordX[i] * coordY[i + 1] - coordX[i + 1] * coordY[i];
		signedArea += partialSignedArea;
		centerX += (coordX[i] + coordX[i + 1]) * partialSignedArea;
		centerY += (coordY[i] + coordY[i + 1]) * partialSignedArea;
	}

	partialSignedArea = coordX[lastIndex] * coordY[0] - coordX[lastIndex] * coordY[0];
	signedArea += partialSignedArea;

	centerX += (coordX[lastIndex] + coordX[0]) * partialSignedArea;
	centerY += (coordY[lastIndex] + coordY[0]) * partialSignedArea;
	
	signedArea /= 2.0;
	centerX /= (6.0 * signedArea);
	centerY /= (6.0 * signedArea);

	delete[] coordX;
	delete[] coordY;

	Vertex centerCoord = Vertex();
	centerCoord.x = centerX;
	centerCoord.y = centerY;

	return centerCoord;
}

bool Polygon::isConvex() {

	// Separate x and y coordinates into two arrays
	int numOfPoints = numOfCoordinates / 2;
	double* coordX = new double[numOfPoints];
	double* coordY = new double[numOfPoints];

	for (int i = 0; i < numOfPoints; i++) {
		coordX[i] = this->coordinates[2 * i];
		coordY[i] = this->coordinates[2 * i + 1];
	}

	/* To know if a polygon is convex I will calculate if the cross products of
	 * the polygon and if they are all negative or all positive, then it is convex. 
	 * 
	 * The reason to check if the cross product is positive or negative is because
	 * when it is positive the angle between two vectors will be between 0 < angle < 180
	 * and the z-vector that are perpendicular to the other two vectors will point upwards.
	 *
	 * If the angle is negative between the two vectors the angle will be between 180 < angle < 360
	 * and the z-vector that are perpendicular to the two vectors will point downwards instead. 
	 * 
	 * Depending on if the polygon is in counter-clockwise or clockwise order the cross products can
	 * be both all positive or all negative to show convexity. Otherwise it is concave.
	 */

	double zCrossProduct = 0.0;
	int allPositive = 0;
	int allNegative = 0;
	for (int k = 0; k < numOfPoints - 2; k++) {
		double dx1 = coordX[k + 1] - coordX[k];
		double dy1 = coordY[k + 1] - coordY[k];

		double dx2 = coordX[k + 2] - coordX[k + 1];
		double dy2 = coordY[k + 2] - coordY[k + 1];
		zCrossProduct = dx1 * dy2 - dy1 * dx2;

		if (zCrossProduct > 0) {
			allPositive++;
		}
		else if (zCrossProduct < 0) {
			allNegative++;
		}
	}

	// We need to calculate for the two points remaining since we only
	// go to n - 2 in the for loop above
	double nextToLastDx1 = coordX[numOfPoints - 1] - coordX[numOfPoints - 2];
	double nextToLastDy1 = coordY[numOfPoints - 1] - coordY[numOfPoints - 2];
	double nextToLastDx2 = coordX[0] - coordX[numOfPoints - 1];
	double nextToLastDy2 = coordY[0] - coordY[numOfPoints - 1];
	zCrossProduct = nextToLastDx1 * nextToLastDy2 - nextToLastDy1 * nextToLastDx2;
	if (zCrossProduct > 0) {
		allPositive++;
	}
	else if (zCrossProduct < 0) {
		allNegative++;
	}

	double dx1 = coordX[0] - coordX[numOfPoints - 1];
	double dy1 = coordY[0] - coordY[numOfPoints - 1];
	double dx2 = coordX[1] - coordX[0];
	double dy2 = coordY[1] - coordY[0];
	zCrossProduct = dx1 * dy2 - dy1 * dx2;
	if (zCrossProduct > 0) {
		allPositive++;
	}
	else if (zCrossProduct < 0) {
		allNegative++;
	}

	bool isConvex = false;
	if (allPositive == numOfPoints || allNegative == numOfPoints)
		isConvex = true;

	delete[] coordX;
	delete[] coordY;

	return isConvex;
}

double Polygon::distance(Shape& shape) {
	double distance = abs(sqrt(pow(this->position().x - shape.position().x, 2) + pow(this->position().y - shape.position().y, 2)));
	return distance;
}