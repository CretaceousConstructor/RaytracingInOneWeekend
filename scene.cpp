#include "scene.h"

scene::scene()
{
	//two_balls_scene();
	//two_perlin_spheres();
	//sphere_texture_scene();
	//rectangle_scene();
	//cornell_box();
	//testing_scene();
	//random_balls_scene();
	cornell_smoke();
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
	renstate.view_plane_samples_per_pixel = 25;


	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(13., 2, 3.),          //lookfrom,
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

	auto instance_globe = make_shared<instance>(globe);
	instance_globe->SetRotation(0., glm::radians(15.0), 0.);
	instance_globe->SetScale(1.5, 1.0, 1.0);

	w.add_object(instance_globe);
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
	renstate.view_plane_samples_per_pixel = 200;
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

	auto green_wall = make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(555., 555., 555.0), vec3(-1., 0., 0.), green);
	auto red_wall   = make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(0., 555., 555.), vec3(1., 0., 0.), red);
	auto light_obj  = make_shared<rectangle>(vec3(130., 0., 0.0), vec3(0., 0., -105.), point3(213., 554., 332.), vec3(0., -1., 0.), light);

	auto white_wall0 = make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 0., 555.), vec3(0., 1., 0.), white);
	auto white_wall1 = make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 555., 555.), vec3(0., -1., 0.), white);
	auto white_wall2 = make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 555., 0.), point3(0., 0., 555.), vec3(0., 0., -1.), white);

	auto white_box0 = make_shared<instance>(make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white));
	auto white_box1 = make_shared<instance>(make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white));

	white_box0->SetRotation(0., glm::radians(15.0), 0.);
	white_box0->SetTranslation(vec3(265, 0, 295));

	white_box1->SetRotation(0., glm::radians(-18.0), 0.);
	white_box1->SetTranslation(vec3(130, 0, 65));

	w.add_object(green_wall);
	w.add_object(red_wall);
	w.add_object(light_obj);

	w.add_object(white_wall0);
	w.add_object(white_wall1);
	w.add_object(white_wall2);

	w.add_object(white_box0);
	w.add_object(white_box1);
}

void scene::testing_scene()
{
	renstate.aspect_ratio                 = 1.0;
	renstate.image_width                  = 200;
	renstate.view_plane_samples_per_pixel = 25;
	renstate.image_height                 = static_cast<int>(renstate.image_width / renstate.aspect_ratio);
	backgroundcolor = color(0.70, 0.80, 1.00);


	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(0., 0., 1.5),        //lookfrom,
	        TrekMath::point3(0., 0., 0.),         //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),         //vup,
	        45.0,                                  //VERTICAL field-of-view in degrees
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

	//w.add_object(make_shared<box>(point3(-2., 0., -4.), point3(2., 4., 0), white));

	auto box_ptr = make_shared<box>(point3(-2., -2., -2.), point3(2., 2., 2.), green);

	//auto box_instance = make_shared<instance>(box_ptr);
	//auto &trans_of_boxins = box_instance->get_transformation();

	//trans_of_boxins.SetRotation(glm::radians(45.), glm::radians(25.), 0.0);
	//trans_of_boxins.SetTranslation(2.0, 1.0, -3.0);
	////w.add_object(box_instance);
	auto box_medium = make_shared<constant_medium>(box_ptr, 0.01, color(0., 0., 0.));
	//w.add_object(box_ptr);
	w.add_object(box_medium);



}

