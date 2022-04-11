#include "pinHole.h"

pinHole::pinHole(std::unique_ptr<sampler> &&arg_viewPlaneSampler, TrekMath::point3 lookfrom, TrekMath::point3 lookat, TrekMath::vec3 vup, double vfov, double aspect_ratio, std::optional<double> view_dist_optional, double _time0, double _time1) 
	:
    camera(lookfrom, lookat, vup, vfov, aspect_ratio, view_dist_optional),
    sampler_of_view_plane(std::move(arg_viewPlaneSampler))
{
}

void pinHole::render_scence(world &world, std::ofstream &result)
{
#ifdef DEBUG
	std::cout << "P3\n"
	          << DefaultRenderState::image_width << ' ' << DefaultRenderState::image_height << "\n255\n";
#endif        // DEBUG

	result << "P3\n"
	       << DefaultRenderState::image_width << ' ' << DefaultRenderState::image_height << "\n255\n";

	for (int j = DefaultRenderState::image_height - 1; j >= 0; --j)
	{        //jmax  = 99   y axis goes up
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		//std::cerr << "\rScanlines remaining: " << j << ' ' << std::endl;
		for (int i = 0; i < DefaultRenderState::image_width; ++i)
		{        //imax = 199
			//
			//  ny(j)
			//   |
			//   |
			//   |
			//(0,0)------>nx(i)
			TrekMath::color pixel_color(0, 0, 0);

			auto samples_per_set = sampler_of_view_plane->get_num_of_samples_per_pix();

			for (int s = 0; s < samples_per_set; ++s)
			{
				//// random_double returns a random real in [0,1]. [i+0,i+1] 最大[image_width - 1, image_width]

				auto p = sampler_of_view_plane->sample_unit_square();

				auto u = ((double) i + p.x) / ((double) DefaultRenderState::image_width);         //u是 占图片宽的比例
				auto v = ((double) j + p.y) / ((double) DefaultRenderState::image_height);        //v是 占图片高的比例

				ray r = this->get_ray(u, v);
				pixel_color += tracer_ptr->trace_ray(r, 0);
			}

			colors::write_color(result, pixel_color, samples_per_set);
		}
	}
	std::cerr << "\nDone.\n";
}

ray pinHole::get_ray(double s, double t) const
{
	auto           sample_point_on_view_plane = lower_left_corner + s * horizontal + t * vertical;
	TrekMath::vec3 dir                        = (sample_point_on_view_plane.x - 0.0) * u + (sample_point_on_view_plane.y - 0.0) * v + view_plane_distance * (-w);

	return ray(eye, dir,random_double(time0, time1));


}
