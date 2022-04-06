#pragma once

#include "colors.h"
#include "renderState.h"
#include "shadeRec.h"
#include "world.h"
class tracer
{
  public:
	tracer() = delete;
	tracer(const world *const world);
	virtual ~tracer() = default;

	virtual color trace_ray(const ray &r) const                     = 0;
	virtual color trace_ray(const ray &r, int argument_depth) const = 0;

  protected:
	const world *world_ptr;
};