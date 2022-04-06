#include "phong.h"

phong::phong() :
    material(),
    ambient_brdf(std::make_unique<lambertian>()),
    diffuse_brdf(std::make_unique<lambertian>()),
    specular_brdf(std::make_unique<glossySpecular>())
{
	ambient_brdf->cl = TrekMath::color(0.25, .1, 0.5);
	ambient_brdf->kd = 0.25;        //ka

	diffuse_brdf->cl = TrekMath::color(0.25, .1, 0.5);
	diffuse_brdf->kd = 0.25;        //kd

	specular_brdf->cs  = TrekMath::color(0.25, .1, 0.5);        //ks
	specular_brdf->ks  = 0.5;                                   //ks
	specular_brdf->exp = 1.6;
}

color phong::shade(shadeRec &sr)
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
	TrekMath::color L  = ambient_brdf->rho(sr, wo) * sr.wor->ambient_light_ptr->L(sr);

	//材质中，点光源(point)和平行(directional)光源的照明

	for (auto direct_light : sr.wor->lights)
	{
		TrekMath::vec3 wi = direct_light->get_direction(sr);        //对于点光源来说就是被渲染点 指向 灯泡的向量

		double NdotWi = glm::dot(sr.normal, wi);

		if (NdotWi > 0.0)
		{
			bool in_shadow = false;
			if (direct_light->casts_shadows())
			{
				ray shadowRay(sr.hitPoint, wi);
				in_shadow = direct_light->in_shadow(shadowRay, sr);
			}

			//if (!in_shadow) {
			if (!in_shadow)
			{
				//Lo = fr(p,l(p),wo)             * ls*cl              * cosθl  点光源
				//Lo = fr(p,l,wo)                * ls*cl              * cosθl  平行光源
				L += ((diffuse_brdf->f(sr, wi, wo) + specular_brdf->f(sr, wi, wo)) * direct_light->L(sr) * NdotWi);
			}
		}
	}

	return L;
}

TrekMath::color phong::area_light_shade(shadeRec &sr)
{
	TrekMath::vec3  wo = -sr.cast_ray.direction();
	TrekMath::color L  = ambient_brdf->rho(sr, wo) * sr.wor->ambient_light_ptr->L(sr);

	for (auto direct_light : sr.wor->lights)
	{
		TrekMath::vec3 wi     = direct_light->get_direction(sr);        //对于点光源来说就是被渲染点 指向 灯泡的向量
		double         NdotWi = glm::dot(sr.normal, wi);
		if (NdotWi > 0.0)
		{
			bool in_shadow = false;
			if (direct_light->casts_shadows())
			{
				ray shadowRay(sr.hitPoint, wi);
				in_shadow = direct_light->in_shadow(shadowRay, sr);
			}
			if (!in_shadow)
			{
				//Lo = fr(p,l(p),wo)             * ls*cl              * cosθl  点光源
				//Lo = fr(p,l,wo)                * ls*cl              * cosθl  平行光源
				L += (diffuse_brdf->f(sr, wi, wo) + specular_brdf->f(sr, wi, wo)) * direct_light->L(sr) * direct_light->G(sr) * NdotWi / direct_light->pdf(sr);
			}
		}
	}

	return L;
}

TrekMath::color phong::path_shade(shadeRec &sr)
{
	TrekMath::vec3 wo = -sr.cast_ray.direction();

	TrekMath::vec3 wi;

	double pdf;
	color  fr     = specular_brdf->sample_f(sr, wi, wo, pdf);
	double NdotWi = glm::dot(sr.normal, wi);
	ray    reflected_ray(sr.hitPoint, wi);
	return (fr * sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * NdotWi / pdf);
}

TrekMath::color phong::global_shade(shadeRec &sr)
{
	color L(0., 0., 0.);

	if (sr.depth == 0)
	{
		L = area_light_shade(sr);
	}

	TrekMath::vec3 wo = -sr.cast_ray.direction();
	TrekMath::vec3 wi;
	double         pdf;
	color          fr     = specular_brdf->sample_f(sr, wi, wo, pdf);
	double         NdotWi = glm::dot(sr.normal, wi);
	ray            reflected_ray(sr.hitPoint, wi);
	L += fr * sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * NdotWi / pdf;
	return L;
}

void phong::set_ambient_brdf(std::unique_ptr<lambertian> &&arg_ambient_brdf)
{
	ambient_brdf = std::move(arg_ambient_brdf);
}

void phong::set_diffuse_brdf(std::unique_ptr<lambertian> &&arg_diffuse_brdf)
{
	diffuse_brdf = std::move(arg_diffuse_brdf);
}

void phong::set_specular_brdf(std::unique_ptr<glossySpecular> &&arg_specular_brdf)
{
	specular_brdf = std::move(arg_specular_brdf);
}

void phong::set_ambient_k(double arg_ka)
{
	if (ambient_brdf != nullptr)
	{
		ambient_brdf->kd = arg_ka;
	}
}

void phong::set_diffuse_k(double arg_kd)
{
	if (diffuse_brdf != nullptr)
	{
		diffuse_brdf->kd = arg_kd;
	}
}

void phong::set_specular_exp(double arg_exp)
{
	if (specular_brdf != nullptr)
	{
		specular_brdf->exp = arg_exp;
	}
}

void phong::set_ambient_color(TrekMath::color arg_ambient_color)
{
	if (ambient_brdf != nullptr)
	{
		ambient_brdf->cl = arg_ambient_color;
	}
}

void phong::set_diffuse_color(TrekMath::color arg_diffuse_color)
{
	if (diffuse_brdf != nullptr)
	{
		diffuse_brdf->cl = arg_diffuse_color;
	}
}

void phong::set_specular_color(TrekMath::color arg_specular_color)
{
	if (specular_brdf != nullptr)
	{
		specular_brdf->cs = arg_specular_color;
	}
}

void phong::set_specular_k(double arg_ks)
{
	if (specular_brdf != nullptr)
	{
		specular_brdf->ks = arg_ks;
	}
}
