#pragma once

#include "MultipleObj.h"
#include "box.h"
#include "camera.h"
#include "checker_texture.h"
#include "constant_medium.h"
#include "dielectric.h"
#include "diffuse.h"
#include "diffuse_light.h"
#include "hammersley.h"
#include "image_texture.h"
#include "instance.h"
#include "metal.h"
#include "movingSphere.h"
#include "multiJittering.h"
#include "noise_texture.h"
#include "pathTracer.h"
#include "pinHole.h"
#include "rectangle.h"
#include "renderingState.h"
#include "sphere.h"
#include "thinLens.h"
#include <memory>

using std::make_shared;
using std::make_unique;

class scene
{
  public:
	scene();
	void render(std::ofstream &result);

  private:
	MultipleObj world;
	std::shared_ptr<hittable> lights;

	std::unique_ptr<camera> cam;
	void                    random_balls_scene();
	void                    two_balls_scene();
	void                    two_perlin_spheres();
	void                    sphere_texture_scene();
	void                    rectangle_scene();
	void                    cornell_box();
	void                    testing_scene();
	void                    cornell_smoke();
	void                    final_scene();

	color backgroundcolor{0., 0., 0.};

	static constexpr double start_time = 0.0;
	static constexpr double end_time   = 1.0;

	renderingState renstate;
};
