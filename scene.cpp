#include "scene.h"

scene::scene()
{
	//two_balls_scene();
	//two_perlin_spheres();
	//sphere_texture_scene();
	//rectangle_scene();
	cornell_box();
	//cornell_box_testing();
	//================================================================================================

	std::shared_ptr<tracer> tracer_p = std::make_shared<pathTrace>(&w);
	tracer_p->set_back_ground_color(backgroundcolor);

	w.set_tracer_ptr(tracer_p);
	cam->set_tracer_ptr(tracer_p);
}

void scene::render(std::ofstream &result)
{
	cam->render_scence(w, result, renstate);
}

void scene::random_balls_scene()
{
	backgroundcolor = color(0.70, 0.80, 1.00);
	cam =
	    make_unique<thinLens>(
	        0.1,         //aperture
	        10.0,        //view plane distance
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        std::make_unique<multiJittering>(renstate.lense_samples_per_pixel, renstate.lense_sample_sets),

	        TrekMath::point3(13., 2., 3.),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        start_time,
	        end_time);

	auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

	w.add_object(make_shared<sphere>(point3(0., -1000., 0.), 1000., make_shared<diffuse>(checker)));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto   choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo     = TrekMath::random(0., 1.) * TrekMath::random(0., 1.);
					sphere_material = make_shared<diffuse>(albedo);
					auto center2    = center + vec3(0, random_double(0, .5), 0);
					w.add_object(make_shared<movingSphere>(
					    center, center2, start_time, end_time, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo     = TrekMath::random(0.5, 1);
					auto fuzz       = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					w.add_object(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					w.add_object(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	w.add_object(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<diffuse>(color(0.4, 0.2, 0.1));
	w.add_object(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	w.add_object(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	w.generating_acceleration_structure(start_time, end_time);
	//================================================================================================
}

void scene::two_balls_scene()
{
	backgroundcolor = color(0.70, 0.80, 1.00);
	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(13., 2., 3.),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        std::nullopt,        //view distance

	        start_time,
	        end_time);

	auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

	w.add_object(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<diffuse>(checker)));
	w.add_object(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<diffuse>(checker)));

	w.generating_acceleration_structure(start_time, end_time);
}

void scene::two_perlin_spheres()
{
	backgroundcolor = color(0.70, 0.80, 1.00);

	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(13., 2., 3.),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        std::nullopt,        //view distance

	        start_time,
	        end_time);

	auto pertext = make_shared<noise_texture>(4.0);
	w.add_object(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<diffuse>(pertext)));
	w.add_object(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<diffuse>(pertext)));

	w.generating_acceleration_structure(start_time, end_time);
}

void scene::sphere_texture_scene()
{
	backgroundcolor = color(0.70, 0.80, 1.00);

	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(0., 0., 12.),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        std::nullopt,        //view distance

	        start_time,
	        end_time);

	auto earth_texture = make_shared<image_texture>("data/earthmap.jpg");
	auto earth_surface = make_shared<diffuse>(earth_texture);
	auto globe         = make_shared<sphere>(point3(0, 0, 0), 2, earth_surface);

	w.add_object(globe);
	w.generating_acceleration_structure(start_time, end_time);
}

void scene::rectangle_scene()
{
	backgroundcolor                       = color(0., 0., 0.);
	renstate.view_plane_samples_per_pixel = 400;

	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(26., 3., 6.),        //lookfrom,
	        TrekMath::point3(0., 2., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        std::nullopt,        //view distance
	        start_time,
	        end_time);

	auto pertext = make_shared<noise_texture>(4);
	w.add_object(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<diffuse>(pertext)));
	w.add_object(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<diffuse>(pertext)));

	auto difflight = make_shared<diffuse_light>(color(4, 4, 4));
	w.add_object(make_shared<rectangle>(vec3(2., 0., 0.), vec3(0., 2., 0.), point3(3.0, 1.0, -2.0), vec3(0., 0., 1.), difflight));
}

void scene::cornell_box()

{
	renstate.aspect_ratio                 = 1.0;
	renstate.image_width                  = 600;
	renstate.view_plane_samples_per_pixel = 400;
	renstate.image_height                 = static_cast<int>(renstate.image_width / renstate.aspect_ratio);
	backgroundcolor                       = color(0., 0., 0.);

	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(278., 278., -800.),        //lookfrom,
	        TrekMath::point3(278., 278., 0.),           //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),              //vup,
	        40.0,                                       //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        std::nullopt,        //view distance

	        start_time,
	        end_time);

	auto red   = make_shared<diffuse>(color(.65, .05, .05));
	auto white = make_shared<diffuse>(color(.73, .73, .73));
	auto green = make_shared<diffuse>(color(.12, .45, .15));
	auto light = make_shared<diffuse_light>(color(15, 15, 15));

	w.add_object(make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(555., 555., 555.0), vec3(-1., 0., 0.), green));
	w.add_object(make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(0., 555., 555.), vec3(1., 0., 0.), red));

	w.add_object(make_shared<rectangle>(vec3(130., 0., 0.0), vec3(0., 0., -105.), point3(213., 554., 332.), vec3(0., -1., 0.), light));

	w.add_object(make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 0., 555.), vec3(0., 1., 0.), white));

	w.add_object(make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 555., 555.), vec3(0., -1., 0.), white));

	w.add_object(make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 555., 0.), point3(0., 0., 555.), vec3(0., 0., -1.), white));

	w.add_object(make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));

	w.add_object(make_shared<box>(point3(265, 0, 295), point3(430, 330, 460), white));
}

void scene::testing_scene()
{
	renstate.aspect_ratio = 1.0;
	renstate.image_width  = 400;
	//TO DO : check if this number is not square of some integer;
	renstate.view_plane_samples_per_pixel = 25;
	renstate.image_height                 = static_cast<int>(renstate.image_width / renstate.aspect_ratio);
	backgroundcolor                       = color{0.70, 0.80, 1.00};

	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(0., 2.5, -10.),        //lookfrom,
	        TrekMath::point3(0., 2.5, 0.),          //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),          //vup,
	        45.0,                                   //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        std::nullopt,        //view distance
	        start_time,
	        end_time);

	auto red   = make_shared<diffuse>(color(.65, .05, .05));
	auto white = make_shared<diffuse>(color(.73, .73, .73));
	auto green = make_shared<diffuse>(color(.12, .45, .15));
	auto light = make_shared<diffuse_light>(color(15, 15, 15));

	//w.add_object(make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(555., 555., 555.0), vec3(-1., 0., 0.), green));
	//w.add_object(make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(0., 555., 555.), vec3(1., 0., 0.), red));

	//w.add_object(make_shared<rectangle>(vec3(130., 0., 0.0), vec3(0., 0., -105.), point3(213., 554., 332.), vec3(0., -1., 0.), light));

	//w.add_object(make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 0., 555.), vec3(0., 1., 0.), white));

	//w.add_object(make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 555., 555.), vec3(0., -1., 0.), white));

	//w.add_object(make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 555., 0.), point3(0., 0., 555.), vec3(0., 0., -1.), white));

	w.add_object(make_shared<box>(point3(-2., 0., -4.), point3(2., 4., 0), white));
	w.add_object(make_shared<box>(point3(-2, 0, 1.), point3(2., 4, 5.0), green));

	//w.add_object(make_shared<box>(point3(265, 0, 295), point3(430, 330, 460), white));
}
