#pragma once

#include "camera.h"
#include "nrooks.h"
class pinHole : public camera {
public:
	pinHole() = delete;
	pinHole(
		std::unique_ptr<sampler>&& arg_viewPlaneSampler,


		TrekMath::point3 lookfrom,
		TrekMath::point3 lookat,
		TrekMath::vec3   vup,
		double vfov, // VERTICAL field-of-view in degrees
		double aspect_ratio, // one is in the same with picture we produce
		std::unique_ptr< tracer>&& arg_ray_cast,
		std::optional<double> view_dist_optional = std::nullopt
	)
		: camera(lookfrom, lookat, vup, vfov, aspect_ratio, std::move(arg_ray_cast),view_dist_optional)
		, 
		samp_on_view_plane(std::move(arg_viewPlaneSampler))
	{

	}


	void render_scence(world& world, std::ofstream& result) override;


private:
	color ray_color(const ray& r, const hittable& argument_world, int argument_depth);



	virtual ray get_ray(double s, double t) const override;

private:
	std::unique_ptr<sampler> samp_on_view_plane;
	double zoom_factor;


};