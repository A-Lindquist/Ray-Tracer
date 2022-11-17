// Triangle Class
#include "Triangle.h"
#include <iostream>

// ===== TRIANGLE ===== //

// Default Constructor
Triangle::Triangle()
{
	v1 = Vertex();
	v2 = Vertex();
	v3 = Vertex();

	surface = Surface();

	edge_1 = v2.sub(v1);
	edge_2 = v3.sub(v2);
	edge_3 = v1.sub(v3);

	normal = (edge_1.cross(edge_2)).normalize();
}

// Parameterized Constructor
Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, Surface surface)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	this->surface = surface;

	edge_1 = this->v2.sub(this->v1);
	edge_2 = this->v3.sub(this->v2);
	edge_3 = this->v1.sub(this->v3);

	normal = (edge_1.cross(edge_2)).normalize();
}

// Null Representation
Triangle::Triangle(int null)
{
	isNull = true;
}

Triangle::~Triangle() {}

// Get Ray Intersection
Vertex Triangle::getRayIntersection(Ray ray)
{
	// Denominator
	double denom = normal.dot(ray.direction);

	// Is ray parallel to triangel?
	if (denom == 0)
		return Vertex(NULL);

	// T Value
	double t = normal.dot(v1.sub(ray.origin)) / denom;

	// No intersection?
	if (t < 0)
		return Vertex(NULL);

	// Point to Test
	Vertex point = ray.getPoint(t);

	// Point in Triangle?
	Vertex point_from_v1 = point.sub(v1);
	Vertex point_from_v2 = point.sub(v2);
	Vertex point_from_v3 = point.sub(v3);

	// Fix Normal Direction
	if (denom > 0)
		normal = normal.uniformScale(-1.0f);

	double dirA = (point_from_v1.cross(edge_1)).dot(normal);
	double dirB = (point_from_v2.cross(edge_2)).dot(normal);
	double dirC = (point_from_v3.cross(edge_3)).dot(normal);

	// Inside Triangle?
	if (((dirA > -0.001) == (dirB > -0.001)) && ((dirA > -0.001) == (dirC > -0.001)))
	{
		return point;
	}

	// Outside Triangle
	return Vertex(NULL);
}

// String Representation
std::string Triangle::toString()
{
	return "Triangle( Vertices[" + v1.toString() + ", " + v2.toString() + ", " + v3.toString() + "], "
		+ "surface: " + surface.toString() + " normal: " + normal.toString() + " )";
}

// Get Shape Type
std::string Triangle::getType()
{
	return "TRIANGLE";
}