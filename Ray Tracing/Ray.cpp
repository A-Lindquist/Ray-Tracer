// Ray Class
#include "Ray.h"

// ===== RAY ===== //

// Default Constructor
Ray::Ray()
{
	origin = new Vertex();
	direction = new Vertex();
}

// Parameterized Constructor
Ray::Ray(Vertex* origin, Vertex* direction)
{
	this->origin = origin;
	this->direction = direction->normalize();
}

// String Representation
std::string Ray::toString()
{
	return "[Origin: " + origin->toString() + "  |  (Direction: " + direction->toString() + "]";
}

// Get Point Intersection
Vertex* Ray::getPoint(double t)
{
	double dx = direction->x;
	double dy = direction->y;
	double dz = direction->z;

	double x = origin->x + (t * dx);
	double y = origin->y + (t * dy);
	double z = origin->z + (t * dz);

	return new Vertex(x, y, z);
}