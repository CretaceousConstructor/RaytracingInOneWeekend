#pragma once
#include "tracer.h"

#include "MultipleObj.h"


class globalTrace : public tracer {
public:
	globalTrace(const MultipleObj* const world);
	TrekMath::color trace_ray(const ray& r) const override;
	TrekMath::color trace_ray(const ray& r, int argument_depth) const override;

};