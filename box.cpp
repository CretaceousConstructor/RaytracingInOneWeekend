#include "box.h"

box::box(TrekMath::point3 p0, TrekMath::point3 p1)
	:
	x0(p0.x), y0(p0.y), z0(p0.z), x1(p1.x), y1(p1.y), z1(p1.z)
{
}

bool box::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const
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

	double t0, t1;
	int face_in, face_out;

	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.) ? 0 : 3;

	}

	else {
		t0 = ty_min;
		face_in = (b >= 0.) ? 1 : 4;
	}


	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (c > 0.) ? 2 : 5;
	}


	if (tx_max < ty_max) {
		t1 = tx_max;
		face_out = (a >= 0.) ? 3 : 0;

	}

	else {
		t1 = ty_max;
		face_out = (b >= 0.) ? 4 : 1;

	}


	if (tz_max < t1) {
		t1 = tz_max;
		face_out = (c >= 0.) ? 5 : 2;
	}

	double tmin;
	TrekMath::normal tempNor;

	if (t0 < t1 && t1 > kEpsilon) {
		if (t0 > kEpsilon) {	
			tmin = t0;
			tempNor = get_face_nornal(face_in);
		}
		else {
			tmin = t1;
			tempNor = get_face_nornal(face_out);
		}

		sr.set_front_face_and_normal(r, tempNor);
		sr.hitPoint = r.point_at_parameter(tmin);
		sr.t = tmin;
		sr.local_hitPoint = sr.hitPoint;
		sr.hit_an_object = true;
		sr.mat_ptr = mat_ptr;

		return true;
	}
	else {
		return false;
	}



}

std::string box::objectType() const
{
	return std::string("box");
}

TrekMath::normal box::get_face_nornal(const int face_int) const
{
	switch (face_int)
	{
	case 0: return (TrekMath::normal(-1., 0., 0.)); // -x
	case 1: return (TrekMath::normal(0., -1., 0.)); // -y
	case 2: return (TrekMath::normal(0., 0., -1.)); // -z
	case 3: return (TrekMath::normal(1., 0., 0.));	  // x
	case 4: return (TrekMath::normal(0., 1., 0.));	  // y
	case 5: return (TrekMath::normal(0., 0., 1.));	  // z
	}
}
