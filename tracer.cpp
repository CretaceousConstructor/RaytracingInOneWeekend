#include "tracer.h"

tracer::tracer(const MultipleObj *const world)

    :
    world_ptr(world)
{
}

void tracer::set_back_ground_color(color c)
{
	background = c;
}
