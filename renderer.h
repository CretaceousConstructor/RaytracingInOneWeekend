#pragma once


#include "scene.h"
#include <fstream>
#include <iostream>
#include <memory>
//#include "cuda_runtime.h"
//#include "./cuda_kernel.cuh"
//#include "./cuda_kernel.cuh"

class Renderer
{
  public:
	Renderer();
	void StartToRender();
	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;
	Renderer(Renderer &&)                 = delete;
	Renderer &operator=(Renderer &&) = delete;
	~Renderer();


  private:
	scene         first_scene;
	std::ofstream result;

	static constexpr double start_time{0.0};
	static constexpr double end_time{1.0};
};
