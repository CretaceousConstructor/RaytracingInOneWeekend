#pragma once

#include "tracer.h"

#include "world.h"


class pathTrace : public tracer
{
  public:
	pathTrace(const world *const world);
	TrekMath::color trace_ray(const ray &r) const override;
	TrekMath::color trace_ray(const ray &r, int argument_depth) const override;
};