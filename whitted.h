#pragma once
#include "tracer.h"
#include "renderState.h"

class whitted : public tracer {
public:

	whitted(const world* const world);
	color trace_ray(const ray& r) const override;
	color trace_ray(const ray& r, int argument_depth) const override;

};