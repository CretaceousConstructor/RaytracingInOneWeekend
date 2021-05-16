#pragma once
#include "camera.h"
#include "Ray.h"
#include "pinHole.h"
class thinLens : public camera
{

public:
	thinLens() = delete;
	thinLens(
		double aperture,
		double focal_plane_dis,
		std::unique_ptr<sampler>&& arg_samp_view_plane,
		std::unique_ptr<sampler>&& arg_samp_lense,

		TrekMath::point3 lookfrom,
		TrekMath::point3 lookat,
		TrekMath::vec3   vup,
		double vfov, // VERTICAL field-of-view in degrees
		double aspect_ratio, // one is in the same with picture we produce
		std::unique_ptr< tracer>&& arg_ray_cast,

		std::optional<double> view_dist_optional = std::nullopt
	)
		:
		camera(lookfrom, lookat, vup, vfov, aspect_ratio,std::move(arg_ray_cast),view_dist_optional),
		lens_radius(aperture / 2.0),
		samp_on_view_plane(std::move(arg_samp_view_plane)),
		samp_on_lense(std::move(arg_samp_lense)),
		focal_plane_distance(focal_plane_dis)
	{

	}

	void render_scence(world& world, std::ofstream& result) override;

private:

	color ray_color(const ray& r, const hittable& argument_world, int argument_depth);

	ray get_ray(double s, double t) const override;
	TrekMath::vec3 ray_direction(const TrekMath::point2& pixel_point, const TrekMath::point2& lens_point) const;


private:



	std::unique_ptr<sampler> samp_on_lense;
	std::unique_ptr<sampler> samp_on_view_plane;
	double lens_radius;
	double focal_plane_distance;

	double zoom_factor;
	double exposure_time;

};