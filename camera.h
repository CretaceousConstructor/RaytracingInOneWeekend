#pragma once
#include "Ray.h"
#include "colors.h"
#include "hittable.h"
#include "material.h"
#include "renderState.h"
#include "renderingState.h"
#include "sampler.h"
#include "tracer.h"
#include "MultipleObj.h"
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
	    double                _time0             = 0,
	    double                _time1             = 0);

	virtual ~camera() = default;

  public:
	virtual void render_scence(MultipleObj &world, std::ofstream &result, const renderingState &rs)      ;
	//virtual void render_scence(MultipleObj &world, MultipleObj &lights, std::ofstream &result, const renderingState &rs);
	virtual void render_scence(MultipleObj &world, std::shared_ptr<hittable>& lights, std::ofstream &result, const renderingState &rs);

	void set_tracer_ptr(std::shared_ptr<tracer> arg_tracer);

  protected:
	[[nodiscard]] virtual ray get_ray(double s, double t) const = 0;

  protected:
	TrekMath::point3 eye{};
	TrekMath::point2 lower_left_corner{};
	TrekMath::vec2   horizontal{};
	TrekMath::vec2   vertical{};
	TrekMath::vec3   u{};
	TrekMath::vec3   v{};
	TrekMath::vec3   w{};

	TrekMath::real          view_plane_distance;
	TrekMath::real          time0, time1;        // shutter open/close times
	std::shared_ptr<tracer> tracer_ptr;          //tracer used to trace scenes
};