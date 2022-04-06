#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include "sampler.h"
#include "world.h"
#include "sphere.h"
#include "colors.h"
#include "camera.h"
#include "pinHole.h"
#include "thinLens.h"
#include "areaLighting.h"
#include "material.h"
#include "rectangle.h"
#include "nrooks.h"
#include "hammersley.h"
#include "multiJittering.h"
#include "renderState.h"
#include "rayCast.h"
#include "ambient.h"
#include "pointLight.h"
#include "areaLight.h"
#include "ambientOccluder.h"
#include "matte.h"
#include "phong.h"
#include "emissive.h"
#include "environmentLight.h"
#include "triangle.h"
#include "box.h"
#include "disk.h"
#include "torus.h"
#include "whitted.h"
#include "reflective.h"
#include "glossyReflector.h"
#include "pathTrace.h"
#include "globalTrace.h"
#include "transparent.h"
#include "diffuse.h"
#include "metal.h"
#include "dielectric.h"
#include "movingSphere.h"
//#include "cuda_runtime.h"
//#include "./cuda_kernel.cuh"
//#include "./cuda_kernel.cuh"

class renderer {


public:
	renderer();
	void startToRender();
	void cleanUp();
private:


	world w;
	std::unique_ptr<camera> cam;
	std::ofstream result;
	

};


