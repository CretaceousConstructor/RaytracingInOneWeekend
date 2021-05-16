//#pragma once
//
//#include "hittable.h"
//#include "color.h"
//class material {
//public:
//	virtual bool scatter(const ray& r_in, const hit_record& rec, TrekMath::color& attenuation, ray& scattered) const = 0;
//};
//
////lambertian always scatters!
////class lambertian : public material {
////public:
////	lambertian(const TrekMath::color& a) : albedo(a) {}
////
////	virtual bool scatter(
////		const ray& r_in, const hit_record& rec, TrekMath::color& attenuation, ray& scattered
////	) const {
////
////		TrekMath::vec3 scatter_direction = rec.normal + TrekMath::random_unit_vector();
////
////		scattered = ray(rec.p, scatter_direction);
////		attenuation = albedo;
////		return true;
////	}
////
////public:
////	TrekMath::color albedo; //漫反射系数
////
////};
//
////metal: only front face scatters
//class metal : public material {
//public:
//	metal(const TrekMath::color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
//
//	virtual bool scatter(
//		const ray& r_in, const hit_record& rec, TrekMath::color& attenuation, ray& scattered
//	) const {
//		TrekMath::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
//		scattered = ray(rec.p, reflected + fuzz * TrekMath::random_in_unit_sphere());
//
//		attenuation = albedo;
//		return (glm::dot(scattered.direction(), rec.normal) > 0);
//
//	}
//
//public:
//	TrekMath::color albedo;
//	double fuzz;
//};
//
//
//
//class dielectric : public material {
//public:
//	dielectric(double ri) : ref_idx(ri) {}
//
//	virtual bool scatter(
//		const ray& r_in, const hit_record& rec, TrekMath::color& attenuation, ray& scattered
//	) const {
//		//Attenuation is always 1 — the glass surface absorbs nothing
//		attenuation =TrekMath::color(1.0, 1.0, 1.0);
//		//决定是从air进入glass 或者glass 进入 air
//
//		double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);
//
//
//		TrekMath::vec3 unit_direction = glm::normalize(r_in.direction());
//
//		double cos_theta = fmin(glm::dot(-unit_direction, rec.normal), 1.0);
//		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
//
//		//全反射
//		if (etai_over_etat * sin_theta > 1.0) {
//			// Must Reflect
//			vec3 reflected = reflect(unit_direction, rec.normal);
//			scattered = ray(rec.p, reflected);
//			return true;
//
//		}
//
//		//现实情况是除了全反射情况外，
//		//同时存在反射光线和折射光线，
//		//我们可以利用shlick概率公式来模拟这样的情况
//		//因为我们一次仅仅scatter一条光线必须做出反射还是折射的抉择
//		double reflect_prob = schlick(cos_theta, etai_over_etat);
//		if (random_double() < reflect_prob)
//		{
//			vec3 reflected = reflect(unit_direction, rec.normal);
//			scattered = ray(rec.p, reflected);
//			return true;
//		}
//		else {
//
//			vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
//			scattered = ray(rec.p, refracted);
//			return true;
//		}
//
//		return false; //不会发送的情况
//		
//	}
//public:
//	double ref_idx;
//private:
//
//	static double schlick(double cosine, double ref_idx) {
//		auto r0 = (1 - ref_idx) / (1 + ref_idx);
//		r0 = r0 * r0;
//		return r0 + (1 - r0) * pow((1 - cosine), 5);
//	}
//};
