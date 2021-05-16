#pragma once
#include <iostream>

#include "TrekMath.h"
using namespace TrekMath;

class colors {
public:
	static  void write_color(std::ostream& out, TrekMath::color pixel_color, int samples_per_pixel) {
		auto r = pixel_color.x;
		auto g = pixel_color.y;
		auto b = pixel_color.z;

		// Divide the color total by the number of samples.
		auto scale = 1.0 / samples_per_pixel;//这里相当于直接做了box filtering,全部平均了，以后需要一定的改变
		r *= scale;
		g *= scale;
		b *= scale;
		//clamp_individual_component(r, g, b);
		max_to_one(r, g, b);




		//GAMMA CORRECTION
		//raise to power of 1.f / gamma
		const auto gamma = 2.2;
		auto gammaInverse = 1.0 / gamma;
		//gamma correction
		r = glm::pow(r, gammaInverse);
		g = glm::pow(g, gammaInverse);
		b = glm::pow(b, gammaInverse);




		out << static_cast<int>(255 * r) << ' '
			<< static_cast<int>(255 * g) << ' '
			<< static_cast<int>(255 * b) << '\n';


	}

	static void clamp_individual_component(glm::f64& r, glm::f64& g, glm::f64& b) {
		r = TrekMath::clamp(r, 0.0, 1.0);
		g = TrekMath::clamp(g, 0.0, 1.0);
		b = TrekMath::clamp(b, 0.0, 1.0);

	}
	static void max_to_one(glm::f64& r, glm::f64& g, glm::f64& b) {
		auto max_value = glm::max(r, glm::max(g, b));

		if (max_value > 1.0) {
			r = r / max_value;
			g = g / max_value;
			b = b / max_value;
		}
		else {

			return;
		}

	}




};


/*	r = glm::sqrt(scale * r);
		g = glm::sqrt(scale * g);
		b = glm::sqrt(scale * b);*/


		/*out << static_cast<int>(255 * TrekMath::clamp(r, 0.0, 1.0)) << ' '
		<< static_cast<int>(255 * TrekMath::clamp(g, 0.0, 1.0)) << ' '
		<< static_cast<int>(255 * TrekMath::clamp(b, 0.0, 1.0)) << '\n';*/

		// Write the translated [0,255] value of each color component.
	   /* out << static_cast<int>(256 * TrekMath::clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * TrekMath::clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * TrekMath::clamp(b, 0.0, 0.999)) << '\n';*/