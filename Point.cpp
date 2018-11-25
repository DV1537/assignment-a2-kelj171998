#include "pch.h"
#include "Point.hpp"

Point::Point(double x, double y) {
	this->point.x = x;
	this->point.y = y;
}

Point::~Point() {

}

std::string Point::getType() const {
	return "Point";
}

double Point::area() {
	return 0.0;
}

double Point::circumference() {
	return 0.0;
}

Point::Vertex Point::position() {
	return this->point;
}

bool Point::isConvex() {
	return false;
}

double Point::distance(Shape& shape) {
	double distance = abs(sqrt(pow(this->position().x - shape.position().x, 2) + pow(this->position().y - shape.position().y, 2)));
	return distance;
}