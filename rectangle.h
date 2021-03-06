#pragma once

#include "hittable.h"
#include "sampler.h"
#include <memory>
class rectangle : public hittable{
public:
	rectangle() = default;
	rectangle(TrekMath::vec3  arg_a, TrekMath::vec3 arg_b, TrekMath::point3 arg_p0, TrekMath::vec3 arg_normal)
		:
		hittable(),
		a(arg_a),b(arg_b),p0(arg_p0),normal(glm::normalize(arg_normal))
	{
		inv_area = 1.0 / glm::length(glm::cross(a, b));
	};

   bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const override;
   
   std::string objectType() const override;


private:
	TrekMath::vec3 a;
	TrekMath::vec3 b;
	TrekMath::point3 p0;
	TrekMath::vec3 normal;
	static constexpr double kEpsilon = 0.00001;
	double inv_area;
	std::shared_ptr<material> mat_ptr;
	std::unique_ptr<sampler> sampler_ptr;
	
public:

	TrekMath::point3 sample() override;
	double pdf(shadeRec& sr) override;
	TrekMath::normal get_normal(const TrekMath::point3& point_on_object) override;
	
	void set_sampler(std::unique_ptr<sampler>&& arg_sam);
};