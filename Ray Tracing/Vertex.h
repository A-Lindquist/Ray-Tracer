#pragma once

#ifndef VERTEX_H
#define VERTEX_H

// Vertex Class
#include <string>
#include <cmath>

// ===== VERTEX ===== //
class Vertex
{
public:

	// Attributes:
	double x;
	double y;
	double z;

	// color 
	double r;
	double g;
	double b;

	bool isNull = false;

	// Default Constructor
	Vertex();

	// Parameterized Constructor
	Vertex(double x, double y, double z);

	// Null Representation
	Vertex(int null);

	// Destructor
	~Vertex();

	// String Representation
	std::string toString();

	// Vertex Addition
	Vertex add(Vertex other);

	// Vertex Subtraction
	Vertex sub(Vertex other);

	// Vertex Dot Product
	double dot(Vertex other);

	// Vertex Cross Product
	Vertex cross(Vertex other);

	// Vertex Uniform Scale (vertex * int)
	Vertex uniformScale(double scalar);

	// Vertex Euclidean Distance
	double distance(Vertex other);

	// Normalize Vertex
	Vertex normalize();
};

#endif // !VERTEX_H
