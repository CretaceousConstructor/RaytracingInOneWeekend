#pragma once

#include "AABB.h"

#include <memory>
#include <string>

class hittable
{
  protected:
	hittable();
	hittable(std::shared_ptr<material> arg_mat_ptr);
	virtual ~hittable() = default;

  public:
	virtual bool        hit(const ray &r, double t_min, double t_max, shadeRec &sr) const = 0;
	virtual bool        bounding_box(double time0, double time1, AABB &output_box) const;
	virtual std::string objectType() const                                                = 0;

  public:
	virtual bool             shadow_hit(const ray &r, double &t_shadow) const;
	virtual TrekMath::point3 sample();
	virtual TrekMath::normal get_normal(const TrekMath::point3 &p);
	virtual double           pdf(shadeRec &sr);

  public:
	std::shared_ptr<material> get_mat_ptr();
	void                      set_shadows_object(bool arg_shadows);
	void                      set_material(std::shared_ptr<material> arg_mat);
	//virtual bbox get_bounding_box();
  protected:
	bool                      shadows;
	std::shared_ptr<material> mat_ptr = nullptr;
};