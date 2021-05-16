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
	//�����У�����(ambient)��Դ������

	TrekMath::vec3  wo = -sr.cast_ray.direction();
	TrekMath::color L = ambient_brdf->rho(sr, wo) * sr.wor->ambient_light_ptr->L(sr);

	//�����У����Դ(point)��ƽ��(directional)��Դ������

	for (auto direct_light : sr.wor->lights) {

		TrekMath::vec3 wi = direct_light->get_direction(sr); //���ڵ��Դ��˵���Ǳ���Ⱦ�� ָ�� ���ݵ�����

		double NdotWi = glm::dot(sr.normal, wi);

		if (NdotWi > 0.0) {
			bool in_shadow = false;
			if (direct_light->casts_shadows()) {
				ray shadowRay(sr.hitPoint, wi);
				in_shadow = direct_light->in_shadow(shadowRay, sr);

			}

			//if (!in_shadow) {
			if (!in_shadow) {

				//Lo = fr(p,l(p),wo)             * ls*cl              * cos��l  ���Դ
				//Lo = fr(p,l,wo)                * ls*cl              * cos��l  ƽ�й�Դ
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

		TrekMath::vec3 wi = direct_light->get_direction(sr); //���ڵ��Դ��˵���Ǳ���Ⱦ�� ָ�� ���ݵ�����

		double NdotWi = glm::dot(sr.normal, wi);

		if (NdotWi > 0.0) {
			bool in_shadow = false;
			if (direct_light->casts_shadows()) {
				ray shadowRay(sr.hitPoint, wi);
				in_shadow = direct_light->in_shadow(shadowRay, sr);

			}
			if (!in_shadow) {

				//Lo = fr(p,l(p),wo)             * ls*cl              * cos��l  ���Դ
				//Lo = fr(p,l,wo)                * ls*cl              * cos��l  ƽ�й�Դ
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
