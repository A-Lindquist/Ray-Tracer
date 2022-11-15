// Intersection Class
#include "Intersection.h"

// ===== INTERSECTION ===== //

// Default Constructor
Intersection::Intersection()
{
	shape = NULL;
	point = new Vertex();
	t = -1.0;
}

// Parameterized Constructor
Intersection::Intersection(Shape* shape, Vertex* point, double t)
{
	this->shape = shape;
	this->point = point;
	this->t = t;
}