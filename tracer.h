#pragma once





#include "tracer.fwd.h"
#include "world.fwd.h"


#include "colors.h"
#include "renderState.h"
#include "shadeRec.h"
#include "material.h"
//#include "hittable.h"


class tracer
{
  public:
	tracer() = delete;
	tracer(const world *const world);
	virtual ~tracer() = default;

	virtual color trace_ray(const ray &r) const                     = 0;
	virtual color trace_ray(const ray &r, int argument_depth) const = 0;
	void set_back_ground_color(color c);

  protected:
	const world *world_ptr;


//std::shared_ptr<hittable> world_ptr;




	color        background{0.70, 0.80, 1.00};


};