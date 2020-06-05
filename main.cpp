#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;

	if (depth <= 0) {
		return color(0.0, 0.0, 0.0);
	}
	// shadow acne problem. solved by limiting minmum value of t to 0.001
	if (world.hit(r, 0.001, infinity, rec)) {
		//diffuse rays generated!
		point3 target = rec.p + rec.normal + random_unit_vector();
		//diffuse rays generated!
		//point3 target = rec.p + rec.normal + random_in_unit_sphere();
		//diffuse rays generated!
		//point3 target = rec.p + random_in_hemisphere(rec.normal);
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world,depth - 1);
		//more different the normals are,more different the colors  on piexls are
		//return 0.5 * (rec.normal + color(1, 1, 1));
	}

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

	hittable_list world;
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5));
	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0));


	camera cam;

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