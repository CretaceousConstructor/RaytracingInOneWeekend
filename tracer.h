#pragma once

#include "tracer.fwd.h"
#include "world.fwd.h"

#include "colors.h"
#include "hittable.h"
#include "material.h"
#include "renderState.h"
#include "shadeRec.h"

class tracer
{
  public:
	tracer() = delete;
	tracer(const MultipleObj *const world);
	virtual ~tracer() = default;

	[[nodiscard]] virtual color trace_ray(const ray &r) const                                              = 0;
	[[nodiscard]] virtual color trace_ray(const ray &r, int argument_depth) const                          = 0;
	[[nodiscard]] virtual color trace_ray(const ray &r, const hittable &objects, int argument_depth) const = 0;
	[[nodiscard]] virtual color trace_ray(const ray &r, const hittable &objects, const hittable &lights, int argument_depth) const = 0;

	[[nodiscard]] virtual color trace_ray(const ray &r, const hittable &objects, std::shared_ptr<hittable> lights, int argument_depth) const = 0;

	void set_back_ground_color(color c);

  protected:
	const MultipleObj *world_ptr;

	//std::shared_ptr<hittable> world_ptr;

	color background{0.70, 0.80, 1.00};



};