#include "thinLens.h"

thinLens::thinLens(double aperture, double focal_plane_dis, std::unique_ptr<sampler> &&arg_samp_view_plane, std::unique_ptr<sampler> &&arg_samp_lense, TrekMath::point3 lookfrom, TrekMath::point3 lookat, TrekMath::vec3 vup, double vfov, double aspect_ratio, double _time0,
                   double _time1)

    :
    camera(lookfrom, lookat, vup, vfov, aspect_ratio, focal_plane_dis,_time0,_time1),
    lens_radius(aperture / 2.0),
    samp_on_view_plane(std::move(arg_samp_view_plane)),
    samp_on_lense(std::move(arg_samp_lense))
{
}

void thinLens::render_scence(MultipleObj &world, std::ofstream &result,const renderingState& rs)
{
#ifdef DEBUG
	std::cout << "P3\n"
	          <<rs.image_width << ' ' <<rs.image_height << "\n255\n";
#endif        // DEBUG

	result << "P3\n"
	       << rs.image_width << ' ' << rs.image_height << "\n255\n";
	for (int j = rs.image_height - 1; j >= 0; --j)
	{        //jmax  = 99   y axis goes up
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		//std::cerr << "\rScanlines remaining: " << j << ' ' << std::endl;
		for (int i = 0; i < rs.image_width; ++i)
		{        //imax = 199
			//
			//  ny(j)
			//   |
			//   |
			//   |
			//(0,0) ------>nx(i)
			color pixel_color(0, 0, 0);
			auto  samples_per_pix = samp_on_view_plane->get_num_of_samples_per_pix();
			for (int s = 0; s < samples_per_pix; ++s)
			{
				//// random_double returns a random real in [0,1]. [i+0,i+1]'s range is [image_width - 1, image_width]

				auto p = samp_on_view_plane->sample_unit_square();
				auto u = ((double) i + p.x) / ((double) rs.image_width);         //u�� ռͼƬ��ı���
				auto v = ((double) j + p.y) / ((double) rs.image_height);        //u�� ռͼƬ�ߵı���

				ray r = this->get_ray(u, v);

				pixel_color += tracer_ptr->trace_ray(r, 0);
			}

			colors::write_color(result, pixel_color, samples_per_pix);
		}
	}
	std::cerr << "\nDone.\n";
}

ray thinLens::get_ray(double s, double t) const
{
	auto           p                     = samp_on_lense->sample_unit_disk();
	TrekMath::vec2 sample_point_on_lense = lens_radius * p;
	TrekMath::vec3 offset                = u * sample_point_on_lense.x + v * sample_point_on_lense.y;

	auto           sample_point_on_view_plane = lower_left_corner + s * horizontal + t * vertical;
	TrekMath::vec3 dir                        = (sample_point_on_view_plane.x - sample_point_on_lense.x) * u + (sample_point_on_view_plane.y - sample_point_on_lense.y) * v + view_plane_distance * (-w);

	return ray(eye + offset, dir, random_double(time0, time1));

}
