#include "diffuse.h"

diffuse::diffuse(const color &a) :
    albedo(std::make_shared<solid_color>(a))
{
}

diffuse::diffuse(std::shared_ptr<texture> a) :
    albedo(a)
{
}

TrekMath::color diffuse::path_shade(shadeRec &sr, const hittable &objects, std::shared_ptr<hittable> lights)
{
	//Lambertian材质的scattering pdf符合半球上的cosine分布,那么我们就依据scattering pdf做重要性采样，得到随机方向
	const auto importance_pdf = std::make_shared<CosinePdfHemisphere>(sr.normal);
	//向光源采样的pdf
	const auto light_pdf = std::make_shared<HittablePdf>(*lights, sr.hitPoint);

	const MixturePdf mixed_pdf{light_pdf, importance_pdf};
	//根据Lambertian材质的scattering pdf来进行重要性采样，采样出符合scattering pdf的任意方向，得到scatter_direction和其对应的pdf值
	//auto scattered = ray(sr.hitPoint, p.Generate(), sr.cast_ray.time());
	//auto scattered = ray(sr.hitPoint, light_pdf.Generate(), sr.cast_ray.time());
	//因为是从视点发射 视线光线 出去，那么实际上scattered.direction()是 光源光线 入射到渲染点的方向的反方向。
	//这个pdf是蒙特卡洛采样的pdf，因为是lambertian，所以用重要性采样直接选成和lambertian的scattering pdf一样的pdf
	//const auto pdf = glm::dot(sr.normal, scattered.direction()) / glm::pi<double>();
	//const auto pdf_value = p.Value(scattered.direction());
	//const auto pdf_val = light_pdf.Value(scattered.direction());

	auto       scattered = ray(sr.hitPoint, mixed_pdf.Generate(), sr.cast_ray.time());
	const auto pdf_val   = mixed_pdf.Value(scattered.direction());

	// Catch degenerate scatter direction
	if (near_zero(scattered.direction()))
	{
		scattered.setDir(sr.normal);
	}

	// A * s(direction) * color(direction)
	const auto alb = albedo->value(sr.texcor, sr.hitPoint);

	return (alb * scattering_pdf(sr, scattered) * sr.wor->tracer_ptr->trace_ray(scattered, objects, lights, sr.depth + 1)) / pdf_val;
}

//TrekMath::color diffuse::path_shade(shadeRec &sr)
//{
//	////Lambertian材质的scattering pdf符合半球上的cosine分布
//	//const CosinePdfHemisphere p(sr.normal);
//
//	////根据Lambertian材质的scattering pdf来进行重要性采样，选出的任意方向，得到scatter_direction和其对应的pdf值
//	//auto scattered = ray(sr.hitPoint, p.Generate(), sr.cast_ray.time());
//	////因为是从视点发射 视线光线 出去，那么实际上scattered.direction()是 光源光线 入射到渲染点的方向的反方向。
//	////这个pdf是蒙特卡洛采样的pdf，因为是lambertian，所以用重要性采样直接选成和lambertian的scattering pdf一样的pdf
//	////const auto pdf = glm::dot(sr.normal, scattered.direction()) / glm::pi<double>();
//	//const auto pdf_value = p.Value(scattered.direction());
//
//	//// Catch degenerate scatter direction
//	//if (near_zero(scattered.direction()))
//	//{
//	//	scattered.setDir(sr.normal);
//	//}
//
//	//const auto alb = albedo->value(sr.texcor, sr.hitPoint);
//
//	//// A * s(direction) * color(direction)
//	//return (alb * scattering_pdf(sr, scattered) * sr.wor->tracer_ptr->trace_ray(scattered, sr.depth + 1)) / pdf_value;
//	return {0.f, 0.f, 0.f};
//}

double diffuse::scattering_pdf(const shadeRec &sr, const ray &scattered)
{
	const auto cosine = glm::dot(sr.normal, scattered.direction());
	return cosine < 0 ? 0 : cosine / glm::pi<double>();
}
