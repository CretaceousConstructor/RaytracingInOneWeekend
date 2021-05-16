#pragma once

#include "world.h"
#include "colors.h"
#include "shadeRec.h"
class tracer {

public:

	tracer() =delete;
	tracer(const world* const world)

		:world_ptr(world)
	{

	}



	virtual color trace_ray(const ray& r ) const = 0;
	virtual color trace_ray(const ray& r, int argument_depth) const = 0;


protected:

	const world* world_ptr;



};