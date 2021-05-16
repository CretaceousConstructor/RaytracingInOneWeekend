#pragma once
#include "sampler.h"

class  jittered : public sampler
{
public:
	jittered() = delete;
	//一个set对应一个pixel
	jittered(int numSamples, int numSets)
		:sampler(numSamples, numSets)
	{
		
		generate_samples();

	};


private:
	virtual void generate_samples() override {

		

		for (int p = 0; p < num_sets; p++){
			for (int j = 0; j < sqrt_of_numSamples; j++){
				for (int k = 0; k < sqrt_of_numSamples; k++){
					//假设n为5
					// range of k :[0 + 0, 0 + 1] / n ∈ [0,1/5]
					// range of k :[1 + 0, 1 + 1] / n ∈ [1/5,2/5]


					//  y
					//  |
					//  |
					//  |------ x


					TrekMath::point2 sp((k + TrekMath::random_double()) / sqrt_of_numSamples, (j + TrekMath::random_double()) / sqrt_of_numSamples);

					unit_square_samples.push_back(sp);
				}
			}
		}


		map_square_samples_to_unit_disk();
		map_square_samples_to_hemisphere();

	}



};

