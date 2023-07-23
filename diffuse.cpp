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
	//Lambertian���ʵ�scattering pdf���ϰ����ϵ�cosine�ֲ�,��ô���Ǿ�����scattering pdf����Ҫ�Բ������õ��������
	const auto importance_pdf = std::make_shared<CosinePdfHemisphere>(sr.normal);
	//���Դ������pdf
	const auto light_pdf = std::make_shared<HittablePdf>(*lights, sr.hitPoint);

	const MixturePdf mixed_pdf{light_pdf, importance_pdf};
	//����Lambertian���ʵ�scattering pdf��������Ҫ�Բ���������������scattering pdf�����ⷽ�򣬵õ�scatter_direction�����Ӧ��pdfֵ
	//auto scattered = ray(sr.hitPoint, p.Generate(), sr.cast_ray.time());
	//auto scattered = ray(sr.hitPoint, light_pdf.Generate(), sr.cast_ray.time());
	//��Ϊ�Ǵ��ӵ㷢�� ���߹��� ��ȥ����ôʵ����scattered.direction()�� ��Դ���� ���䵽��Ⱦ��ķ���ķ�����
	//���pdf�����ؿ��������pdf����Ϊ��lambertian����������Ҫ�Բ���ֱ��ѡ�ɺ�lambertian��scattering pdfһ����pdf
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
//	////Lambertian���ʵ�scattering pdf���ϰ����ϵ�cosine�ֲ�
//	//const CosinePdfHemisphere p(sr.normal);
//
//	////����Lambertian���ʵ�scattering pdf��������Ҫ�Բ�����ѡ�������ⷽ�򣬵õ�scatter_direction�����Ӧ��pdfֵ
//	//auto scattered = ray(sr.hitPoint, p.Generate(), sr.cast_ray.time());
//	////��Ϊ�Ǵ��ӵ㷢�� ���߹��� ��ȥ����ôʵ����scattered.direction()�� ��Դ���� ���䵽��Ⱦ��ķ���ķ�����
//	////���pdf�����ؿ��������pdf����Ϊ��lambertian����������Ҫ�Բ���ֱ��ѡ�ɺ�lambertian��scattering pdfһ����pdf
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
