#pragma once
#include <optional>
#include <memory>
#include <iostream>
#include <fstream>
#include "sampler.h"
#include "Ray.h"
#include "colors.h"
#include "hittable.h"
#include "world.h"
#include "material.h"
#include "renderState.h"
#include "tracer.h"
class camera {
public:
	camera() = delete;
	camera(
		TrekMath::point3 lookfrom,
		TrekMath::point3 lookat,
		TrekMath::vec3   vup,
		double vfov, // VERTICAL field-of-view in degrees
		double aspect_ratio, // one is in the same with picture we produce

		std::unique_ptr<tracer>&& arg_ray_cast,
		std::optional<double> view_dist_optional = std::nullopt
	)

		:eye(lookfrom),
		tracer_ptr(std::move(arg_ray_cast))
	{

		double view_dist;
		if (view_dist_optional.has_value()) {
			view_dist = view_dist_optional.value();
		}
		else {
			view_dist = glm::length((lookfrom - lookat));
		}


		view_plane_distance = view_dist;

		auto theta = TrekMath::degrees_to_radians(vfov);

		auto h = tan(theta / 2) * 1.0;  // assume view_length = 1.0 first

		//     /|
		//    / |
		//   /  |  h
		//  /   |
		// /-1--|--
	    // \    |
	    //  \   |
	    //	 \  |  
	    //	  \ |
	    //	   \|
		auto viewport_height = 2.0 * h;
		auto viewport_width = aspect_ratio * viewport_height; //keep proportionate with picture we are gonna produce


													//                               u(x)
		w = glm::normalize(-(lookat - lookfrom));   //                           v(y)/
		u = glm::normalize((glm::cross(vup, w)));   //                            | /
		v = glm::cross(w, u);                       //                            |/
							                        // lookat*            lookfrom*------> w(z)     										

	
		//  vertical
		//  v(y)
		// /\
		//  |
		//  |
		//  |  
		//  |
		//  |
		//  |----------->u(x)   horizontal
		//  horizontal,vertical,lower_left_corner这三个都是在标准坐标系下(  (1,0,0) (0,1,0) (0,0,1)做基底 )的向量，之后可以通过uvw转换
		//
		horizontal = view_dist * viewport_width * TrekMath::vec2(1.,0.);   //利用相似三角形
		vertical =  view_dist * viewport_height  * TrekMath::vec2(0., 1.);    //利用相似三角形
		lower_left_corner = TrekMath::vec2(0.0, 0.0) - horizontal / 2. - vertical / 2.;

	}




	virtual void render_scence(world& world, std::ofstream& result) = 0;



protected:

	virtual ray get_ray(double s, double t) const  = 0;
	TrekMath::point3 eye;
	TrekMath::point2 lower_left_corner;
	TrekMath::vec2 horizontal;
	TrekMath::vec2 vertical;
	TrekMath::vec3 u, v, w;

	std::unique_ptr< tracer> tracer_ptr;

	double view_plane_distance;



};