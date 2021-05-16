#pragma once


#include "sampler.h"



class hammersley : public sampler {



public:
	hammersley() = delete;
	//一个set对应一个pixel
	hammersley(int numSamples, int numSets)
		:sampler(numSamples, numSets)
	{
		
		generate_samples();
		
	};



private:
	virtual void generate_samples() override {


		//在主对角线上产生samples

		for (int p = 0; p < num_sets; p++) {
			for (int j = 0; j < num_samples; j++) {
				double nInverse = 1.0 / num_samples;
				TrekMath::point2 pv;


				pv.x = nInverse * j;
				pv.y = phi(j);

				unit_square_samples.push_back(pv);
			}
		}
		map_square_samples_to_unit_disk();
		map_square_samples_to_hemisphere();

	}

	double phi(int j) {
		double x = 0.0;
		double f = 0.5;


		//j = 1101. = 13
		//   .1011 

		while (j) {
			x += f * (((j & 1) == 0) ? 0.0 : 1.0);
			j >>= 1;
			f *= 0.5;
		}

		return x;
	}


};