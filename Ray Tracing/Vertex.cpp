// Vertex Class
#include "Vertex.h"
#include <iostream>

// ===== VERTEX ===== //

// Default Constructor
Vertex::Vertex()
{
	x = 0, y = 0, z = 0;
	r = x, g = y, b = z;
}
	
// Parameterized Constructor
Vertex::Vertex(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	r = x, g = y, b = z;
}

// Null Representation
Vertex::Vertex(int null)
{
	isNull = true;
}

Vertex::~Vertex() {}

// String Representation
std::string Vertex::toString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// Vertex Addition
Vertex Vertex::add(Vertex other)
{
	return Vertex(this->x + other.x, this->y + other.y, this->z + other.z);
}

// Vertex Subtraction
Vertex Vertex::sub(Vertex other)
{
	return Vertex(this->x - other.x, this->y - other.y, this->z - other.z);
}

// Vertex Dot Product
double Vertex::dot(Vertex other)
{
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

// Vertex Cross Product
Vertex Vertex::cross(Vertex other)
{
	double i = (this->y * other.z) - (this->z * other.y);
	double j = (this->z * other.x) - (this->x * other.z);
	double k = (this->x * other.y) - (this->y * other.x);
	return Vertex(i, j, k);
}

// Vertex Uniform Scale (vertex * int)
Vertex Vertex::uniformScale(double scalar)
{
	return Vertex(this->x * scalar, this->y * scalar, this->z * scalar);
}

// Vertex Euclidean Distance
double Vertex::distance(Vertex other)
{
	double i = (other.x - this->x) * (other.x - this->x);
	double j = (other.y - this->y) * (other.y - this->y);
	double k = (other.z - this->z) * (other.z - this->z);
	return sqrt(i + j + k);
}

// Normalize Vertex
Vertex Vertex::normalize()
{
	double length = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	return Vertex(this->x / length, this->y / length, this->z / length);
}