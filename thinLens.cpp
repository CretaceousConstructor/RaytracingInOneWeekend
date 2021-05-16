#include "thinLens.h"

TrekMath::vec3 thinLens::ray_direction(const TrekMath::point2& pixel_point, const TrekMath::point2& lens_point) const 
{

	//这里的pixel point和lense point都是在标准坐标系下的点，之后再通过uvw的组合转换到我们需要摄像机坐标系内的向量
   TrekMath::point2 p;//hit point on focal plane

   p.x = pixel_point.x * focal_plane_distance / view_plane_distance;
   p.y = pixel_point.y * focal_plane_distance / view_plane_distance;

   TrekMath::vec3 dir = (p.x - lens_point.x)* u +  (p.y - lens_point.y) * v - focal_plane_distance * w;

	

   return dir;




}

void thinLens::render_scence(world& world, std::ofstream& result)
{



#ifdef DEBUG
	std::cout << "P3\n" << renderState::image_width << ' ' << renderState::image_height << "\n255\n";
#endif // DEBUG

	result << "P3\n" << renderState::image_width << ' ' << renderState::image_height << "\n255\n";
	for (int j = renderState::image_height - 1; j >= 0; --j) {   //jmax  = 99   y axis goes up
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		//std::cerr << "\rScanlines remaining: " << j << ' ' << std::endl;
		for (int i = 0; i < renderState::image_width; ++i) {     //imax = 199
			//   
			//  ny(j)
			//   |
			//   |
			//   |
		 //(0,0) ------>nx(i)
			color pixel_color(0, 0, 0);
			auto view_plane_samples_per_pixel = samp_on_view_plane->get_num_of_samples_per();
			for (int s = 0; s < view_plane_samples_per_pixel; ++s) {
				//// random_double returns a random real in [0,1]. [i+0,i+1] 最大[image_width - 1, image_width]

				auto p = samp_on_view_plane->sample_unit_square();
				auto u = ((double)i + p.x) / ((double)renderState::image_width); //u是 占图片宽的比例
				auto v = ((double)j + p.y) / ((double)renderState::image_height);//u是 占图片高的比例

				ray r = this->get_ray(u, v);
				//pixel_color += ray_color(r, world, renderState::max_depth);

				pixel_color += tracer_ptr->trace_ray(r);

			}

			colors::write_color(result, pixel_color, view_plane_samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";



}
//
//color thinLens::ray_color(const ray& r, const hittable& argument_world, int argument_depth)
//{
//	hit_record rec;
//
//	//too many bounces
//	if (argument_depth <= 0) {
//		return TrekMath::color(0.0, 0.0, 0.0);
//	}
//
//	// shadow acne problem. solved by limiting minmum value of t to 0.001
//	if (argument_world.hit(r, epsilon, infinity, rec)) {
//
//		ray scattered;
//		color attenuation;
//		shared_ptr<material> mat = rec.mat_ptr;
//
//
//
//		//ray r      ray scattered
//		//   \      /
//		//    \    /
//		//     \  /
//		//      \/
//		//------------------
//		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
//		{
//			return attenuation * ray_color(scattered, argument_world, argument_depth - 1);
//		}
//		//doesn't scatter,some crazy material like metal,see code here:
//		return TrekMath::color(0, 0, 0);
//	}
//
//	//if the ray Didn't hit anything
//	//using interpolation to generate background color or envirenment lighting
//	//if the ray didn't hit anything,background color will be returned;
//	vec3 unit_direction = glm::normalize((r.direction()));
//	auto t = 0.5 * (unit_direction.y + 1.0);
//	return (1.0 - t) * TrekMath::color(1.0, 1.0, 1.0) + t * TrekMath::color(0.5, 0.7, 1.0);
//}

ray thinLens::get_ray(double s, double t) const
{
	auto p = samp_on_lense->sample_unit_disk();
	TrekMath::vec2 sample_point_on_lense = lens_radius * p;
	TrekMath::vec3 offset = u * sample_point_on_lense.x + v * sample_point_on_lense.y;

	auto sample_point_on_view_plane = lower_left_corner + s * horizontal + t * vertical;
	auto dir = ray_direction(sample_point_on_view_plane, sample_point_on_lense);


	dir = glm::normalize(dir);
	return ray(eye + offset,dir);
}
