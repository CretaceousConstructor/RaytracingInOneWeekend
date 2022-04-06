#pragma once
#include "Ray.h"
#include "colors.h"
#include "hittable.h"
#include "material.h"
#include "renderState.h"
#include "sampler.h"
#include "tracer.h"
#include "world.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
class camera
{
  public:
	camera() = delete;
	camera(
	    TrekMath::point3      lookfrom,
	    TrekMath::point3      lookat,
	    TrekMath::vec3        vup,
	    double                vfov,                // VERTICAL field-of-view in degrees
	    double                aspect_ratio,        // one is in the same with picture we produce
	    std::optional<double> view_dist_optional = std::nullopt,
	    double _time0 = 0,
	    double _time1 = 0);

	virtual void render_scence(world &world, std::ofstream &result) = 0;
	void         set_tracer_ptr(std::shared_ptr<tracer> arg_tracer);

	virtual ~camera() = default;

  protected:
	virtual ray      get_ray(double s, double t) const = 0;
	TrekMath::point3 eye;
	TrekMath::point2 lower_left_corner;
	TrekMath::vec2   horizontal;
	TrekMath::vec2   vertical;
	TrekMath::vec3   u, v, w;

	double view_plane_distance;

	double                  time0, time1;        // shutter open/close times
	std::shared_ptr<tracer> tracer_ptr;
};