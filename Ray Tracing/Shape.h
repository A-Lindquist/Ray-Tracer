#pragma once

#ifndef SHAPE_H
#define SHAPE_H

// Shape Class
#include "Vertex.h"
#include "Ray.h"
#include "Surface.h"

// ===== SHAPE ===== //
class Shape
{
public:
	
	// Attribute
	Surface surface;

	bool isNull = false;

	Vertex normal; // for triangles
	Vertex center; // for spheres

	// Get Ray Intersection
	virtual Vertex getRayIntersection(Ray ray) = 0;

	// Get Shape Type
	virtual std::string getType() = 0;

	// String Representation
	virtual std::string toString() = 0;
};

#endif // !SHAPE_H
