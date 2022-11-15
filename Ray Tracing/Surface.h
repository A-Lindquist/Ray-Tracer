#pragma once

#ifndef SURFACE_H
#define SURFACE_H

// Surface Class
#include <string>

class Surface
{
public:

	// Surface Attributes

	// Difuesed Color
	double dr;
	double dg;
	double db;

	// Ambient Color
	double ar;
	double ag;
	double ab;

	// Specular Color
	double sr;
	double sg;
	double sb;

	// Properties
	double spec_power;
	double k_refl;


	// Defaulat Constructor
	Surface();

	// Parameterized Constructor
	Surface(double dr, double dg, double db, double ar, double ag, double ab, double sr, double sg, double sb, double spec_power, double k_refl);

	// To String
	std::string toString();
};

#endif // !SURFACE_H

