#include "bbox.h"

bool bbox::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const
{
	double ox = r.origin().x;
	double oy = r.origin().y;
	double oz = r.origin().z;
	double dx = r.direction().x;
	double dy = r.direction().y;
	double dz = r.direction().z;

	double tx_min;
	double ty_min;
	double tz_min;

	double tx_max;
	double ty_max;
	double tz_max;

	double a = 1. / dx;

	if (a >= 0.) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else
	{
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}


	double b = 1. / dy;

	if (b >= 0.) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}						 
	else
	{
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}





	double c = 1. / dz;

	if (c >= 0.) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else
	{
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}


	double t0,t1;

	t0 = std::max({ tx_min, ty_min, tz_min });
	t1 = std::min({ tx_max, ty_max, tz_max });

	return (t0 < t1 && t1 > kEpsilon); //needs to take t_min and t_max into account;

}

std::string bbox::objectType() const
{
	return std::string("bbox");
}
