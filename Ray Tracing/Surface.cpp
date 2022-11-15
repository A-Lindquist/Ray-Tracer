// Surface Class
#include "Surface.h"

// ===== SURFACE ===== //

// Defaulat Constructor
Surface::Surface()
{
	dr = 0;
	dg = 0;
	db = 0;

	ar = 0;
	ag = 0;
	ab = 0;

	sr = 0;
	sg = 0;
	sb = 0;

	spec_power = 0;
	k_refl = 0;
}

// Parameterized Constructor
Surface::Surface(double dr, double dg, double db, double ar, double ag, double ab, double sr, double sg, double sb, double spec_power, double k_refl)
{
	this->dr = dr;
	this->dg = dg;
	this->db = db;

	this->ar = ar;
	this->ag = ag;
	this->ab = ab;

	this->sr = sr;
	this->sg = sg;
	this->sb = sb;

	this->spec_power = spec_power;
	this->k_refl = k_refl;
}

// To String
std::string Surface::toString()
{
	return "Surface(" + std::to_string(dr) + ", " + std::to_string(dg) + ", " + std::to_string(db) + ", "
		+ std::to_string(ar) + ", " + std::to_string(ag) + ", " + std::to_string(ab) + ", "
		+ std::to_string(sr) + ", " + std::to_string(sg) + ", " + std::to_string(sb) + ", "
		+ std::to_string(spec_power) + ", " + std::to_string(k_refl) + ")";
}