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
	    double                _time0             = 0.,
	    double                _time1             = 0.);

  public:
	//void render_scence(MultipleObj &world, std::ofstream &result, const renderingState &rs) override;
	//void render_scence(MultipleObj &world, MultipleObj &lights, std::ofstream &result, const renderingState &rs) override;
	[[nodiscard]] void render_scence(MultipleObj &world, std::shared_ptr<hittable> &lights, std::ofstream &result, const renderingState &rs)override;

  protected:
	[[nodiscard]] virtual ray get_ray(double s, double t) const override final;

  private:
	std::unique_ptr<sampler> sampler_of_view_plane;
};