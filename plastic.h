#pragma once
#include "material.h"
#include "lambertian.h"
#include "glossySpecular.h"
#include "shadeRec.h"

class plastic : public material {

public:
	plastic();

	virtual color shade(shadeRec& sr) override;

protected:
	std::unique_ptr<BRDF> ambient_brdf;
	std::unique_ptr<BRDF> diffuse_brdf;
	std::unique_ptr<BRDF> specular_brdf;


};