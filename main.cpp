#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include "material.h"




//process: ray bounces few times(maybe 20 times),then not hitting anything, background color returned
//the for every bounce, attenuation is multiplyed by background color returned
color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;



	//too many bounces
	if (depth <= 0) {
		return color(0.0, 0.0, 0.0);
	}

	// shadow acne problem. solved by limiting minmum value of t to 0.001
	if (world.hit(r, 0.001, infinity, rec)) {
		
		ray scattered;
		color attenuation;
		shared_ptr<material> mat = rec.mat_ptr;

		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		//doesn't scatter
		return color(0, 0, 0);
	}

	//if the ray Didn't hit anything
	//using interpolation to generate background color or envirenment lighting
	//if the ray didn't hit anything,background color will be returned;
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}




int main() {

	const auto aspect_ratio = (double)16 / (double)9;
	const int image_width = 384;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	//     ---------
	//     |       |
	//     |       |
	//     ---------

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	auto R = cos(pi / 4);
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, make_shared<lambertian>(color(.1, .2, .5))));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, make_shared<lambertian>(color(.8, .8, 0.))));
	world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, make_shared<metal>(color(.8, .6, .2), 0.3)));
	world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, make_shared<dielectric>(1.5)));
	world.add(make_shared<sphere>(point3(-1, 0, -1), -0.45, make_shared<dielectric>(1.5)));


	point3 lookfrom(3, 3, 2);
	point3 lookat(0, 0, -1);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture =0.5;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	for (int j = image_height - 1; j >= 0; --j) {   //jmax  = 99   y axis goes up
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {     //imax = 199
			//   
			//  ny(j)
			//   |
			//   |
			//   |
			//   ------>nx(i)
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				//// Returns a random real in [0,1). [i+0,i+1)
				auto u = (i + random_double()) / ((double)image_width - 1.0);
				auto v = (j + random_double()) / ((double)image_height - 1.0);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}

			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}