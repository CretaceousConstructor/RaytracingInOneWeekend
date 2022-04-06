#include "jittered.h"

void jittered::generate_samples(const double exp)
{



	for (int p = 0; p < num_sets; p++) {
		for (int j = 0; j < sqrt_of_numSamples; j++) {
			for (int k = 0; k < sqrt_of_numSamples; k++) {
				//����nΪ5����sqrt_of_numSamplesΪ5
				// kΪ0ʱ :[0 + 0, 0 + 1] / n �� [0,1/5]
				// kΪ1ʱ :[1 + 0, 1 + 1] / n �� [1/5,2/5]


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
	map_square_samples_to_hemisphere(exp);

}