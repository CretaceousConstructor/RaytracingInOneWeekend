#include "renderer.h"

//cam(
//       std::make_unique<pinHole>(
//           std::make_unique<multiJittering>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets),
//           TrekMath::point3(-2., 2.0, 1.0),        //lookfrom,
//           TrekMath::point3(0., 0., -1.),          //lookat,
//           TrekMath::vec3(0.0, 1.0, 0.0),          //vup,
//           20.0,                                   //VERTICAL field-of-view in degrees
//           renderState::aspect_ratio,              //
//           std::make_optional<double>(1.0)         //view_dist_optional
//           )),

//std::make_unique<thinLens>(
//    2.0,                                                                               //aperture
//    glm::length(TrekMath::point3(3., 3., 2.0) - TrekMath::point3(0., 0., -1.)),        //focal_plane_dis
//    std::make_unique<hammersley>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets),
//    std::make_unique<multiJittering>(renderState::lense_samples_per_pixel, renderState::lense_sample_sets),

//    TrekMath::point3(3., 3., 2.0),        //lookfrom,
//    TrekMath::point3(0., 0., -1.),        //lookat,
//    TrekMath::vec3(0.0, 1.0, 0.0),        //vup,
//    20.0,                                 //VERTICAL field-of-view in degrees
//    renderState::aspect_ratio,
//    glm::length(TrekMath::point3(3., 3., 2.0) - TrekMath::point3(0., 0., -1.))        //view_dist_optional

//    )),

