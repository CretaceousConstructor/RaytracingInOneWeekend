#include "phong.h"

color phong::shade(shadeRec& sr)
{
	//eye            light
	//   \          / 
	// wo \        / wi
	// sr.r\      /
	//      \    /
	//       \  /
	//        \/
	//         
	//
	//材质中，环境(ambient)光源的照明

	TrekMath::vec3  wo = -sr.cast_ray.direction();
	TrekMath::color L = ambient_brdf->rho(sr, wo) * sr.wor->ambient_light_ptr->L(sr);

	//材质中，点光源(point)和平行(directional)光源的照明

	for (auto direct_light : sr.wor->lights) {

		TrekMath::vec3 wi = direct_light->get_direction(sr); //对于点光源来说就是被渲染点 指向 灯泡的向量

		double NdotWi = glm::dot(sr.normal, wi);

		if (NdotWi > 0.0) {
			bool in_shadow = false;
			if (direct_light->casts_shadows()) {
				ray shadowRay(sr.hitPoint, wi);
				in_shadow = direct_light->in_shadow(shadowRay, sr);

			}

			//if (!in_shadow) {
			if (!in_shadow) {

				//Lo = fr(p,l(p),wo)             * ls*cl              * cosθl  点光源
				//Lo = fr(p,l,wo)                * ls*cl              * cosθl  平行光源
				L += ((diffuse_brdf->f(sr, wi, wo) + specular_brdf->f(sr, wi, wo)) * direct_light->L(sr) * NdotWi);

			}


		}

	}




	return L;
}

TrekMath::color phong::area_light_shade(shadeRec& sr)
{
	TrekMath::vec3 wo = -sr.cast_ray.direction();
	TrekMath::color L = ambient_brdf->rho(sr, wo) * sr.wor->ambient_light_ptr->L(sr);
	
	for (auto direct_light : sr.wor->lights) {

		TrekMath::vec3 wi = direct_light->get_direction(sr); //对于点光源来说就是被渲染点 指向 灯泡的向量

		double NdotWi = glm::dot(sr.normal, wi);

		if (NdotWi > 0.0) {
			bool in_shadow = false;
			if (direct_light->casts_shadows()) {
				ray shadowRay(sr.hitPoint, wi);
				in_shadow = direct_light->in_shadow(shadowRay, sr);

			}
			if (!in_shadow) {

				//Lo = fr(p,l(p),wo)             * ls*cl              * cosθl  点光源
				//Lo = fr(p,l,wo)                * ls*cl              * cosθl  平行光源
				L += (diffuse_brdf->f(sr, wi, wo) + specular_brdf->f(sr, wi, wo)) * direct_light->L(sr) * direct_light->G(sr) * NdotWi / direct_light->pdf(sr);

			}


		}

	}




	return L;


}



void phong::set_ambient_brdf(std::unique_ptr<lambertian>&& arg_ambient_brdf)
{
	ambient_brdf = std::move(arg_ambient_brdf);
}

void phong::set_diffuse_brdf(std::unique_ptr<lambertian>&& arg_diffuse_brdf)
{
	diffuse_brdf = std::move(arg_diffuse_brdf);
}

void phong::set_specular_brdf(std::unique_ptr<glossySpecular>&& arg_specular_brdf)
{
	specular_brdf  = std::move(arg_specular_brdf);
}




void phong::set_ka(double arg_ka)
{
	if (ambient_brdf != nullptr) {
		ambient_brdf->kd = arg_ka;
	}
}

void phong::set_kd(double arg_kd)
{
	if (diffuse_brdf != nullptr) {
		diffuse_brdf->kd = arg_kd;
	}
}

void phong::set_specular_exp(double arg_exp)
{
	if (specular_brdf != nullptr) {
		specular_brdf->exp = arg_exp;
	}
}

void phong::set_ambient_color(TrekMath::color arg_ambient_color)
{
	if (ambient_brdf != nullptr) {
		ambient_brdf->cd = arg_ambient_color;
	}
}

void phong::set_diffuse_color(TrekMath::color arg_diffuse_color)
{


	if (diffuse_brdf != nullptr) {
		diffuse_brdf->cd = arg_diffuse_color;
	}


}

void phong::set_specular_color(TrekMath::color arg_specular_color)
{
	if (specular_brdf != nullptr) {
		specular_brdf->ks = arg_specular_color;
	}
}
