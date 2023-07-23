#pragma once

#include "MultipleObj.h"
#include "tracer.h"

class pathTracer : public tracer
{
  public:
	pathTracer(const MultipleObj *const world);
	[[nodiscard]] TrekMath::color trace_ray(const ray &r) const override;
	[[nodiscard]] TrekMath::color trace_ray(const ray &r, int argument_depth) const override;
	[[nodiscard]] TrekMath::color trace_ray(const ray &r, const hittable &objects, int argument_depth) const override;
	[[nodiscard]] TrekMath::color trace_ray(const ray &r, const hittable &objects, const hittable &lights, int argument_depth) const override;
	[[nodiscard]] TrekMath::color trace_ray(const ray &r, const hittable &objects, std::shared_ptr<hittable> lights, int argument_depth) const override;




};