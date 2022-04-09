#include "scene.h"

scene::scene()
{
	two_balls_scene();

	//two_perlin_spheres();
	//================================================================================================

	std::shared_ptr<tracer> tracer_p = std::make_shared<pathTrace>(&w);
	w.set_tracer_ptr(tracer_p);
	cam->set_tracer_ptr(tracer_p);
}

void scene::render(std::ofstream &result)
{
	cam->render_scence(w, result);
}

void scene::random_balls_scene()
{
	cam =
	    std::make_unique<thinLens>(
	        0.1,        //aperture
	        10.0,
	        std::make_unique<hammersley>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets),
	        std::make_unique<multiJittering>(renderState::lense_samples_per_pixel, renderState::lense_sample_sets),

	        TrekMath::point3(13., 2., 3.),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renderState::aspect_ratio,
	        start_time,
	        end_time);

	auto checker = make_shared<checkerTexture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
	w.add_object(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<diffuse>(checker)));

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
					//auto albedo     = TrekMath::random(0., 1.) * TrekMath::random(0., 1.);
					auto albedo     = std::make_shared<solid_color>(TrekMath::random(0., 1.) * TrekMath::random(0., 1.));
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

	auto material2 = make_shared<diffuse>(std::make_shared<solid_color>(color(0.4, 0.2, 0.1)));
	w.add_object(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	w.add_object(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	w.generating_acceleration_structure(start_time, end_time);
	//================================================================================================
}

void scene::two_balls_scene()
{
	//pinHole(
	//    std::unique_ptr<sampler> &&arg_viewPlaneSampler,

	//    TrekMath::point3      lookfrom,
	//    TrekMath::point3      lookat,
	//    TrekMath::vec3        vup,
	//    double                vfov,                // VERTICAL field-of-view in degrees
	//    double                aspect_ratio,        //
	//    std::optional<double> view_dist_optional = std::nullopt,
	//    double _time0 = 0.,
	//    double _time1 = 0.);

	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets),

	        TrekMath::point3(13., 2., 3.),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renderState::aspect_ratio,
	        10.0,
	        start_time,
	        end_time);

	auto checker = make_shared<checkerTexture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

	w.add_object(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<diffuse>(checker)));
	w.add_object(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<diffuse>(checker)));

	w.generating_acceleration_structure(start_time, end_time);
}

void scene::two_perlin_spheres()
{
	cam =
	    std::make_unique<thinLens>(
	        0.0,         //aperture
	        10.0,        //dist_to_focus
	        std::make_unique<hammersley>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets),
	        std::make_unique<multiJittering>(renderState::lense_samples_per_pixel, renderState::lense_sample_sets),

	        TrekMath::point3(13., 2., 3.),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
	        20.0,                                 //VERTICAL field-of-view in degrees
	        renderState::aspect_ratio,
	        start_time,
	        end_time);

	auto checker = make_shared<checkerTexture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

	w.add_object(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<diffuse>(checker)));
	w.add_object(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<diffuse>(checker)));

	w.generating_acceleration_structure(start_time, end_time);
}
