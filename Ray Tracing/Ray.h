#pragma once

#ifndef RAY_H
#define RAY_H

// Ray Class
#include "Vertex.h"
#include <string>

// ===== RAY ===== //
class Ray
{
public:

	// Attributes
	Vertex origin;
	Vertex direction;

	// Default Constructor
	Ray();

	// Parameterized Constructor
	Ray(Vertex origin, Vertex direction);

	// Destructor
	~Ray();

	// String Representation
	std::string toString();

	// Get Point Intersection
	Vertex getPoint(double t);
};

#endif // !RAY_H
