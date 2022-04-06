#pragma once

#include "camera.h"
#include "nrooks.h"
class pinHole : public camera
{
  public:
	pinHole() = delete;
	pinHole(
	    std::unique_ptr<sampler> &&arg_viewPlaneSampler,

	    TrekMath::point3      lookfrom,
	    TrekMath::point3      lookat,
	    TrekMath::vec3        vup,
	    double                vfov,                // VERTICAL field-of-view in degrees
	    double                aspect_ratio,        //
	    std::optional<double> view_dist_optional = std::nullopt,
	    double _time0 = 0.,
	    double _time1 = 0.);

	void render_scence(world &world, std::ofstream &result) override;

	~pinHole() = default;

  private:
	virtual ray get_ray(double s, double t) const override;

  private:
	std::unique_ptr<sampler> sampler_of_view_plane;
};