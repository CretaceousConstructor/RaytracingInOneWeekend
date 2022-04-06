#pragma once

#include "tracer.h"
class areaLighting : public tracer {
public:
	areaLighting(const world* const world);


	virtual color trace_ray(const ray& r ) const override;
	virtual color trace_ray(const ray& r,  int argument_depth) const override;

};