// Sphere Class
#include "Sphere.h"

// ===== SPHERE ===== //

// Default Constructor
Sphere::Sphere()
{
	center = Vertex();
	radius = 0.0;
	surface = Surface();
}

// Parameterized Constructor
Sphere::Sphere(Vertex center, double radius, Surface surface)
{
	this->center = center;
	this->radius = radius;
	this->surface = surface;
}

// Destructor
Sphere::~Sphere() {}

// Get Ray Intersection
Vertex Sphere::getRayIntersection(Ray ray)
{
	Vertex distance = ray.origin.sub(center);

	// Setup for Quadratic Equation
	double a = ray.direction.dot(ray.direction);
	double b = 2 * distance.dot(ray.direction);
	double c = distance.dot(distance) - (radius * radius);

	double discriminant = (b * b) - (4 * a * c);

	// Valid discriminant?
	if (discriminant >= 0)
	{
		//Quadratic Formula:
		double additive = (-b + sqrt(discriminant)) / (2 * a);
		double subtractive = (-b - sqrt(discriminant)) / (2 * a);

		// Return closest Ray|Sphere intersection
		double t = std::min(additive, subtractive);
		if (t >= 0)
			return ray.getPoint(t);
	}

	// Invalid Intersection
	return Vertex(NULL);
}

// String Representation
std::string Sphere::toString()
{
	return "Sphere( center: " + center.toString() + ", radius: " + std::to_string(radius) + ", surface: " + surface.toString() + " )";
}

// Get Shape Type
std::string Sphere::getType()
{
	return "SPHERE";
}