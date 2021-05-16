#include "renderer.h"


renderer::renderer()
	:
	cam(
	//	std::make_unique<thinLens>
	//	(
	//		0.5,						      //aperture
	//		2.7,                             //focal_plane_dis
	//		std::make_unique<hammersley>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets),
	//		std::make_unique<multiJittering>(renderState::lense_samples_per_pixel, renderState::lense_sample_sets),

	//		TrekMath::point3(0, 0, 500.0), //lookfrom,
	//		TrekMath::point3(-5.0, 0., 0.),  //lookat,
	//		TrekMath::vec3(0.0, 1.0, 0.0),   //vup,
	//		40.0,                            //VERTICAL field-of-view in degrees 
	//		renderState::aspect_ratio,
	//		std::make_unique<rayCast>(&w),
	//		850.0                             //view_dist_optional
	//		)
	//)
	std::make_unique<pinHole>
	(
		std::make_unique<multiJittering>(renderState::view_plane_samples_per_pixel,renderState::view_plane_sample_sets),
		TrekMath::point3(0.0, 60.0, 200.0), //lookfrom,
		TrekMath::point3(0., 27., 0.),  //lookat,
		TrekMath::vec3(0.0, 1.0, 0.0),   //vup,
		40.0,                            //VERTICAL field-of-view in degrees 
		renderState::aspect_ratio ,       //
		std::make_unique<areaLighting>(&w)
		//850.0                            //view_dist_optional
		)
   )
	,
	result("Picture.ppm", std::ofstream::out)
{
	



	//ADDING area lighting 
	auto mat_of_area_light = std::make_shared<emissive>();
	mat_of_area_light->setRadianceScaling(.5);
	mat_of_area_light->setEmissiveColor(TrekMath::color(1.,1.,1.));

	auto object_for_area_light = std::make_shared<rectangle>(TrekMath::vec3(0., 0., -25.), TrekMath::vec3(25.,0., 0.), TrekMath::point3(-12.5,140.,12.5),  TrekMath::vec3(0., -1., 0.) );
	object_for_area_light->set_material(mat_of_area_light);
	object_for_area_light->set_sampler(std::make_unique<multiJittering>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets)); //renderState::view_plane_samples_per_pixel¿ÉÒÔ¸ÄÂð£¿
	object_for_area_light->set_shadows_object(false);

	//w.add_object(object_for_area_light);
	auto area_light_ptr = std::make_shared<areaLight>();
	area_light_ptr->set_object(object_for_area_light);
	area_light_ptr->set_shadows_light(true);

	//ADDING other lights
	w.ambient_light_ptr  =  std::make_shared<ambientOccluder>(); //ambient light
	//w.add_light(area_light_ptr);
	//w.add_light(make_shared<pointLight>(TrekMath::point3(300.,100.,-400.),0.7,color(1.0,1.0,1.0)));//point light


	auto environmentlight = std::make_shared<environmentLight>();

	environmentlight->set_sampler(std::make_unique<multiJittering>(renderState::view_plane_samples_per_pixel, renderState::view_plane_sample_sets));
	environmentlight->set_shadows_light(true);
	environmentlight->set_material(mat_of_area_light);

	w.add_light(environmentlight);



	//ADDING material
	//auto mat = std::make_shared<matte>();
	auto mat_sphere = std::make_shared<matte>();
	auto mat_plane =  std::make_shared<matte>();
	mat_plane->ambient_brdf->cd = TrekMath::color(.5, 1, 0.2);
	mat_plane->ambient_brdf->kd = 0.15;  //ka
	mat_plane->diffuse_brdf->cd = TrekMath::color(.5, 1, 0.2);
	mat_plane->diffuse_brdf->kd = 0.25;  //kd

	//ADDING objects
	w.add_object(make_shared<sphere>(TrekMath::point3(0., 25., 0.), 25., mat_sphere));
	//w.add_object(make_shared<plane> (TrekMath::point3(0., 0., -50.), TrekMath::point3(0., 0.,1.), mat_plane));
	w.add_object(make_shared<plane> (TrekMath::point3(0., 0., 0.), TrekMath::point3(0., 1., 0.), mat_plane));



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

