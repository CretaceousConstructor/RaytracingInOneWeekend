#pragma once
#include "tracer.h"
#include "MultipleObj.h"

class whitted : public tracer {
public:

	whitted(const MultipleObj* const world);
	color trace_ray(const ray& r) const override;
	color trace_ray(const ray& r, int argument_depth) const override;

};