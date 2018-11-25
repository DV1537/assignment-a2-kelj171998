#include "pch.h"
#include "Line.hpp"
#include <cmath>

Line::Line(double x1, double y1, double x2, double y2) {
	this->startPoint.x = x1;
	this->startPoint.y = y1;

	this->endPoint.x = x2;
	this->endPoint.y = y2;
}

Line::~Line() {

}

std::string Line::getType() const {
	return "Line";
}

double Line::area() {
	return 0.0;
}

double Line::circumference() {
	return 0.0;
}

Line::Vertex Line::position() {
	Vertex middlePoint = Vertex();

	double centerX = (this->startPoint.x + this->endPoint.x) / 2.0;
	double centerY = (this->startPoint.y + this->endPoint.y) / 2.0;

	middlePoint.x = centerX;
	middlePoint.y = centerY;

	return middlePoint;
}

bool Line::isConvex() {
	return false;
}

double Line::distance(Shape& shape) {
	// Return distance to center of another shape
	// Use distance formula here
	double distance = abs(sqrt(pow(this->position().x - shape.position().x, 2) + pow(this->position().y - shape.position().y, 2)));
	return distance;
}