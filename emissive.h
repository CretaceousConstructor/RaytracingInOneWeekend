#include "material.h"
#include "TrekMath.h"
#include "shadeRec.h"

class emissive : public material
{
public:
	emissive() = default;
	TrekMath::color get_emissive_Le(shadeRec& sr) override;
	TrekMath::color area_light_shade(shadeRec& sr) override;
	TrekMath::color shade(shadeRec& sr) override;

	void setRadianceScaling(double arg_ls);
	void setEmissiveColor(TrekMath::color c);

private:
	double ls; //radiance scaling factor
	TrekMath::color ce;//emissive color



};