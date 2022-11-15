// Light Class
#include "Light.h"

// ===== LIGHT ===== //

// Default Constructor
Light::Light()
{
	position = new Vertex();
	color = new Vertex();
}

// Parameterized Constructor
Light::Light(Vertex* position, Vertex* color)
{
	this->position = position;
	this->color = color;
}

// String Representation
std::string Light::toString()
{
	return "LIGHT: [Position: " + position->toString() + "  |  (Color: " + color->toString() + "]";
}