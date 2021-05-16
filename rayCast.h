#pragma once

#include "tracer.h"
class rayCast : public tracer {


public:
	rayCast(const world* const world);
	

	virtual color trace_ray(const ray& r) const override;
	virtual color trace_ray(const ray& r, int argument_depth) const override;


};