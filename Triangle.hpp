#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.hpp"

class Triangle : public Shape {
	Vertex startPoint;
	Vertex middlePoint;
	Vertex endPoint;
	const double PI = 3.14159;

public:
	Triangle(double startX, double startY, 
			 double middleX, double middleY, 
			 double endX, double endY);

	virtual ~Triangle();

	std::string getType() const override;
	double area() override;
	double circumference() override;
	Vertex position() override;
	bool isConvex() override;
	double distance(Shape& shape) override;
};

#endif