void scene::cornell_smoke()
{
	renstate.aspect_ratio                 = 1.0;
	renstate.image_width                  = 600;
	renstate.view_plane_samples_per_pixel = 100;
	renstate.image_height                 = static_cast<int>(renstate.image_width / renstate.aspect_ratio);

	backgroundcolor = color(0., 0., 0.);


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
	auto light = make_shared<diffuse_light>(color(7, 7, 7));

	auto green_wall = make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(555., 555., 555.0), vec3(-1., 0., 0.), green);
	auto red_wall   = make_shared<rectangle>(vec3(0., 0., -555.0), vec3(0., -555., 0.), point3(0., 555., 555.), vec3(1., 0., 0.), red);
	auto light_obj  = make_shared<rectangle>(vec3(300., 0., 0.0), vec3(0., 0., -305.), point3(133., 554., 432.), vec3(0., -1., 0.), light);

	auto white_wall0 = make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 0., 555.), vec3(0., 1., 0.), white);
	auto white_wall1 = make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 0., -555.), point3(0., 555., 555.), vec3(0., -1., 0.), white);
	auto white_wall2 = make_shared<rectangle>(vec3(555., 0., 0.0), vec3(0., 555., 0.), point3(0., 0., 555.), vec3(0., 0., -1.), white);

	auto white_box0 = make_shared<instance>(make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white));
	auto white_box1 = make_shared<instance>(make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white));



	white_box0->SetRotation(0., glm::radians(15.0), 0.);
	white_box0->SetTranslation(vec3(265, 0, 295));
	white_box1->SetRotation(0., glm::radians(-18.0), 0.);
	white_box1->SetTranslation(vec3(130, 0, 65));

	w.add_object(green_wall);
	w.add_object(red_wall);
	w.add_object(light_obj);

	w.add_object(white_wall0);
	w.add_object(white_wall1);
	w.add_object(white_wall2);

	w.add_object(make_shared<constant_medium>(white_box0, 0.01, color(0, 0, 0)));
	w.add_object(make_shared<constant_medium>(white_box1, 0.01, color(1, 1, 1)));




}

void scene::final_scene()
{




	renstate.aspect_ratio                 = 1.0;
	renstate.image_width                  = 800;
	renstate.view_plane_samples_per_pixel = 10000;
	renstate.image_height                 = static_cast<int>(renstate.image_width / renstate.aspect_ratio);
	backgroundcolor                       = color{0., 0., 0.};




	cam =
	    std::make_unique<pinHole>(
	        std::make_unique<hammersley>(renstate.view_plane_samples_per_pixel, renstate.view_plane_sample_sets),
	        TrekMath::point3(478., 278., -600.),        //lookfrom,
	        TrekMath::point3(278., 278., 0.),           //lookat,
	        TrekMath::vec3(0.0, 1.0, 0.0),              //vup,
	        40.0,                                       //VERTICAL field-of-view in degrees
	        renstate.aspect_ratio,
	        std::nullopt,        //view distance

	        start_time,
	        end_time);





	

	auto ground = make_shared<diffuse>(color(0.48, 0.83, 0.53));

	const int boxes_per_side = 20;
	for (int i = 0; i < boxes_per_side; i++)
	{
		for (int j = 0; j < boxes_per_side; j++)
		{
			auto w_  = 100.0;
			auto x0 = -1000.0 + i * w_;
			auto z0 = -1000.0 + j * w_;
			auto y0 = 0.0;
			auto x1 = x0 + w_;
			auto y1 = random_double(1, 101);
			auto z1 = z0 + w_;

			w.add_object(make_shared<box>(point3(x0, y0, z0), point3(x1, y1, z1), ground));
		}
	}

	//hittable_list objects;

	//objects.add(make_shared<bvh_node>(boxes1, 0, 1));

	//auto light = make_shared<diffuse_light>(color(7, 7, 7));
	//objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

	//auto center1                = point3(400, 400, 200);
	//auto center2                = center1 + vec3(30, 0, 0);
	//auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
	//objects.add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

	//objects.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
	//objects.add(make_shared<sphere>(
	//    point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)));

	//auto boundary = make_shared<sphere>(point3(360, 150, 145), 70, make_shared<dielectric>(1.5));
	//objects.add(boundary);
	//objects.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
	//boundary = make_shared<sphere>(point3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
	//objects.add(make_shared<constant_medium>(boundary, .0001, color(1, 1, 1)));

	//auto emat = make_shared<diffuse>(make_shared<image_texture>("earthmap.jpg"));
	//objects.add(make_shared<sphere>(point3(400, 200, 400), 100, emat));
	//auto pertext = make_shared<noise_texture>(0.1);
	//objects.add(make_shared<sphere>(point3(220, 280, 300), 80, make_shared<diffuse>(pertext)));

	//hittable_list boxes2;
	//auto          white = make_shared<lambertian>(color(.73, .73, .73));
	//int           ns    = 1000;
	//for (int j = 0; j < ns; j++)
	//{
	//	boxes2.add(make_shared<sphere>(point3::random(0, 165), 10, white));
	//}

	//objects.add(make_shared<translate>(
	//    make_shared<rotate_y>(
	//        make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
	//    vec3(-100, 270, 395)));

	//return objects;


}
