#include "pch.h"
#include "Triangle.hpp"
#include <cmath>
#include <iostream>

Triangle::Triangle(double startX, double startY, double middleX, double middleY, double endX, double endY) {
	this->startPoint.x = startX;
	this->startPoint.y = startY;

	this->middlePoint.x = middleX;
	this->middlePoint.y = middleY;

	this->endPoint.x = endX;
	this->endPoint.y = endY;
}

Triangle::~Triangle() {

}

std::string Triangle::getType() const {
	return "Triangle";
}

double Triangle::area() {
	double denominator = abs(startPoint.x * (middlePoint.y - endPoint.y) + 
	                         middlePoint.x * (endPoint.y - startPoint.y) +
							 endPoint.x * (startPoint.y - middlePoint.y));

	double area = denominator / 2.0;

	return area;
}

double Triangle::circumference() {

	// Distance from start point to middle point
	double distStartToMiddle = abs(sqrt(pow(this->startPoint.x - this->middlePoint.x, 2) + pow(this->startPoint.y - this->middlePoint.y, 2)));

	// Distance from middle point to end point
	double distMiddleToEnd = abs(sqrt(pow(this->middlePoint.x - this->endPoint.x, 2) + pow(this->middlePoint.y - this->endPoint.y, 2)));

	// Distance from end point to start point
	double distEndToStart = abs(sqrt(pow(this->endPoint.x - this->startPoint.x, 2) + pow(this->endPoint.y - this->startPoint.y, 2)));

	double circumference = distStartToMiddle + distMiddleToEnd + distEndToStart;

	return circumference;
}

Triangle::Vertex Triangle::position() {
	Vertex centerPoint = Vertex();

	double centerX = (this->startPoint.x + this->middlePoint.x + this->endPoint.x) / 3.0;
	double centerY = (this->startPoint.y + this->middlePoint.y + this->endPoint.y) / 3.0;

	centerPoint.x = centerX;
	centerPoint.y = centerY;

	return centerPoint;
}

bool Triangle::isConvex() {
	return true;
}

double Triangle::distance(Shape& shape) {
	double distance = abs(sqrt(pow(this->position().x - shape.position().x, 2) + pow(this->position().y - shape.position().y, 2)));
	return distance;
}