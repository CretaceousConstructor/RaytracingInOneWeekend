#include "camera.h"

camera::camera(TrekMath::point3 lookfrom, TrekMath::point3 lookat, TrekMath::vec3 vup, double vfov, double aspect_ratio, std::optional<double> view_dist_optional, double _time0, double _time1)

    :
    eye(lookfrom),
    time0(_time0),
    time1(_time1)
{
	double view_dist;
	if (view_dist_optional.has_value())
	{
		view_dist = view_dist_optional.value();
	}
	else
	{
		view_dist = glm::length((lookfrom - lookat));
	}

	view_plane_distance = view_dist;

	auto theta = TrekMath::degrees_to_radians(vfov);

	auto h = tan(theta / 2) * 1.0;        // assume view_length = 1.0,then scale
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
	auto viewport_width  = aspect_ratio * viewport_height;        //keep proportionate with picture we are gonna produce

	                                                   //                               u(x)
	w = glm::normalize(-(lookat - lookfrom));        //                           v(y)/
	u = glm::normalize((glm::cross(vup, w)));      //                            | /
	v = glm::cross(w, u);                          //                            |/
	                                                   // lookat*            lookfrom*------> w(z)

	//vertical
	// v(y)
	// /\
	//  |
	//  |
	//  |
	//  |
	//  |
	//  |----------->u(x)   horizontal
	//  horizontal,vertical,lower_left_corner这三个都是在标准坐标系下(  (1,0,0) (0,1,0) (0,0,1)做基底 )的向量，之后可以通过uvw转换

	horizontal        = view_dist * viewport_width * TrekMath::vec2(1., 0.);         //利用相似三角形拉伸向量
	vertical          = view_dist * viewport_height * TrekMath::vec2(0., 1.);        //利用相似三角形拉伸向量
	lower_left_corner = TrekMath::vec2(0.0, 0.0) - horizontal / 2. - vertical / 2.;
}

//void camera::render_scence(MultipleObj &world, MultipleObj &lights, std::ofstream &result, const renderingState &rs)
//{
//	return;
//}


void camera::render_scence(MultipleObj &world, std::ofstream &result, const renderingState &rs)
{
	return;
}

void camera::render_scence(MultipleObj &world, std::shared_ptr<hittable> &lights, std::ofstream &result, const renderingState &rs)
{
	return;
}

void camera::set_tracer_ptr(std::shared_ptr<tracer> arg_tracer)
{
	tracer_ptr = std::move(arg_tracer);
}
