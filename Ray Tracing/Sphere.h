#pragma once

#ifndef SPHERE_H
#define SPHERE_H

// Sphere Class
#include <string>
#include <cmath>
#include <algorithm>
#include "Shape.h"
#include "Vertex.h"
#include "Surface.h"
#include "Ray.h"

// ===== SPHERE ===== //
class Sphere : public Shape
{
public:

	// Attributes:
	double radius;

	// Default Constructor
	Sphere();

	// Parameterized Constructor
	Sphere(Vertex center, double radius, Surface surface);

	// Destructor
	~Sphere();

	// Get Ray Intersection
	Vertex getRayIntersection(Ray ray);

	// Get Shape Type
	std::string getType();

	// String Representation
	std::string toString();
};

#endif // !SPHERE_H