renderer::renderer() :
    cam(
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
            0.0,
            1.0)),
    result("Picture.ppm", std::ofstream::out)
{
	//TESTING AREA LIGHT
	//auto object_for_area_light = std::make_shared<rectangle>(TrekMath::vec3(0.,100., 0.), TrekMath::vec3(100.,0., 0.), TrekMath::point3(-50.,-50.,0.),  TrekMath::vec3(0., 0., 1.));

	//SETING camera
	std::shared_ptr<tracer> tracer_p = std::make_shared<pathTrace>(&w);
	w.set_tracer_ptr(tracer_p);
	cam->set_tracer_ptr(tracer_p);

	////ADDING area lighting
	//auto mat_of_area_light = std::make_shared<emissive>();
	//mat_of_area_light->setRadianceScaling(1.5);
	//mat_of_area_light->setEmissiveColor(TrekMath::color(1., 1., 1.));
	//auto object_for_area_light = std::make_shared<rectangle>(TrekMath::vec3(0., 0., -2.), TrekMath::vec3(2., 0., 0.), TrekMath::point3(-1, 3.8, 1), TrekMath::vec3(0., -1., 0.));
	//object_for_area_light->set_material(mat_of_area_light);
	//object_for_area_light->set_sampler(std::make_unique<multiJittering>(renderState::samples_per_set, renderState::view_plane_sample_sets));        //renderState::view_plane_samples_per_pixel¿ÉÒÔ¸ÄÂð£¿
	//object_for_area_light->set_shadows_object(false);
	//w.add_object(object_for_area_light);
	//auto area_light_ptr = std::make_shared<areaLight>();
	//area_light_ptr->set_object(object_for_area_light);
	//area_light_ptr->set_shadows_light(true);
	//w.add_light(area_light_ptr);
	////ADDING other lights
	//w.ambient_light_ptr = std::make_shared<ambientOccluder>();        //ambient light
	////w.add_light(make_shared<pointLight>(TrekMath::point3(30., 70., 50.), 0.3, color(1.0, 1.0, 1.0)));//point light
	//auto mat_of_envir_light = std::make_shared<emissive>();        //environment light
	//mat_of_envir_light->setRadianceScaling(0.4);
	//mat_of_envir_light->setEmissiveColor(TrekMath::color(1., 1., 1.));
	//auto environmentlight = std::make_shared<environmentLight>();
	//environmentlight->set_sampler(std::make_unique<multiJittering>(renderState::samples_per_set, renderState::view_plane_sample_sets));
	//environmentlight->set_shadows_light(true);
	//environmentlight->set_material(mat_of_envir_light);
	////w.add_light(environmentlight);

	////ADDING materials

	///**************************************************/
	//auto mat_plane = std::make_shared<matte>();
	//mat_plane->set_ambient_k(1.0);
	//mat_plane->set_ambient_color(TrekMath::color(1.0, 1.0, 1.0));
	//mat_plane->set_diffuse_k(1.0);
	//mat_plane->set_diffuse_color(TrekMath::color(1.0, 1.0, 1.0));
	///**************************************************/
	//auto mat_left = std::make_shared<matte>();
	//mat_left->set_ambient_k(0.8);
	//mat_left->set_ambient_color(TrekMath::color(1.0, 0.0, 0.0));
	//mat_left->set_diffuse_k(0.9);
	//mat_left->set_diffuse_color(TrekMath::color(1.0, 0.0, 0.0));
	///**************************************************/
	//auto mat_transparent = std::make_shared<transparent>();
	//mat_transparent->set_specular_k(0.5);
	//mat_transparent->set_specular_exp(2000.0);
	//mat_transparent->set_transmitter_ior(1.5);
	//mat_transparent->set_transmitter_k(0.9);
	//mat_transparent->set_reflective_k(0.1);
	///**************************************************/
	//auto mat_right = std::make_shared<matte>();
	//mat_right->set_ambient_k(0.8);
	//mat_right->set_ambient_color(TrekMath::color(0.0, 1.0, 0.0));
	//mat_right->set_diffuse_k(0.9);
	//mat_right->set_diffuse_color(TrekMath::color(0.0, 1.0, 0.0));
	///**************************************************/

	//auto mat_sphere = std::make_shared<reflective>();
	//mat_sphere->set_ambient_k(0.15);
	//mat_sphere->set_ambient_color(TrekMath::color(1.0, 1.0, 1.0));
	//mat_sphere->set_diffuse_k(0.25);
	//mat_sphere->set_diffuse_color(TrekMath::color(1.0, 1.0, 1.0));
	//mat_sphere->set_specular_exp(1.6);
	//mat_sphere->set_specular_k(0.8);
	//mat_sphere->set_specular_color(TrekMath::color(1.0, 1.0, 1.0));

	//mat_sphere->set_reflective_k(0.5);
	//mat_sphere->set_reflective_color(TrekMath::color(1.0, 1.0, 1.0));

	///**************************************************/
	//auto mat_sphere1 = std::make_shared<reflective>();
	//mat_sphere1->set_ambient_k(0.1);
	//mat_sphere1->set_ambient_color(TrekMath::color(0.3, 0.5, 0.7));
	//mat_sphere1->set_diffuse_k(0.27);
	//mat_sphere1->set_diffuse_color(TrekMath::color(0.3, 0.5, 0.7));
	//mat_sphere1->set_specular_exp(2.);
	//mat_sphere1->set_specular_color(TrekMath::color(0.3, 0.5, 0.7));
	//mat_sphere1->set_reflective_k(0.45);
	//mat_sphere1->set_reflective_color(TrekMath::color(0.3, 0.5, 0.7));
	///**************************************************/
	//auto mat_sphere2 = std::make_shared<reflective>();
	//mat_sphere2->set_ambient_k(0.15);
	//mat_sphere2->set_ambient_color(TrekMath::color(0.3, 0.3, 0.3));
	//mat_sphere2->set_diffuse_k(0.3);
	//mat_sphere2->set_diffuse_color(TrekMath::color(0.3, 0.3, 0.3));
	//mat_sphere2->set_specular_exp(1.8);
	//mat_sphere2->set_specular_color(TrekMath::color(0.3, 0.3, 0.3));
	//mat_sphere2->set_reflective_k(0.6);
	//mat_sphere2->set_reflective_color(TrekMath::color(0.3, 0.3, 0.3));
	///**************************************************/
	//double exp            = 50.;
	//auto   mat_glossy_ptr = std::make_shared<glossyReflector>();

	//mat_glossy_ptr->set_sampler(renderState::samples_per_set, renderState::view_plane_sample_sets, exp);
	//mat_glossy_ptr->set_ambient_k(0.);
	//mat_glossy_ptr->set_ambient_color(color(1.0, 1.0, 0.3));
	//mat_glossy_ptr->set_diffuse_k(0.);
	//mat_glossy_ptr->set_diffuse_color(color(1.0, 1.0, 0.3));
	//mat_glossy_ptr->set_specular_k(0.);
	//mat_glossy_ptr->set_specular_exp(exp);                           //
	//mat_glossy_ptr->set_specular_color(color(1.0, 1.0, 0.3));        //

	//mat_glossy_ptr->set_k_glossy_reflective(0.9);
	//mat_glossy_ptr->set_exponent_glossy_reflective(exp);
	//mat_glossy_ptr->set_color_glossy_reflective(TrekMath::color(1., 1., 0.3));

	////ADDING objects

	///**************************************************/

	//auto bottom_wall = std::make_shared<rectangle>(TrekMath::vec3(0., 0., -8.), TrekMath::vec3(8., 0., 0.), TrekMath::point3(-4., -4., 4.), TrekMath::vec3(0., 1., 0.));
	//bottom_wall->set_material(mat_plane);
	//auto left_wall = std::make_shared<rectangle>(TrekMath::vec3(0., 8., 0.), TrekMath::vec3(0., 0., -8.), TrekMath::point3(-4., -4., 4.), TrekMath::vec3(1., 0., 0.));
	//left_wall->set_material(mat_sphere);
	//auto right_wall = std::make_shared<rectangle>(TrekMath::vec3(0., 0., -8.), TrekMath::vec3(0., 8., 0.), TrekMath::point3(4., -4., 4.), TrekMath::vec3(-1., 0., 0.));
	//right_wall->set_material(mat_right);

	//auto top_wall = std::make_shared<rectangle>(TrekMath::vec3(0., 0., -8.), TrekMath::vec3(8., 0., 0.), TrekMath::point3(-4., 4., 4.), TrekMath::vec3(0., -1., 0.));
	//top_wall->set_material(mat_plane);

	//auto back_wall = std::make_shared<rectangle>(TrekMath::vec3(0., 8., 0.), TrekMath::vec3(8., 0., 0.), TrekMath::point3(-4., -4., -4.), TrekMath::vec3(0., 0., 1.));
	//back_wall->set_material(mat_plane);

	////auto a_box = make_shared<box>(TrekMath::point3(-20., 0., -20.), TrekMath::point3(20., 40., 20.));
	////a_box->set_material(mat_sphere);
	////w.add_object(a_box);
	////w.add_object(make_shared<sphere>(TrekMath::point3(0., 20., 0.), 20., mat_sphere));
	//w.add_object(make_shared<sphere>(TrekMath::point3(0., -2., 0.), 1.5, mat_transparent));
	////w.add_object(make_shared<sphere>(TrekMath::point3(48., 20., 8.), 20., mat_sphere2));
	////w.add_object(make_shared<plane>(TrekMath::point3(0., -2., 0.), TrekMath::point3(0., 1., 0.), mat_plane));

	//w.add_object(bottom_wall);
	//w.add_object(left_wall);
	//w.add_object(right_wall);
	//w.add_object(top_wall);
	//w.add_object(back_wall);

	////auto object_for_plane = std::make_shared<rectangle>(TrekMath::vec3(0., 0., -8.), TrekMath::vec3(8., 0., 0.), TrekMath::point3(-4., -2., 4.), TrekMath::vec3(0., 1., 0.));
	////object_for_plane->set_material(mat_plane);
	////w.add_object(object_for_plane);
	////w.add_object(make_shared<torus>(2.0, 0.5, mat_sphere));
	////w.add_object(make_shared<disk>(TrekMath::point3(0., 20., 0.),10.,TrekMath::normal(0.,0.,1.), mat_sphere));
	////w.add_object(make_shared<triangle>(TrekMath::point3(-40., 0., 0.), TrekMath::point3(-25., 0., 0.), TrekMath::point3(-32.5, 30., 0.), mat_tri));




	auto ground_material = std::make_shared<diffuse>(color(0.5, 0.5, 0.5));
	w.add_object(std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

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
					auto albedo     = TrekMath::random(0.,1.) * TrekMath::random(0.,1.);
					sphere_material = make_shared<diffuse>(albedo);
					auto center2    = center + vec3(0, random_double(0, .5), 0);
					w.add_object(make_shared<movingSphere>(
					    center, center2, 0.0, 1.0, 0.2, sphere_material));
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





}

void renderer::startToRender()
{
	cam->render_scence(w, result);
}

void renderer::cleanUp()
{
	result.close();
	system("OpenPic.bat");
}