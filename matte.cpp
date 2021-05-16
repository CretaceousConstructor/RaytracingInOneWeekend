#include "matte.h"

color matte::shade(shadeRec& sr)
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
	TrekMath::vec3  wo = -sr.cast_ray.direction();
	//matte的材质中，环境光源ambient(替代全局光照的间接计算)照射到matte表面的材质lambertian 返回的ρ是个常数
				 //Lo =               ρhh         *                      Li
	TrekMath::color L = ambient_brdf->rho(sr, wo) * sr.wor->ambient_light_ptr->L(sr);
	//matte的材质中，点光源的direct diffuse照明

	for (auto other_light : sr.wor->lights) {

		TrekMath::vec3 wi = other_light->get_direction(sr); //对于点光源来说就是被渲染点 指向 灯泡的向量
		double NdotWi = glm::dot(sr.normal, wi);

		if (NdotWi > 0.0) {
			bool in_shadow = false;
			if (other_light->casts_shadows()) {
				ray shadowRay(sr.hitPoint, wi);
				in_shadow = other_light->in_shadow(shadowRay, sr);

			}
			if (!in_shadow) {

				//Lo = fr(p,l(p),wo)             * ls*cl              * cosθl  点光源
				//Lo = fr(p,l,wo)                * ls*cl              * cosθl  平行光源
				L += diffuse_brdf->f(sr, wo, wi) * other_light->L(sr) * NdotWi;
			}
		}

	}

	return L;

}

TrekMath::color matte::area_light_shade(shadeRec& sr)
{
	TrekMath::vec3 wo =-sr.cast_ray.direction();
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

			//if (!in_shadow) {
			if (!in_shadow) {

				//Lo = fr(p,l(p),wo)             * ls*cl              * cosθl  点光源
				//Lo = fr(p,l,wo)                * ls*cl              * cosθl  平行光源
				L += diffuse_brdf->f(sr, wi, wo) * direct_light->L(sr) * direct_light->G(sr)* NdotWi / direct_light->pdf(sr);

			}

		}

	}




	return L;


}

void matte::set_ambient_brdf(std::unique_ptr<lambertian>&& arg_ambient_brdf)
{
	ambient_brdf  = std::move(arg_ambient_brdf);
}

void matte::set_diffuse_brdf(std::unique_ptr<lambertian>&& arg_diffuse_brdf)
{
	diffuse_brdf = std::move(arg_diffuse_brdf);
}

void matte::set_ka(double arg_ka)
{
	if (ambient_brdf != nullptr) {
		ambient_brdf->kd = arg_ka;
	}
}

void matte::set_kd(double arg_kd)
{
	if (diffuse_brdf != nullptr) {
		diffuse_brdf->kd = arg_kd;
	}
}

void matte::set_ambient_color(TrekMath::color arg_ambient_color)
{
	if (ambient_brdf != nullptr) {
		ambient_brdf->cd = arg_ambient_color;
	}
}

void matte::set_diffuse_color(TrekMath::color arg_diffuse_color)
{


	if (diffuse_brdf != nullptr) {
		diffuse_brdf->cd = arg_diffuse_color;
	}


}
