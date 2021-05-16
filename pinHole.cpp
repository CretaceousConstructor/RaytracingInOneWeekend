#include "pinHole.h"

void pinHole::render_scence(world& world, std::ofstream& result)
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
			auto view_plane_samples_per_pixel =  samp_on_view_plane->get_num_of_samples_per();
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

ray pinHole::get_ray(double s, double t) const
{

	auto sample_point_on_view_plane = lower_left_corner + s * horizontal + t * vertical;

	TrekMath::vec3 dir = (sample_point_on_view_plane.x - 0.0) * u + (sample_point_on_view_plane.y - 0.0) * v - view_plane_distance * w;


	return ray(eye, dir);
}

