#pragma once

#ifndef INTERSECTION_H
#define INTERSECTION_H

// Intersection Class
#include "Shape.h"
#include "Vertex.h"

// ===== TRIANGLE ===== //
class Intersection
{
public:

	// Attributes:
	Shape* shape = nullptr;
	Vertex point;
	double t;

	// Default Constructor
	Intersection();

	// Parameterized Constructor
	Intersection(Shape* shape, Vertex point, double t);

	// Destructor
	~Intersection();
};

#endif // !INTERSECTION_H
