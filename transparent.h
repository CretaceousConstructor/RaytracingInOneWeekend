#pragma once
#include "phong.h"
#include "perfectSpecular.h"
#include "perfectTransmitter.h"
class transparent : public phong {


public:
	transparent();
	virtual TrekMath::color shade(shadeRec& sr);
	void set_transmitter_ior(double arg_ior);
	void set_transmitter_k(double arg_kt);


	void set_reflective_k(double arg_kr);
	void set_reflective_color(TrekMath::color arg_cr);


private:
	std::unique_ptr< perfectSpecular > reflective_brdf;
	std::unique_ptr< perfectTransmitter > specular_btdf;

};