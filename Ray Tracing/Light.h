#pragma

#ifndef LIGHT_H
#define LIGHT_H

// Light Class
#include "Vertex.h"
#include <string>

class Light
{
public:
	// Attributes
	Vertex* position;
	Vertex* color;

	// Default Constructor
	Light();

	// Parameterized Constructor
	Light(Vertex* position, Vertex* color);

	// String Representation
	std::string toString();
};

#endif // LIGHT_H