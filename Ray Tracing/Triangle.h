#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

// Triangle Class
#include <string>
#include "Shape.h"
#include "Vertex.h"
#include "Surface.h"
#include "Ray.h"

// ===== TRIANGLE ===== //
class Triangle : public Shape
{
public:

	// Attributes:
	Vertex v1;
	Vertex v2;
	Vertex v3;

	Vertex edge_1;
	Vertex edge_2;
	Vertex edge_3;

	// Default Constructor
	Triangle();

	// Parameterized Constructor
	Triangle(Vertex v1, Vertex v2, Vertex v3, Surface surface);

	// Null Representation
	Triangle(int null);

	// Destructor
	~Triangle();

	// Get Ray Intersection
	Vertex getRayIntersection(Ray ray);

	// Get Shape Type
	std::string getType();

	// String Representation
	std::string toString();
};

#endif // !TRIANGLE_H
