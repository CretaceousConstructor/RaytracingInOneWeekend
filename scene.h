#pragma once

#include "camera.h"
#include "checkerTexture.h"
#include "dielectric.h"
#include "diffuse.h"
#include "hammersley.h"
#include "multiJittering.h"
#include "world.h"

#include "metal.h"
#include "movingSphere.h"
#include "pathTrace.h"
#include "pinHole.h"
#include "thinLens.h"

#include <memory>

class scene
{
  public:
	scene();
	void render(std::ofstream &result);

  private:
	world                   w;
	std::unique_ptr<camera> cam;
	void                    random_balls_scene();
	void                    two_balls_scene();
	void                    two_perlin_spheres();
	static constexpr double start_time = 0.0;
	static constexpr double end_time   = 1.0;
};
