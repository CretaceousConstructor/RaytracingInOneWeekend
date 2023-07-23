#pragma once
#include "Ray.h"
#include "camera.h"
class thinLens : public camera
{
  public:
	thinLens() = delete;
	thinLens(
	    double                     aperture,
	    double                     focal_plane_dis,
	    std::unique_ptr<sampler> &&arg_samp_view_plane,
	    std::unique_ptr<sampler> &&arg_samp_lense,

	    TrekMath::point3 lookfrom,
	    TrekMath::point3 lookat,
	    TrekMath::vec3   vup,
	    double           vfov,                // VERTICAL field-of-view in degrees
	    double           aspect_ratio,        // one is in the same with picture we produce
	    double           _time0 = 0.,
	    double           _time1 = 0.);

	void render_scence(MultipleObj &world, std::ofstream &result,const renderingState& rs) override;

  private:
	ray            get_ray(double s, double t) const override;

  private:
	std::unique_ptr<sampler> samp_on_lense;
	std::unique_ptr<sampler> samp_on_view_plane;
	double                   lens_radius;

	
	
	
	double exposure_time{};


};