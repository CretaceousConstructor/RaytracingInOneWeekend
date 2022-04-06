#include "glossySpecular.h"
#include "material.h"
#include "phong.h"
#include "tracer.h"
#include "world.h"
class glossyReflector : public phong
{
  public:
	glossyReflector();
	void set_sampler(const int num_samples, const int sample_sets, const double exp);

	void set_k_glossy_reflective(const double k);

	void set_exponent_glossy_reflective(const double exp);

	void set_color_glossy_reflective(TrekMath::color cr);

	TrekMath::color area_light_shade(shadeRec &sr) override;

	TrekMath::color path_shade(shadeRec &sr);

	TrekMath::color global_shade(shadeRec &sr) override;

  private:
	std::unique_ptr<glossySpecular> glossy_specular_brdf;
};