#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.hpp"

class Polygon : public Shape {
	double* coordinates;
	int numOfCoordinates;

public:
	Polygon(double* coordinates);
	Polygon(double* coordinates, const int numOfCoordinates);
	virtual ~Polygon();

	std::string getType() const override;
	double area() override;
	double circumference() override;
	Vertex position() override;
	bool isConvex() override;
	double distance(Shape& shape) override;
};

#endif
